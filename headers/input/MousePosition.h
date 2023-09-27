#ifndef MOUSEPOSITION_H
#define MOUSEPOSITION_H

#include "Input.h"

class MousePositionInput : public Input {
private:
  int x;
  int y;
public:
  MousePositionInput();
  MousePositionInput(int x, int y);
  ~MousePositionInput();
  int GetX() const;
  int GetY() const;
  static MousePositionInput FromJson(const Json& json);
  static Json ToJson(const MousePositionInput& mousePositionInput);
};

#endif