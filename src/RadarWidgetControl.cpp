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
    _polarGrid.setDistanceMin(ui.distanceLimitsEdit(0));
    _polarGrid.setDistanceMax(ui.distanceLimitsEdit(1));
    handle = true;
  }
  if (ui.distanceStepEdit.handle()) {
    _polarGrid.setDistanceStep(ui.distanceStepEdit());
    handle = true;
  }
  if (ui.bearingLimitsEdit.handle()) {
    _polarGrid.setBearingMin(ui.bearingLimitsEdit(0));
    _polarGrid.setBearingMax(ui.bearingLimitsEdit(1));
    handle = true;
  }
  if (ui.bearingStepEdit.handle()) {
    _polarGrid.setBearingStep(ui.bearingStepEdit());
    handle = true;
  }
  if (ui.rotationEdit.handle()) {
    _polarGrid.setRotation(ui.rotationEdit());
    handle = true;
  }
  if (ui.pixelSizeEdit.handle()) {
    _polarGrid.setPixelWidth(ui.pixelSizeEdit());
    _polarGrid.setPixelHeight(ui.pixelSizeEdit());
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
  _polarGrid.updateGrid();
  _radarWidget.setGrid(_polarGrid);

  // Color Scheme
  if (ui.monochromeFlag()) {
    _radarWidget.setColorScheme<ColorSchemeMono>(0, _polarGrid.nodeSize());
  } else {
    _radarWidget.setColorScheme<ColorSchemeTurbo>(0, _polarGrid.nodeSize());
  }

  // Test Data
  std::vector<double> val(_radarWidget.grid().nodeSize());
  std::iota(val.begin(), val.end(), 0);

  std::vector<double> r(_radarWidget.grid().nodeSize());
  std::vector<double> phi(_radarWidget.grid().nodeSize());
  std::size_t k{};
  for (const auto &r_k : _radarWidget.grid().distanceNodes()) {
    for (const auto &phi_k : _radarWidget.grid().bearingNodes()) {
      r[k] = r_k;
      phi[k] = phi_k;
      ++k;
    }
  }
  _radarWidget.setData(r, phi, val);
}
