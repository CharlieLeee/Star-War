#pragma once
#include "Bullet.h"

class Player
{
public:
	Player(RenderWindow *window, Texture *texture, Texture *bulletTex, float _shootTimer, bool isLeft);
	~Player();

	// Orient 1 / -1
	int orient;

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
	RectangleShape hpBack;

	// Initial position
	Vector2f InitPos;

	// Player bullet vector
	std::vector<Bullet> bullets;

	// 2 Player mode
	bool isLeft;

public:
	// Helper function
	void shoot(Vector2f speed, Vector2f accelerationType);
	void Movement(RenderTarget &window, float dt, Keyboard::Key UpKey = Keyboard::W
		, Keyboard::Key DownKey = Keyboard::S
		, Keyboard::Key LeftKey = Keyboard::A
		, Keyboard::Key RightKey = Keyboard::D);
	void Reset();
	void ResetVelocity();
	void BounceOff();
	void Draw(RenderWindow &window);
	void Update(RenderTarget &window, float dt);
};
