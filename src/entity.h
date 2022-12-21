#pragma once
#include <SDL.h>
#include <SDL_image.h>
#include "vmath.h"

class Entity
{
public:
	Entity(Vector2f p_pos, SDL_Rect frame, SDL_Texture* p_texture);
	~Entity();
	void setFrame(SDL_Rect frame);
	Vector2f& getPos();
	SDL_Texture* getTexture();
	SDL_Rect getCurrentFrame();
	float getAngle();
	void init();

protected:
	SDL_Rect currentFrame;
	SDL_Texture* texture;

	Vector2f pos;
	float angle;
};

