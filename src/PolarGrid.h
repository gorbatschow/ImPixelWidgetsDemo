#pragma once
#include <cassert>
#include <cmath>
#include <vector>

class PolarGrid {
public:
  PolarGrid() = default;
  ~PolarGrid() = default;

  void makeExample();
  void updateGrid();

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

  void updateDistanceNodes();

  // Bearing
  // ---------------------------------------------------------------------------
  inline void setBearingMin(double min) { _bearingMin = min; }
  inline double bearingMin() const { return _bearingMin; }

  inline void setBearingMax(double max) { _bearingMax = max; }
  inline double bearingMax() const { return _bearingMax; }

  inline void setBearingStep(double step) { _bearingStep = step; }
  inline double bearingStep() const { return _bearingStep; }

  void updateBearingNodes();

  inline const std::vector<double> &bearingNodes() const {
    return _bearingNodes;
  }

  inline std::size_t nodeSize() const {
    return _distanceNodes.size() * _bearingNodes.size();
  }

  // Rotation
  // ---------------------------------------------------------------------------
  inline void setRotation(double rot) { _rotation = rot; }
  inline double rotation() const { return _rotation; }

  // Cartesian
  // ---------------------------------------------------------------------------
  void updateCartesianNodes();

  inline const std::vector<double> &xNodes() const { return _xNodes; }
  inline const std::vector<double> &yNodes() const { return _yNodes; }

  // Pixel
  // ---------------------------------------------------------------------------
  inline void setPixelWidth(std::size_t w) { _pixelWidth = w; }
  inline double pixelWidth() const { return _pixelWidth; }

  inline void setPixelHeight(std::size_t h) { _pixelHeight = h; }
  inline double pixelHeight() const { return _pixelHeight; }

  inline std::size_t pixelSize() const { return _pixelWidth * _pixelHeight; }

  inline const std::vector<std::size_t> &nodeToPixel(std::size_t node_r,
                                                     std::size_t node_phi) {
    return _pixelMap.at(node_r).at(node_phi);
  }

  inline const std::vector<std::size_t> &nodeToPixel(std::size_t node_index) {
    const std::size_t node_r{node_index / _bearingNodes.size()};
    const std::size_t node_phi{node_index % _bearingNodes.size()};
    return _pixelMap.at(node_r).at(node_phi);
  }

  inline const std::vector<std::size_t> &polarToPixel(double r, double phi) {
    std::size_t node_r{}, node_phi{};
    polarToNode(r, phi, node_r, node_phi);
    return nodeToPixel(node_r, node_phi);
  }

  void bindNodesToPixels();

  // Helpers
  // ---------------------------------------------------------------------------
  inline double sind(double v) const {
    return sin(fmod(v, 360.) * M_PI / 180.);
  }

  inline double cosd(double v) const {
    return cos(fmod(v, 360.) * M_PI / 180.);
  }

  inline double atan2d(double y, double x) const {
    return atan2(y, x) * 180. / M_PI;
  }

  inline void polarToCart(double r, double phi, double &x, double &y) const {
    x = r * cosd(90. - phi - _rotation);
    y = r * sind(90. - phi - _rotation);
  }

  inline void cartToPolar(double y, double x, double &r, double &phi) const {
    r = sqrt(x * x + y * y);
    phi = fmod(90. - atan2d(y, x) + 360. - _rotation, 360.);
  }

  inline void polarToNode(double r, double phi, std::size_t &node_r,
                          std::size_t &node_phi) const {
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
  std::vector<double> _bearingNodes{};

  // Rotation
  double _rotation{};

  // Cartesian
  std::vector<double> _xNodes;
  std::vector<double> _yNodes;

  // Pixes
  std::size_t _pixelWidth{};
  std::size_t _pixelHeight{};

  // Map nodes to pixels
  std::vector<std::vector<std::vector<std::size_t>>> _pixelMap;
};
