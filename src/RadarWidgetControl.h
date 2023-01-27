#pragma once
#include "PixelMultiPolarGrid.h"
#include "RadarWidget.h"
#include <imw.h>
#include <numeric>

class RadarWidgetControl {
public:
  // Constructor
  RadarWidgetControl(RadarWidget &widget);

  // Destructor
  ~RadarWidgetControl() = default;

  // Paint
  void paint();

private:
  struct Ui {
    Imw::SpinBox<int> rotationEdit{"Rotation"};
    Imw::SpinBox<int> pixelSizeEdit{"Image Size"};
    Imw::CheckBox monochromeFlag{"Monochrome"};
    Imw::CheckBox displayScatterFlag{"Display Grid"};

    Ui() {
      rotationEdit.setValue(0);
      pixelSizeEdit.setValue(512);
      rotationEdit.setValueLimits({-360, 360});
      pixelSizeEdit.setValueLimits({1, 1024});
    }
  };
  Ui ui;

  struct UiBlock {
    Imw::MultiSpinBox<int> distanceLimitsEdit{2, "Distance Min/Max"};
    Imw::SpinBox<int> distanceStepEdit{"Distance Step"};
    Imw::MultiSpinBox<int> bearingLimitsEdit{2, "Bearing Min/Max"};
    Imw::SpinBox<int> bearingStepEdit{"Bearing Step"};

    UiBlock() {
      distanceLimitsEdit.setValue(100, 0);
      distanceLimitsEdit.setValue(1000, 1);
      distanceStepEdit.setValue(10);
      bearingLimitsEdit.setValue(0, 0);
      bearingLimitsEdit.setValue(180, 1);
      bearingStepEdit.setValue(10);

      distanceLimitsEdit.setValueLimits({0, 100000}, 0);
      distanceStepEdit.setValueLimits({1, 100000});
      bearingLimitsEdit.setValueLimits({0, 360}, 0);
      bearingLimitsEdit.setValueLimits({0, 360}, 1);
      bearingStepEdit.setValueLimits({1, 360});
    }
  };
  UiBlock ui1, ui2;

  RadarWidget &_radarWidget;
  PolarGridConfig _polarConfig1, _polarConfig2;
  std::shared_ptr<PixelMultiPolarGrid> _multiGrid{new PixelMultiPolarGrid()};

  bool paintBlock(UiBlock &ui, PolarGridConfig &config);
  void setTestData();
};
