#pragma once
#include "SFML\Graphics.hpp"
#include <iostream>
using namespace sf;

#define NUM_OF_LINE 4

class Menu
{
public:
	Menu(float width, float height);
	~Menu();

	void Draw(RenderWindow *window);
	void MoveUp();
	void MovedDown();
	void MenuUpdate(float dt);
	int GetLine();

private:
	int currentLineIndex;
	Font font;
	Text text[NUM_OF_LINE];
	float KeyTimer;
	float KeyLapse;
};

