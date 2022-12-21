#pragma once
#include "entity.h"
#include <vector>
#include <SDL.h>

class Ground : public Entity
{
public:
	Ground(int grid_width, int grid_height, SDL_Rect frame, SDL_Texture* texture, std::vector<int> collisionLine);
	void Update();
	std::vector<int>& getCollisionLine();
	SDL_Rect const getCollisionBoxAtPosition(float xPosition);
	SDL_Rect const getCollisionBoxForLanding();

private:
	int grid_height;
	int grid_width;
	std::vector<int> collisionLine;
};

