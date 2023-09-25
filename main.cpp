#include <iostream>
#include <string>
#include "Canvaspp.h"



int main() {
  try {
    
    Canvaspp canvaspp;
    canvaspp.Start();
    canvaspp.ShowCanvas();
    //std::this_thread::sleep_for(std::chrono::seconds(10));
    
    //canvaspp.ShutDown();
    
  } catch(const std::exception& e) {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}