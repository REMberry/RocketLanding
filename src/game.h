#ifndef GAME_H
#define GAME_H

#include <random>
#include "SDL.h"
#include "controller.h"
#include "renderer.h"
#include "rocket.h"
#include "ground.h"

class Game {
 public:
  enum class eConditions {None = 0, Landed = 1, BadPosition = 2, BadAngle = 4, BadSpeed = 8};


  Game(std::size_t grid_width, std::size_t grid_height, Renderer &renderer);
  void Run(Controller const &controller, Renderer &renderer,
           std::size_t target_frame_duration);
  int GetHeight() const;
  bool CheckCollision(Rocket& rocket, Ground& ground);
  bool CheckLanding();
  bool RepeatEndless{ true };

 private:
  bool running = false;

  Ground ground;
  Rocket rocket;
  SDL_Point food;

  eConditions result;

  std::random_device dev;
  std::mt19937 engine;
  std::uniform_int_distribution<int> random_w;
  std::uniform_int_distribution<int> random_h;

  void Update();
};

#endif