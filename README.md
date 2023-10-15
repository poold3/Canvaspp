# Canvas++
A simple GUI for C++ applications using the HTML canvas element and the basic ctx JavaScript commands as found at https://developer.mozilla.org/en-US/docs/Web/API/CanvasRenderingContext2D.
## Dependencies
### WebSocket++ v0.8.2
https://docs.websocketpp.org/index.html

https://github.com/zaphoyd/websocketpp
### JSON for Modern C++ v3.11.2
https://json.nlohmann.me/

https://github.com/nlohmann/json
### Standalone Asio C++ Library v1.28.0
https://think-async.com/Asio/AsioStandalone.html

WebSocket++ normally requires a dependency on the Boost Asio library. Standalone Asio is a smaller library that will offer the same features needed. However, in order to let the compiler know you wish to use Standalone Asio, you must define ASIO_STANDALONE in your compiler command.
## Makefile
If you would like to use the provided Makefile to compile Canvas++, simply follow the steps on the Makefile and run make. This should produce a working shared library file in the lib directory.
## Basic Example
A basic example that sets mouse click and key press handlers. This example also shows how to add images and sounds. Finally, the example shows how to draw images onto the canvas using the CtxCommandBuilder and how to play sounds. Notice how the while loop will continue until the user closes the browser, and thus closes the connection.
```
#include <iostream>
#include <string>
#include <chrono>
#include "Canvaspp.h"
#include "CtxCommandBuilder.h"

MouseClickLambda mouseDownHandler = [](MouseClick click) {
  std::cout << "DOWN: " << click.x << " " << click.y << std::endl;
};

MouseClickLambda mouseUpHandler = [](MouseClick click) {
  std::cout << "UP: " << click.x << " " << click.y << std::endl;
};

KeyPressLambda keyDownHandler = [](std::string code) {
  std::cout << "DOWN: " << code << std::endl;
};

KeyPressLambda keyUpHandler = [](std::string code) {
  std::cout << "UP: " << code << std::endl;
};

int main() {
  try {
    Canvaspp canvaspp;
    canvaspp.Start();
    canvaspp.ShowCanvas();
    
    canvaspp.SetTrackMousePosition(true);

    canvaspp.SetTrackMouseClick(true);
    canvaspp.SetMouseUpHandler(mouseUpHandler);
    canvaspp.SetMouseDownHandler(mouseDownHandler);

    canvaspp.SetTrackKeyPress(true);
    canvaspp.SetKeyUpHandler(keyUpHandler);
    canvaspp.SetKeyDownHandler(keyDownHandler);
    
    canvaspp.AddImage("main_1", "references/main_1.png");
    canvaspp.AddImage("main_2", "references/main_2.png");
    canvaspp.AddImage("main_3", "references/main_3.png");
    canvaspp.AddImage("main_4", "references/main_4.png");
    canvaspp.AddImage("main_5", "references/main_5.png");
    canvaspp.AddSound(Sound("softPiano", "references/soft_piano_trimmed.mp3", true));
    std::string images[5] = {"main_1", "main_2", "main_3", "main_4", "main_5"};
    int numImages = 5;

    while (!canvaspp.IsSoundLoaded("softPiano")) {

    }
    canvaspp.PlaySound("softPiano");

    while (!canvaspp.IsImageLoaded("main_1") || !canvaspp.IsImageLoaded("main_2") || !canvaspp.IsImageLoaded("main_3") || !canvaspp.IsImageLoaded("main_4") || !canvaspp.IsImageLoaded("main_5")) {

    }

    CtxCommandBuilder commandBuilder;
    int currentImage = 0;
    
    while (canvaspp.HasConnections()) {
      std::this_thread::sleep_for(std::chrono::milliseconds(75));
      
      if (currentImage == numImages) {
        currentImage = 0;
      }
      commandBuilder.Clear();
      Dimensions dimensions = canvaspp.GetDimensions();
      commandBuilder.clearRect(0, 0, dimensions.width, dimensions.height);
      commandBuilder.drawImage(images[currentImage], 0, 0, dimensions.width, dimensions.height);
      canvaspp.SendCtxCommand(commandBuilder.ToString());
      ++currentImage;
      
    }
  
    canvaspp.Stop();
  } catch(const std::exception& e) {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}
```

