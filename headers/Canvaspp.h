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

#include <Input.h>
#include <Output.h>

using Json = nlohmann::json;

typedef websocketpp::server<websocketpp::config::asio> Server;
typedef void(*MouseClickLambda)(MouseClick mouseClick);

class Canvaspp {
private:
  Server server;
  std::set<websocketpp::connection_hdl, std::owner_less<websocketpp::connection_hdl>> connections;
  std::thread thread;
  std::mutex serverMutex;
  std::mutex connectionsMutex;
  Dimensions dimensions;
  MousePosition mousePosition;
  MouseClickLambda mouseClickLambda = nullptr;

  void SetDimensions(const Dimensions& dimensions);
  void SetMousePosition(const MousePosition& mousePosition);
  void MessageHandler(websocketpp::connection_hdl hdl, Server::message_ptr msg);
  void CloseConnections();
  bool SendJSON(const std::string jsonStr);
public:
  Canvaspp();
  ~Canvaspp();
  void ShowCanvas();
  void Start();
  void Stop();
  int GetNumConnections();
  static std::string JsonToStr(const Json json);
  static Json StrToJson(const std::string str);
  MousePosition GetMousePosition() const;
  Dimensions GetDimensions() const;
  bool IsMousePositionCurrent() const;
  bool SetUpdateMousePosition(bool update);
  bool SetTrackMouseClick(bool track);
  void SetMouseClickHandler(MouseClickLambda mouseClickLambda);
  bool SendCtxCommand(std::string command);
};

#endif