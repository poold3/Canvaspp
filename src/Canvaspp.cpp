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

void Canvaspp::SetImageLoaded(const std::string& imageLoaded) {
  std::lock_guard<std::mutex> serverLock(this->imagesLoadedMutex);
  this->imagesLoaded.insert(imageLoaded);
}

void Canvaspp::SetSoundLoaded(const std::string& soundLoaded) {
  std::lock_guard<std::mutex> serverLock(this->soundsLoadedMutex);
  this->soundsLoaded.insert(soundLoaded);
}

void Canvaspp::SetTextMeasurement(const MeasuredText& measuredText) {
  std::lock_guard<std::mutex> serverLock(this->measuredTextsMutex);
  this->measuredTexts[measuredText.text] = measuredText.measurement;
}

void Canvaspp::SetPromptResponse(const PromptResponse& promptResponse) {
  std::lock_guard<std::mutex> connectionLock(this->promptResponsesMutex);
  this->promptResponses[promptResponse.key] = promptResponse.response;
}

void Canvaspp::SetConfirmResponse(const ConfirmResponse& confirmResponse) {
  std::lock_guard<std::mutex> connectionLock(this->confirmResponsesMutex);
  this->confirmResponses[confirmResponse.key] = confirmResponse.response;
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
    } else if (inputCode == INPUT_CODE::CODE::MOUSE_DOWN) {
      if (this->mouseDownLambda != nullptr) {
        this->mouseDownLambda(Input::GetMouseClick(json));
      }
    } else if (inputCode == INPUT_CODE::CODE::MOUSE_UP) {
      if (this->mouseUpLambda != nullptr) {
        this->mouseUpLambda(Input::GetMouseClick(json));
      }
    } else if (inputCode == INPUT_CODE::CODE::KEY_DOWN) {
      if (this->keyDownLambda != nullptr) {
        this->keyDownLambda(Input::GetKeyPress(json));
      }
    } else if (inputCode == INPUT_CODE::CODE::KEY_UP) {
      if (this->keyUpLambda != nullptr) {
        this->keyUpLambda(Input::GetKeyPress(json));
      }
    } else if (inputCode == INPUT_CODE::CODE::IMAGE_LOADED) {
      this->SetImageLoaded(Input::GetImageLoaded(json));
    } else if (inputCode == INPUT_CODE::CODE::SOUND_LOADED) {
      this->SetSoundLoaded(Input::GetSoundLoaded(json));
    } else if (inputCode == INPUT_CODE::CODE::MEASURED_TEXT) {
      this->SetTextMeasurement(Input::GetMeasuredText(json));
    } else if (inputCode == INPUT_CODE::CODE::PROMPT_RESPONSE) {
      this->SetPromptResponse(Input::GetPromptResponse(json));
    } else if (inputCode == INPUT_CODE::CODE::CONFIRM_RESPONSE) {
      this->SetConfirmResponse(Input::GetConfirmResponse(json));
    }

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

Canvaspp::Canvaspp() {
  this->server.set_error_channels(websocketpp::log::elevel::all);
  this->server.set_access_channels(websocketpp::log::alevel::all);
  this->server.set_message_handler([this](websocketpp::connection_hdl hdl, Server::message_ptr msg) {
    this->MessageHandler(hdl, msg);
  });
  this->server.set_open_handler([this](websocketpp::connection_hdl hdl) {
    std::lock_guard<std::mutex> connectionLock(this->connectionsMutex);
    this->connections.insert(hdl);
    this->hasConnections = true;
  });
  this->server.set_close_handler([this](websocketpp::connection_hdl hdl) {
    std::lock_guard<std::mutex> connectionLock(this->connectionsMutex);
    this->connections.erase(hdl);
    if (this->connections.size() == 0) {
      this->hasConnections = false;
    }
  });
  
  this->server.init_asio();
  this->server.set_reuse_addr(true);
}

Canvaspp::~Canvaspp() {
  if (!this->isShuttingDown) {
    this->Stop();
  }
}

void Canvaspp::ShowCanvas() {
  int currentConnections = this->GetNumConnections();
  #ifdef WSL
    std::string command = "explorer.exe \"$(wslpath -w ui/index.html)\"";
  #elif defined(WINDOWS)
    std::string command = "explorer.exe \"ui/index.html\"";
  #elif defined(LINUX)
    std::string command = "xdg-open ui/index.html";
  #elif defined(MACOS)
    std::string command = "open ui/index.html";
  #else
    throw std::runtime_error("No OS specified.")
  #endif
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
  this->serverThread = std::thread([](Server& server) {
    server.run();
  }, std::ref(this->server));
}

void Canvaspp::Stop() {
  this->isShuttingDown = true;
  std::lock_guard<std::mutex> serverLock(this->serverMutex);
  this->server.stop_listening();
  this->server.stop_perpetual();
  this->CloseConnections();
  this->serverThread.join();
}

int Canvaspp::GetNumConnections() {
  std::lock_guard<std::mutex> connectionMutex(this->connectionsMutex);
  return this->connections.size();
}