## Canvaspp
The ShowCanvas() method has to use an OS specifc command in order to open your default browser. You must define your specifc OS in your compile command. Current possible OS are: WSL, WINDOWS, LINUX, and MACOS. One way to do this is using the "-D" flag. This is the first step if you compile with the provided Makefile.

Any media that you want to use in the GUI should be placed in the ui directory. The ui directory should be placed in your current working directory. When referencing that media object, the src/url should be a relative path as if the starting directory was the ui directory. For example, an image called smile.png in the ui directory would have this src/url: smile.png.
### void Start();
Server starts listening on port 65000 and begins accepting connections.
this->serverThread is used to run the server.
### void Stop();
Stops listening for new connections. Tells server to shutdown once all connections are closed.
Closes all connections with this->CloseConnections(). Joins this->serverThread.
### void ShowCanvas();
Runs the OS command to open the client's default browser to ui/index.html.
Waits a maximum of 10 seconds for a connection to be opened or throws a runtime error.
### int GetNumConnections();
Returns the current number of connections in this->connections.
### bool HasConnections();
Returns this->hasConnections. this->hasConnections is updated on the open and close connection handlers.
Returns true if there is at least 1 open connection.
### static std::string JsonToStr(const Json json);
Helper function that converts a Json object to a json string.
### static Json StrToJson(const std::string str);
Helper function that converts a json string object to a Json object.
### MousePosition GetMousePosition() const;
If the client has been updated to track the mouse position using SetTrackMousePosition(true),
returns the current mouse position of the user.
### Dimensions GetDimensions() const;
Returns the current dimensions of the client canvas.
### bool IsMousePositionCurrent() const;
Returns true if the current mouse position accurate. AKA if SetTrackMousePosition(true) has been used.
### bool SetTrackMousePosition(bool track);
Tells the client whether or not to transmit the current mouse position of the user to the server.
Returns true if the command was successfully sent to the client.
### bool SetTrackMouseClick(bool track);
Tells the client whether or not to transmit the mouse position when a mouse click occurs.
The server will then call the mouse click handlers.
Returns true if the command was successfully sent to the client.
### void SetMouseDownHandler(MouseClickLambda mouseDownLambda);
Sets the handler to be called when the user clicks down with their mouse. In order for this handler to be used,
SetTrackMouseClick(true) must have been called.
### void SetMouseUpHandler(MouseClickLambda mouseUpLambda);
Sets the handler to be called when the user releases a click with their mouse. In order for this handler to be used,
SetTrackMouseClick(true) must have been called.
### bool SendCtxCommand(std::string command);
Sends a series of ctx commands to the client to be executed.
Returns true if the command was successfully sent to the client.
### bool AddImage(std::string name, std::string src);
Sends a new image for the client to begin loading for use.
Returns true if the command was successfully sent to the client.
### bool IsImageLoaded(std::string name);
Returns true if the client has told the server the specified image has loaded and is thus ready for use.
### bool SetBackgroundColor(const Color& color);
Sends a color to be set as the background of the client canvas.
Returns true if the command was successfully sent to the client.
### bool SetCursor(std::string keyword);
Sends a keyword to determine the cursor type of the client.
For valid keywords, see https://developer.mozilla.org/en-US/docs/Web/CSS/cursor.
Returns true if the command was successfully sent to the client.
### bool SetCursor(std::string src, int x, int y, std::string fallbackKeyword = "auto");
Sends a reference image url to set the cursor of the client.
x and y refer to the hotspot of the cursor image, or the exact cursor position.
Returns true if the command was successfully sent to the client.
### bool AddSound(const Sound& sound);
Sends a new sound for the client to begin loading for use.
Returns true if the command was successfully sent to the client.
### bool IsSoundLoaded(std::string name);
Returns true if the client has told the server the specified sound has loaded and is thus ready for use.
### bool PlaySound(std::string name, int startTime = -1);
Tells the client to play the specified sound.
Option to set the start time of the sound to a certain amount of seconds after the start.
By default, the sound will continue playing from where it was paused.
If the sound already finished playing, the sound will restart from the beginning.
Returns true if the command was successfully sent to the client.
Note that browsers may require some sort of user interaction on the page (A mouse click or key press) before allowing sound to be played.
### bool PauseSound(std::string name);
Tells the client to pause the specified sound.
Returns true if the command was successfully sent to the client.
### bool SetTrackKeyPress(bool track);
Tells the client whether or not to transmit the key code when a key press occurs.
The server will then call the key press handlers.
Returns true if the command was successfully sent to the client.
### void SetKeyDownHandler(KeyPressLambda keyDownLambda);
Sets the handler to be called when the user presses a key down. In order for this handler to be used,
SetTrackKeyPress(true) must have been called.
### void SetKeyUpHandler(KeyPressLambda keyUpLambda);
Sets the handler to be called when the user releases a pressed key. In order for this handler to be used,
SetTrackKeyPress(true) must have been called.
### bool MeasureText(std::string text);
Instructs the client to measure the pixel length of a certain string.
Returns true if the command was successfully sent to the client.
### int GetTextMeasurement(std::string text);
Returns the pixel measurement of a std::string if it has been received from the client.
Returns -1 if the measurement is unknown/has not been received yet.
### bool Alert(std::string alert);
Tells the client to call the window.alert() function with the provided std::string.
Returns true if the command was successfully sent to the client.
### bool SetTitle(std::string title);
Sets the title of the client window.
Returns true if the command was successfully sent to the client.
### bool SetFavicon(std::string href);
Sets the favicon of the client window. Not neccessary to use AddImage() first.
It is recommended to use a .ico file for favicons. The href is a relative path from the index.html file to the .ico file.
Returns true if the command was successfully sent to the client.
### bool Prompt(std::string key, std::string prompt);
Tells the client to call the window.prompt() function with the provided std::string prompt.
The key will be used to store the response. Use GetPromptResponse() to access the client response.
Returns true if the command was successfully sent to the client.
### std::pair<bool, std::string> GetPromptResponse(std::string key);
Returns the prompt response if it has been received from the client.
You must provide the key that was used in Prompt().
Returns an std::pair<bool, std::string>.
If the response is unknown/has not been received yet, the std::pair.first will be false.
Otherwise, the std::pair.first will be true, and the std::pair.second will contain the response.
### bool Confirm(std::string key, std::string message);
Tells the client to call the window.confirm() function with the provided std::string message.
The key will be used to store the response. Use GetConfirmResponse() to access the client response.
Returns true if the command was successfully sent to the client.
### std::pair<bool, bool> GetConfirmResponse(std::string key);
Returns the confirm response if it has been received from the client.
You must provide the key that was used in Confirm().
Returns an std::pair<bool, bool>.
If the response is unknown/has not been received yet, the std::pair.first will be false.
Otherwise, the std::pair.first will be true, and the std::pair.second will contain the response.

