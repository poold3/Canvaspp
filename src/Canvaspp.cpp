#include "Canvaspp.h"

void Canvaspp::MessageHandler(websocketpp::connection_hdl hdl, Server::message_ptr msg) {
  try {
    std::cout << msg->get_payload() << std::endl;
  } catch(const std::exception& e) {
    std::cerr << e.what() << std::endl;
  }
}

void Canvaspp::CloseConnections() {
  std::lock_guard<std::mutex> connectionLock(this->connectionsMutex);
  for (websocketpp::connection_hdl hdl: this->connections) {
    auto connection = this->server.get_con_from_hdl(hdl);
    connection->close(1000, "Server closing!");
  }
}

Canvaspp::Canvaspp() {
  this->server.set_error_channels(websocketpp::log::elevel::all);
  this->server.set_access_channels(websocketpp::log::alevel::all);
  this->server.set_message_handler(Canvaspp::MessageHandler);
  this->server.set_open_handler([this](websocketpp::connection_hdl hdl) {
    std::lock_guard<std::mutex> connectionLock(this->connectionsMutex);
    this->connections.insert(hdl);
  });
  this->server.set_close_handler([this](websocketpp::connection_hdl hdl) {
    std::lock_guard<std::mutex> connectionLock(this->connectionsMutex);
    this->connections.erase(hdl);
  });
  
  this->server.init_asio();
  this->server.set_reuse_addr(true);
}

Canvaspp::~Canvaspp() {
  if (this->GetNumConnections() > 0) {
    this->Stop();
  }
}

void Canvaspp::ShowCanvas() {
  std::string command = "explorer.exe \"$(wslpath -w ui/index.html)\"";
  std::system(command.c_str());
}

void Canvaspp::Start() {
  std::lock_guard<std::mutex> serverLock(this->serverMutex);
  this->server.listen(65000);
  this->server.start_accept();
  this->thread = std::thread([](Server& server) {
    server.run();
  }, std::ref(this->server));
}

void Canvaspp::Stop() {
  std::lock_guard<std::mutex> serverLock(this->serverMutex);
  this->server.stop_listening();
  this->server.stop_perpetual();
  this->CloseConnections();
  this->thread.join();
}

int Canvaspp::GetNumConnections() {
  std::lock_guard<std::mutex> connectionMutex(this->connectionsMutex);
  return this->connections.size();
}