#ifndef CTXCOMMANDBUILDER_H
#define CTXCOMMANDBUILDER_H

#include <string>
#include <iostream>
#include <stdexcept>

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
  std::string ToString() {
    std::string str = "rgba(";
    return "rgba(" + std::to_string(r) + "," + std::to_string(g) + "," + std::to_string(b) + "," + std::to_string(a) + ")";
  }
};

class CtxCommandBuilder {
private:
  std::string buffer;
public:
  CtxCommandBuilder();
  ~CtxCommandBuilder();
  void Clear();
  std::string ToString() const;

  // ctx instance properties
  CtxCommandBuilder& direction(std::string dir);
  CtxCommandBuilder& fillStyle(Color color);
  CtxCommandBuilder& filter(std::string fltr);
  CtxCommandBuilder& font(std::string fnt);
  CtxCommandBuilder& fontKerning(std::string fnt);
  CtxCommandBuilder& globalAlpha(double alpha);
  CtxCommandBuilder& globalCompositeOperation(std::string gCO);
  CtxCommandBuilder& imageSmoothingEnabled(bool enabled);
  CtxCommandBuilder& imageSmoothingQuality(std::string quality);
  CtxCommandBuilder& letterSpacing(int pixels);
  CtxCommandBuilder& lineCap(std::string cap);
  CtxCommandBuilder& lineDashOffset(double offset);
  CtxCommandBuilder& lineJoin(std::string join);
  CtxCommandBuilder& lineWidth(int width);
  CtxCommandBuilder& miterLimit(int limit);
  CtxCommandBuilder& shadowBlur(double blur);
  CtxCommandBuilder& shadowColor(Color color);
  CtxCommandBuilder& shadowOffsetX(double offset);
  CtxCommandBuilder& shadowOffsetY(double offset);
  CtxCommandBuilder& strokeStyle(Color color);
  CtxCommandBuilder& textAlign(std::string align);
  CtxCommandBuilder& textBaseline(std::string baseline);
  CtxCommandBuilder& textRendering(std::string rendering);
  CtxCommandBuilder& wordSpacing(int pixels);

  // ctx instance methods
  
};

#endif