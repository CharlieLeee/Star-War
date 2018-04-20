#include "Enemy.h"

Enemy::Enemy(Texture *texture, Vector2u windowSize, float maxV)
	:acceleration(0.7f),
	drag(0.1f),
	maxV(maxV),
	currentV(0.f, 0.f),
	mult(62.5f)
{	
	this->bulletTimer = 0.f;
	
	this->HPMax = rand()%3 + 1;
	
	this->HP = HPMax;
	this->texture = texture;
	this->shape.setTexture(*texture);

	this->shape.setScale(0.44f, 0.44f);
	
	this->range = windowSize.y - this->shape.getGlobalBounds().height;

	this->shape.setPosition(windowSize.x, rand()%this->range);

	this->ehpBack.setSize(Vector2f(this->HPMax * 20.f, 5.f));
	this->ehpBack.setFillColor(Color(159, 159, 159, 120));
	this->ehp.setFillColor(Color(32, 164, 212, 140));
}

Enemy::~Enemy(){}

void Enemy::UpdateHP()
{
	this->ehpBack.setPosition(this->shape.getPosition().x, this->shape.getPosition().y - ehp.getGlobalBounds().height);

	this->ehp.setSize(Vector2f(this->HP * 20.f, 5.f));

	this->ehp.setPosition(this->shape.getPosition().x, this->shape.getPosition().y - ehp.getGlobalBounds().height);
}

void Enemy::Move(float dt)
{
	Vector2f direction(-1.0f, 0.f);

	// Acceleration
	if (abs(currentV.x) < this->maxV)
	{
		currentV.x += acceleration * direction.x * dt * mult;
		//std::cout << currentV.x << std::endl;
	}

	// Drag
	if (currentV.x < 0.f)
	{
		currentV.x += drag * dt * mult;
		if (currentV.x > 0.f)
		{
			currentV.x = 0;
		}
	}
	
	
	this->shape.move(currentV.x * dt * this->mult, 0);
}

void Enemy::Draw(RenderWindow & window)
{
	// Draw enemy sprite
	window.draw(this->shape);

	window.draw(this->ehpBack);
	// Draw HP bar
	window.draw(this->ehp);
}

void Enemy::Update(float dt)
{
	this->Move(dt);
	this->UpdateHP();
}



