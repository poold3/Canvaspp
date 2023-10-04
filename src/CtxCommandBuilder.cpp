#include "CtxCommandBuilder.h"

CtxCommandBuilder::CtxCommandBuilder() {
  this->buffer = "";
}

CtxCommandBuilder::~CtxCommandBuilder() {
  this->buffer = "";
}

void CtxCommandBuilder::Clear() {
  this->buffer = "";
}

std::string CtxCommandBuilder::ToString() const {
  return this->buffer;
}

// Instance Properties
CtxCommandBuilder& CtxCommandBuilder::direction(std::string dir) {
  if (dir == "ltr" || dir == "rtl" || dir == "inherit") {
    this->buffer.append("ctx.direction = '" + dir + "';");
    return *this;
  } else {
    throw std::invalid_argument("Invalid direction string.");
  }
}

CtxCommandBuilder& CtxCommandBuilder::fillStyle(Color color) {
  this->buffer.append("ctx.fillStyle = '" + color.ToString() + "';");
  return *this;
}

CtxCommandBuilder& CtxCommandBuilder::filter(std::string fltr) {
  this->buffer.append("ctx.filter = '" + fltr + "';");
  return *this;
}

CtxCommandBuilder& CtxCommandBuilder::font(std::string fnt) {
  this->buffer.append("ctx.font = '" + fnt + "';");
  return *this;
}

CtxCommandBuilder& CtxCommandBuilder::fontKerning(std::string fnt) {
  if (fnt == "auto" || fnt == "normal" || fnt == "none") {
    this->buffer.append("ctx.fontKerning = '" + fnt + "';");
    return *this;
  } else {
    throw std::invalid_argument("Invalid fontKerning string.");
  }
}

CtxCommandBuilder& CtxCommandBuilder::globalAlpha(double alpha) {
  this->buffer.append("ctx.globalAlpha = " + std::to_string(alpha) + ";");
  return *this;
}

CtxCommandBuilder& CtxCommandBuilder::globalCompositeOperation(std::string gCO) {
  this->buffer.append("ctx.font = '" + gCO + "';");
  return *this;
}

CtxCommandBuilder& CtxCommandBuilder::imageSmoothingEnabled(bool enabled) {
  std::string val = (enabled ? "true" : "false");
  this->buffer.append("ctx.imageSmoothingEnabled = " + val + ";");
  return *this;
}

CtxCommandBuilder& CtxCommandBuilder::imageSmoothingQuality(std::string quality) {
  if (quality == "low" || quality == "medium" || quality == "high") {
    this->buffer.append("ctx.imageSmoothingQuality = '" + quality + "';");
    return *this;
  } else {
    throw std::invalid_argument("Invalid imageSmoothingQuality string.");
  }
}

CtxCommandBuilder& CtxCommandBuilder::letterSpacing(int pixels) {
  this->buffer.append("ctx.letterSpacing  = '" + std::to_string(pixels) + "px';");
  return *this;
}

CtxCommandBuilder& CtxCommandBuilder::lineCap(std::string cap) {
  if (cap == "butt" || cap == "round" || cap == "square") {
    this->buffer.append("ctx.lineCap = '" + cap + "';");
    return *this;
  } else {
    throw std::invalid_argument("Invalid lineCap string.");
  }
}

CtxCommandBuilder& CtxCommandBuilder::lineDashOffset(double offset) {
  this->buffer.append("ctx.lineDashOffset = " + std::to_string(offset) + ";");
  return *this;
}

CtxCommandBuilder& CtxCommandBuilder::lineJoin(std::string join) {
  if (join == "round" || join == "bevel" || join == "miter") {
    this->buffer.append("ctx.lineJoin  = '" + join + "';");
    return *this;
  } else {
    throw std::invalid_argument("Invalid lineJoin string.");
  }
}

CtxCommandBuilder& CtxCommandBuilder::lineWidth(int width) {
  this->buffer.append("ctx.lineWidth = " + std::to_string(width) + ";");
  return *this;
}

CtxCommandBuilder& CtxCommandBuilder::miterLimit(int limit) {
  this->buffer.append("ctx.miterLimit = " + std::to_string(limit) + ";");
  return *this;
}

CtxCommandBuilder& CtxCommandBuilder::shadowBlur(double blur) {
  this->buffer.append("ctx.shadowBlur = " + std::to_string(blur) + ";");
  return *this;
}

CtxCommandBuilder& CtxCommandBuilder::shadowColor(Color color) {
  this->buffer.append("ctx.shadowColor = '" + color.ToString() + "';");
  return *this;
}

CtxCommandBuilder& CtxCommandBuilder::shadowOffsetX(double offset) {
  this->buffer.append("ctx.shadowOffsetX = " + std::to_string(offset) + ";");
  return *this;
}

CtxCommandBuilder& CtxCommandBuilder::shadowOffsetY(double offset) {
  this->buffer.append("ctx.shadowOffsetY = " + std::to_string(offset) + ";");
  return *this;
}

CtxCommandBuilder& CtxCommandBuilder::strokeStyle(Color color) {
  this->buffer.append("ctx.strokeStyle = '" + color.ToString() + "';");
  return *this;
}

