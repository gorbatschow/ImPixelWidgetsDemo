#pragma once
#include "ColorRGBA.h"
#include <algorithm>

class ColorScheme {
public:
  ColorScheme() = default;
  virtual ~ColorScheme() = default;

  inline void setValueMin(double min) { _valueMin = min; }
  inline double valueMin() const { return _valueMin; }

  inline void setValueMax(double max) { _valueMax = max; }
  inline double valueMax() const { return _valueMax; }

  inline ColorRGBA valueToColor(double value, double alpha = 1.0) {
    value = std::clamp(value, _valueMin, _valueMax);
    value = value / _valueMax;
    return {uint8_t(red(value) * ColorRGBA_Max),
            uint8_t(green(value) * ColorRGBA_Max),
            uint8_t(blue(value) * ColorRGBA_Max),
            uint8_t(alpha * ColorRGBA_Max)};
  }

  virtual double red(const double &value) const = 0;
  virtual double green(const double &value) const = 0;
  virtual double blue(const double &value) const = 0;

private:
  double _valueMin{0};
  double _valueMax{1};
};

// Monochromatic
// -----------------------------------------------------------------------------
class ColorSchemeMono : public ColorScheme {
public:
  virtual double red(const double &value) const { return value; }
  virtual double green(const double &value) const { return value; }
  virtual double blue(const double &value) const { return value; }
};
