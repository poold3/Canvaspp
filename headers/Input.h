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
    MOUSE_POSITION
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

class Input {
public:
  static INPUT_CODE::CODE FindInputCode(int code);
  static INPUT_CODE::CODE GetInputCode(const Json& json);
  static Dimensions GetDimensions(const Json& json);
  static MousePosition GetMousePosition(const Json& json);
};

#endif