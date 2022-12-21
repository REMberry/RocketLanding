#include "entity.h"

Entity::Entity(Vector2f p_pos, SDL_Rect frame, SDL_Texture* p_texture)
:pos(p_pos), texture(p_texture), angle(0), currentFrame(frame)
{

}
Entity::~Entity()
{
	if (this->texture != NULL)
	{
		SDL_DestroyTexture(this->texture);
	}
}
void Entity::setFrame(SDL_Rect frame)
{
	this->currentFrame = frame;
}
Vector2f& Entity::getPos()
{
	return this->pos;
}
SDL_Texture* Entity::getTexture()
{
	return this->texture;
}
SDL_Rect Entity::getCurrentFrame()
{
	return this->currentFrame;
}
float Entity::getAngle()
{
	return this->angle;
}

void Entity::init()
{

}

