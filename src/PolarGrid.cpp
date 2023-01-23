#include "PolarGrid.h"

void PolarGrid::makeExample() {
    setDistanceMin(100.);
    setDistanceMax(1000.);
    setDistanceStep(1.);
    setRotation(-90);
    setBearingMin(0);
    setBearingMax(180);
    setBearingStep(0.5);
    setPixelWidth(2048);
    setPixelHeight(2048);
    updateGrid();
}

void PolarGrid::updateGrid() {
    updateDistanceNodes();
    updateBearingNodes();
    updateCartesianNodes();
    bindNodesToPixels();
}

void PolarGrid::updateDistanceNodes() {
    assert(_distanceMax > _distanceMin);

    auto r{_distanceMin};
    _distanceNodes.reserve(int(_distanceMax / _distanceStep));
    while (r <= _distanceMax) {
        _distanceNodes.push_back(r);
        r += _distanceStep;
    }
}

void PolarGrid::updateBearingNodes() {
    assert(_bearingMax > _bearingMin);

    auto phi{_bearingMin};
    _bearingNodes.reserve(int(_bearingMax / _bearingStep));
    while (phi <= _bearingMax - _bearingStep) {
        _bearingNodes.push_back(phi);
        phi += _bearingStep;
    }
}

void PolarGrid::updateCartesianNodes() {
    _xNodes.resize(_distanceNodes.size() * _bearingNodes.size());
    _yNodes.resize(_distanceNodes.size() * _bearingNodes.size());
    for (std::size_t i{}, k{}; i != _distanceNodes.size(); ++i) {
        for (std::size_t j{}; j != _bearingNodes.size(); ++j, ++k) {
            polarToCart(_distanceNodes[i], _bearingNodes[j], _xNodes[k],
                        _yNodes[k]);
        }
    }
}

void PolarGrid::bindNodesToPixels() {
    // Resize
    _pixelMap.clear();
    _pixelMap.resize(_distanceNodes.size());
    for (auto &value : _pixelMap) {
        value.resize(_bearingNodes.size());
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
