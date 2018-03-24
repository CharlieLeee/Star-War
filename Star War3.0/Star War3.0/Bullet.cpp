#include "Bullet.h"

Bullet::Bullet(Texture *texture, Vector2f pos, Vector2f maxV, Vector2f acceleration)
{
	this->shape.setTexture(*texture);

	this->shape.setScale(0.07f, 0.07f);
	this->shape.setPosition(pos);

	this->currentV = Vector2f(1.f, 0.f);
	this->maxV = maxV;
	this->acceleration = acceleration;

	this->mult = 62.5f;
}


void Bullet::Move(const float & dt)
{
	if (currentV.x < this->maxV.x)
	{
		currentV.x += acceleration.x * dt * mult;
	}

	if (abs(currentV.y) < abs(this->maxV.y))
	{

		currentV.y += acceleration.y * dt * mult;

	}

	this->shape.setRotation(atan2(this->currentV.y, this->currentV.x) * 180 / 3.14159265359);
	this->shape.move(currentV * dt * mult);
}

Bullet::~Bullet()
{
}
