#include "input/MousePosition.h"

MousePositionInput::MousePositionInput() : Input() {
  this->x = -1;
  this->y = -1;
}

MousePositionInput::MousePositionInput(int x, int y) : Input(INPUT_CODE::CODE::MOUSE_POSITION) {
  this->x = x;
  this->y = y;
}

MousePositionInput::~MousePositionInput() {
  this->x = -1;
  this->y = -1;
}

int MousePositionInput::GetX() const {
  return this->x;
}
int MousePositionInput::GetY() const {
  return this->y;
}

MousePositionInput MousePositionInput::FromJson(const Json& json) {
  if (!json.at("x").is_number()) {
    throw std::invalid_argument("The \"x\" field is not a number.");
  } else if (!json.at("y").is_number()) {
    throw std::invalid_argument("The \"y\" field is not a number.");
  }

  int x = json.at("x");
  int y = json.at("y");

  return MousePositionInput(x, y);
}

Json MousePositionInput::ToJson(const MousePositionInput& mousePositionInput) {
  Json json;

  json["code"] = mousePositionInput.GetCode();
  json["x"] = mousePositionInput.GetX();
  json["y"] = mousePositionInput.GetY();
  
  return json;
}
