#include "Input.h"

INPUT_CODE::CODE Input::FindInputCode(int code) {
  for (int i = static_cast<int>(INPUT_CODE::CODE::NONE); i <= static_cast<int>(INPUT_CODE::CODE::CONFIRM_RESPONSE); ++i) {
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

std::string Input::GetImageLoaded(const Json& json) {
  if (!json.at("name").is_string()) {
    throw std::invalid_argument("The \"name\" field is not a string.");
  }

  return json.at("name");
}

std::string Input::GetSoundLoaded(const Json& json) {
  if (!json.at("name").is_string()) {
    throw std::invalid_argument("The \"name\" field is not a string.");
  }

  return json.at("name");
}

std::string Input::GetKeyPress(const Json& json) {
  if (!json.at("pressCode").is_string()) {
    throw std::invalid_argument("The \"pressCode\" field is not a string.");
  }

  return json.at("pressCode");
}

MeasuredText Input::GetMeasuredText(const Json& json) {
  if (!json.at("text").is_string()) {
    throw std::invalid_argument("The \"text\" field is not a string.");
  } else if (!json.at("measurement").is_number()) {
    throw std::invalid_argument("The \"measurement\" field is not a number.");
  }

  std::string text = json.at("text");
  int measurement = json.at("measurement");

  return MeasuredText(text, measurement);
}

PromptResponse Input::GetPromptResponse(const Json& json) {
  if (!json.at("key").is_string()) {
    throw std::invalid_argument("The \"key\" field is not a string.");
  } else if (!json.at("response").is_string()) {
    throw std::invalid_argument("The \"response\" field is not a string.");
  }

  std::string key = json.at("key");
  std::string response = json.at("response");

  return PromptResponse(key, response);
}

ConfirmResponse Input::GetConfirmResponse(const Json& json) {
  if (!json.at("key").is_string()) {
    throw std::invalid_argument("The \"key\" field is not a string.");
  } else if (!json.at("response").is_boolean()) {
    throw std::invalid_argument("The \"response\" field is not a bool.");
  }

  std::string key = json.at("key");
  bool response = json.at("response");

  return ConfirmResponse(key, response);
}
