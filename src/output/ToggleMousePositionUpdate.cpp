#include "output/ToggleMousePositionUpdate.h"

ToggleMousePositionUpdate::ToggleMousePositionUpdate() : Output() {
  this->update = false;
}

ToggleMousePositionUpdate::ToggleMousePositionUpdate(bool update) : Output(OUTPUT_CODE::CODE::TOGGLE_MOUSE_POSITION_TRANSMISSION) {
  this->update = update;
}

ToggleMousePositionUpdate::~ToggleMousePositionUpdate() {
  this->update = false;
}

int ToggleMousePositionUpdate::GetUpdate() const {
  return this->update;
}

ToggleMousePositionUpdate ToggleMousePositionUpdate::FromJson(const Json& json) {
  if (!json.at("update").is_boolean()) {
    throw std::invalid_argument("The \"update\" field is not a boolean.");
  }

  bool update = json.at("update");

  return ToggleMousePositionUpdate(update);
}

Json ToggleMousePositionUpdate::ToJson(const ToggleMousePositionUpdate& toggleUpdate) {
  Json json;

  json["code"] = toggleUpdate.GetCode();
  json["update"] = toggleUpdate.GetUpdate();
  
  return json;
}
