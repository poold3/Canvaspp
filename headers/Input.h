#ifndef INPUT_H
#define INPUT_H

#include <string>
#include <iostream>
#include <stdexcept>
#include <nlohmann/json.hpp>

using Json = nlohmann::json;

namespace INPUT_CODE {
  enum CODE {
    NONE,
    DIMENSIONS,
    MOUSE_POSITION,
    MOUSE_DOWN,
    MOUSE_UP,
    IMAGE_LOADED,
    SOUND_LOADED,
    KEY_DOWN,
    KEY_UP,
    MEASURED_TEXT,
    PROMPT_RESPONSE,
    CONFIRM_RESPONSE
  };
}

struct Dimensions {
  int width;
  int height;
  Dimensions() {
    this->width = 0;
    this->height = 0;
  }
  Dimensions(int width, int height) {
    this->width = width;
    this->height = height;
  }
};

struct MousePosition {
  int x;
  int y;
  MousePosition() {
    this->x = -1;
    this->y = -1;
  }
  MousePosition(int x, int y) {
    this->x = x;
    this->y = y;
  }
};

struct MouseClick {
  int x;
  int y;
  MouseClick() {
    this->x = -1;
    this->y = -1;
  }
  MouseClick(int x, int y) {
    this->x = x;
    this->y = y;
  }
};

struct MeasuredText {
  std::string text;
  int measurement;
  MeasuredText() {
    this->text = "";
    this->measurement = -1;
  }
  MeasuredText(std::string text, int measurement) {
    this->text = text;
    this->measurement = measurement;
  }
};

struct PromptResponse {
  std::string key;
  std::string response;
  PromptResponse() {
    this->key = "";
    this->response = "";
  }
  PromptResponse(std::string key, std::string response) {
    this->key = key;
    this->response = response;
  }
};

struct ConfirmResponse {
  std::string key;
  bool response;
  ConfirmResponse() {
    this->key = "";
    this->response = false;
  }
  ConfirmResponse(std::string key, bool response) {
    this->key = key;
    this->response = response;
  }
};

class Input {
public:
  /* Returns the INPUT_CODE that corresponds with the provided int. */
  static INPUT_CODE::CODE FindInputCode(int code);

  /* Extracts the INPUT_CODE from a Json object. The INPUT_CODE field in the Json must be called "code". */
  static INPUT_CODE::CODE GetInputCode(const Json& json);

  /* Returns a Dimensions object with the correct DIMENSIONS value. */
  static Dimensions GetDimensions(const Json& json);

  /* Returns a MousePosition object with the correct MOUSE_POSITION value. */
  static MousePosition GetMousePosition(const Json& json);

  /* Returns a MouseClick object with the correct MOUSE_DOWN or MOUSE_UP value. */
  static MouseClick GetMouseClick(const Json& json);

  /* Returns a std::string with the correct IMAGE_LOADED value. */
  static std::string GetImageLoaded(const Json& json);

  /* Returns a std::string with the correct SOUND_LOADED value. */
  static std::string GetSoundLoaded(const Json& json);

  /* Returns a std::string with the correct KEY_DOWN or KEY_UP value. */
  static std::string GetKeyPress(const Json& json);

  /* Returns a MeasuredText object with the correct MEASURED_TEXT value. */
  static MeasuredText GetMeasuredText(const Json& json);

  /* Returns a PromptResponse object with the correct PROMPT_RESPONSE value. */
  static PromptResponse GetPromptResponse(const Json& json);

  /* Returns a ConfirmResponse object with the correct CONFIRM_RESPONSE value. */
  static ConfirmResponse GetConfirmResponse(const Json& json);
};

#endif