#ifndef CTXCOMMANDBUILDER_H
#define CTXCOMMANDBUILDER_H

#include <string>
#include <iostream>
#include <stdexcept>
#include <cmath>

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

const double PI = 2 * std::acos(0.0);

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
  CtxCommandBuilder& arc(int x, int y, int radius, double startAngle, double endAngle, bool counterclockwise = false);
  CtxCommandBuilder& arcTo(int x1, int y1, int x2, int y2, int radius);
  CtxCommandBuilder& beginPath();
  CtxCommandBuilder& bezierCurveTo(int cp1x, int cp1y, int cp2x, int cp2y, int x, int y);
  CtxCommandBuilder& clearRect(int x, int y, int width, int height);
  CtxCommandBuilder& closePath();
  CtxCommandBuilder& drawImage(std::string imageName, int dx, int dy);
  CtxCommandBuilder& drawImage(std::string imageName, int dx, int dy, int dWidth, int dHeight);
  CtxCommandBuilder& drawImage(std::string imageName, int sx, int sy, int sWidth, int sHeight, int dx, int dy, int dWidth, int dHeight);
  CtxCommandBuilder& fill();
  CtxCommandBuilder& fillRect(int x, int y, int width, int height);
  CtxCommandBuilder& fillText(std::string text, int x, int y, int maxWidth = 0);
  CtxCommandBuilder& lineTo(int x, int y);
  CtxCommandBuilder& moveTo(int x, int y);
  CtxCommandBuilder& quadraticCurveTo(int cpx, int cpy, int x, int y);
  CtxCommandBuilder& rect(int x, int y, int width, int height);
  CtxCommandBuilder& reset();
  CtxCommandBuilder& resetTransform();
  CtxCommandBuilder& restore();
  CtxCommandBuilder& rotate(double degrees);
  CtxCommandBuilder& roundRect(int x, int y, int width, int height, int radii);
  CtxCommandBuilder& save();
  CtxCommandBuilder& scale(int x, int y);
  CtxCommandBuilder& setLineDash(int segments[], int segmentsLength);
  CtxCommandBuilder& setTransform(double a, double b, double c, double d, double e, double f);
  CtxCommandBuilder& stroke();
  CtxCommandBuilder& strokeRect(int x, int y, int width, int height);
  CtxCommandBuilder& strokeText(std::string text, int x, int y, int maxWidth = 0);
  CtxCommandBuilder& transform(double a, double b, double c, double d, double e, double f);
  CtxCommandBuilder& translate(int x, int y);
};

#endif