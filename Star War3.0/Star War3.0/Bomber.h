#pragma once
#include "Bullet.h"

class Bomber
{
public:
	Bomber(Texture *texture, Vector2u windowSize);
	~Bomber();

	Sprite shape;
	Texture *texture;
	Vector2f size;
	Vector2f posi;
	Vector2f aimdir;
	
	float mult = 62.5f;
	int range;

	void Draw(RenderWindow *window);
	void Move(float speed, const float &deltaTime, Vector2f playerPos, RenderWindow *window); 
};