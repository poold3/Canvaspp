#ifndef CANVASPP_H
#define CANVASPP_H

#include <iostream>
#include <string>
#include <thread>
#include <mutex>
#include <set>
#include <websocketpp/config/asio_no_tls.hpp>
#include <websocketpp/server.hpp>

typedef websocketpp::server<websocketpp::config::asio> Server;

class Canvaspp {
private:
  Server server;
  std::set<websocketpp::connection_hdl, std::owner_less<websocketpp::connection_hdl>> connections;
  std::thread thread;
  std::mutex serverMutex;
  std::mutex connectionsMutex;

  static void MessageHandler(websocketpp::connection_hdl hdl, Server::message_ptr msg);
  void CloseConnections();
public:
  Canvaspp();
  ~Canvaspp();
  void ShowCanvas();
  void Start();
  void Stop();
  int GetNumConnections();
};

#endif