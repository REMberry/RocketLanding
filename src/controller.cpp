#include "controller.h"
#include <iostream>
#include "SDL.h"
#include "rocket.h"

Controller::Controller()
{
}

void Controller::ChangeBoost(Rocket &rocket, Rocket::Direction input) const
{
    rocket.boostDirection = input;
    return;
}
void Controller::ChangeRotation(Rocket& rocket, Rocket::Rotation input) const
{
    rocket.boostRotation = input;
    return;
}
void Controller::CheckRestart(bool &restart, bool &quit) const
{
    restart = false;
    quit = false;
    SDL_Event e;
    while (SDL_PollEvent(&e))
    {
        if (e.type == SDL_QUIT)
        {
            quit = true;
        }
        else if (e.type == SDL_KEYDOWN && e.key.keysym.sym == SDLK_r)
        {
            restart = true;
        }
    }
}
void Controller::HandleInput(bool &running, bool &endlessRepeat, Rocket &rocket) const
{
  SDL_Event e;
  while (SDL_PollEvent(&e))
  {
    if (e.type == SDL_QUIT)
    {
      endlessRepeat = false;
      running = false;
    }
    else if (e.type == SDL_KEYUP)
    {
        switch (e.key.keysym.sym)
        {
        case SDLK_UP:
            ChangeBoost(rocket, Rocket::Direction::none);
            break;

        case SDLK_DOWN:

            break;

        case SDLK_LEFT:
            ChangeRotation(rocket, Rocket::Rotation::none);
            break;

        case SDLK_RIGHT:
            ChangeRotation(rocket, Rocket::Rotation::none);
            break;
        }
    }
    else if (e.type == SDL_KEYDOWN)
    {
        switch (e.key.keysym.sym)
      {
        case SDLK_UP:
            ChangeBoost(rocket, Rocket::Direction::boostUp);
          break;

        case SDLK_DOWN:
          //ChangeDirection(rocket, Rocket::Direction::boostUp);
          break;

        case SDLK_LEFT:
            ChangeRotation(rocket, Rocket::Rotation::left);
            break;

        case SDLK_RIGHT:
            ChangeRotation(rocket, Rocket::Rotation::right);
            break;
      }
    }
  }
}