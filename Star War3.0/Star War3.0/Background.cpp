#include "Background.h"



Background::Background(Texture *targetTex, RenderWindow *window)
{
	this->backgroundTex = targetTex;
	this->backSprite.setTexture(*this->backgroundTex);

	// Fill the screen
	float scale1 = window->getSize().x / (this->backSprite.getGlobalBounds().width);

	float scale2 = window->getSize().y / this->backSprite.getGlobalBounds().height;

	this->backSprite.setScale(Vector2f(scale1, scale2));
	this->backSprite.setPosition(0.f, 0.f);

	this->mult = 62.5f;
	this->scrollSpeed = Vector2f(-10.f, 0.f);

	this->movingBack1Shape.setTexture(*targetTex);
	this->movingBack2Shape.setTexture(*targetTex);

	this->movingBack1Shape.setScale(Vector2f(scale1, scale2));
	this->movingBack2Shape.setScale(Vector2f(scale1, scale2));

	this->movingBack1Shape.setPosition(0.f, 0.f);
	//std::cout << this->movingBack1Shape.getPosition().x << std::endl;
	this->movingBack2Shape.setPosition(this->movingBack1Shape.getGlobalBounds().width, 0.f);
	//std::cout << this->movingBack2Shape.getPosition().x << std::endl;
}



Background::~Background()
{
}

void Background::UpdateMovingBack(RenderWindow * window, float dt, Vector2f scrollSpeed)
{
	this->scrollSpeed = scrollSpeed;
	
	this->movingBack1Shape.move(this->scrollSpeed.x * dt * mult, 0.f);
	this->movingBack2Shape.move(this->scrollSpeed.x * dt * mult, 0.f);

	if (this->movingBack1Shape.getPosition().x + this->movingBack1Shape.getGlobalBounds().width < 0)
	{
		this->movingBack1Shape.setPosition(this->movingBack2Shape.getPosition().x + this->movingBack2Shape.getGlobalBounds().width, 0.f);
	}

	if (this->movingBack2Shape.getPosition().x + this->movingBack2Shape.getGlobalBounds().width < 0)
	{
		this->movingBack2Shape.setPosition(this->movingBack1Shape.getPosition().x + this->movingBack1Shape.getGlobalBounds().width, 0.f);
	}
}

void Background::DrawStatic(RenderWindow *window)
{
	window->draw(this->backSprite);
}

void Background::ChangeTex(Texture *After, RenderWindow *window)
{
	this->backSprite.setTexture(*After);
	// Fill the screen
	float scale1 = window->getSize().x / (this->backSprite.getGlobalBounds().width);

	float scale2 = window->getSize().y / this->backSprite.getGlobalBounds().height;

	this->backSprite.setScale(Vector2f(scale1, scale2));

}

void Background::DrawMoving(RenderWindow *window)
{
	window->draw(this->movingBack1Shape);
	window->draw(this->movingBack2Shape);
}
