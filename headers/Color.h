#ifndef COLOR_H
#define COLOR_H

#include <string>

struct Color {
  int r,g,b;
  double a;
  Color () {
    this->r = 0;
    this->g = 0;
    this->b = 0;
    this->a = 1.0;
  }
  Color (int r, int g, int b, double a = 1.0) {
    this->r = r;
    this->g = g;
    this->b = b;
    this->a = a;
  }
  std::string ToString() const {
    std::string str = "rgba(";
    return "rgba(" + std::to_string(r) + "," + std::to_string(g) + "," + std::to_string(b) + "," + std::to_string(a) + ")";
  }
};

#endif