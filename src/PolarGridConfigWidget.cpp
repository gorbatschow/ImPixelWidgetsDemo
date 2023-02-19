#include "PolarGridConfigWidget.h"

PolarGridConfigWidget::PolarGridConfigWidget() {
  setTestData();

  ui.distanceLimitsEdit.trigger();
  ui.distanceStepEdit.trigger();
  ui.bearingLimitsEdit.trigger();
  ui.bearingStepEdit.trigger();
  ui.rotationEdit.trigger();
  ui.pixelSizeEdit.trigger();
  ui.displayScatterFlag.trigger();
}

void PolarGridConfigWidget::paint() {
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
  if (ui.distanceLimitsEdit.handle()) {
    _configChanged = true;
  }
  if (ui.distanceStepEdit.handle()) {
    _configChanged = true;
  }
  if (ui.bearingLimitsEdit.handle()) {
    _configChanged = true;
  }
  if (ui.bearingStepEdit.handle()) {
    _configChanged = true;
  }
  if (ui.rotationEdit.handle()) {
    _configChanged = true;
  }
  if (ui.pixelSizeEdit.handle()) {
    _configChanged = true;
  }
  if (ui.monochromeFlag.handle()) {
  }
  if (ui.displayScatterFlag.handle()) {
  }
}

void PolarGridConfigWidget::setTestData() {}

void PolarGridConfigWidget::getGridConfig(PolarGridConfig &config) const {
  config.setDistanceMin(ui.distanceLimitsEdit(0));
  config.setDistanceMax(ui.distanceLimitsEdit(1));
  config.setDistanceStep(ui.distanceStepEdit());
  config.setBearingMin(ui.bearingLimitsEdit(0));
  config.setBearingMax(ui.bearingLimitsEdit(1));
  config.setBearingStep(ui.bearingStepEdit());
  config.setRotation(ui.rotationEdit());
  config.setPixelWidth(ui.pixelSizeEdit());
  config.setPixelHeight(ui.pixelSizeEdit());
  _configChanged = false;
}
