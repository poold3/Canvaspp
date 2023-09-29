#include "Input.h"

INPUT_CODE::CODE Input::FindInputCode(int code) {
  for (int i = static_cast<int>(INPUT_CODE::CODE::NONE); i <= static_cast<int>(INPUT_CODE::CODE::MOUSE_CLICK); ++i) {
    if (i == code) {
      return static_cast<INPUT_CODE::CODE>(i);
    }
  }
  return INPUT_CODE::CODE::NONE;
}

INPUT_CODE::CODE Input::GetInputCode(const Json& json) {
  if (!json.at("code").is_number()) {
    throw std::invalid_argument("The \"code\" field is not a number.");
  }

  int code = json.at("code");

  return Input::FindInputCode(code);
}

Dimensions Input::GetDimensions(const Json& json) {
  if (!json.at("width").is_number()) {
    throw std::invalid_argument("The \"width\" field is not a number.");
  } else if (!json.at("height").is_number()) {
    throw std::invalid_argument("The \"height\" field is not a number.");
  }

  int width = json.at("width");
  int height = json.at("height");

  return Dimensions(width, height);
}

MousePosition Input::GetMousePosition(const Json& json) {
  if (!json.at("x").is_number()) {
    throw std::invalid_argument("The \"x\" field is not a number.");
  } else if (!json.at("y").is_number()) {
    throw std::invalid_argument("The \"y\" field is not a number.");
  }

  int x = json.at("x");
  int y = json.at("y");

  return MousePosition(x, y);
}

MouseClick Input::GetMouseClick(const Json& json) {
  if (!json.at("x").is_number()) {
    throw std::invalid_argument("The \"x\" field is not a number.");
  } else if (!json.at("y").is_number()) {
    throw std::invalid_argument("The \"y\" field is not a number.");
  }

  int x = json.at("x");
  int y = json.at("y");

  return MouseClick(x, y);
}
