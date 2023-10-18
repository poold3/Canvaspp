#ifndef CTXCOMMANDBUILDER_H
#define CTXCOMMANDBUILDER_H

#include <string>
#include <iostream>
#include <stdexcept>
#include <cmath>

#include "Color.h"

const double PI = 2 * std::acos(0.0);

class CtxCommandBuilder {
private:
  std::string buffer;
public:
  CtxCommandBuilder();
  ~CtxCommandBuilder();

  /* Clears the current command buffer. */
  void Clear();

  /* Returns the current buffer. */
  std::string ToString() const;

  // ctx instance properties
  /* https://developer.mozilla.org/en-US/docs/Web/API/CanvasRenderingContext2D/direction */
  CtxCommandBuilder& direction(std::string dir);

  /* https://developer.mozilla.org/en-US/docs/Web/API/CanvasRenderingContext2D/fillStyle */
  CtxCommandBuilder& fillStyle(Color color);

  /* https://developer.mozilla.org/en-US/docs/Web/API/CanvasRenderingContext2D/filter */
  CtxCommandBuilder& filter(std::string fltr);

  /* https://developer.mozilla.org/en-US/docs/Web/API/CanvasRenderingContext2D/font */
  CtxCommandBuilder& font(std::string fnt);

  /* https://developer.mozilla.org/en-US/docs/Web/API/CanvasRenderingContext2D/fontKerning */
  CtxCommandBuilder& fontKerning(std::string fnt);

  /* https://developer.mozilla.org/en-US/docs/Web/API/CanvasRenderingContext2D/globalAlpha */
  CtxCommandBuilder& globalAlpha(double alpha);

  /* https://developer.mozilla.org/en-US/docs/Web/API/CanvasRenderingContext2D/globalCompositeOperation */
  CtxCommandBuilder& globalCompositeOperation(std::string gCO);

  /* https://developer.mozilla.org/en-US/docs/Web/API/CanvasRenderingContext2D/imageSmoothingEnabled */
  CtxCommandBuilder& imageSmoothingEnabled(bool enabled);

  /* https://developer.mozilla.org/en-US/docs/Web/API/CanvasRenderingContext2D/imageSmoothingQuality */
  CtxCommandBuilder& imageSmoothingQuality(std::string quality);

  /* https://developer.mozilla.org/en-US/docs/Web/API/CanvasRenderingContext2D/letterSpacing */
  CtxCommandBuilder& letterSpacing(double pixels);

  /* https://developer.mozilla.org/en-US/docs/Web/API/CanvasRenderingContext2D/lineCap */
  CtxCommandBuilder& lineCap(std::string cap);

  /* https://developer.mozilla.org/en-US/docs/Web/API/CanvasRenderingContext2D/lineDashOffset */
  CtxCommandBuilder& lineDashOffset(double offset);

  /* https://developer.mozilla.org/en-US/docs/Web/API/CanvasRenderingContext2D/lineJoin */
  CtxCommandBuilder& lineJoin(std::string join);

  /* https://developer.mozilla.org/en-US/docs/Web/API/CanvasRenderingContext2D/lineWidth */
  CtxCommandBuilder& lineWidth(double width);

  /* https://developer.mozilla.org/en-US/docs/Web/API/CanvasRenderingContext2D/miterLimit */
  CtxCommandBuilder& miterLimit(double limit);

  /* https://developer.mozilla.org/en-US/docs/Web/API/CanvasRenderingContext2D/shadowBlur */
  CtxCommandBuilder& shadowBlur(double blur);

  /* https://developer.mozilla.org/en-US/docs/Web/API/CanvasRenderingContext2D/shadowColor */
  CtxCommandBuilder& shadowColor(Color color);

  /* https://developer.mozilla.org/en-US/docs/Web/API/CanvasRenderingContext2D/shadowOffsetX */
  CtxCommandBuilder& shadowOffsetX(double offset);

  /* https://developer.mozilla.org/en-US/docs/Web/API/CanvasRenderingContext2D/shadowOffsetY */
  CtxCommandBuilder& shadowOffsetY(double offset);

  /* https://developer.mozilla.org/en-US/docs/Web/API/CanvasRenderingContext2D/strokeStyle */
  CtxCommandBuilder& strokeStyle(Color color);

  /* https://developer.mozilla.org/en-US/docs/Web/API/CanvasRenderingContext2D/textAlign */
  CtxCommandBuilder& textAlign(std::string align);

  /* https://developer.mozilla.org/en-US/docs/Web/API/CanvasRenderingContext2D/textBaseline */
  CtxCommandBuilder& textBaseline(std::string baseline);

  /* https://developer.mozilla.org/en-US/docs/Web/API/CanvasRenderingContext2D/textRendering */
  CtxCommandBuilder& textRendering(std::string rendering);

  /* https://developer.mozilla.org/en-US/docs/Web/API/CanvasRenderingContext2D/wordSpacing */
  CtxCommandBuilder& wordSpacing(double pixels);

  // ctx instance methods
  /* https://developer.mozilla.org/en-US/docs/Web/API/CanvasRenderingContext2D/arc */
  CtxCommandBuilder& arc(double x, double y, double radius, double startAngle, double endAngle, bool counterclockwise = false);
  
  /* https://developer.mozilla.org/en-US/docs/Web/API/CanvasRenderingContext2D/arcTo */
  CtxCommandBuilder& arcTo(double x1, double y1, double x2, double y2, double radius);

