#include "Output.h"

OUTPUT_CODE::CODE Output::FindOutputCode(int code) {
  for (int i = static_cast<int>(OUTPUT_CODE::CODE::NONE); i <= static_cast<int>(OUTPUT_CODE::CODE::LOAD_IMAGE); ++i) {
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

Json Output::GetTrackMouseClick(const TrackMouseClick& trackMouseClick) {
  Json json;
  json["code"] = OUTPUT_CODE::CODE::TRACK_MOUSE_CLICK;
  json["track"] = trackMouseClick.track;
  return json;
}

Json Output::GetCtxCommand(const CtxCommand& ctxCommand) {
  Json json;
  json["code"] = OUTPUT_CODE::CODE::CTX_COMMAND;
  json["command"] = ctxCommand.command;
  return json;
}

Json Output::GetLoadImage(const LoadImage& loadImage) {
  Json json;
  json["code"] = OUTPUT_CODE::CODE::LOAD_IMAGE;
  json["name"] = loadImage.name;
  json["src"] = loadImage.src;
  return json;
}
