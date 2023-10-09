#include <iostream>
#include <string>
#include <chrono>
#include "Canvaspp.h"
#include "CtxCommandBuilder.h"

MouseClickLambda mouseDownHandler = [](MouseClick click) {
  std::cout << "DOWN: " << click.x << " " << click.y << std::endl;
};

MouseClickLambda mouseUpHandler = [](MouseClick click) {
  std::cout << "UP: " << click.x << " " << click.y << std::endl;
};

KeyPressLambda keyDownHandler = [](std::string code) {
  std::cout << "DOWN: " << code << std::endl;
};

KeyPressLambda keyUpHandler = [](std::string code) {
  std::cout << "UP: " << code << std::endl;
};

int main() {
  try {
    Canvaspp canvaspp;
    canvaspp.Start();
    canvaspp.ShowCanvas();
    
    canvaspp.SetTrackMousePosition(true);
    canvaspp.SetTrackMouseClick(true);
    canvaspp.SetTrackKeyPress(true);
    canvaspp.SetMouseUpHandler(mouseUpHandler);
    canvaspp.SetMouseDownHandler(mouseDownHandler);
    canvaspp.SetKeyUpHandler(keyUpHandler);
    canvaspp.SetKeyDownHandler(keyDownHandler);
    
    canvaspp.AddImage("main_1", "references/main_1.png");
    canvaspp.AddImage("main_2", "references/main_2.png");
    canvaspp.AddImage("main_3", "references/main_3.png");
    canvaspp.AddImage("main_4", "references/main_4.png");
    canvaspp.AddImage("main_5", "references/main_5.png");
    canvaspp.AddSound(Sound("softPiano", "references/soft_piano_trimmed.mp3", true));
    std::string images[5] = {"main_1", "main_2", "main_3", "main_4", "main_5"};
    int numImages = 5;
    std::this_thread::sleep_for(std::chrono::seconds(5));
    while (!canvaspp.IsSoundLoaded("softPiano")) {

    }
    canvaspp.PlaySound("softPiano");

    while (!canvaspp.IsImageLoaded("main_1") || !canvaspp.IsImageLoaded("main_2") || !canvaspp.IsImageLoaded("main_3") || !canvaspp.IsImageLoaded("main_4") || !canvaspp.IsImageLoaded("main_5")) {

    }

    CtxCommandBuilder commandBuilder;
    int currentImage = 0;
    
    while (canvaspp.HasConnections()) {
      std::this_thread::sleep_for(std::chrono::milliseconds(75));
      
      if (currentImage == numImages) {
        currentImage = 0;
      }
      commandBuilder.Clear();
      Dimensions dimensions = canvaspp.GetDimensions();
      commandBuilder.clearRect(0, 0, dimensions.width, dimensions.height);
      commandBuilder.drawImage(images[currentImage], 0, 0, dimensions.width, dimensions.height);
      canvaspp.SendCtxCommand(commandBuilder.ToString());
      ++currentImage;
      
    }
  
    canvaspp.Stop();
  } catch(const std::exception& e) {
    std::cerr << e.what() << std::endl;
  }

  return 0;
}