#include <string>
#include <iostream>
#include "rocket.h"
#include <SDL.h>
#define _USE_MATH_DEFINES // for C++
#include <vmath.h>

Rocket::Rocket(int grid_width, int grid_height, SDL_Rect frame, SDL_Texture* texture)
    : Entity(Vector2f(0,0), frame, texture)
{
    // init base class
    Entity::pos.x = 0.2f * grid_width;
    Entity::pos.y = 0.2f * grid_height;
    Entity::angle = 45;

    // init variable
    this->landed = false;
    this->alive = true;
    this->grid_height = grid_height;
    this->grid_width = grid_width;
    this->speedVector = { 0,0 };
    this->accelVector = { 0,0 };
    this->boostDirection = Direction::none;
    this->collisionBox = SDL_Rect{6,3,10,27};
	return;
}
SDL_Rect Rocket::getCollisionBoxAtCurrentPosition() 
{
    SDL_Rect result = { 0,0,0,0 };

    result.x = Entity::getPos().x + this->collisionBox.x;
    result.y = Entity::getPos().y + this->collisionBox.x;
    result.w = this->collisionBox.w;
    result.h = this->collisionBox.h;
    return result;
}
float Rocket::getSpeed() const
{
    float abs = this->speedVector.getAbs();
    return abs;
}
float Rocket::getHeight() const
{
    return grid_height - Entity::pos.y;
}
float Rocket::getLateral() const
{
    return Entity::pos.x;
}
void Rocket::setCrash(bool hasCrashed)
{
    this->alive = !hasCrashed;
    updateTexture();
}
void Rocket::setLanding(bool hasLanded)
{
    this->landed = true;
    updateTexture();
}
bool Rocket::isLandingSpeed()
{
    return (this->getSpeed() < this->landingSpeed);
}
bool Rocket::isLandingAngle()
{
    return (Entity::angle < this->landingAngle&&
        Entity::angle > -this->landingAngle);
}

void Rocket::updateTexture()
{
    int width = Entity::currentFrame.w;
    int height = Entity::currentFrame.h;
    Direction dir = this->boostDirection;
    Rotation rot = this->boostRotation;

    if (this->alive == false)
    {
        setFrame(SDL_Rect{ width * 6 , 0, width, height });
        return;
    }

    if (dir == Direction::boostUp)
    {
        if (rot == Rotation::left)
        {
            setFrame(SDL_Rect{ width * 3 , 0, width, height });
        }
        if (rot == Rotation::right)
        {
            setFrame(SDL_Rect{ width * 2, 0, width, height });
        }
        if (rot == Rotation::none)
        {
            setFrame(SDL_Rect{ width, 0, width, height });
        }
    }
    if (dir == Direction::none)
    {
        if (rot == Rotation::left)
        {
            setFrame(SDL_Rect{ width * 5, 0, width, height });
        }
        if (rot == Rotation::right)
        {
            setFrame(SDL_Rect{ width * 1, 0, width, height });
        }
        if (rot == Rotation::none)
        {
            setFrame(SDL_Rect{ 0, 0, width, height });
        }
    }
    return;
}

void Rocket::Update()
{
    if (this->alive == false)
    {
        updateTexture();
        return;
    }

    // calculate angle
    Entity::angle = Entity::angle + 0.6*this->rotationSpeed * sin(Entity::angle * M_PI / 180);

    if (this->boostRotation == Rotation::left)
    {
        Entity::angle = Entity::angle - this->rotationSpeed;
       
    }
    if (this->boostRotation == Rotation::right)
    {
        Entity::angle = Entity::angle + this->rotationSpeed;
    }

    Vector2f boardPosition = { this->getLateral(), this->getHeight() };
    Vector2f accelerationVector = { 0,0 };
    Vector2f boostVector = Vector2f::getVectorFromAbsAngle(boostAbs, Entity::angle);


    // calculate acceleration
    accelerationVector = accelerationVector + gravityVector;

    // add friction
    if (speedVector.y < 0)
    {
        accelerationVector.y = accelerationVector.y - 0.01 * speedVector.y;
    }


    if (this->boostDirection == Direction::boostUp)
    {
        accelerationVector = accelerationVector + boostVector;
    }

    // calc speed
    this->speedVector = speedVector + accelerationVector;
    
    
    // calc position
    boardPosition = boardPosition + speedVector;

    // position ends?
    if (boardPosition.y <= 0 + Entity::currentFrame.h)
    {
        boardPosition.y = 0 + Entity::currentFrame.h;
        speedVector = { 0,0 };
    }

    // check position
    if (boardPosition.x > grid_width - 1)
        boardPosition.x = 0;

    if (boardPosition.x < 0)
        boardPosition.x = grid_width - 1;

    Entity::pos = BoardToGlobalPosition(boardPosition);

    updateTexture();
   
}
Vector2f Rocket::BoardToGlobalPosition(Vector2f boardPosition)
{
    boardPosition.y = this->grid_height - boardPosition.y;
    return boardPosition;
}
