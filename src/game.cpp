#include "game.h"
#include <iostream>
#include "SDL.h"
#include "helperFunctions.h"

Game::Game(std::size_t grid_width, std::size_t grid_height, Renderer& renderer)
       :rocket(grid_width, grid_height, SDL_Rect{ 0, 0, 22, 40 },
        renderer.LoadTexture("res/gfx/rocketAnimation640.png")),
        ground(grid_width, grid_height, SDL_Rect{ 0,0,640,640 },
        renderer.LoadTexture("res/gfx/ground640.png"),
        readCsv("res/ground.csv")),
        engine(dev())
{   
}

void Game::Run(Controller const &controller, Renderer &renderer,
               std::size_t target_frame_duration) {
  Uint32 title_timestamp = SDL_GetTicks();
  Uint32 frame_start;
  Uint32 frame_end;
  Uint32 frame_duration;
  int frame_count = 0;
  running = true;
  result = eConditions::None;

  while (running) {
    frame_start = SDL_GetTicks();

    // Game Loop
    controller.HandleInput(running, this->RepeatEndless ,rocket);
    Update();
    renderer.Render(rocket, ground);


    // Count time    
    frame_end = SDL_GetTicks();
    frame_count++;

    // Update window title
    if (frame_end - title_timestamp >= 1000) {
      renderer.UpdateWindowTitle(rocket.getHeight(), frame_count, rocket.getSpeed()*frame_count);
      frame_count = 0;
      title_timestamp = frame_end;
    }

    //frame_end = SDL_GetTicks();
    frame_duration = frame_end - frame_start;

    if (frame_duration < target_frame_duration) {
      SDL_Delay(target_frame_duration - frame_duration);
    }
  }
}

bool Game::CheckCollision(Rocket& rocket, Ground& ground)
{
    bool result;
    SDL_Rect rocketBox = rocket.getCollisionBoxAtCurrentPosition();
    SDL_Rect groundBox = ground.getCollisionBoxAtPosition(rocketBox.x);
    SDL_bool collision = SDL_HasIntersection(&rocketBox, &groundBox);

    result = collision == SDL_bool::SDL_TRUE;

    return result;
}
bool Game::CheckLanding()
{
    bool landingComplete = false;
    bool speedOk = false;
    bool angleOk = false;
    bool spaceOk = false;

    SDL_Rect rocketBox;
    SDL_Rect groundBox;

    //check speed
    speedOk = rocket.isLandingSpeed();
    //check angle
    angleOk = rocket.isLandingAngle();
    //check position
    rocketBox = rocket.getCollisionBoxAtCurrentPosition();
    groundBox = ground.getCollisionBoxForLanding();
    spaceOk = SDL_HasIntersection(&rocketBox, &groundBox);

    landingComplete = speedOk && angleOk && spaceOk;

    if(landingComplete)
        std::cout << "Rocket has landed correctly!" << std::endl;
    else
        std::cout << "Rocket is damaged!" << std::endl;

    if (!speedOk)
        std::cout << "Rocket speed was to high!" << std::endl;

    if (!angleOk)
        std::cout << "Rocket angle was out of range!" << std::endl;

    if (!spaceOk)
        std::cout << "Missed the landing area!" << std::endl;

    return landingComplete;
}

void Game::Update() {
    //if (!rocket.alive) return;
    
    rocket.Update();
    ground.Update();

    if (CheckCollision(rocket, ground))
    {
        if (CheckLanding())
        {
            rocket.setLanding(true);
            running = false;
        }
        else
        {
            rocket.setCrash(true);
            running = false;
        }
    }
}

int Game::GetHeight() const { return rocket.getHeight(); }