CtxCommandBuilder& CtxCommandBuilder::textAlign(std::string align) {
  if (align == "left" || align == "right" || align == "center" || align == "start" || align == "end") {
    this->buffer.append("ctx.textAlign = '" + align + "';");
    return *this;
  } else {
    throw std::invalid_argument("Invalid textAlign string.");
  }
}

CtxCommandBuilder& CtxCommandBuilder::textBaseline(std::string baseline) {
  if (baseline == "top" || baseline == "hanging" || baseline == "middle" || baseline == "alphabetic" || baseline == "ideographic" || baseline == "bottom") {
    this->buffer.append("ctx.textBaseline = '" + baseline + "';");
    return *this;
  } else {
    throw std::invalid_argument("Invalid textBaseline string.");
  }
}

CtxCommandBuilder& CtxCommandBuilder::textRendering(std::string rendering) {
  if (rendering == "auto" || rendering == "optimizeSpeed" || rendering == "optimizeLegibility" || rendering == "geometricPrecision") {
    this->buffer.append("ctx.textRendering = '" + rendering + "';");
    return *this;
  } else {
    throw std::invalid_argument("Invalid textRendering string.");
  }
}

CtxCommandBuilder& CtxCommandBuilder::wordSpacing(int pixels) {
  this->buffer.append("ctx.wordSpacing = '" + std::to_string(pixels) + "px';");
  return *this;
}

// Instance Methods
CtxCommandBuilder& CtxCommandBuilder::arc(int x, int y, int radius, double startAngle, double endAngle, bool counterclockwise) {
  double startAngleRadians = (startAngle * PI) / 180.0;
  double endAngleRadians = (endAngle * PI) / 180.0;
  std::string counterclockwiseStr = (counterclockwise ? "true" : "false");
  this->buffer.append("ctx.arc(" + std::to_string(x) + "," + std::to_string(y) + "," + std::to_string(radius) + "," + std::to_string(startAngleRadians) + "," + std::to_string(endAngleRadians) + "," + counterclockwiseStr + ");");
  return *this;
}

CtxCommandBuilder& CtxCommandBuilder::arcTo(int x1, int y1, int x2, int y2, int radius) {
  this->buffer.append("ctx.arcTo(" + std::to_string(x1) + "," + std::to_string(y1) + "," + std::to_string(x2) + "," + std::to_string(y2) + "," + std::to_string(radius) + ");");
  return *this;
}

CtxCommandBuilder& CtxCommandBuilder::beginPath() {
  this->buffer.append("ctx.beginPath();");
  return *this;
}

CtxCommandBuilder& CtxCommandBuilder::bezierCurveTo(int cp1x, int cp1y, int cp2x, int cp2y, int x, int y) {
  this->buffer.append("ctx.bezierCurveTo(" + std::to_string(cp1x) + "," + std::to_string(cp1y) + "," + std::to_string(cp2x) + "," + std::to_string(cp2y) + "," + std::to_string(x) + "," + std::to_string(y) + ");");
  return *this;
}


CtxCommandBuilder& CtxCommandBuilder::clearRect(int x, int y, int width, int height) {
  this->buffer.append("ctx.clearRect(" + std::to_string(x) + "," + std::to_string(y) + "," + std::to_string(width) + "," + std::to_string(height) + ");");
  return *this;
}

CtxCommandBuilder& CtxCommandBuilder::closePath() {
  this->buffer.append("ctx.closePath();");
  return *this;
}

CtxCommandBuilder& CtxCommandBuilder::drawImage(std::string imageName, int dx, int dy) {
  this->buffer.append("ctx.drawImage(images." + imageName + "," + std::to_string(dx) + "," + std::to_string(dy) + ");");
  return *this;
}

CtxCommandBuilder& CtxCommandBuilder::drawImage(std::string imageName, int dx, int dy, int dWidth, int dHeight) {
  this->buffer.append("ctx.drawImage(images." + imageName + "," + std::to_string(dx) + "," + std::to_string(dy) + "," + std::to_string(dWidth) + "," + std::to_string(dHeight) + ");");
  return *this;
}

CtxCommandBuilder& CtxCommandBuilder::drawImage(std::string imageName, int sx, int sy, int sWidth, int sHeight, int dx, int dy, int dWidth, int dHeight) {
  this->buffer.append("ctx.drawImage(images." + imageName + "," + std::to_string(sx) + "," + std::to_string(sy) + "," + std::to_string(sWidth) + "," + std::to_string(sHeight) + "," + std::to_string(dx) + "," + std::to_string(dy) + "," + std::to_string(dWidth) + "," + std::to_string(dHeight) + ");");
  return *this;
}

CtxCommandBuilder& CtxCommandBuilder::fill() {
  this->buffer.append("ctx.fill();");
  return *this;
}


CtxCommandBuilder& CtxCommandBuilder::fillRect(int x, int y, int width, int height) {
  this->buffer.append("ctx.fillRect(" + std::to_string(x) + "," + std::to_string(y) + "," + std::to_string(width) + "," + std::to_string(height) + ");");
  return *this;
}

