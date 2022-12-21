#ifndef RENDERER_H
#define RENDERER_H

#include <vector>
#include <SDL_image.h>
#include <SDL.h>
#include "rocket.h"



class Renderer {
 public:
  Renderer(const std::size_t screen_width, const std::size_t screen_height,
           const std::size_t grid_width, const std::size_t grid_height);
  ~Renderer();

  void Clear();
  void WriteToBoard();
  void Render(Entity& rocket, Entity& ground);
  void UpdateWindowTitle(int score, int fps, float speed);
  void ShowMessagebox();

  SDL_Texture* LoadTexture(const char* p_filePath);

 private:
  SDL_Window *sdl_window;
  SDL_Renderer *sdl_renderer;
  SDL_Rect pixel_block;

  const std::size_t screen_width;
  const std::size_t screen_height;
  const std::size_t grid_width;
  const std::size_t grid_height;

  void RenderEntity(Entity& entity);
};

#endif
