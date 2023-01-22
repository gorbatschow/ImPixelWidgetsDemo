#pragma once
#include "RadarWidget.h"
#include <ImApplication.h>

class ImPixelWidgetsDemo : public ImApplication {
public:
  ImPixelWidgetsDemo();

  void paint() override {
    ImGui::Begin("Radar Widget");
    _radarWidget.paint();
    ImGui::End();
  }

  RadarWidget _radarWidget;

  struct Ui {};
  Ui ui;
};
