#include <iostream>
#include "helperFunctions.h"
#include "controller.h"
#include "game.h"
#include "renderer.h"
#include "rocket.h"

int main(int argc, char* args[]) {
  constexpr std::size_t kFramesPerSecond{60};
  constexpr std::size_t kMsPerFrame{1000 / kFramesPerSecond};
  constexpr std::size_t kScreenWidth{640};
  constexpr std::size_t kScreenHeight{640};
  constexpr std::size_t kGridWidth{640};
  constexpr std::size_t kGridHeight{640};

  Renderer renderer(kScreenWidth, kScreenHeight, kGridWidth, kGridHeight);
  Controller controller;
 
  int attempt = 0;
  bool replay = true;

  while (replay)
  {
	  attempt++;
	  Game game(kGridWidth, kGridHeight, renderer);
	  game.Run(controller, renderer, kMsPerFrame);

	  if (!game.RepeatEndless) break;

	  std::cout << "-------------------" << std::endl;
	  std::cout << "Press 'R' for Reset" << std::endl;
	  std::cout << std::endl;

	  bool checkRestart = true;
	  while (checkRestart)
	  {
		  bool quit, restart;
		  controller.CheckRestart(restart, quit);
		  if (restart)
		  {
			  checkRestart = false;
			  break;
		  }
		  if (quit)
		  {
			  replay = false;
			  checkRestart = false;
			  break;
		  }
			  
	  }
  }
  std::cout << "Game has terminated successfully!\n";
  return 0;
}
