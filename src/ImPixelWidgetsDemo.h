#pragma once
#include "RadarWidget.h"
#include "RadarWidgetControl.h"
#include <ImApplication.h>

class ImPixelWidgetsDemo : public ImApplication {
public:
  // Constructor
  ImPixelWidgetsDemo();

  // Destructor
  ~ImPixelWidgetsDemo() = default;

  // Test Data
  void setTestData();

  // Paint
  void paint() override;

private:
  RadarWidget _radarWidget;
  RadarWidgetControl _radarWidgetControl{_radarWidget};
};
