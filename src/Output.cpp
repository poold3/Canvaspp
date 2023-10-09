#include "Output.h"

OUTPUT_CODE::CODE Output::FindOutputCode(int code) {
  for (int i = static_cast<int>(OUTPUT_CODE::CODE::NONE); i <= static_cast<int>(OUTPUT_CODE::CODE::TRACK_KEY_PRESS); ++i) {
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

Json Output::GetTrackMousePosition(const bool& trackMousePosition) {
  Json json;
  json["code"] = OUTPUT_CODE::CODE::TRACK_MOUSE_POSITION;
  json["track"] = trackMousePosition;
  return json;
}

Json Output::GetTrackMouseClick(const bool& trackMouseClick) {
  Json json;
  json["code"] = OUTPUT_CODE::CODE::TRACK_MOUSE_CLICK;
  json["track"] = trackMouseClick;
  return json;
}

Json Output::GetCtxCommand(const std::string& ctxCommand) {
  Json json;
  json["code"] = OUTPUT_CODE::CODE::CTX_COMMAND;
  json["command"] = ctxCommand;
  return json;
}

Json Output::GetLoadImage(const LoadImage& loadImage) {
  Json json;
  json["code"] = OUTPUT_CODE::CODE::LOAD_IMAGE;
  json["name"] = loadImage.name;
  json["src"] = loadImage.src;
  return json;
}

Json Output::GetSetBackgroundColor(const Color& color) {
  Json json;
  json["code"] = OUTPUT_CODE::CODE::SET_BACKGROUND_COLOR;
  json["color"] = color.ToString();
  return json;
}

Json Output::GetSetCursor(const Cursor& cursor) {
  Json json;
  json["code"] = OUTPUT_CODE::CODE::SET_CURSOR;
  json["cursor"] = cursor.ToString();
  return json;
}

Json Output::GetAddSound(const Sound& sound) {
  Json json;
  json["code"] = OUTPUT_CODE::CODE::ADD_SOUND;
  json["name"] = sound.name;
  json["src"] = sound.src;
  json["volume"] = sound.volume;
  json["playbackRate"] = sound.playbackRate;
  json["loop"] = sound.loop;
  return json;
}

Json Output::GetPlaySound(const std::string& name, int startTime) {
  Json json;
  json["code"] = OUTPUT_CODE::CODE::PLAY_SOUND;
  json["name"] = name;
  json["startTime"] = startTime;
  return json;
}

Json Output::GetPauseSound(const std::string& name) {
  Json json;
  json["code"] = OUTPUT_CODE::CODE::PAUSE_SOUND;
  json["name"] = name;
  return json;
}

Json Output::GetTrackKeyPress(const bool& keyPress) {
  Json json;
  json["code"] = OUTPUT_CODE::CODE::TRACK_KEY_PRESS;
  json["track"] = keyPress;
  return json;
}
