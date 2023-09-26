#ifndef DIMENSIONS_H
#define DIMENSIONS_H

#include "Input.h"

class Dimensions : public Input {
private:
  int width;
  int height;
public:
  Dimensions();
  Dimensions(INPUT_CODE code, int width, int height);
  ~Dimensions();
  int GetWidth() const;
  int GetHeight() const;
  static Dimensions FromJson(const Json& json);
  static Json ToJson(const Dimensions& dimensions);
};

#endif