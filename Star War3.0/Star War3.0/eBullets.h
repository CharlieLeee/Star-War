#pragma once
#include "Bullet.h"

class eBullets
{
public:
	eBullets(Texture *texture, Vector2f pos, Vector2f direction, int ownerID = 0);
	~eBullets();
	Sprite shape;
	Vector2f direction;
	float mult;
	void Move(float speed, const float &dt, int ID);

private:
	int ownerID;

public:
	int getID() const;
};

