#pragma once
#include <PixelGridData.h>
#include <PixelGridDataImage.h>
#include <PixelMultiPolarGrid.h>
#include <imw.h>
#include <numeric>

class PolarGridConfigWidget {
public:
  // Constructor
  PolarGridConfigWidget();

  // Destructor
  ~PolarGridConfigWidget() = default;

  // Paint
  void paint();
  void setTestData();

  // Get Config
  bool configChanged() const { return _configChanged; }
  void getGridConfig(PolarGridConfig &config) const;

private:
  struct Ui {
    Imw::MultiSpinBox<int> distanceLimitsEdit{2, "Distance Min/Max"};
    Imw::SpinBox<int> distanceStepEdit{"Distance Step"};
    Imw::MultiSpinBox<int> bearingLimitsEdit{2, "Bearing Min/Max"};
    Imw::SpinBox<int> bearingStepEdit{"Bearing Step"};
    Imw::SpinBox<int> rotationEdit{"Rotation"};
    Imw::SpinBox<int> pixelSizeEdit{"Image Size"};
    Imw::CheckBox monochromeFlag{"Monochrome"};
    Imw::CheckBox displayScatterFlag{"Display Grid"};
    Imw::Button updateGridBtn{"Update"};

    Ui() {
      distanceLimitsEdit.setValue(100, 0);
      distanceLimitsEdit.setValue(1000, 1);
      distanceStepEdit.setValue(10);
      bearingLimitsEdit.setValue(0, 0);
      bearingLimitsEdit.setValue(180, 1);
      bearingStepEdit.setValue(10);
      rotationEdit.setValue(0);
      pixelSizeEdit.setValue(512);

      distanceLimitsEdit.setValueLimits({0, 100000}, 0);
      distanceStepEdit.setValueLimits({1, 100000});
      bearingLimitsEdit.setValueLimits({0, 360}, 0);
      bearingLimitsEdit.setValueLimits({0, 360}, 1);
      bearingStepEdit.setValueLimits({1, 360});
      rotationEdit.setValueLimits({-360, 360});
      pixelSizeEdit.setValueLimits({1, 1024});
    }
  };
  Ui ui;

  mutable bool _configChanged{};
};
