#include "ground.h"
#include <vector>
#include <SDL.h>

Ground::Ground(int grid_width, int grid_height, SDL_Rect frame, SDL_Texture* texture, std::vector<int> collisionLine)
	: Entity(Vector2f(0, 0), frame, texture)
{
	this->collisionLine = collisionLine;
	this->grid_height = grid_height;
	this->grid_width = grid_width;
}
std::vector<int>& Ground::getCollisionLine()
{
	return this->collisionLine;
}
const SDL_Rect Ground::getCollisionBoxAtPosition(float xPosition)
{
	SDL_Rect result = { 0,0,0,0 };
	int xIndex = 0;

	xIndex = (int)xPosition;
	if (xIndex < 0)
		xIndex = 0;
	if (xIndex >= collisionLine.size())
		xIndex = collisionLine.size() - 1;

	try
	{
		result.x = xIndex;
		result.y = grid_height - collisionLine[xIndex];
		result.w = 1;
		result.h = 1;
	}
	catch (const std::exception&)
	{
		std::cerr << "Error while indexing vector!";
	}



	return result;
}
SDL_Rect const Ground::getCollisionBoxForLanding()
{
	SDL_Rect landingBox{ 0,0,0,0 };
	landingBox.x = 293;
	landingBox.y = grid_height- collisionLine[293] - 5;
	landingBox.w = 33;
	landingBox.h = 10;
	return landingBox;
}

void Ground::Update()
{

}
