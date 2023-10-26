#ifndef CANVASPP_H
#define CANVASPP_H

#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <set>
#include <map>
#include <stdexcept>
#include <chrono>
#include <functional>

#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>
#include <nlohmann/json.hpp>

#include "Input.h"
#include "Output.h"

using Json = nlohmann::json;

typedef websocketpp::server<websocketpp::config::asio> Server;
typedef std::function<void(MouseClick)> MouseClickLambda;
typedef std::function<void(std::string)> KeyPressLambda;

class Canvaspp {
private:
  Server server;
  std::thread serverThread;

  // Stored connections
  std::set<websocketpp::connection_hdl, std::owner_less<websocketpp::connection_hdl>> connections;
  
  // Mutexes
  std::mutex serverMutex;
  std::mutex connectionsMutex;
  std::mutex imagesLoadedMutex;
  std::mutex soundsLoadedMutex;
  std::mutex measuredTextsMutex;
  std::mutex promptResponsesMutex;
  std::mutex confirmResponsesMutex;

  // Canvas Properties
  Dimensions dimensions;
  MousePosition mousePosition;

  // Mouse Click and Key Press Handlers
  MouseClickLambda mouseDownLambda = nullptr;
  MouseClickLambda mouseUpLambda = nullptr;
  KeyPressLambda keyDownLambda = nullptr;
  KeyPressLambda keyUpLambda = nullptr;

  // Client Response Storage
  std::set<std::string> imagesLoaded;
  std::set<std::string> soundsLoaded;
  std::map<std::string, int> measuredTexts;
  std::map<std::string, std::string> promptResponses;
  std::map<std::string, bool> confirmResponses;

  // Useful bools
  bool hasConnections = false;
  bool isShuttingDown = false;

  /* Returns current time using std::chrono::high_resolution_clock. Useful for timeouts on loops. */
  std::chrono::_V2::system_clock::time_point GetCurrentTime() const;

  /* Called by MessageHandler() when the canvas dimensions are updated. */
  void SetDimensions(const Dimensions& dimensions);

  /* Called by MessageHandler() when the canvas mouse position is updated. */
  void SetMousePosition(const MousePosition& mousePosition);

  /* Called by MessageHandler() when an image has successfully loaded in the client.
  The image can now be drawn. */
  void SetImageLoaded(const std::string& imageLoaded);

  /* Called by MessageHandler() when a sound has successfully loaded in the client.
  The sound can now be played. */
  void SetSoundLoaded(const std::string& soundLoaded);

  /* Called by MessageHandler() when a string was successfully measured in the client.
  The measurement can now be viewed. */
  void SetTextMeasurement(const MeasuredText& measuredText);

  /* Called by MessageHandler() when a prompt response was returned from the client.
  The response can now be viewed. */
  void SetPromptResponse(const PromptResponse& promptResponse);

  /* Called by MessageHandler() when a confirm response was returned from the client.
  The response can now be viewed. */
  void SetConfirmResponse(const ConfirmResponse& confirmResponse);

  /* Handles all incoming messages from the client. Uses the INPUT_CODES to distinguish message type. */
  void MessageHandler(websocketpp::connection_hdl hdl, Server::message_ptr msg);

  /* Closes any open connections with the server.
  Requires std::lock_guard<std::mutex> serverLock(this->serverMutex); to be run before calling. */
  void CloseConnections();

  /* Sends a json string to all open client connections.
  All json strings should have a "code" field wih an OUTPUT_CODE and the corresponding information. */
  bool SendJSON(const std::string jsonStr);
public:
  // The ideal animation rate for web browsers is 60 fps which is around 1 frame every 16667 microseconds.
  static constexpr int IDEAL_ANIMATION_RATE = 16667;

  /* Sets server channels and server handlers. Performs basic server initiation. */
  Canvaspp();

  /* Calls this->Stop() if !this->isShuttingDown. */
  ~Canvaspp();

  /* Runs the OS command to open the client's default browser to ui/index.html.
  Waits a maximum of 10 seconds for a connection to be opened or throws a runtime error. */
  void ShowCanvas();

  /* Server starts listening on port 65000 and begins accepting connections.
  this->serverThread is used to run the server. */
  void Start();

  /* Stops listening for new connections. Tells server to shutdown once all connections are closed.
  Closes all connections with this->CloseConnections(). Joins this->serverThread. */
  void Stop();

  /* Returns the current number of connections in this->connections. */
  int GetNumConnections();

  /* Returns this->hasConnections. this->hasConnections is updated on the open and close connection handlers.
  Returns true if there is at least 1 open connection. */
  bool HasConnections();

  /* Helper function that converts a Json object to a json string. */
  static std::string JsonToStr(const Json json);

  /* Helper function that converts a json string object to a Json object. */
  static Json StrToJson(const std::string str);

  /* If the client has been updated to track the mouse position using SetTrackMousePosition(true),
  returns the current mouse position of the user. */
  MousePosition GetMousePosition() const;

  /* Returns the current dimensions of the client canvas. */
  Dimensions GetDimensions() const;

  /* Returns true if the current mouse position accurate. AKA if SetTrackMousePosition(true) has been used. */
  bool IsMousePositionCurrent() const;

  /* Tells the client whether or not to transmit the current mouse position of the user to the server.
  Returns true if the command was successfully sent to the client. */
  bool SetTrackMousePosition(bool track);

