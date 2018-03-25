#include "eBullets.h"



eBullets::eBullets(Texture *texture, Vector2f pos, Vector2f direction)
{
	this->shape.setTexture(*texture);

	this->shape.setScale(0.05f, 0.04f);
	this->shape.setPosition(pos);
	this->direction = direction;
	this->mult = 62.5f;
}


eBullets::~eBullets()
{
}

void eBullets::Move(float speed, const float & dt)
{
	this->shape.move(this->direction.x * speed * dt * mult, this->direction.y * speed * dt * mult);
	if (this->direction.x != 0.f && this->direction.y != 0.f)
	{
		this->shape.setRotation(180.f + atan2(this->direction.y, this->direction.x) * 180 / 3.14159265359);
	}
}
