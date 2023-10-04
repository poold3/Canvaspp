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
    canvaspp.AddImage("BeachLogo", "references/BeachLogo.PNG");
    while (!canvaspp.IsImageLoaded("BeachLogo")) {

    }
    
    ctxBuilder.drawImage("BeachLogo", 0, 0);
    canvaspp.SendCtxCommand(ctxBuilder.ToString());
    ctxBuilder.Clear();
    while (canvaspp.GetNumConnections() != 0) {
      
    }
  
    canvaspp.Stop();
  } catch(const std::exception& e) {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}