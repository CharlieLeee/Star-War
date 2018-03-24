#pragma once
#include "Bullet.h"

class Player
{
public:
	Player(Texture *texture, Texture *bulletTex, float _shootTimer);
	~Player();

	// Player Sprite
	Sprite shape;
	Texture* texture;
	
	// Player Bullets texture
	Texture *bulletTex;

	// Player HP
	// May change to private later!!!
	int HP;
	int HPMax;

	// Player score
	int score;

	// Shooting timer
	float shootTimer;
	float shootCnt;
	
	// Collide damage
	int collideDamage;

	// Current speed
	Vector2f currentV;
	
	// Max Velocity
	float maxV;
	// Acceleration
	float acceleration;
	// Drag
	float drag;

	// Multiplier
	float mult;

	// HP Bar
	RectangleShape hpBar;

	// Initial position
	Vector2f InitPos;

	// Player bullet vector
	std::vector<Bullet> bullets;

public:
	// Helper function
	void shoot(Vector2f speed, Vector2f accelerationType);
	void Movement(RenderTarget &window, float dt);
	void Reset();
	void ResetVelocity();
	void BounceOff();
	void Draw(RenderWindow &window);
	void Update(RenderTarget &window, float dt);
};