CtxCommandBuilder& CtxCommandBuilder::fillText(std::string text, int x, int y, int maxWidth) {
  if (maxWidth == 0) {
    this->buffer.append("ctx.fillText(" + text + "," + std::to_string(x) + "," + std::to_string(y) + ");");
  } else {
    this->buffer.append("ctx.fillText(" + text + "," + std::to_string(x) + "," + std::to_string(y) + "," + std::to_string(maxWidth) + ");");
  }
  return *this;
}

CtxCommandBuilder& CtxCommandBuilder::lineTo(int x, int y) {
  this->buffer.append("ctx.lineTo(" + std::to_string(x) + "," + std::to_string(y) + ");");
  return *this;
}

CtxCommandBuilder& CtxCommandBuilder::moveTo(int x, int y) {
  this->buffer.append("ctx.moveTo(" + std::to_string(x) + "," + std::to_string(y) + ");");
  return *this;
}

CtxCommandBuilder& CtxCommandBuilder::quadraticCurveTo(int cpx, int cpy, int x, int y) {
  this->buffer.append("ctx.quadraticCurveTo(" + std::to_string(cpx) + "," + std::to_string(cpy) + "," + std::to_string(x) + "," + std::to_string(y) + ");");
  return *this;
}


CtxCommandBuilder& CtxCommandBuilder::rect(int x, int y, int width, int height) {
  this->buffer.append("ctx.rect(" + std::to_string(x) + "," + std::to_string(y) + "," + std::to_string(width) + "," + std::to_string(height) + ");");
  return *this;
}

CtxCommandBuilder& CtxCommandBuilder::reset() {
  this->buffer.append("ctx.reset();");
  return *this;
}

CtxCommandBuilder& CtxCommandBuilder::resetTransform() {
  this->buffer.append("ctx.resetTransform();");
  return *this;
}

CtxCommandBuilder& CtxCommandBuilder::restore() {
  this->buffer.append("ctx.restore();");
  return *this;
}


CtxCommandBuilder& CtxCommandBuilder::rotate(double degrees) {
  double radians = (degrees * PI) / 180.0;
  this->buffer.append("ctx.rotate(" + std::to_string(radians) + ");");
  return *this;
}

CtxCommandBuilder& CtxCommandBuilder::roundRect(int x, int y, int width, int height, int radii) {
  this->buffer.append("ctx.roundRect(" + std::to_string(x) + "," + std::to_string(y) + "," + std::to_string(width) + "," + std::to_string(height) + "," + std::to_string(radii) + ");");
  return *this;
}

CtxCommandBuilder& CtxCommandBuilder::save() {
  this->buffer.append("ctx.save();");
  return *this;
}

CtxCommandBuilder& CtxCommandBuilder::scale(int x, int y) {
  this->buffer.append("ctx.scale(" + std::to_string(x) + "," + std::to_string(y) + ");");
  return *this;
}

CtxCommandBuilder& CtxCommandBuilder::setLineDash(int segments[], int segmentsLength) {
  this->buffer.append("ctx.setLineDash([");
  for (int i = 0; i < segmentsLength; ++i) {
    if (i != 0) {
      this->buffer.append(",");
    }
    this->buffer.append(std::to_string(segments[i]));
  }
  this->buffer.append("]);");
  return *this;
}

CtxCommandBuilder& CtxCommandBuilder::setTransform(double a, double b, double c, double d, double e, double f) {
  this->buffer.append("ctx.setTransform(" + std::to_string(a) + "," + std::to_string(b) + "," + std::to_string(c) + "," + std::to_string(d) + "," + std::to_string(e) + "," + std::to_string(f) + ");");
  return *this;
}

CtxCommandBuilder& CtxCommandBuilder::stroke() {
  this->buffer.append("ctx.stroke();");
  return *this;
}

CtxCommandBuilder& CtxCommandBuilder::strokeRect(int x, int y, int width, int height) {
  this->buffer.append("ctx.strokeRect(" + std::to_string(x) + "," + std::to_string(y) + "," + std::to_string(width) + "," + std::to_string(height) + ");");
  return *this;
}

CtxCommandBuilder& CtxCommandBuilder::strokeText(std::string text, int x, int y, int maxWidth) {
  if (maxWidth == 0) {
    this->buffer.append("ctx.strokeText(" + text + "," + std::to_string(x) + "," + std::to_string(y) + ");");
  } else {
    this->buffer.append("ctx.strokeText(" + text + "," + std::to_string(x) + "," + std::to_string(y) + "," + std::to_string(maxWidth) + ");");
  }
  return *this;
}

CtxCommandBuilder& CtxCommandBuilder::transform(double a, double b, double c, double d, double e, double f) {
  this->buffer.append("ctx.transform(" + std::to_string(a) + "," + std::to_string(b) + "," + std::to_string(c) + "," + std::to_string(d) + "," + std::to_string(e) + "," + std::to_string(f) + ");");
  return *this;
}

CtxCommandBuilder& CtxCommandBuilder::translate(int x, int y) {
  this->buffer.append("ctx.translate(" + std::to_string(x) + "," + std::to_string(y) + ");");
  return *this;
}
