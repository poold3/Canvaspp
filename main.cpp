#include <iostream>
#include <string>
#include <chrono>
#include "Canvaspp.h"
#include "CtxCommandBuilder.h"

MouseClickLambda mouseClickHandler = [](MouseClick click) {
  std::cout << click.x << ", " << click.y << std::endl;
};

int main() {
  try {
    CtxCommandBuilder ctxBuilder;

    Canvaspp canvaspp;
    canvaspp.Start();
    canvaspp.ShowCanvas();
    std::this_thread::sleep_for(std::chrono::seconds(5));
    canvaspp.AddSound(Sound("Piano", "references/soft_piano_trimmed.mp3"));
    canvaspp.AddSound(Sound("PianoLoop", "references/soft_piano_trimmed.mp3", true));
    while (!canvaspp.IsSoundLoaded("Piano")) {

    }
    canvaspp.PlaySound("Piano");
    std::this_thread::sleep_for(std::chrono::seconds(5));
    canvaspp.PauseSound("Piano");
    canvaspp.PlaySound("PianoLoop", 10);
    while (canvaspp.GetNumConnections() != 0) {
      
    }
  
    canvaspp.Stop();
  } catch(const std::exception& e) {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}