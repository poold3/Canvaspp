#include "Canvaspp.h"

void Canvaspp::SetDimensions(const Dimensions& dimensions) {
  this->dimensions = dimensions;
}

void Canvaspp::SetMousePosition(const MousePosition& mousePosition) {
  this->mousePosition = mousePosition;
}

void Canvaspp::MessageHandler(websocketpp::connection_hdl hdl, Server::message_ptr msg) {
  try {
    std::cout << msg->get_payload() << std::endl;
    Json json = Canvaspp::StrToJson(msg->get_payload());
    INPUT_CODE::CODE inputCode = Input::GetInputCode(json);

    if (inputCode == INPUT_CODE::CODE::DIMENSIONS) {
      this->SetDimensions(Input::GetDimensions(json));
    } else if (inputCode == INPUT_CODE::CODE::MOUSE_POSITION) {
      this->SetMousePosition(Input::GetMousePosition(json));
    } else if (inputCode == INPUT_CODE::CODE::MOUSE_CLICK) {
      if (this->mouseClickLambda != nullptr) {
        this->mouseClickLambda(Input::GetMouseClick(json));
      }
    }

  } catch(const std::exception& e) {
    std::cerr << e.what() << std::endl;
  }
}

/*Requires std::lock_guard<std::mutex> serverLock(this->serverMutex); */
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
  this->server.set_message_handler([this](websocketpp::connection_hdl hdl, Server::message_ptr msg) {
    this->MessageHandler(hdl, msg);
  });
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
  int currentConnections = this->GetNumConnections();
  std::string command = "explorer.exe \"$(wslpath -w ui/index.html)\"";
  std::system(command.c_str());

  //Await Canvas Connection
  while (this->GetNumConnections() == currentConnections) {

  }
}

void Canvaspp::Start() {
  std::lock_guard<std::mutex> serverLock(this->serverMutex);
  this->server.reset();
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

bool Canvaspp::SendJSON(const std::string jsonStr) {
  try {
    if (this->GetNumConnections() > 0) {
      std::lock_guard<std::mutex> serverLock(this->serverMutex);
      std::lock_guard<std::mutex> connectionMutex(this->connectionsMutex);
      for (websocketpp::connection_hdl hdl: this->connections) {
        auto connection = this->server.get_con_from_hdl(hdl);
        std::error_code ec = connection->send(jsonStr, websocketpp::frame::opcode::value::text);
        if (ec.value() != 0) {
          throw std::runtime_error(ec.message());
        }
      }
    } else {
      throw std::invalid_argument("Failed to send JS command: no open connections.");
    }
    return true;
  } catch(const std::exception& e) {
    std::cerr << e.what() << std::endl;
    return false;
  }
}

std::string Canvaspp::JsonToStr(const Json json) {
  return json.dump();
}

Json Canvaspp::StrToJson(const std::string str) {
  return Json::parse(str);
}

MousePosition Canvaspp::GetMousePosition() const {
  return this->mousePosition;
}

bool Canvaspp::IsMousePositionCurrent() const {
  return (this->mousePosition.x != -1) && (this->mousePosition.y != -1);
}

bool Canvaspp::SetUpdateMousePosition(bool update) {
  if (!update) {
    this->mousePosition.x = -1;
    this->mousePosition.y = -1;
  }
  UpdateMousePosition updateMousePosition(update);
  Json json = Output::GetUpdateMousePosition(updateMousePosition);
  std::string jsonStr = Canvaspp::JsonToStr(json);
  return this->SendJSON(jsonStr);
}

bool Canvaspp::SetTrackMouseClick(bool track) {
  if (!track) {
    this->mouseClickLambda = nullptr;
  }
  TrackMouseClick trackMouseClick(track);
  Json json = Output::GetTrackMouseClick(trackMouseClick);
  std::string jsonStr = Canvaspp::JsonToStr(json);
  return this->SendJSON(jsonStr);
}

void Canvaspp::SetMouseClickHandler(MouseClickLambda mouseClickLambda) {
  this->mouseClickLambda = mouseClickLambda;
}

bool Canvaspp::SendCtxCommand(std::string command) {
  CtxCommand ctxCommand(command);
  Json json = Output::GetCtxCommand(ctxCommand);
  std::string jsonStr = Canvaspp::JsonToStr(json);
  return this->SendJSON(jsonStr);
}
