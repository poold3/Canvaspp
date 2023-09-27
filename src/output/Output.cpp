#include "output/Output.h"

OUTPUT_CODE::CODE Output::FindOutputCode(int code) {
  for (int i = static_cast<int>(OUTPUT_CODE::CODE::NONE); i <= static_cast<int>(OUTPUT_CODE::CODE::TOGGLE_MOUSE_POSITION_TRANSMISSION); ++i) {
    if (i == code) {
      return static_cast<OUTPUT_CODE::CODE>(i);
    }
  }
  return OUTPUT_CODE::CODE::NONE;
}

Output::Output() {
  this->code = OUTPUT_CODE::CODE::NONE;
}

Output::Output(OUTPUT_CODE::CODE code) {
  this->code = code;
}

Output::~Output() {
  this->code = OUTPUT_CODE::CODE::NONE;
}

OUTPUT_CODE::CODE Output::GetCode() const {
  return this->code;
}

Output Output::FromJson(const Json& json) {
  if (!json.at("code").is_number()) {
    throw std::invalid_argument("The \"code\" field is not a number.");
  }

  int code = json.at("code");

  return Output(Output::FindOutputCode(code));
}

Json Output::ToJson(const Output& output) {
  Json json;

  json["code"] = output.GetCode();
  
  return json;
}
