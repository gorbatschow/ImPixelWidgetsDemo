#pragma once
#include <cassert>
#include <cmath>
#include <vector>

class PolarGrid {
public:
  PolarGrid() = default;
  ~PolarGrid() = default;

  inline void makeDefaultGrid() {
    setDistanceMin(100.);
    setDistanceMax(1000.);
    setDistanceStep(10.);
    setBearingBias(-90);
    setBearingMin(0);
    setBearingMax(180);
    setBearingStep(10.);
    setPixelWidth(1024);
    setPixelHeight(1024);
    updateGrid();
  }

  inline void updateGrid() {
    updateDistanceNodes();
    updateBearingNodes();
    updateCartesianNodes();
    bindNodesToPixels();
  }

  // Distance
  // ---------------------------------------------------------------------------
  inline void setDistanceMin(double min) { _distanceMin = min; }
  double distanceMin() const { return _distanceMin; }

  inline void setDistanceMax(double max) { _distanceMax = max; }
  double distanceMax() const { return _distanceMax; }

  inline void setDistanceStep(double step) { _distanceStep = step; }
  double distanceStep() const { return _distanceStep; }

  inline const std::vector<double> &distanceNodes() const {
    return _distanceNodes;
  }

  inline void updateDistanceNodes() {
    assert(_distanceMax > _distanceMin);

    auto r{_distanceMin};
    _distanceNodes.reserve(int(_distanceMax / _distanceStep));
    while (r <= _distanceMax) {
      _distanceNodes.push_back(r);
      r += _distanceStep;
    }
  }

  // Bearing
  // ---------------------------------------------------------------------------
  inline void setBearingMin(double min) { _bearingMin = min; }
  inline double bearingMin() const { return _bearingMin; }

  inline void setBearingMax(double max) { _bearingMax = max; }
  inline double bearingMax() const { return _bearingMax; }

  inline void setBearingStep(double step) { _bearingStep = step; }
  inline double bearingStep() const { return _bearingStep; }

  inline void setBearingBias(double bias) { _bearingBias = bias; }
  inline double bearingBias() const { return _bearingBias; }

  inline void updateBearingNodes() {
    assert(_bearingMax > _bearingMin);

    auto phi{_bearingMin};
    _bearingNodes.reserve(int(_bearingMax / _bearingStep));
    while (phi <= _bearingMax) {
      _bearingNodes.push_back(phi);
      phi += _bearingStep;
    }
  }

  inline const std::vector<double> &bearingNodes() const {
    return _bearingNodes;
  }

  // Cartesian
  // ---------------------------------------------------------------------------
  inline void updateCartesianNodes() {
    _xNodes.resize(_distanceNodes.size() * _bearingNodes.size());
    _yNodes.resize(_distanceNodes.size() * _bearingNodes.size());
    for (std::size_t i{}, k{}; i != _distanceNodes.size(); ++i) {
      for (std::size_t j{}; j != _bearingNodes.size(); ++j, ++k) {
        polarToCart(_distanceNodes[i], _bearingNodes[j], _xNodes[k],
                    _yNodes[k]);
      }
    }
  }

  inline const std::vector<double> &xNodes() const { return _xNodes; }
  inline const std::vector<double> &yNodes() const { return _yNodes; }

  // Pixel
  // ---------------------------------------------------------------------------
  inline void setPixelWidth(std::size_t w) { _pixelWidth = w; }
  inline double pixelWidth() const { return _pixelWidth; }

  inline void setPixelHeight(std::size_t h) { _pixelHeight = h; }
  inline double pixelHeight() const { return _pixelHeight; }

  inline const std::vector<std::size_t> &nodeToPixel(std::size_t node_r,
                                                     std::size_t node_phi) {
    return _pixelMap.at(node_r).at(node_phi);
  }

  inline const std::vector<std::size_t> &polarToPixel(double r, double phi) {
    std::size_t node_r{}, node_phi{};
    polarToNode(r, phi, node_r, node_phi);
    return nodeToPixel(node_r, node_phi);
  }

  void bindNodesToPixels() {
    // Resize
    _pixelMap.clear();
    _pixelMap.resize(_distanceNodes.size() + 1);
    for (auto &value : _pixelMap) {
      value.resize(_bearingNodes.size() + 1);
    }

    // Fill
    std::size_t node_r{}, node_phi{};
    double r{}, phi{};
    double x{-_distanceMax};
    double y{+_distanceMax};
    const double dy{_distanceMax * 2. / double(_pixelHeight)};
    const double dx{_distanceMax * 2. / double(_pixelWidth)};

    for (std::size_t i{}, k{}; i != _pixelHeight; ++i) {
      for (std::size_t j{}; j != _pixelWidth; ++j, ++k) {
        cartToPolar(y, x, r, phi);
        polarToNode(r, phi, node_r, node_phi);
        x += dx;
        if (_pixelMap.size() <= node_r) {
          continue;
        }
        if (_pixelMap[node_r].size() <= node_phi) {
          continue;
        }
        _pixelMap[node_r][node_phi].push_back(k);
      }
      x = -_distanceMax;
      y -= dy;
    }
  }

  // Helpers
  // ---------------------------------------------------------------------------
  inline double sind(double v) { return sin(fmod(v, 360.) * M_PI / 180.); }

  inline double cosd(double v) { return cos(fmod(v, 360.) * M_PI / 180.); }

  inline double atan2d(double y, double x) { return atan2(y, x) * 180. / M_PI; }

  inline void polarToCart(double r, double phi, double &x, double &y) {
    x = r * cosd(90. - phi - _bearingBias);
    y = r * sind(90. - phi - _bearingBias);
  }

  inline void cartToPolar(double y, double x, double &r, double &phi) {
    r = sqrt(x * x + y * y);
    phi = fmod(90. - atan2d(y, x) + 360. - _bearingBias, 360.);
  }

  inline void polarToNode(double r, double phi, std::size_t &node_r,
                          std::size_t &node_phi) {
    node_r = std::floor(r / _distanceStep);
    node_phi = std::floor(phi / _bearingStep);
  }

private:
  // Distance
  double _distanceMin{};
  double _distanceMax{};
  double _distanceStep{};
  std::vector<double> _distanceNodes{};

  // Bearing
  double _bearingMin{};
  double _bearingMax{};
  double _bearingStep{};
  double _bearingBias{};
  std::vector<double> _bearingNodes{};

  // Cartesian
  std::vector<double> _xNodes;
  std::vector<double> _yNodes;

  // Pixes
  std::size_t _pixelWidth{};
  std::size_t _pixelHeight{};

  // Map nodes to pixels
  std::vector<std::vector<std::vector<std::size_t>>> _pixelMap;
};