  /* Tells the client whether or not to transmit the mouse position when a mouse click occurs.
  The server will then call the mouse click handlers.
  Returns true if the command was successfully sent to the client. */
  bool SetTrackMouseClick(bool track);

  /* Sets the handler to be called when the user clicks down with their mouse. In order for this handler to be used,
  SetTrackMouseClick(true) must have been called. */
  void SetMouseDownHandler(MouseClickLambda mouseDownLambda);

  /* Sets the handler to be called when the user releases a click with their mouse. In order for this handler to be used,
  SetTrackMouseClick(true) must have been called. */
  void SetMouseUpHandler(MouseClickLambda mouseUpLambda);

  /* Sends a series of ctx commands to the client to be executed.
  Returns true if the command was successfully sent to the client. */
  bool SendCtxCommand(std::string command);

  /* Sends a new image for the client to begin loading for use.
  Returns true if the command was successfully sent to the client. */
  bool AddImage(std::string name, std::string src);

  /* Returns true if the client has told the server the specified image has loaded and is thus ready for use. */
  bool IsImageLoaded(std::string name);

  /* Sends a color to be set as the background of the client canvas.
  Returns true if the command was successfully sent to the client. */
  bool SetBackgroundColor(const Color& color);

  /* Sends a keyword to determine the cursor type of the client.
  For valid keywords, see https://developer.mozilla.org/en-US/docs/Web/CSS/cursor.
  Returns true if the command was successfully sent to the client. */
  bool SetCursor(std::string keyword);

  /* Sends a reference image url to set the cursor of the client.
  x and y refer to the hotspot of the cursor image, or the exact cursor position.
  Returns true if the command was successfully sent to the client. */
  bool SetCursor(std::string src, int x, int y, std::string fallbackKeyword = "auto");

  /* Sends a new sound for the client to begin loading for use.
  Returns true if the command was successfully sent to the client. */
  bool AddSound(const Sound& sound);

  /* Returns true if the client has told the server the specified sound has loaded and is thus ready for use. */
  bool IsSoundLoaded(std::string name);

  /* Tells the client to play the specified sound.
  Option to set the start time of the sound to a certain amount of seconds after the start.
  By default, the sound will continue playing from where it was paused.
  If the sound already finished playing, the sound will restart from the beginning.
  Returns true if the command was successfully sent to the client. */
  bool PlaySound(std::string name, int startTime = -1);

  /* Tells the client to pause the specified sound.
  Returns true if the command was successfully sent to the client. */
  bool PauseSound(std::string name);

  /* Tells the client whether or not to transmit the key code when a key press occurs.
  The server will then call the key press handlers.
  Returns true if the command was successfully sent to the client. */
  bool SetTrackKeyPress(bool track);

  /* Sets the handler to be called when the user presses a key down. In order for this handler to be used,
  SetTrackKeyPress(true) must have been called. */
  void SetKeyDownHandler(KeyPressLambda keyDownLambda);

  /* Sets the handler to be called when the user releases a pressed key. In order for this handler to be used,
  SetTrackKeyPress(true) must have been called. */
  void SetKeyUpHandler(KeyPressLambda keyUpLambda);

  /* Instructs the client to measure the pixel length of a certain string.
  Returns true if the command was successfully sent to the client. */
  bool MeasureText(std::string text);

  /* Returns the pixel measurement of a std::string if it has been received from the client.
  Returns -1 if the measurement is unknown/has not been received yet. */
  int GetTextMeasurement(std::string text);

  /* Tells the client to call the window.alert() function with the provided std::string.
  Returns true if the command was successfully sent to the client. */
  bool Alert(std::string alert);

  /* Sets the title of the client window.
  Returns true if the command was successfully sent to the client. */
  bool SetTitle(std::string title);

  /* Sets the favicon of the client window. Not neccessary to use AddImage() first.
  It is recommended to use a .ico file for favicons. The href is a relative path from the index.html file to the .ico file.
  Returns true if the command was successfully sent to the client. */
  bool SetFavicon(std::string href);

  /* Tells the client to call the window.prompt() function with the provided std::string prompt.
  The key will be used to store the response. Use GetPromptResponse() to access the client response.
  Returns true if the command was successfully sent to the client. */
  bool Prompt(std::string key, std::string prompt);

  /* Returns the prompt response if it has been received from the client.
  You must provide the key that was used in Prompt().
  Returns an std::pair<bool, std::string>.
  If the response is unknown/has not been received yet, the std::pair.first will be false.
  Otherwise, the std::pair.first will be true, and the std::pair.second will contain the response. */
  std::pair<bool, std::string> GetPromptResponse(std::string key);

  /* Tells the client to call the window.confirm() function with the provided std::string message.
  The key will be used to store the response. Use GetConfirmResponse() to access the client response.
  Returns true if the command was successfully sent to the client. */
  bool Confirm(std::string key, std::string message);

  /* Returns the confirm response if it has been received from the client.
  You must provide the key that was used in Confirm().
  Returns an std::pair<bool, bool>.
  If the response is unknown/has not been received yet, the std::pair.first will be false.
  Otherwise, the std::pair.first will be true, and the std::pair.second will contain the response. */
  std::pair<bool, bool> GetConfirmResponse(std::string key);
};

#endif