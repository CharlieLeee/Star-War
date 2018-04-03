#include "Bomber.h"


Bomber::Bomber(Texture *texture, Vector2u windowSize)
{
	this->texture = texture;
	this->size = Vector2f(texture->getSize().x / 2, texture->getSize().y / 2);
	this->shape.setTexture(*texture);
	this->shape.setScale(0.3f, 0.3f);
	this->shape.setOrigin(size);

	this->range = windowSize.x / 2 + this->shape.getGlobalBounds().width;
	int ratio = rand() % 4 + 1;
	if (rand() % 2 == 1)
	{
		this->shape.setPosition(ratio * windowSize.x / 4 + rand() % this->range, 0.f);
	}
	else
	{
		this->shape.setPosition(ratio * windowSize.x / 4 + rand() % this->range, windowSize.y);
	}

	this->mult = 62.5f;
}

Bomber::~Bomber()
{
}

void Bomber::Draw(RenderWindow * window)
{
	window->draw(this->shape);
}

void Bomber::Move(float speed, const float & deltaTime, Vector2f playerPos, RenderWindow *window)
{
	Vector2f playerCurPos = playerPos;
	if (this->shape.getPosition().y < 300)
	{
		this->shape.move(-speed * deltaTime * mult, speed* deltaTime * mult);
	}
	if (this->shape.getPosition().y > (window->getSize().y - 300))
	{
		this->shape.move(-speed * deltaTime * mult, -speed * deltaTime * mult);
	}
	if ((this->shape.getPosition().y >= 300) && (this->shape.getPosition().y <= (window->getSize().y - 300)))
	{
		if ((this->shape.getPosition().x > playerCurPos.x) && (((this->shape.getPosition().x - playerCurPos.x) < 300)) && ((abs(this->shape.getPosition().y - playerCurPos.y) < 200)))
		{
			this->posi = (this->shape.getPosition());
			this->aimdir = (playerCurPos - this->posi);
			Vector2f aimdirnorm = this->aimdir / sqrt(pow(this->aimdir.x, 2) + pow(this->aimdir.y, 2));
			if (!(sqrt(pow(playerCurPos.x - this->shape.getPosition().x, 2) + pow(playerCurPos.y - this->shape.getPosition().y, 2)) < speed))
				this->shape.move(1.8f * aimdirnorm * speed * deltaTime * mult);
		}
		else
		{
			this->shape.move(-2.7f * speed * deltaTime * mult, 5 * sin((this->shape.getPosition().x / 50)));
		}

		this->shape.setRotation(5 * cos((this->shape.getPosition().x / 50)));
	}
}


