#include "Boss.h"



Boss::Boss(float speed,  Texture *texture, int HP, Vector2u windowsize)
{
	this->texture = texture;
	this->size = Vector2f(texture->getSize().x / 2, texture->getSize().y / 2);
	this->shape.setTexture(*texture);
	this->shape.setOrigin(size);

	this->InitPos = Vector2f(windowsize.x + this->shape.getGlobalBounds().width, windowsize.y / 2);
	this->shape.setPosition(this->InitPos);
	this->shape.setPosition(InitPos);
	this->shape.setScale(0.5f, 0.5f);
	this->HP = HP;
	
	this->moveTimer = 0.f;
	this->mult = 62.5f;
	this->enterScene = false;
	this->speed = -speed;
	this->shootTimer = 0.f;
	this->shootTimerMax = 1.5f;
}


Boss::~Boss()
{
}

void Boss::Movement(RenderWindow * window, const float & dt)
{
	this->moveTimer += dt;
	//std::cout << moveTimer << std::endl;
	if (this->shape.getPosition().x > window->getSize().x - this->shape.getGlobalBounds().width)
	{
		this->shape.move(-2.5 * dt * mult, 0.f);
	}
	else
	{
		this->shape.move(speed, 3* sin(this->moveTimer) * dt * mult);
	}

	if (this->shape.getPosition().x < window->getSize().x / 2 )
	{
		this->speed = 0;
	}
}

void Boss::Draw(RenderWindow * window)
{
	window->draw(this->shape);
}
