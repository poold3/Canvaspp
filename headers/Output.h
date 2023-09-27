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
    UPDATE_MOUSE_POSITION
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

class Output {
public:
  static OUTPUT_CODE::CODE FindOutputCode(int code);
  static OUTPUT_CODE::CODE GetOutputCode(const Json& json);
  static Json GetUpdateMousePosition(const UpdateMousePosition& updateMousePosition);
};
#endif