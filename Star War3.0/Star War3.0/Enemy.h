#pragma once
#include "Bullet.h"
#include "eBullets.h"	
class Enemy
{
public:
	// Enemy HP
	int HP;
	// Enemy HP max
	int HPMax;

	// Window witdth
	int range;
	
	// Bullet lapse
	float bulletTimer;
	// Multiplier
	float mult;
	
	// EHP Bar	
	RectangleShape ehp;

	// Enemy Texture
	Sprite shape;
	Texture *texture;
	
	Enemy(Texture *texture, Vector2u windowSize, float maxV);

	~Enemy();

	void UpdateHP();
	void Move(float dt);
	void Draw(RenderWindow & window);
	void Update(float dt);

private:
	float acceleration;
	float drag;
	Vector2f currentV;
	float maxV;
};
