#include "input/Dimensions.h"

Dimensions::Dimensions() : Input() {
  this->width = 0;
  this->height = 0;
}

Dimensions::Dimensions(INPUT_CODE code, int width, int height) : Input(code) {
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
  if (!json.at("code").is_number()) {
    throw std::invalid_argument("The \"code\" field is not a number.");
  } else if (!json.at("width").is_number()) {
    throw std::invalid_argument("The \"width\" field is not a number.");
  } else if (!json.at("height").is_number()) {
    throw std::invalid_argument("The \"height\" field is not a number.");
  }

  int code = json.at("code");
  int width = json.at("width");
  int height = json.at("height");

  return Dimensions(Input::FindInputCode(code), width, height);
}

Json Dimensions::ToJson(const Dimensions& dimensions) {
  Json json;

  json["code"] = dimensions.GetCode();
  json["width"] = dimensions.GetWidth();
  json["height"] = dimensions.GetHeight();
  
  return json;
}
