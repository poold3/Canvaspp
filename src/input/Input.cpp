#include "input/Input.h"

INPUT_CODE Input::FindInputCode(int code) {
  for (int i = static_cast<int>(INPUT_CODE::NONE); i <= static_cast<int>(INPUT_CODE::MOUSE_POSITION); ++i) {
    if (i == code) {
      return static_cast<INPUT_CODE>(i);
    }
  }
  return INPUT_CODE::NONE;
}

Input::Input() {
  this->code = INPUT_CODE::NONE;
}

Input::Input(INPUT_CODE code) {
  this->code = code;
}

Input::~Input() {
  this->code = INPUT_CODE::NONE;
}

INPUT_CODE Input::GetCode() const {
  return this->code;
}

Input Input::FromJson(const Json& json) {
  if (!json.at("code").is_number()) {
    throw std::invalid_argument("The \"code\" field is not a number.");
  }

  int code = json.at("code");

  return Input(Input::FindInputCode(code));
}

Json Input::ToJson(const Input& input) {
  Json json;

  json["code"] = input.GetCode();
  
  return json;
}
