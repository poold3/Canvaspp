#ifndef CANVASPP_H
#define CANVASPP_H

#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <set>
#include <stdexcept>
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>
#include <nlohmann/json.hpp>
#include <input/Input.h>
#include <input/Dimensions.h>
#include <input/MousePosition.h>
#include <output/Output.h>
#include <output/ToggleMousePositionUpdate.h>

using Json = nlohmann::json;

typedef websocketpp::server<websocketpp::config::asio> Server;

struct MousePosition {
  int x;
  int y;
};

class Canvaspp {
private:
  Server server;
  std::set<websocketpp::connection_hdl, std::owner_less<websocketpp::connection_hdl>> connections;
  std::thread thread;
  std::mutex serverMutex;
  std::mutex connectionsMutex;
  int canvasWidth;
  int canvasHeight;
  MousePosition mousePosition;

  void SetDimensions(const Dimensions& dimensions);
  void SetMousePosition(const MousePositionInput& mousePositionInput);
  void MessageHandler(websocketpp::connection_hdl hdl, Server::message_ptr msg);
  void CloseConnections();
public:
  Canvaspp();
  ~Canvaspp();
  void ShowCanvas();
  void Start();
  void Stop();
  int GetNumConnections();
  bool SendJSON(const std::string jsonStr);
  static std::string JsonToStr(const Json json);
  static Json StrToJson(const std::string str);
  MousePosition GetMousePosition() const;
  bool IsMousePositionCurrent() const;
  bool StartUpdateMousePosition();
  bool StopUpdateMousePosition();
};

#endif