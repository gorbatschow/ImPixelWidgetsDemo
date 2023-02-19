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
  std::shared_ptr<PixelPolarGrid> _grid{new PixelPolarGrid{}};
  PixelGridData _data{_grid};
  PixelGridDataImage _image{};
};
