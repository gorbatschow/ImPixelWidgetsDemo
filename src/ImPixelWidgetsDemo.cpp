#include "ImPixelWidgetsDemo.h"

ImPixelWidgetsDemo::ImPixelWidgetsDemo() { _radarWidget.makeExample(); }

void ImPixelWidgetsDemo::paint() {
  ImGui::Begin("Radar Widget");
  _radarWidget.paint();
  ImGui::End();
}
