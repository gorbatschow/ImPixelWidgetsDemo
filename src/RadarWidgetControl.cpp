#include "RadarWidgetControl.h"

RadarWidgetControl::RadarWidgetControl(RadarWidget &widget)
    : _radarWidget(widget) {
  setTestData();

  ui_gridConfig0.bearingLimitsEdit.setValue(0, 0);
  ui_gridConfig0.bearingLimitsEdit.setValue(360, 1);
  ui_gridConfig0.bearingStepEdit.setValue(1);
  ui_gridConfig0.distanceStepEdit.setValue(100);

  ui_gridConfig1.distanceLimitsEdit.setValue(100, 0);
  ui_gridConfig1.distanceLimitsEdit.setValue(500, 1);
  ui_gridConfig1.distanceStepEdit.setValue(100);

  ui_gridConfig2.distanceLimitsEdit.setValue(500, 0);
  ui_gridConfig2.distanceLimitsEdit.setValue(1000, 1);
  ui_gridConfig2.bearingLimitsEdit.setValue(30, 0);
  ui_gridConfig2.bearingLimitsEdit.setValue(150, 1);
  ui_gridConfig2.distanceStepEdit.setValue(100);
  ui_gridConfig2.bearingStepEdit.setValue(10);

  ui_gridCommon.displayScatterFlag.setValue(true);

  triggerGridConfig(ui_gridConfig0);
  triggerGridConfig(ui_gridConfig1);
  triggerGridConfig(ui_gridConfig2);
  triggerGridCommon(ui_gridCommon);
}

void RadarWidgetControl::paint() {
  // First Grid
  ImGui::TextUnformatted("First Grid");
  const bool handleGrid1{paintGridConfig(ui_gridConfig1, _polarConfig1)};
  ImGui::Separator();

  // Second Grid
  ImGui::TextUnformatted("Second Grid");
  const bool handleGrid2{paintGridConfig(ui_gridConfig2, _polarConfig2)};
  ImGui::Separator();

  // Sub grid
  ImGui::TextUnformatted("Sub Grid");
  const bool handleGrid0{paintGridConfig(ui_gridConfig0, _polarConfig0)};
  ImGui::Separator();

  // Common
  const bool handleCommon{paintGridCommon(ui_gridCommon)};

  if (handleGrid0 || handleGrid1 || handleGrid2 || handleCommon) {
    setTestData();
  }
}

void RadarWidgetControl::triggerGridConfig(UiGridConfig &ui) {
  ui.distanceLimitsEdit.trigger();
  ui.distanceStepEdit.trigger();
  ui.bearingLimitsEdit.trigger();
  ui.bearingStepEdit.trigger();
}

void RadarWidgetControl::triggerGridCommon(UiGridCommon &ui) {
  ui_gridCommon.subGridFlag.trigger();
  ui_gridCommon.secondGridFlag.trigger();
  ui_gridCommon.rotationEdit.trigger();
  ui_gridCommon.distanceRangeEdit.trigger();
  ui_gridCommon.pixelSizeEdit.trigger();
  ui_gridCommon.displayScatterFlag.trigger();
}

bool RadarWidgetControl::paintGridCommon(UiGridCommon &ui) {
  ui.secondGridFlag.paint();
  ImGui::SameLine();
  ui.subGridFlag.paint();
  ui.rotationEdit.paint();
  ui.distanceRangeEdit.paint();
  ui.pixelSizeEdit.paint();
  ui.monochromeFlag.paint();
  ui.displayScatterFlag.paint();

  bool handle{false};
  if (ui.secondGridFlag.handle()) {
    handle = true;
  }
  if (ui.subGridFlag.handle()) {
    handle = true;
  }
  if (ui.rotationEdit.handle()) {
    _polarConfig0.setRotation(ui.rotationEdit());
    _polarConfig1.setRotation(ui.rotationEdit());
    _polarConfig2.setRotation(ui.rotationEdit());
    handle = true;
  }
  if (ui.distanceRangeEdit.handle()) {
    _polarConfig0.setDistanceRange(ui.distanceRangeEdit());
    _polarConfig1.setDistanceRange(ui.distanceRangeEdit());
    _polarConfig2.setDistanceRange(ui.distanceRangeEdit());
    handle = true;
  }
  if (ui.pixelSizeEdit.handle()) {
    _polarConfig0.setPixelWidth(ui.pixelSizeEdit());
    _polarConfig0.setPixelHeight(ui.pixelSizeEdit());
    _polarConfig1.setPixelWidth(ui.pixelSizeEdit());
    _polarConfig1.setPixelHeight(ui.pixelSizeEdit());
    _polarConfig2.setPixelWidth(ui.pixelSizeEdit());
    _polarConfig2.setPixelHeight(ui.pixelSizeEdit());
    handle = true;
  }
  if (ui.monochromeFlag.handle()) {
    handle = true;
  }
  if (ui.displayScatterFlag.handle()) {
    _radarWidget.setDisplayScatter(ui.displayScatterFlag());
  }

  return handle;
}

bool RadarWidgetControl::paintGridConfig(UiGridConfig &ui,
                                         PolarGridConfig &config) {
  ui.distanceLimitsEdit.paint();
  ui.distanceStepEdit.paint();
  ui.bearingLimitsEdit.paint();
  ui.bearingStepEdit.paint();

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
  if (ui_gridCommon.secondGridFlag()) {
    _multiGrid->setConfig({_polarConfig1, _polarConfig2});
  } else {
    _multiGrid->setConfig({_polarConfig1});
  }
  _radarWidget.setPixelGrid(_multiGrid);

  // Sub Grid
  if (ui_gridCommon.subGridFlag()) {
    _subGrid->setConfig(_polarConfig0);
    _radarWidget.setPixelSubGrid(_subGrid);
  } else {
    _radarWidget.setPixelSubGrid(nullptr);
  }

  // Color Scheme
  if (ui_gridCommon.monochromeFlag()) {
    _radarWidget.setColorScheme<ColorSchemeMono>(0, _multiGrid->gridSize());
  } else {
    _radarWidget.setColorScheme<ColorSchemeTurbo>(0, _multiGrid->gridSize());
  }

  _radarWidget.fillImage(ColorRGBA::Aqua());
  // Test Data
  std::vector<double> val(_multiGrid->gridSize());
  std::iota(val.begin(), val.end(), 0);

  std::vector<double> r{}, phi{};
  _multiGrid->makePolarMesh(r, phi);
  _radarWidget.setPolarData(r.data(), phi.data(), val.data(),
                            _multiGrid->gridSize());

  /*
  std::vector<double> x{}, y{};
  _multiGrid->makeCartesianMesh(x, y);
  _radarWidget.setCartesianData(x.data(), y.data(), val.data(),
                                _multiGrid->gridSize()); */
}
