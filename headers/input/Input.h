#ifndef INPUT_H
#define INPUT_H

#include <string>
#include <iostream>
#include <stdexcept>
#include <nlohmann/json.hpp>
using Json = nlohmann::json;

enum INPUT_CODE {
  NONE,
  DIMENSIONS,
  MOUSE_POSITION
};

class Input {
private:
  INPUT_CODE code;
protected:
  static INPUT_CODE FindInputCode(int code);
public:
  Input();
  Input(INPUT_CODE code);
  ~Input();
  INPUT_CODE GetCode() const;
  static Input FromJson(const Json& json);
  static Json ToJson(const Input& input);
};
#endif