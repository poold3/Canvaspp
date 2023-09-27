#ifndef TOGGLEMOUSEPOSITIONUPDATE_H
#define TOGGLEMOUSEPOSITIONUPDATE_H

#include "Output.h"

class ToggleMousePositionUpdate : public Output {
private:
  bool update;
public:
  ToggleMousePositionUpdate();
  ToggleMousePositionUpdate(bool update);
  ~ToggleMousePositionUpdate();
  int GetUpdate() const;
  static ToggleMousePositionUpdate FromJson(const Json& json);
  static Json ToJson(const ToggleMousePositionUpdate& toggleUpdate);
};

#endif