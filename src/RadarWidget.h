#pragma once
#include "ColorScheme.h"
#include "PixelData.h"
#include "PolarGrid.h"
#include <implot.h>

class RadarWidget {
public:
  // Constructor
  RadarWidget();

  // Destructor
  ~RadarWidget() = default;

  // Example
  void makeExample();

  // Paint
  void paint();

private:
  ImVec2 _boundsMin;
  ImVec2 _boundsMax;
  PixelData _pixels;
  PolarGrid _grid;
  ColorSchemeMono _colorScheme;
};
