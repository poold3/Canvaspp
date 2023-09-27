#include <iostream>
#include <string>
#include "Canvaspp.h"

int main() {
  try {
    
    Canvaspp canvaspp;
    canvaspp.Start();
    canvaspp.ShowCanvas();

    std::this_thread::sleep_for(std::chrono::seconds(5));
    canvaspp.StartUpdateMousePosition();
    std::this_thread::sleep_for(std::chrono::seconds(5));
    canvaspp.StopUpdateMousePosition();
    while (canvaspp.GetNumConnections() != 0) {
      
    }
  
    canvaspp.Stop();
    
  } catch(const std::exception& e) {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}