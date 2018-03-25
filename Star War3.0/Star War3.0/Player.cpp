#include "Player.h"

Player::Player(RenderWindow	*window, Texture *texture, Texture *bulletTex, float _shootTimer, bool isLeft)
{
	{
		// Init HP
		this->HPMax = 5;
		this->HP = this->HPMax;

		// Init HP Bar
		this->hpBar.setFillColor(Color::Magenta);

		// Check player number
		this->isLeft = isLeft;

		// Init score
		this->score = 0;

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
		this->InitPos = Vector2f(0.f, 45.f);

		if (isLeft)
			this->shape.setPosition(this->InitPos);
		else
			this->shape.setPosition(window->getSize().x, 0.f);

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
	if (accelerationType.y != 0.f)
	{
		this->bullets.push_back(Bullet(bulletTex, this->shape.getPosition() + upOffset, speed, accelerationType));
		this->bullets.push_back(Bullet(bulletTex, this->shape.getPosition() + offset, speed, Vector2f(accelerationType.x, -accelerationType.y)));
	}
	else
	{
		this->bullets.push_back(Bullet(bulletTex, this->shape.getPosition() + center, speed, accelerationType));
	}
	this->shootTimer = 0; // Reset timer
}

void Player::Movement(RenderTarget &window, float dt)
{
	Vector2f direction(0.f, 0.f);

	if (Keyboard::isKeyPressed(Keyboard::A))
	{
		direction.x = -1.f;

		if (currentV.x > -maxV)
			currentV.x += acceleration * direction.x * dt * mult;
	}
	if (Keyboard::isKeyPressed(Keyboard::D))
	{
		direction.x = 1.f;

		if (currentV.x < maxV)
			currentV.x += acceleration * direction.x * dt * mult;
	}
	if (Keyboard::isKeyPressed(Keyboard::W))
	{
		direction.y = -1.f;

		if (currentV.y > -maxV)
			currentV.y += acceleration * direction.y * dt * mult;
	}
	if (Keyboard::isKeyPressed(Keyboard::S))
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
	this->shape.setPosition(InitPos);
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
	window.draw(this->hpBar);
}

void Player::Update(RenderTarget &window, float dt)
{
	this->Movement(window, dt);

	this->hpBar.setSize(Vector2f(20.f * this->HP, 5.f));
	this->hpBar.setPosition(this->shape.getPosition().x, this->shape.getPosition().y - hpBar.getGlobalBounds().height - 10);
}

