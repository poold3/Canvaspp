#include "Canvaspp.h"

std::chrono::_V2::system_clock::time_point Canvaspp::GetCurrentTime() const {
  return std::chrono::high_resolution_clock::now();
}

void Canvaspp::SetDimensions(const Dimensions& dimensions) {
  this->dimensions = dimensions;
}

void Canvaspp::SetMousePosition(const MousePosition& mousePosition) {
  this->mousePosition = mousePosition;
}

void Canvaspp::SetImageLoaded(const ImageLoaded& imageLoaded) {
  std::lock_guard<std::mutex> serverLock(this->imagesLoadedMutex);
  if (this->imagesLoaded.count(imageLoaded.name) == 1) {
    this->imagesLoaded.at(imageLoaded.name) = true;
  }
}

void Canvaspp::SetSoundLoaded(const SoundLoaded& soundLoaded) {
  std::lock_guard<std::mutex> serverLock(this->soundsLoadedMutex);
  this->soundsLoaded.insert(soundLoaded.name);
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
    } else if (inputCode == INPUT_CODE::CODE::IMAGE_LOADED) {
      this->SetImageLoaded(Input::GetImageLoaded(json));
    } else if (inputCode == INPUT_CODE::CODE::SOUND_LOADED) {
      this->SetSoundLoaded(Input::GetSoundLoaded(json));
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
  auto start = this->GetCurrentTime();
  while (this->GetNumConnections() == currentConnections) {
    if (std::chrono::duration_cast<std::chrono::milliseconds>(this->GetCurrentTime() - start) >= std::chrono::seconds(10)) {
      throw std::runtime_error("Failed to show and connect canvas.");
    }
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

Dimensions Canvaspp::GetDimensions() const {
  return this->dimensions;
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

bool Canvaspp::AddImage(std::string name, std::string src) {
  std::lock_guard<std::mutex> serverLock(this->imagesLoadedMutex);
  if (this->imagesLoaded.count(name) == 1) {
    throw std::invalid_argument("This image already exists.");
  }
  this->imagesLoaded.insert(std::pair<std::string, bool>(name, false));
  LoadImage loadImage(name, src);
  Json json = Output::GetLoadImage(loadImage);
  std::string jsonStr = Canvaspp::JsonToStr(json);
  return this->SendJSON(jsonStr);
}

bool Canvaspp::IsImageLoaded(std::string name) {
  std::lock_guard<std::mutex> serverLock(this->imagesLoadedMutex);
  if (this->imagesLoaded.count(name) != 1) {
    throw std::invalid_argument("This image does not exist.");
  }
  return this->imagesLoaded.at(name);
}

bool Canvaspp::SetBackgroundColor(const Color& color) {
  Json json = Output::GetSetBackgroundColor(color);
  std::string jsonStr = Canvaspp::JsonToStr(json);
  return this->SendJSON(jsonStr);
}

bool Canvaspp::SetCursor(std::string keyword) {
  Cursor cursor(keyword);
  Json json = Output::GetSetCursor(cursor);
  std::string jsonStr = Canvaspp::JsonToStr(json);
  return this->SendJSON(jsonStr);
}

bool Canvaspp::SetCursor(std::string src, int x, int y, std::string fallbackKeyword) {
  Cursor cursor(src, x, y, fallbackKeyword);
  Json json = Output::GetSetCursor(cursor);
  std::string jsonStr = Canvaspp::JsonToStr(json);
  return this->SendJSON(jsonStr);
}

bool Canvaspp::AddSound(const Sound& sound) {
  Json json = Output::GetAddSound(sound);
  std::string jsonStr = Canvaspp::JsonToStr(json);
  return this->SendJSON(jsonStr);
}

bool Canvaspp::IsSoundLoaded(std::string name) {
  std::lock_guard<std::mutex> serverLock(this->soundsLoadedMutex);
  return this->soundsLoaded.count(name) == 1;
}

bool Canvaspp::PlaySound(std::string name, int startTime) {
  Json json = Output::GetPlaySound(name, startTime);
  std::string jsonStr = Canvaspp::JsonToStr(json);
  return this->SendJSON(jsonStr);
}

bool Canvaspp::PauseSound(std::string name) {
  Json json = Output::GetPauseSound(name);
  std::string jsonStr = Canvaspp::JsonToStr(json);
  return this->SendJSON(jsonStr);
}
