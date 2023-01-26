#include "RadarWidgetControl.h"

RadarWidgetControl::RadarWidgetControl(RadarWidget &widget)
    : _radarWidget(widget) {
  setTestData();

  ui.distanceLimitsEdit.trigger();
  ui.distanceStepEdit.trigger();
  ui.bearingLimitsEdit.trigger();
  ui.bearingStepEdit.trigger();
  ui.rotationEdit.trigger();
  ui.pixelSizeEdit.trigger();
  ui.displayScatterFlag.trigger();
}

void RadarWidgetControl::paint() {
  // Paint
  ui.distanceLimitsEdit.paint();
  ui.distanceStepEdit.paint();
  ui.bearingLimitsEdit.paint();
  ui.bearingStepEdit.paint();
  ui.rotationEdit.paint();
  ui.pixelSizeEdit.paint();
  ui.monochromeFlag.paint();
  ui.displayScatterFlag.paint();
  ImGui::Separator();
  // ui.updateGridBtn.paint();

  // Handle
  bool handle{};
  if (ui.distanceLimitsEdit.handle()) {
    _polarConfig.setDistanceMin(ui.distanceLimitsEdit(0));
    _polarConfig.setDistanceMax(ui.distanceLimitsEdit(1));
    handle = true;
  }
  if (ui.distanceStepEdit.handle()) {
    _polarConfig.setDistanceStep(ui.distanceStepEdit());
    handle = true;
  }
  if (ui.bearingLimitsEdit.handle()) {
    _polarConfig.setBearingMin(ui.bearingLimitsEdit(0));
    _polarConfig.setBearingMax(ui.bearingLimitsEdit(1));
    handle = true;
  }
  if (ui.bearingStepEdit.handle()) {
    _polarConfig.setBearingStep(ui.bearingStepEdit());
    handle = true;
  }
  if (ui.rotationEdit.handle()) {
    _polarGrid->setRotation(ui.rotationEdit());
    handle = true;
  }
  if (ui.pixelSizeEdit.handle()) {
    _polarGrid->setPixelWidth(ui.pixelSizeEdit());
    _polarGrid->setPixelHeight(ui.pixelSizeEdit());
    handle = true;
  }
  if (ui.monochromeFlag.handle()) {
    handle = true;
  }
  if (ui.displayScatterFlag.handle()) {
    _radarWidget.setDisplayScatter(ui.displayScatterFlag());
  }

  if (handle) {
    setTestData();
  }
}

void RadarWidgetControl::setTestData() {
  // Grid
  _polarGrid->setConfig(_polarConfig);
  _radarWidget.setPixelGrid(_polarGrid);

  // Color Scheme
  if (ui.monochromeFlag()) {
    _radarWidget.setColorScheme<ColorSchemeMono>(0, _polarGrid->nodeSize());
  } else {
    _radarWidget.setColorScheme<ColorSchemeTurbo>(0, _polarGrid->nodeSize());
  }

  // Test Data
  std::vector<double> val(_radarWidget.grid().nodeSize());
  std::iota(val.begin(), val.end(), 0);
  _radarWidget.setCartesianData(_polarGrid->yNodes2D(), _polarGrid->xNodes2D(),
                                val.data(), _polarGrid->nodeSize());
}
