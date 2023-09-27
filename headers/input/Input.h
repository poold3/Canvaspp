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


class Input {
private:
  INPUT_CODE::CODE code;
protected:
  static INPUT_CODE::CODE FindInputCode(int code);
public:
  Input();
  Input(INPUT_CODE::CODE code);
  ~Input();
  INPUT_CODE::CODE GetCode() const;
  static Input FromJson(const Json& json);
  static Json ToJson(const Input& input);
};
#endif