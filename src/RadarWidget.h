#pragma once
#include "PixelData.h"
#include "PolarGrid.h"
#include <implot.h>

class RadarWidget {
public:
  RadarWidget() {
    _grid.makeDefaultGrid();
    _pixels.resize(_grid.pixelWidth(), _grid.pixelHeight());
    _pixels.fill(ColorRGBA_Aqua);
    _pixels.fill(_grid.nodeToPixels(10, 10));
    _pixels.loadTexture();

    const auto r{_grid.distanceMax()};
    _boundsMin = {float(-r), float(-r)};
    _boundsMax = {float(+r), float(+r)};
  }

  void paint() {
    const auto flags_plt{ImPlotFlags_NoTitle | ImPlotFlags_NoLegend |
                         ImPlotFlags_NoMenus | ImPlotFlags_NoBoxSelect |
                         ImPlotFlags_Equal};

    if (ImPlot::BeginPlot("Plot", {-1, -1}, flags_plt)) {
      ImPlot::PlotImage("Pixels", _pixels.imID(), _boundsMin, _boundsMax);
      ImPlot::PlotScatter("Nodes", _grid.xNodes().data(), _grid.yNodes().data(),
                          _grid.xNodes().size());

      ImPlot::EndPlot();
    }
  }

private:
  ImVec2 _boundsMin;
  ImVec2 _boundsMax;
  PixelData _pixels;
  PolarGrid _grid;
};
