#ifndef OUTPUT_H
#define OUTPUT_H

#include <string>
#include <iostream>
#include <stdexcept>
#include <nlohmann/json.hpp>
using Json = nlohmann::json;

namespace OUTPUT_CODE {
  enum CODE {
    NONE,
    UPDATE_MOUSE_POSITION,
    TRACK_MOUSE_CLICK,
    CTX_COMMAND
  };
}

struct UpdateMousePosition {
  bool update;
  UpdateMousePosition() {
    this->update = false;
  }
  UpdateMousePosition(bool update) {
    this->update = update;
  }
};

struct TrackMouseClick {
  bool track;
  TrackMouseClick() {
    this->track = false;
  }
  TrackMouseClick(bool track) {
    this->track = track;
  }
};

struct CtxCommand {
  std::string command;
  CtxCommand() {
    this->command = "";
  }
  CtxCommand(std::string command) {
    this->command = command;
  }
};

class Output {
public:
  static OUTPUT_CODE::CODE FindOutputCode(int code);
  static OUTPUT_CODE::CODE GetOutputCode(const Json& json);
  static Json GetUpdateMousePosition(const UpdateMousePosition& updateMousePosition);
  static Json GetTrackMouseClick(const TrackMouseClick& trackMouseClick);
  static Json GetCtxCommand(const CtxCommand& ctxCommand);
};
#endif