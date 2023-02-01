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
  struct UiGridCommon {
    Imw::CheckBox secondGridFlag{"Second grid"};
    Imw::CheckBox subGridFlag{"Sub grid"};
    Imw::SpinBox<int> rotationEdit{"Rotation"};
    Imw::SpinBox<int> distanceRangeEdit{"Distance Range"};
    Imw::SpinBox<int> pixelSizeEdit{"Image Size"};
    Imw::CheckBox monochromeFlag{"Monochrome"};
    Imw::CheckBox displayScatterFlag{"Display Grid"};

    UiGridCommon() {
      secondGridFlag.setValue(true);
      rotationEdit.setValue(0);
      distanceRangeEdit.setValue(1500);
      pixelSizeEdit.setValue(512);
      rotationEdit.setValueLimits({-360, 360});
      distanceRangeEdit.setValueLimits({0, 10000});
      pixelSizeEdit.setValueLimits({1, 1024});
    }
  };
  UiGridCommon ui_gridCommon;

  struct UiGridConfig {
    Imw::MultiSpinBox<int> distanceLimitsEdit{2, "Distance Min/Max"};
    Imw::SpinBox<int> distanceStepEdit{"Distance Step"};
    Imw::MultiSpinBox<int> bearingLimitsEdit{2, "Bearing Min/Max"};
    Imw::SpinBox<int> bearingStepEdit{"Bearing Step"};

    UiGridConfig() {
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
  UiGridConfig ui_gridConfig0, ui_gridConfig1, ui_gridConfig2;

  RadarWidget &_radarWidget;
  PolarGridConfig _polarConfig1, _polarConfig2, _polarConfig0;
  std::shared_ptr<PixelMultiPolarGrid> _multiGrid{new PixelMultiPolarGrid()};
  std::shared_ptr<PixelPolarGrid> _subGrid{new PixelPolarGrid()};

  bool paintGridConfig(UiGridConfig &ui, PolarGridConfig &config);
  bool paintGridCommon(UiGridCommon &ui);
  void triggerGridConfig(UiGridConfig &ui);
  void triggerGridCommon(UiGridCommon &ui);
  void setTestData();
};
