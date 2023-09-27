#include "input/Dimensions.h"

Dimensions::Dimensions() : Input() {
  this->width = 0;
  this->height = 0;
}

Dimensions::Dimensions(int width, int height) : Input(INPUT_CODE::CODE::DIMENSIONS) {
  this->width = width;
  this->height = height;
}

Dimensions::~Dimensions() {
  this->width = 0;
  this->height = 0;
}

int Dimensions::GetWidth() const {
  return this->width;
}

int Dimensions::GetHeight() const {
  return this->height;
}

Dimensions Dimensions::FromJson(const Json& json) {
  if (!json.at("width").is_number()) {
    throw std::invalid_argument("The \"width\" field is not a number.");
  } else if (!json.at("height").is_number()) {
    throw std::invalid_argument("The \"height\" field is not a number.");
  }

  int width = json.at("width");
  int height = json.at("height");

  return Dimensions(width, height);
}

Json Dimensions::ToJson(const Dimensions& dimensions) {
  Json json;

  json["code"] = dimensions.GetCode();
  json["width"] = dimensions.GetWidth();
  json["height"] = dimensions.GetHeight();
  
  return json;
}
