#include <iostream>
#include <string>
#include "Canvaspp.h"

MouseClickLambda mouseClickHandler = [](MouseClick click) {
  std::cout << click.x << ", " << click.y << std::endl;
};

int main() {
  try {
    
    Canvaspp canvaspp;
    canvaspp.Start();
    canvaspp.ShowCanvas();
    
    canvaspp.SetTrackMouseClick(true);

    std::this_thread::sleep_for(std::chrono::seconds(5));

    canvaspp.SetMouseClickHandler(mouseClickHandler);

    std::this_thread::sleep_for(std::chrono::seconds(5));

    canvaspp.SetTrackMouseClick(false);


    while (canvaspp.GetNumConnections() != 0) {
      
    }
  
    canvaspp.Stop();
    
  } catch(const std::exception& e) {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}