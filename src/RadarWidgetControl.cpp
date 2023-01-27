#include "RadarWidgetControl.h"

RadarWidgetControl::RadarWidgetControl(RadarWidget &widget)
    : _radarWidget(widget) {
  setTestData();

  ui1.distanceLimitsEdit.setValue(100, 0);
  ui1.distanceLimitsEdit.setValue(500, 1);

  ui2.distanceLimitsEdit.setValue(500, 0);
  ui2.distanceLimitsEdit.setValue(1000, 1);

  ui.rotationEdit.trigger();
  ui.pixelSizeEdit.trigger();
  ui.displayScatterFlag.trigger();

  ui1.distanceLimitsEdit.trigger();
  ui1.distanceStepEdit.trigger();
  ui1.bearingLimitsEdit.trigger();
  ui1.bearingStepEdit.trigger();

  ui2.distanceLimitsEdit.trigger();
  ui2.distanceStepEdit.trigger();
  ui2.bearingLimitsEdit.trigger();
  ui2.bearingStepEdit.trigger();
}

void RadarWidgetControl::paint() {
  // Handle
  bool handle{};

  ImGui::TextUnformatted("First Grid");
  handle = handle || paintBlock(ui1, _polarConfig1);
  ImGui::Separator();
  ImGui::TextUnformatted("Second Grid");
  handle = handle || paintBlock(ui2, _polarConfig2);
  ImGui::Separator();

  ui.rotationEdit.paint();
  ui.pixelSizeEdit.paint();
  ui.monochromeFlag.paint();
  ui.displayScatterFlag.paint();

  if (ui.rotationEdit.handle()) {
    _polarConfig1.setRotation(ui.rotationEdit());
    _polarConfig2.setRotation(ui.rotationEdit());
    handle = true;
  }
  if (ui.pixelSizeEdit.handle()) {
    _polarConfig1.setPixelWidth(ui.pixelSizeEdit());
    _polarConfig2.setPixelHeight(ui.pixelSizeEdit());
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

bool RadarWidgetControl::paintBlock(UiBlock &ui, PolarGridConfig &config) {
  ImGui::PushID(&ui);
  ui.distanceLimitsEdit.paint();
  ui.distanceStepEdit.paint();
  ui.bearingLimitsEdit.paint();
  ui.bearingStepEdit.paint();
  ImGui::PopID();

  bool handle{false};

  if (ui.distanceLimitsEdit.handle()) {
    config.setDistanceMin(ui.distanceLimitsEdit(0));
    config.setDistanceMax(ui.distanceLimitsEdit(1));
    handle = true;
  }
  if (ui.distanceStepEdit.handle()) {
    config.setDistanceStep(ui.distanceStepEdit());
    handle = true;
  }
  if (ui.bearingLimitsEdit.handle()) {
    config.setBearingMin(ui.bearingLimitsEdit(0));
    config.setBearingMax(ui.bearingLimitsEdit(1));
    handle = true;
  }
  if (ui.bearingStepEdit.handle()) {
    config.setBearingStep(ui.bearingStepEdit());
    handle = true;
  }

  return handle;
}

void RadarWidgetControl::setTestData() {
  // Grid
  _multiGrid->setConfig({_polarConfig1, _polarConfig2});
  _radarWidget.setPixelGrid(_multiGrid);

  // Color Scheme
  if (ui.monochromeFlag()) {
    _radarWidget.setColorScheme<ColorSchemeMono>(0, _multiGrid->gridSize());
  } else {
    _radarWidget.setColorScheme<ColorSchemeTurbo>(0, _multiGrid->gridSize());
  }

  // Test Data
  std::vector<double> val(_multiGrid->gridSize());
  std::iota(val.begin(), val.end(), 0);

  //  std::vector<double> r{}, phi{};
  //  _polarGrid->makePolarMesh(r, phi);
  //  _radarWidget.setPolarData(r.data(), phi.data(), val.data(),
  //                            _polarGrid->gridSize());

  std::vector<double> x{}, y{};
  _multiGrid->makeCartesianMesh(x, y);
  _radarWidget.setCartesianData(x.data(), y.data(), val.data(),
                                _multiGrid->gridSize());
}
