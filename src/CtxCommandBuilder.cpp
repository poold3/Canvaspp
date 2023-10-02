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

CtxCommandBuilder& CtxCommandBuilder::clearRect(int x, int y, int width, int height) {
  this->buffer.append("ctx.clearRect(" + std::to_string(x) + "," + std::to_string(y) + "," + std::to_string(width) + "," + std::to_string(height) + ");");
  return *this;
}

CtxCommandBuilder& CtxCommandBuilder::fillRect(int x, int y, int width, int height) {
  this->buffer.append("ctx.fillRect(" + std::to_string(x) + "," + std::to_string(y) + "," + std::to_string(width) + "," + std::to_string(height) + ");");
  return *this;
}

CtxCommandBuilder& CtxCommandBuilder::rect(int x, int y, int width, int height) {
  this->buffer.append("ctx.rect(" + std::to_string(x) + "," + std::to_string(y) + "," + std::to_string(width) + "," + std::to_string(height) + ");");
  return *this;
}

CtxCommandBuilder& CtxCommandBuilder::rotate(double degrees) {
  double radians = (degrees * PI) / 180.0;
  this->buffer.append("ctx.rotate(" + std::to_string(radians) + ");");
  return *this;
}
