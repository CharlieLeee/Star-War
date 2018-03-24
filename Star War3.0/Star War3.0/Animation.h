#pragma once
#include "Bullet.h"
class Animation
{
public:
	Animation(Texture *texture, Vector2u imageCount, float switchTime, Vector2f size, Vector2f pos);
	~Animation();

	IntRect uvRect;
	RectangleShape shape;

	// Update once
	void Update(int row, float deltaTime);

	// Loop updating sprite
	void UpdateLoop(int row, float deltaTime);

	void UpdateAll(float deltaTime);

	void Draw(RenderWindow *window);
private:
	Vector2u imageCount;
	Vector2u currentImage;

	float totalTime;
	float switchTime;

	// States
	bool loopIsDone;
};