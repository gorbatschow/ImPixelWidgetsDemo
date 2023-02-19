#include "ImPixelWidgetsDemo.h"
#include <implot.h>
#include <numeric>

ImPixelWidgetsDemo::ImPixelWidgetsDemo() {
  auto config{PolarGridConfig()};
  config.setBearingMin(0);
  config.setBearingMax(181);
  config.setDistanceMin(0);
  config.setDistanceMax(1000);
  config.setPixelWidth(1024);
  config.setPixelHeight(1024);
}

void ImPixelWidgetsDemo::paint() {
  ImGui::Begin("Radar Widget Control");
  if (_gridConfigWidget.configChanged()) {
    auto config{PolarGridConfig()};
    _gridConfigWidget.getGridConfig(config);
    _grid->setConfig(config);
    _data.setLinearValues();
    _image.setColorScheme<ColorSchemeTurbo>(0, _data.size());
    _image.clear();
    _image.fillData(_data);
    _image.render();
  }
  _gridConfigWidget.paint();
  ImGui::End();

  ImGui::Begin("Radar Widget");
  const auto flags_plt{ImPlotFlags_NoTitle | ImPlotFlags_NoLegend |
                       ImPlotFlags_NoMenus | ImPlotFlags_NoBoxSelect |
                       ImPlotFlags_Equal};
  if (ImPlot::BeginPlot("Plot", {-1, -1}, flags_plt)) {
    ImPlot::PlotImage("Pixels", _image.imID(), _grid->cartesianBoundsMin(),
                      _grid->cartesianBoundsMax());
    ImPlot::EndPlot();
  }
  ImGui::End();
}