  /* https://developer.mozilla.org/en-US/docs/Web/API/CanvasRenderingContext2D/beginPath */
  CtxCommandBuilder& beginPath();

  /* https://developer.mozilla.org/en-US/docs/Web/API/CanvasRenderingContext2D/bezierCurveTo */
  CtxCommandBuilder& bezierCurveTo(double cp1x, double cp1y, double cp2x, double cp2y, double x, double y);

  /* https://developer.mozilla.org/en-US/docs/Web/API/CanvasRenderingContext2D/clearRect */
  CtxCommandBuilder& clearRect(double x, double y, double width, double height);

  /* https://developer.mozilla.org/en-US/docs/Web/API/CanvasRenderingContext2D/closePath */
  CtxCommandBuilder& closePath();

  /* https://developer.mozilla.org/en-US/docs/Web/API/CanvasRenderingContext2D/drawImage */
  CtxCommandBuilder& drawImage(std::string imageName, double dx, double dy);

  /* https://developer.mozilla.org/en-US/docs/Web/API/CanvasRenderingContext2D/drawImage */
  CtxCommandBuilder& drawImage(std::string imageName, double dx, double dy, double dWidth, double dHeight);

  /* https://developer.mozilla.org/en-US/docs/Web/API/CanvasRenderingContext2D/drawImage */
  CtxCommandBuilder& drawImage(std::string imageName, double sx, double sy, double sWidth, double sHeight, double dx, double dy, double dWidth, double dHeight);
  
  /* https://developer.mozilla.org/en-US/docs/Web/API/CanvasRenderingContext2D/fill */
  CtxCommandBuilder& fill();

  /* https://developer.mozilla.org/en-US/docs/Web/API/CanvasRenderingContext2D/fillRect */
  CtxCommandBuilder& fillRect(double x, double y, double width, double height);

  /* https://developer.mozilla.org/en-US/docs/Web/API/CanvasRenderingContext2D/fillText */
  CtxCommandBuilder& fillText(std::string text, double x, double y, double maxWidth = 0);

  /* https://developer.mozilla.org/en-US/docs/Web/API/CanvasRenderingContext2D/lineTo */
  CtxCommandBuilder& lineTo(double x, double y);

  /* https://developer.mozilla.org/en-US/docs/Web/API/CanvasRenderingContext2D/moveTo */
  CtxCommandBuilder& moveTo(double x, double y);

  /* https://developer.mozilla.org/en-US/docs/Web/API/CanvasRenderingContext2D/quadraticCurveTo */
  CtxCommandBuilder& quadraticCurveTo(double cpx, double cpy, double x, double y);

  /* https://developer.mozilla.org/en-US/docs/Web/API/CanvasRenderingContext2D/rect */
  CtxCommandBuilder& rect(double x, double y, double width, double height);

  /* https://developer.mozilla.org/en-US/docs/Web/API/CanvasRenderingContext2D/reset */
  CtxCommandBuilder& reset();

  /* https://developer.mozilla.org/en-US/docs/Web/API/CanvasRenderingContext2D/resetTransform */
  CtxCommandBuilder& resetTransform();

  /* https://developer.mozilla.org/en-US/docs/Web/API/CanvasRenderingContext2D/restore */
  CtxCommandBuilder& restore();

  /* https://developer.mozilla.org/en-US/docs/Web/API/CanvasRenderingContext2D/rotate */
  CtxCommandBuilder& rotate(double degrees);

  /* https://developer.mozilla.org/en-US/docs/Web/API/CanvasRenderingContext2D/roundRect */
  CtxCommandBuilder& roundRect(double x, double y, double width, double height, double radii);

  /* https://developer.mozilla.org/en-US/docs/Web/API/CanvasRenderingContext2D/save */
  CtxCommandBuilder& save();

  /* https://developer.mozilla.org/en-US/docs/Web/API/CanvasRenderingContext2D/scale */
  CtxCommandBuilder& scale(double x, double y);

  /* https://developer.mozilla.org/en-US/docs/Web/API/CanvasRenderingContext2D/setLineDash */
  CtxCommandBuilder& setLineDash(double segments[], int segmentsLength);

  /* https://developer.mozilla.org/en-US/docs/Web/API/CanvasRenderingContext2D/setTransform */
  CtxCommandBuilder& setTransform(double a, double b, double c, double d, double e, double f);

  /* https://developer.mozilla.org/en-US/docs/Web/API/CanvasRenderingContext2D/stroke */
  CtxCommandBuilder& stroke();

  /* https://developer.mozilla.org/en-US/docs/Web/API/CanvasRenderingContext2D/strokeRect */
  CtxCommandBuilder& strokeRect(double x, double y, double width, double height);

  /* https://developer.mozilla.org/en-US/docs/Web/API/CanvasRenderingContext2D/strokeText */
  CtxCommandBuilder& strokeText(std::string text, double x, double y, double maxWidth = 0);

  /* https://developer.mozilla.org/en-US/docs/Web/API/CanvasRenderingContext2D/transform */
  CtxCommandBuilder& transform(double a, double b, double c, double d, double e, double f);

  /* https://developer.mozilla.org/en-US/docs/Web/API/CanvasRenderingContext2D/translate */
  CtxCommandBuilder& translate(double x, double y);
};

#endif