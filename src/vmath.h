#pragma once
#include <iostream>
#define _USE_MATH_DEFINES // for C++
#include <math.h>

struct Vector2f
{
	static Vector2f getVectorFromAbsAngle(float abs, float angle)
	{
		Vector2f temp = { 0,0 };
		temp.x = sin(angle * M_PI / 180) * abs;
		temp.y = cos(angle * M_PI / 180) * abs;
		return temp;
	}
	Vector2f() :
		x(0.0f), y(0.0f) {};
	Vector2f(float p_x, float p_y)
		:x(p_x), y(p_y) {};
	void print()
	{
		std::cerr << x << ", " << y << std::endl;
	}
	float getAbs() const
	{
		return sqrt(x * x + y * y);
	}

	Vector2f operator+ (Vector2f& first)
	{
		Vector2f res;
		res.x = this->x + first.x;
		res.y = this->y + first.y;
		return res;
	}

	float x, y;
};

