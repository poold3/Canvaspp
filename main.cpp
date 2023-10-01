#include <iostream>
#include <string>
#include "Canvaspp.h"
#include "CtxCommandBuilder.h"

MouseClickLambda mouseClickHandler = [](MouseClick click) {
  std::cout << click.x << ", " << click.y << std::endl;
};

int main() {
  try {
    
    /*
    Canvaspp canvaspp;
    canvaspp.Start();
    canvaspp.ShowCanvas();

    while (canvaspp.GetNumConnections() != 0) {
      
    }
  
    canvaspp.Stop();
    */
    CtxCommandBuilder ctxBuilder;
    ctxBuilder.textAlign("right").lineCap("square").font("bold 48px serif").lineWidth(15);
    std::cout << ctxBuilder.ToString() << std:: endl;
    ctxBuilder.Clear();
    std::cout << ctxBuilder.ToString() << std:: endl;
  } catch(const std::exception& e) {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}