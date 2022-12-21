#include "renderer.h"
#include <iomanip>
#include <sstream>
#include <iostream>
#include <string>
#include <vector>


Renderer::Renderer(const std::size_t screen_width,
                   const std::size_t screen_height,
                   const std::size_t grid_width,
                   const std::size_t grid_height)
                    : screen_width(screen_width),
                      screen_height(screen_height),
                      grid_width(grid_width),
                      grid_height(grid_height),
                      sdl_window(NULL),
                      sdl_renderer(NULL)
{
  // Initialize SDL
  if (SDL_Init(SDL_INIT_VIDEO) < 0) {
    std::cerr << "SDL could not initialize.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  if (!(IMG_Init(IMG_INIT_PNG) & IMG_INIT_PNG))
  {
      std::cerr << "SDL_image could not initialize.\n";
      std::cerr << "SDL_Error: " << IMG_GetError() << "\n";
  }
  //if (TTF_Init() < 0)
  //{
  //    std::cerr << "SDL_ttf could not initialize!SDL_ttf Error : % s\n";
  //    std::cerr << "SDL_Error: " << TTF_GetError() << "\n";
  //}



  // Create Window
  sdl_window = SDL_CreateWindow("Rocket Game", SDL_WINDOWPOS_CENTERED,
                                SDL_WINDOWPOS_CENTERED, screen_width,
                                screen_height, SDL_WINDOW_SHOWN);

  if (nullptr == sdl_window) {
    std::cerr << "Window could not be created.\n";
    std::cerr << " SDL_Error: " << SDL_GetError() << "\n";
  }

  // Create renderer
  auto flags = SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC;
  sdl_renderer = SDL_CreateRenderer(sdl_window, -1, SDL_RENDERER_ACCELERATED);
  if (nullptr == sdl_renderer) {
    std::cerr << "Renderer could not be created.\n";
    std::cerr << "SDL_Error: " << SDL_GetError() << "\n";
  }

  // Pixel size
  pixel_block.w = screen_width / grid_width;
  pixel_block.h = screen_height / grid_height;
}

Renderer::~Renderer() {
  SDL_DestroyWindow(sdl_window);
  SDL_Quit();
}

SDL_Texture* Renderer::LoadTexture(const char* p_filePath)
{
    SDL_Texture* texture = NULL;
    texture = IMG_LoadTexture(sdl_renderer, p_filePath);

    if (texture == NULL)
    {
        std::cerr << "Failed to load image! " << IMG_GetError() << std::endl;
    }
    return texture;
}



void Renderer::Render(Entity& rocket, Entity& ground)
{
  // Clear screen
  SDL_RenderClear(sdl_renderer);

  RenderEntity(ground);
  RenderEntity(rocket);
  
  SDL_RenderPresent(sdl_renderer);
}

void Renderer::UpdateWindowTitle(int score, int fps, float speed)
{
    std::stringstream stream;
    stream << std::fixed << std::setprecision(2) << speed;

    std::string title
    {
       "Rocket Height: " + std::to_string(score) +
       " Speed: " + stream.str() +
       " FPS: " + std::to_string(fps)
    };
     SDL_SetWindowTitle(sdl_window, title.c_str());
}

void Renderer::RenderEntity(Entity& entity)
{
    SDL_Rect src;
    src.x = entity.getCurrentFrame().x;
    src.y = entity.getCurrentFrame().y;
    src.w = entity.getCurrentFrame().w;
    src.h = entity.getCurrentFrame().h;

    SDL_Rect dst;
    dst.x = entity.getPos().x * pixel_block.w;
    dst.y = entity.getPos().y * pixel_block.h;
    dst.w = entity.getCurrentFrame().w * pixel_block.w;
    dst.h = entity.getCurrentFrame().h * pixel_block.h;

    SDL_Texture* texture = entity.getTexture();

    double angle = entity.getAngle();

    SDL_RenderCopyEx(sdl_renderer, texture, &src, &dst, angle, NULL, SDL_FLIP_NONE);
}
void Renderer::ShowMessagebox()
{
    SDL_ShowSimpleMessageBox(SDL_MESSAGEBOX_INFORMATION, "Result", "test", this->sdl_window);
}
/*
void Renderer::WriteToBoard()
{
    TTF_Font* Sans = TTF_OpenFont("C:/Windows/Fonts/Arial.ttf", 14);
    TTF_CloseFont(Sans);
    SDL_Color White = { 255, 255, 255 };
    SDL_Surface* surfaceMessage =
        TTF_RenderText_Solid(Sans, "put your text here", White);
    SDL_Texture* Message = SDL_CreateTextureFromSurface(sdl_renderer, surfaceMessage);
    SDL_Rect Message_rect; //create a rect
    Message_rect.x = 0;  //controls the rect's x coordinate 
    Message_rect.y = 0; // controls the rect's y coordinte
    Message_rect.w = 400; // controls the width of the rect
    Message_rect.h = 400; // controls the height of the rect
    SDL_RenderCopy(sdl_renderer, Message, NULL, &Message_rect);
    SDL_FreeSurface(surfaceMessage);
    SDL_DestroyTexture(Message);
}
*/