bool Canvaspp::HasConnections() {
  std::lock_guard<std::mutex> connectionMutex(this->connectionsMutex);
  return this->hasConnections;
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

bool Canvaspp::SetTrackMousePosition(bool track) {
  if (!track) {
    this->mousePosition.x = -1;
    this->mousePosition.y = -1;
  }
  Json json = Output::GetTrackMousePosition(track);
  std::string jsonStr = Canvaspp::JsonToStr(json);
  return this->SendJSON(jsonStr);
}

bool Canvaspp::SetTrackMouseClick(bool track) {
  if (!track) {
    this->mouseDownLambda = nullptr;
    this->mouseUpLambda = nullptr;
  }
  Json json = Output::GetTrackMouseClick(track);
  std::string jsonStr = Canvaspp::JsonToStr(json);
  return this->SendJSON(jsonStr);
}

void Canvaspp::SetMouseDownHandler(MouseClickLambda mouseDownLambda) {
  this->mouseDownLambda = mouseDownLambda;
}

void Canvaspp::SetMouseUpHandler(MouseClickLambda mouseUpLambda) {
  this->mouseUpLambda = mouseUpLambda;
}

bool Canvaspp::SendCtxCommand(std::string command) {
  Json json = Output::GetCtxCommand(command);
  std::string jsonStr = Canvaspp::JsonToStr(json);
  return this->SendJSON(jsonStr);
}

bool Canvaspp::AddImage(std::string name, std::string src) {
  LoadImage loadImage(name, src);
  Json json = Output::GetLoadImage(loadImage);
  std::string jsonStr = Canvaspp::JsonToStr(json);
  return this->SendJSON(jsonStr);
}

bool Canvaspp::IsImageLoaded(std::string name) {
  std::lock_guard<std::mutex> serverLock(this->imagesLoadedMutex);
  return this->imagesLoaded.count(name) == 1;
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
  if (!this->IsSoundLoaded(name)) {
    throw std::invalid_argument("Sound: " + name + " is not yet loaded.");
  }
  Json json = Output::GetPlaySound(name, startTime);
  std::string jsonStr = Canvaspp::JsonToStr(json);
  return this->SendJSON(jsonStr);
}

bool Canvaspp::PauseSound(std::string name) {
  if (!this->IsSoundLoaded(name)) {
    throw std::invalid_argument("Sound: " + name + " is not yet loaded.");
  }
  Json json = Output::GetPauseSound(name);
  std::string jsonStr = Canvaspp::JsonToStr(json);
  return this->SendJSON(jsonStr);
}

bool Canvaspp::SetTrackKeyPress(bool track) {
  if (!track) {
    this->keyDownLambda = nullptr;
    this->keyUpLambda = nullptr;
  }
  Json json = Output::GetTrackKeyPress(track);
  std::string jsonStr = Canvaspp::JsonToStr(json);
  return this->SendJSON(jsonStr);
}

void Canvaspp::SetKeyDownHandler(KeyPressLambda keyDownLambda) {
  this->keyDownLambda = keyDownLambda;
}

void Canvaspp::SetKeyUpHandler(KeyPressLambda keyUpLambda) {
  this->keyUpLambda = keyUpLambda;
}

bool Canvaspp::MeasureText(std::string text) {
  std::lock_guard<std::mutex> serverLock(this->measuredTextsMutex);
  this->measuredTexts[text] = -1;
  Json json = Output::GetMeasureText(text);
  std::string jsonStr = Canvaspp::JsonToStr(json);
  return this->SendJSON(jsonStr);
}

int Canvaspp::GetTextMeasurement(std::string text) {
  std::lock_guard<std::mutex> serverLock(this->measuredTextsMutex);
  if (this->measuredTexts.count(text) == 1) {
    return this->measuredTexts.at(text);
  } else {
    return -1;
  }
}

bool Canvaspp::Alert(std::string alert) {
  Json json = Output::GetAlert(alert);
  std::string jsonStr = Canvaspp::JsonToStr(json);
  return this->SendJSON(jsonStr);
}

bool Canvaspp::SetTitle(std::string title) {
  Json json = Output::GetSetTitle(title);
  std::string jsonStr = Canvaspp::JsonToStr(json);
  return this->SendJSON(jsonStr);
}

bool Canvaspp::SetFavicon(std::string href) {
  Json json = Output::GetSetFavicon(href);
  std::string jsonStr = Canvaspp::JsonToStr(json);
  return this->SendJSON(jsonStr);
}

bool Canvaspp::Prompt(std::string key, std::string prompt) {
  std::lock_guard<std::mutex> serverLock(this->promptResponsesMutex);
  this->promptResponses.erase(key);
  Json json = Output::GetPrompt(key, prompt);
  std::string jsonStr = Canvaspp::JsonToStr(json);
  return this->SendJSON(jsonStr);
}

std::pair<bool, std::string> Canvaspp::GetPromptResponse(std::string key) {
  std::lock_guard<std::mutex> serverLock(this->promptResponsesMutex);
  if (this->promptResponses.count(key) == 0) {
    return std::pair<bool, std::string>(false, "");
  }
  return std::pair<bool, std::string>(true, this->promptResponses.at(key));
}

bool Canvaspp::Confirm(std::string key, std::string message) {
  std::lock_guard<std::mutex> serverLock(this->confirmResponsesMutex);
  this->confirmResponses.erase(key);
  Json json = Output::GetConfirm(key, message);
  std::string jsonStr = Canvaspp::JsonToStr(json);
  return this->SendJSON(jsonStr);
}

std::pair<bool, bool> Canvaspp::GetConfirmResponse(std::string key) {
  std::lock_guard<std::mutex> serverLock(this->confirmResponsesMutex);
  if (this->confirmResponses.count(key) == 0) {
    return std::pair<bool, bool>(false, false);
  }
  return std::pair<bool, bool>(true, this->confirmResponses.at(key));
}
