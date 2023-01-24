#include "ImPixelWidgetsDemo.h"
#include <numeric>

ImPixelWidgetsDemo::ImPixelWidgetsDemo() {}

void ImPixelWidgetsDemo::paint() {
  ImGui::Begin("Radar Widget Control");
  _radarWidgetControl.paint();
  ImGui::End();

  ImGui::Begin("Radar Widget");
  _radarWidget.paint();
  ImGui::End();
}
