#include "Player.h"

Player::Player(RenderWindow	*window, Texture *texture, Texture *bulletTex, float _shootTimer, bool isLeft)
	: HPMax(5)
	, isLeft(isLeft)
	, score(0)
	, currentV(Vector2f(12.f, 0.f))
{
	{
		// Init HP
		this->HP = this->HPMax;

		// Init HP Bar
		this->hpBar.setFillColor(Color(225, 15, 15, 220));
		this->hpBack.setFillColor(Color(159, 159, 159, 120));
		// Init properties
		this->collideDamage = 1; // Collide damage
		this->maxV = 10.f; // Player max moving speed 
		this->acceleration = 1.f;
		// Drag
		this->drag = 0.2f;

		// Init timer
		this->shootTimer = _shootTimer; // Lapse between bullets
		this->shootCnt = 0.f; // Shooting counter

		// Set sprite properties
		this->texture = texture;
		this->shape.setTexture(*texture);

		// Set initial position


		if (isLeft)
			this->InitPos = Vector2f(30.f, 45.f);
		else
			this->InitPos = Vector2f(window->getSize().x, 45.f);

		this->shape.setPosition(this->InitPos);
		// Init bullet texture
		this->bulletTex = bulletTex;

		if (isLeft)
			this->shape.setScale(0.15f, 0.15f);
		else
			this->shape.setScale(-0.15f, 0.15f);

		// Set multiplier
		this->mult = 62.5f;

	}

}


Player::~Player()
{
}

void Player::shoot(Vector2f speed, Vector2f accelerationType)
{
	Vector2f offset(10.f, 20.f);
	Vector2f upOffset(10.f, 78.f);
	Vector2f center(10.f, 49.f);
	if (isLeft)
	{
		if (accelerationType.y != 0.f)
		{
			this->bullets.push_back(Bullet(bulletTex, this->shape.getPosition() + upOffset, speed, accelerationType, isLeft));
			this->bullets.push_back(Bullet(bulletTex, this->shape.getPosition() + offset, speed, Vector2f(accelerationType.x, -accelerationType.y), isLeft));
		}
		else
		{
			this->bullets.push_back(Bullet(bulletTex, this->shape.getPosition() + center, speed, accelerationType, isLeft));
		}
	}
	else
	{
		if (accelerationType.y != 0.f)
		{
			this->bullets.push_back(Bullet(bulletTex, this->shape.getPosition() + upOffset, -speed, accelerationType, isLeft));
			this->bullets.push_back(Bullet(bulletTex, this->shape.getPosition() + offset, -speed, Vector2f(accelerationType.x, -accelerationType.y), isLeft));
		}
		else
		{
			this->bullets.push_back(Bullet(bulletTex, this->shape.getPosition() + center, -speed, accelerationType, isLeft));
		}
	}

	this->shootTimer = 0; // Reset timer
}

void Player::Movement(RenderTarget &window, float dt, Keyboard::Key UpKey
	, Keyboard::Key DownKey
	, Keyboard::Key LeftKey
	, Keyboard::Key RightKey)
{
	Vector2f direction(0.f, 0.f);

	if (Keyboard::isKeyPressed(LeftKey))
	{
		direction.x = -1.f;

		if (currentV.x > -maxV)
			currentV.x += acceleration * direction.x * dt * mult;
	}
	if (Keyboard::isKeyPressed(RightKey))
	{
		direction.x = 1.f;

		if (currentV.x < maxV)
			currentV.x += acceleration * direction.x * dt * mult;
	}
	if (Keyboard::isKeyPressed(UpKey))
	{
		direction.y = -1.f;

		if (currentV.y > -maxV)
			currentV.y += acceleration * direction.y * dt * mult;
	}
	if (Keyboard::isKeyPressed(DownKey))
	{
		direction.y = 1.f;

		if (currentV.y < maxV)
			currentV.y += acceleration * direction.y * dt * mult;
	}

	// Drag
	if (currentV.x > 0.f)
	{
		currentV.x -= drag * dt * mult;

		if (currentV.x < 0.f)
			currentV.x = 0;
	}
	else if (currentV.x < 0.f)
	{
		currentV.x += drag * dt * mult;

		if (currentV.x > 0.f)
			currentV.x = 0;
	}

	if (currentV.y > 0.f)
	{
		currentV.y -= drag * dt * mult;

		if (currentV.y < 0.f)
			currentV.y = 0;
	}
	else if (currentV.y < 0.f)
	{
		currentV.y += drag * dt * mult;

		if (currentV.y > 0.f)
			currentV.y = 0;
	}

	// Final move
	shape.move(currentV * dt * mult);

	// Player restrain in the window
	if (this->shape.getPosition().x <= 0)                                                                                  // Left
	{
		this->shape.setPosition(0.f, this->shape.getPosition().y);
		this->currentV.x = 0;
	}

	if (this->shape.getPosition().x >= window.getSize().x - this->shape.getGlobalBounds().width)
	{
		this->shape.setPosition(window.getSize().x - this->shape.getGlobalBounds().width, this->shape.getPosition().y);  // Right
		this->currentV.x = 0;
	}

	if (this->shape.getPosition().y <= 0)
		this->shape.setPosition(this->shape.getPosition().x, 0.f);                                                        // Up

	if (this->shape.getPosition().y >= window.getSize().y - this->shape.getGlobalBounds().height)
		this->shape.setPosition(this->shape.getPosition().x, window.getSize().y - this->shape.getGlobalBounds().height); // Down
}

void Player::Reset()
{
	this->HP = this->HPMax;
	this->score = 0;
	this->maxV = 10.f;
	for (size_t i = 0; i < this->bullets.size(); i++)
	{
		this->bullets.erase(bullets.begin() + i);
	}
	this->shape.setPosition(this->InitPos);
}

void Player::ResetVelocity()
{
	this->currentV = Vector2f(0.f, 0.f);
}

void Player::BounceOff()
{
	this->currentV.x *= -1.2f;
	this->currentV.y *= -1.2f;
}

void Player::Draw(RenderWindow & window)
{
	window.draw(this->shape);
	window.draw(this->hpBack);
	window.draw(this->hpBar);
}

void Player::Update(RenderTarget &window, float dt)
{
	if (this->isLeft)
		this->Movement(window, dt);
	else
		this->Movement(window, dt, Keyboard::Up, Keyboard::Down, Keyboard::Left, Keyboard::Right);

	this->hpBar.setSize(Vector2f(20.f * this->HP, 5.f));
	this->hpBar.setPosition(this->shape.getPosition().x, this->shape.getPosition().y - hpBar.getGlobalBounds().height - 10);
	
	this->hpBack.setSize(Vector2f(20.f * this->HPMax, 5.f));
	this->hpBack.setPosition(this->shape.getPosition().x, this->shape.getPosition().y - hpBar.getGlobalBounds().height - 10);
}

