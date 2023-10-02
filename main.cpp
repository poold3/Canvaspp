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
    ctxBuilder.fillStyle(Color(100,100,100));
    int x = 50;
    int y = 50;
    ctxBuilder.fillRect(x,y,100,100);

    Canvaspp canvaspp;
    canvaspp.Start();
    canvaspp.ShowCanvas();
    std::this_thread::sleep_for(std::chrono::seconds(5));
    canvaspp.SendCtxCommand(ctxBuilder.ToString());
    ctxBuilder.Clear();
    Dimensions dimensions = canvaspp.GetDimensions();
    auto start = std::chrono::high_resolution_clock::now();

    while (canvaspp.GetNumConnections() != 0) {
      auto current = std::chrono::high_resolution_clock::now();
      std::chrono::milliseconds milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(current - start);
      if (milliseconds.count() >= 10) {
        ctxBuilder.Clear();
        x += 1;
        y += 1;
        ctxBuilder.clearRect(0,0,dimensions.width,dimensions.height);
        ctxBuilder.fillRect(x,y,100,100);
        canvaspp.SendCtxCommand(ctxBuilder.ToString());
        start = std::chrono::high_resolution_clock::now();
      }
    }
  
    canvaspp.Stop();
  } catch(const std::exception& e) {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}