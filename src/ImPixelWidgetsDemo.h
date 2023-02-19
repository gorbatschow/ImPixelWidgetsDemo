#pragma once
#include "PolarGridConfigWidget.h"
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
  PolarGridConfigWidget _gridConfigWidget{};
  std::shared_ptr<ImPixel::PolarGrid> _grid{new ImPixel::PolarGrid{}};
  ImPixel::GridData _data{_grid};
  ImPixel::GridDataImage _image{};
};
