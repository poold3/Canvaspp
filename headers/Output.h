#ifndef OUTPUT_H
#define OUTPUT_H

#include <string>
#include <iostream>
#include <stdexcept>
#include <nlohmann/json.hpp>

#include "Color.h"

using Json = nlohmann::json;

namespace OUTPUT_CODE {
  enum CODE {
    NONE,
    TRACK_MOUSE_POSITION,
    TRACK_MOUSE_CLICK,
    CTX_COMMAND,
    LOAD_IMAGE,
    SET_BACKGROUND_COLOR,
    SET_CURSOR,
    ADD_SOUND,
    PLAY_SOUND,
    PAUSE_SOUND,
    TRACK_KEY_PRESS
  };
}

struct LoadImage {
  std::string name;
  std::string src;
  LoadImage() {
    this->name = "";
    this->src = "";
  }
  LoadImage(std::string name, std::string src) {
    this->name = name;
    this->src = src;
  }
};

struct Cursor {
  std::string keyword;
  std::string src;
  int x;
  int y;
  Cursor() {
    this->keyword = "auto";
    this->src = "";
    this->x = 0;
    this->y = 0;
  }
  Cursor(std::string keyword) {
    this->keyword = keyword;
    this->src = "";
    this->x = 0;
    this->y = 0;
  }
  Cursor(std::string src, int x, int y, std::string keyword = "auto") {
    this->keyword = keyword;
    this->src = src;
    this->x = x;
    this->y = y;
  }
  std::string ToString() const {
    if (this->src == "") {
      return this->keyword;
    } else {
      return "url(\"" + this->src + "\") " + std::to_string(this->x) + " " + std::to_string(this->y) + ", " + this->keyword;
    }
  }
};

struct Sound {
  std::string name;
  std::string src;
  int volume;
  int playbackRate;
  bool loop;
  Sound() {
    this->name = "";
    this->src = "";
    this->volume = 1;
    this->playbackRate = 1;
    this->loop = false;
  }
  Sound(std::string name, std::string src, int volume = 1, int playbackRate = 1) {
    this->name = name;
    this->src = src;
    this->volume = volume;
    this->playbackRate = playbackRate;
    this->loop = false;
  }
  Sound(std::string name, std::string src, bool loop, int volume = 1, int playbackRate = 1) {
    this->name = name;
    this->src = src;
    this->volume = volume;
    this->playbackRate = playbackRate;
    this->loop = loop;
  }
};

class Output {
public:
  /* Returns the OUTPUT_CODE that corresponds with the provided int. */
  static OUTPUT_CODE::CODE FindOutputCode(int code);

  /* Extracts the OUTPUT_CODE from a Json object. The OUTPUT_CODE field in the Json must be called "code". */
  static OUTPUT_CODE::CODE GetOutputCode(const Json& json);

  /* Returns a Json object with the correct OUTPUT_CODE and TRACK_MOUSE_POSITION value. */
  static Json GetTrackMousePosition(const bool& trackMousePosition);

  /* Returns a Json object with the correct OUTPUT_CODE and TRACK_MOUSE_CLICK value. */
  static Json GetTrackMouseClick(const bool& trackMouseClick);

  /* Returns a Json object with the correct OUTPUT_CODE and CTX_COMMAND value. */
  static Json GetCtxCommand(const std::string& ctxCommand);

  /* Returns a Json object with the correct OUTPUT_CODE and LOAD_IMAGE value. */
  static Json GetLoadImage(const LoadImage& loadImage);

  /* Returns a Json object with the correct OUTPUT_CODE and SET_BACKGROUND_COLOR value. */
  static Json GetSetBackgroundColor(const Color& color);

  /* Returns a Json object with the correct OUTPUT_CODE and SET_CURSOR value. */
  static Json GetSetCursor(const Cursor& cursor);

  /* Returns a Json object with the correct OUTPUT_CODE and ADD_SOUND value. */
  static Json GetAddSound(const Sound& sound);

  /* Returns a Json object with the correct OUTPUT_CODE and PLAY_SOUND value. */
  static Json GetPlaySound(const std::string& name, int startTime);

  /* Returns a Json object with the correct OUTPUT_CODE and PAUSE_SOUND value. */
  static Json GetPauseSound(const std::string& name);

  /* Returns a Json object with the correct OUTPUT_CODE and TRACK_KEY_PRESS value. */
  static Json GetTrackKeyPress(const bool& keyPress);
};
#endif