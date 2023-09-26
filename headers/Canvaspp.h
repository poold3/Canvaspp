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

using Json = nlohmann::json;

typedef websocketpp::server<websocketpp::config::asio> Server;

class Canvaspp {
private:
  Server server;
  std::set<websocketpp::connection_hdl, std::owner_less<websocketpp::connection_hdl>> connections;
  std::thread thread;
  std::mutex serverMutex;
  std::mutex connectionsMutex;
  int canvasWidth;
  int canvasHeight;

  void SetDimensions(const Dimensions& dimensions);
  void MessageHandler(websocketpp::connection_hdl hdl, Server::message_ptr msg);
  void CloseConnections();
public:
  Canvaspp();
  ~Canvaspp();
  void ShowCanvas();
  void Start();
  void Stop();
  int GetNumConnections();
  bool SendJSONCommand(const std::string jsonStr);
  static std::string JsonToStr(const Json json);
  static Json StrToJson(const std::string str);
};

#endif