#pragma once
#include "RadarWidget.h"
#include <ImApplication.h>

class ImPixelWidgetsDemo : public ImApplication {
public:
  // Constructor
  ImPixelWidgetsDemo();

  // Destructor
  ~ImPixelWidgetsDemo() = default;

  // Paint
  void paint() override;

  RadarWidget _radarWidget;

  struct Ui {};
  Ui ui;
};