## CtxCommandBuilder
Most methods contained in the CtxCommandBuilder are chainable.
### void Clear();
Clears the current command buffer.
### std::string ToString() const;
Returns the current buffer.
### CtxCommandBuilder& direction(std::string dir);
https://developer.mozilla.org/en-US/docs/Web/API/CanvasRenderingContext2D/direction
### CtxCommandBuilder& fillStyle(Color color);
https://developer.mozilla.org/en-US/docs/Web/API/CanvasRenderingContext2D/fillStyle
### CtxCommandBuilder& filter(std::string fltr);
https://developer.mozilla.org/en-US/docs/Web/API/CanvasRenderingContext2D/filter
### CtxCommandBuilder& font(std::string fnt);
https://developer.mozilla.org/en-US/docs/Web/API/CanvasRenderingContext2D/font
### CtxCommandBuilder& fontKerning(std::string fnt);
https://developer.mozilla.org/en-US/docs/Web/API/CanvasRenderingContext2D/fontKerning
### CtxCommandBuilder& globalAlpha(double alpha);
https://developer.mozilla.org/en-US/docs/Web/API/CanvasRenderingContext2D/globalAlpha
### CtxCommandBuilder& globalCompositeOperation(std::string gCO);
https://developer.mozilla.org/en-US/docs/Web/API/CanvasRenderingContext2D/globalCompositeOperation
### CtxCommandBuilder& imageSmoothingEnabled(bool enabled);
https://developer.mozilla.org/en-US/docs/Web/API/CanvasRenderingContext2D/imageSmoothingEnabled
### CtxCommandBuilder& imageSmoothingQuality(std::string quality);
https://developer.mozilla.org/en-US/docs/Web/API/CanvasRenderingContext2D/imageSmoothingQuality
### CtxCommandBuilder& letterSpacing(int pixels);
https://developer.mozilla.org/en-US/docs/Web/API/CanvasRenderingContext2D/letterSpacing
### CtxCommandBuilder& lineCap(std::string cap);
https://developer.mozilla.org/en-US/docs/Web/API/CanvasRenderingContext2D/lineCap
### CtxCommandBuilder& lineDashOffset(double offset);
https://developer.mozilla.org/en-US/docs/Web/API/CanvasRenderingContext2D/lineDashOffset
### CtxCommandBuilder& lineJoin(std::string join);
https://developer.mozilla.org/en-US/docs/Web/API/CanvasRenderingContext2D/lineJoin
### CtxCommandBuilder& lineWidth(int width);
https://developer.mozilla.org/en-US/docs/Web/API/CanvasRenderingContext2D/lineWidth
### CtxCommandBuilder& miterLimit(int limit);
https://developer.mozilla.org/en-US/docs/Web/API/CanvasRenderingContext2D/miterLimit
### CtxCommandBuilder& shadowBlur(double blur);
https://developer.mozilla.org/en-US/docs/Web/API/CanvasRenderingContext2D/shadowBlur
### CtxCommandBuilder& shadowColor(Color color);
https://developer.mozilla.org/en-US/docs/Web/API/CanvasRenderingContext2D/shadowColor
### CtxCommandBuilder& shadowOffsetX(double offset);
https://developer.mozilla.org/en-US/docs/Web/API/CanvasRenderingContext2D/shadowOffsetX
### CtxCommandBuilder& shadowOffsetY(double offset);
https://developer.mozilla.org/en-US/docs/Web/API/CanvasRenderingContext2D/shadowOffsetY
### CtxCommandBuilder& strokeStyle(Color color);
https://developer.mozilla.org/en-US/docs/Web/API/CanvasRenderingContext2D/strokeStyle
### CtxCommandBuilder& textAlign(std::string align);
https://developer.mozilla.org/en-US/docs/Web/API/CanvasRenderingContext2D/textAlign
### CtxCommandBuilder& textBaseline(std::string baseline);
https://developer.mozilla.org/en-US/docs/Web/API/CanvasRenderingContext2D/textBaseline
### CtxCommandBuilder& textRendering(std::string rendering);
https://developer.mozilla.org/en-US/docs/Web/API/CanvasRenderingContext2D/textRendering
### CtxCommandBuilder& wordSpacing(int pixels);
https://developer.mozilla.org/en-US/docs/Web/API/CanvasRenderingContext2D/wordSpacing
### CtxCommandBuilder& arc(int x, int y, int radius, double startAngle, double endAngle, bool counterclockwise = false);
https://developer.mozilla.org/en-US/docs/Web/API/CanvasRenderingContext2D/arc
### CtxCommandBuilder& arcTo(int x1, int y1, int x2, int y2, int radius);
https://developer.mozilla.org/en-US/docs/Web/API/CanvasRenderingContext2D/arcTo
### CtxCommandBuilder& beginPath();
https://developer.mozilla.org/en-US/docs/Web/API/CanvasRenderingContext2D/beginPath
### CtxCommandBuilder& bezierCurveTo(int cp1x, int cp1y, int cp2x, int cp2y, int x, int y);
https://developer.mozilla.org/en-US/docs/Web/API/CanvasRenderingContext2D/bezierCurveTo
### CtxCommandBuilder& clearRect(int x, int y, int width, int height);
https://developer.mozilla.org/en-US/docs/Web/API/CanvasRenderingContext2D/clearRect
### CtxCommandBuilder& closePath();
https://developer.mozilla.org/en-US/docs/Web/API/CanvasRenderingContext2D/closePath
### CtxCommandBuilder& drawImage(std::string imageName, int dx, int dy);
https://developer.mozilla.org/en-US/docs/Web/API/CanvasRenderingContext2D/drawImage
### CtxCommandBuilder& drawImage(std::string imageName, int dx, int dy, int dWidth, int dHeight);
https://developer.mozilla.org/en-US/docs/Web/API/CanvasRenderingContext2D/drawImage
### CtxCommandBuilder& drawImage(std::string imageName, int sx, int sy, int sWidth, int sHeight, int dx, int dy, int dWidth, int dHeight);
https://developer.mozilla.org/en-US/docs/Web/API/CanvasRenderingContext2D/drawImage
### CtxCommandBuilder& fill();
https://developer.mozilla.org/en-US/docs/Web/API/CanvasRenderingContext2D/fill
### CtxCommandBuilder& fillRect(int x, int y, int width, int height);
https://developer.mozilla.org/en-US/docs/Web/API/CanvasRenderingContext2D/fillRect
### CtxCommandBuilder& fillText(std::string text, int x, int y, int maxWidth = 0);
https://developer.mozilla.org/en-US/docs/Web/API/CanvasRenderingContext2D/fillText
### CtxCommandBuilder& lineTo(int x, int y);
https://developer.mozilla.org/en-US/docs/Web/API/CanvasRenderingContext2D/lineTo
### CtxCommandBuilder& moveTo(int x, int y);
https://developer.mozilla.org/en-US/docs/Web/API/CanvasRenderingContext2D/moveTo
### CtxCommandBuilder& quadraticCurveTo(int cpx, int cpy, int x, int y);
https://developer.mozilla.org/en-US/docs/Web/API/CanvasRenderingContext2D/quadraticCurveTo
### CtxCommandBuilder& rect(int x, int y, int width, int height);
https://developer.mozilla.org/en-US/docs/Web/API/CanvasRenderingContext2D/rect
### CtxCommandBuilder& reset();
https://developer.mozilla.org/en-US/docs/Web/API/CanvasRenderingContext2D/reset
### CtxCommandBuilder& resetTransform();
https://developer.mozilla.org/en-US/docs/Web/API/CanvasRenderingContext2D/resetTransform
### CtxCommandBuilder& restore();
https://developer.mozilla.org/en-US/docs/Web/API/CanvasRenderingContext2D/restore
### CtxCommandBuilder& rotate(double degrees);
https://developer.mozilla.org/en-US/docs/Web/API/CanvasRenderingContext2D/rotate
### CtxCommandBuilder& roundRect(int x, int y, int width, int height, int radii);
https://developer.mozilla.org/en-US/docs/Web/API/CanvasRenderingContext2D/roundRect
### CtxCommandBuilder& save();
https://developer.mozilla.org/en-US/docs/Web/API/CanvasRenderingContext2D/save
### CtxCommandBuilder& scale(int x, int y);
https://developer.mozilla.org/en-US/docs/Web/API/CanvasRenderingContext2D/scale
### CtxCommandBuilder& setLineDash(int segments[], int segmentsLength);
https://developer.mozilla.org/en-US/docs/Web/API/CanvasRenderingContext2D/setLineDash
### CtxCommandBuilder& setTransform(double a, double b, double c, double d, double e, double f);
https://developer.mozilla.org/en-US/docs/Web/API/CanvasRenderingContext2D/setTransform
### CtxCommandBuilder& stroke();
https://developer.mozilla.org/en-US/docs/Web/API/CanvasRenderingContext2D/stroke
### CtxCommandBuilder& strokeRect(int x, int y, int width, int height);
https://developer.mozilla.org/en-US/docs/Web/API/CanvasRenderingContext2D/strokeRect
### CtxCommandBuilder& strokeText(std::string text, int x, int y, int maxWidth = 0);
https://developer.mozilla.org/en-US/docs/Web/API/CanvasRenderingContext2D/strokeText
### CtxCommandBuilder& transform(double a, double b, double c, double d, double e, double f);
https://developer.mozilla.org/en-US/docs/Web/API/CanvasRenderingContext2D/transform
### CtxCommandBuilder& translate(int x, int y);
https://developer.mozilla.org/en-US/docs/Web/API/CanvasRenderingContext2D/translate
