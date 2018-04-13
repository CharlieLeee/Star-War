#include "Boss.h"



Boss::Boss(float speed, Texture *texture, int HP, Vector2u windowsize)
	:texture(texture),
	InitPos(windowsize.x + this->shape.getGlobalBounds().width, windowsize.y / 2),
	HP(HP),
	Center(texture->getSize().x / 2, texture->getSize().y / 2),
	moveTimer(0.f),
	mult(62.5f)
{
	this->shape.setTexture(*texture);
	this->shape.setOrigin(Center);

	this->shape.setPosition(this->InitPos);
	this->shape.setPosition(InitPos);
	this->shape.setScale(0.5f, 0.5f);
	
	this->mult = 62.5f;
	this->enterScene = false;
	this->speed = -speed;
	this->shootTimer = 0.f;
	this->shootTimerMax = 1.5f;

	// Boss hp bar
	// Init HP Bar
	this->bossHP.setFillColor(Color::Blue);
}


Boss::~Boss()
{
}

void Boss::Movement(RenderWindow * window, const float & dt)
{
	this->moveTimer += dt;
	
	if (this->shape.getPosition().x > window->getSize().x - this->shape.getGlobalBounds().width)
	{
		this->shape.move(-2.5 * dt * mult, 0.f);
	}
	else
	{
		this->shape.move(speed, 3 * sin(this->moveTimer) * dt * mult);
	}

	if (this->shape.getPosition().x < window->getSize().x / 2)
	{
		this->speed = 0;
	}
}

void Boss::Update(RenderWindow *window, const float & dt)
{
	this->Movement(window, dt);
	this->bossHP.setSize(Vector2f(5.f, 20.f * this->HP));
	this->bossHP.setPosition(this->shape.getPosition().x + 240.f, this->shape.getPosition().y - this->shape.getGlobalBounds().height / 2);
}

void Boss::Draw(RenderWindow *window)
{
	window->draw(this->shape);
	window->draw(this->bossHP);
}
