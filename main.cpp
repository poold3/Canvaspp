#include <iostream>
#include <string>
#include "Canvaspp.h"

int main() {
  try {
    
    Canvaspp canvaspp;
    canvaspp.Start();
    canvaspp.ShowCanvas();

    std::this_thread::sleep_for(std::chrono::seconds(5));
    canvaspp.SetUpdateMousePosition(true);
    std::this_thread::sleep_for(std::chrono::seconds(5));
    std::cout << canvaspp.IsMousePositionCurrent() << std::endl;
    canvaspp.SetUpdateMousePosition(false);
    std::cout << canvaspp.IsMousePositionCurrent() << std::endl;
    while (canvaspp.GetNumConnections() != 0) {
      
    }
  
    canvaspp.Stop();
    
  } catch(const std::exception& e) {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}