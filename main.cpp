#include <iostream>
#include <string>
#include "Canvaspp.h"

int main() {
  try {
    
    Canvaspp canvaspp;
    canvaspp.Start();
    canvaspp.ShowCanvas();

    while (canvaspp.GetNumConnections() != 0) {
      
    }
  
    canvaspp.Stop();
    
  } catch(const std::exception& e) {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}