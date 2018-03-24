#pragma once
#include "Bullet.h"
using MessageContainer = std::vector<std::string>;

class Textbox {
public:
	Textbox();
	Textbox(int l_visible, int l_charSize,
		int l_width, Vector2f l_screenPos);
	~Textbox();

	void Setup(int l_visible, int l_charSize,
		int l_width, Vector2f l_screenPos);
	void Add(std::string l_message, bool isPic, Texture *text = nullptr);
	void Clear();

	void Render(RenderWindow& l_wind);
private:
	MessageContainer m_messages;
	int m_numVisible;
	bool isPic;
	Texture character;

	RectangleShape m_backdrop;
	Font m_font;
	Text m_content;
	RectangleShape photo;
};
