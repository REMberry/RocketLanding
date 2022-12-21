#ifndef ROCKET_H
#define ROCKET_H

#define _USE_MATH_DEFINES
#include <cmath>
#include "entity.h"

class Rocket : public Entity
{
public:
    enum class Direction {none,boostUp};
    enum class Rotation {none, left, right};

    Direction boostDirection;
    Rotation  boostRotation;

    Rocket(int grid_width, int grid_height, SDL_Rect frame, SDL_Texture* texture);

    float getHeight() const;
    float getLateral() const;
    float getSpeed() const;

    void setCrash(bool hasCrashed);
    void setLanding(bool hasLanded);

    bool isAlive() const { return this->alive; };
    bool isLandingSpeed();
    bool isLandingAngle();

    SDL_Rect getCollisionBoxAtCurrentPosition();
    void Update();
private:
    Vector2f accelVector;
    Vector2f speedVector;
    Vector2f gravityVector{Vector2f(0,-0.02)};
    

    const float boostAbs = +0.025;
    const float rotationSpeed = 0.4;
    const float landingSpeed = 0.4;
    const float landingAngle = 3;

    bool alive{ true };
    bool landed{ false };

    SDL_Rect collisionBox;
    int grid_width;
    int grid_height;

    Vector2f BoardToGlobalPosition(Vector2f boardPosition);
    void updateTexture();
};
#endif
