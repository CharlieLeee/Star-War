#include "Buff.h"



Buff::Buff(Texture *texture, Vector2f pos)
{
	this->mult = 62.5f;

	this->shape.setTexture(*texture);

	this->shape.setScale(0.15f, 0.15f);
	this->shape.setOrigin(
		texture->getSize().x / 2,
		texture->getSize().y / 2
	);
	

	this->shape.setPosition(pos);
}


Buff::~Buff()
{
}

void Buff::Update(float speed, const float & dt)
{
	this->shape.move(-speed * mult * dt, 0.f);
	this->shape.rotate(4.f * dt * mult);
}

void Buff::Draw(RenderWindow * window)
{
	window->draw(this->shape);
}
