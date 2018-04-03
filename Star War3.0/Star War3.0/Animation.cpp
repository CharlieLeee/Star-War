#include "Animation.h"



Animation::Animation(Texture *texture, Vector2u imageCount, float switchTime, Vector2f size, Vector2f pos)
{
	// Number of rows and columns
	this->imageCount = imageCount;
	// Time between sprites
	this->switchTime = switchTime;

	this->shape.setTexture(texture);

	this->loopIsDone = false;

	// Timer
	totalTime = 0.f;
	
	currentImage.x = 0;
	currentImage.y = 0;

	// x, y of single rect sprite
	uvRect.width = texture->getSize().x / float(imageCount.x);
	uvRect.height = texture->getSize().y / float(imageCount.y);

	this->shape.setPosition(pos);
	this->shape.setSize(size);
}


Animation::~Animation()
{
}

void Animation::Update(int row, float deltaTime)
{
	// Set current image's y to the y of row
	currentImage.y = row;

	totalTime += deltaTime;
	if (!loopIsDone)
	{
		if (totalTime >= switchTime)
		{
			totalTime -= switchTime;
			currentImage.x++;


			if (currentImage.x == imageCount.x)
			{
				loopIsDone = true;
			}
		}
	}

	uvRect.left = currentImage.x * uvRect.width;
	
	uvRect.top = currentImage.y * uvRect.height;
}

void Animation::UpdateTill(int row, float deltaTime)
{
	// Set current image's y to the y of row
	currentImage.y = row;

	totalTime += deltaTime;
	if (!loopIsDone)
	{
		if (totalTime >= switchTime)
		{
			totalTime -= switchTime;
			currentImage.x++;


			if (currentImage.x == imageCount.x - 1)
			{
				loopIsDone = true;
			}
		}
	}

	uvRect.left = currentImage.x * uvRect.width;

	uvRect.top = currentImage.y * uvRect.height;
}

void Animation::UpdateLoop(int row, float deltaTime)
{
	currentImage.y = row;
	totalTime += deltaTime;

	if (totalTime >= switchTime)
	{
		totalTime -= switchTime;
		currentImage.x++;


		if (currentImage.x >= imageCount.x)
		{
			currentImage.x = 0; 
		}
	}

	uvRect.left = currentImage.x * uvRect.width;
	
	uvRect.top = currentImage.y * uvRect.height;
}

void Animation::UpdateAll(float deltaTime)
{
	// Set current image's y to the y of row

	totalTime += deltaTime;
	if (!loopIsDone)
	{
		if (totalTime >= switchTime)
		{
			totalTime -= switchTime;
			currentImage.x++;


			if (currentImage.x == imageCount.x)
			{
				currentImage.y++;
				currentImage.x = 0;
			}

			if (currentImage.x == imageCount.x &&
				currentImage.y == imageCount.y)
			{
				loopIsDone = true;
			}
		}
	}

	uvRect.left = currentImage.x * uvRect.width;

	uvRect.top = currentImage.y * uvRect.height;
}

void Animation::Draw(RenderWindow * window)
{
	window->draw(this->shape);
}

