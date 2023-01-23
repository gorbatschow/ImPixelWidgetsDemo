#include "RadarWidget.h"

RadarWidget::RadarWidget() {}

void RadarWidget::makeExample() {
  _grid.makeExample();
  _pixels.resize(_grid.pixelWidth(), _grid.pixelHeight());
  _pixels.fill(ColorRGBA_Transparent);
  _colorScheme.setValueMax(_grid.nodeSize());
  for (std::size_t i{}; i != _grid.nodeSize(); ++i) {
    _pixels.fill(_grid.nodeToPixel(i), _colorScheme.valueToColor(i));
  }
  _pixels.loadTexture();

  const auto r{_grid.distanceMax()};
  _boundsMin = {float(-r), float(-r)};
  _boundsMax = {float(+r), float(+r)};
}

void RadarWidget::paint() {
  const auto flags_plt{ImPlotFlags_NoTitle | ImPlotFlags_NoLegend |
                       ImPlotFlags_NoMenus | ImPlotFlags_NoBoxSelect |
                       ImPlotFlags_Equal};

  if (ImPlot::BeginPlot("Plot", {-1, -1}, flags_plt)) {
    ImPlot::PlotImage("Pixels", _pixels.imID(), _boundsMin, _boundsMax);
    /*
    ImPlot::PlotScatter("Nodes", _grid.xNodes().data(), _grid.yNodes().data(),
                        _grid.xNodes().size()); */

    ImPlot::EndPlot();
  }
}
