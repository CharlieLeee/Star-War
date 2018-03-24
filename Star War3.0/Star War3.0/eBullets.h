#pragma once
#include "Bullet.h"

class eBullets
{
public:
	eBullets(Texture *texture, Vector2f pos, Vector2f direction);
	~eBullets();
	Sprite shape;
	Vector2f direction;
	float mult;
	void Move(float speed, const float &dt);
};

