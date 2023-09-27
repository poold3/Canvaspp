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
    TOGGLE_MOUSE_POSITION_TRANSMISSION
  };
}

class Output {
private:
  OUTPUT_CODE::CODE code;
protected:
  static OUTPUT_CODE::CODE FindOutputCode(int code);
public:
  Output();
  Output(OUTPUT_CODE::CODE code);
  ~Output();
  OUTPUT_CODE::CODE GetCode() const;
  static Output FromJson(const Json& json);
  static Json ToJson(const Output& output);
};
#endif