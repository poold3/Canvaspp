#include "Output.h"

OUTPUT_CODE::CODE Output::FindOutputCode(int code) {
  for (int i = static_cast<int>(OUTPUT_CODE::CODE::NONE); i <= static_cast<int>(OUTPUT_CODE::CODE::UPDATE_MOUSE_POSITION); ++i) {
    if (i == code) {
      return static_cast<OUTPUT_CODE::CODE>(i);
    }
  }
  return OUTPUT_CODE::CODE::NONE;
}

OUTPUT_CODE::CODE Output::GetOutputCode(const Json& json) {
  if (!json.at("code").is_number()) {
    throw std::invalid_argument("The \"code\" field is not a number.");
  }
  int code = json.at("code");
  return Output::FindOutputCode(code);
}

Json Output::GetUpdateMousePosition(const UpdateMousePosition& updateMousePosition) {
  Json json;
  json["code"] = OUTPUT_CODE::CODE::UPDATE_MOUSE_POSITION;
  json["update"] = updateMousePosition.update;
  return json;
}