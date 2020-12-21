#pragma once
#include <SFML/Graphics.hpp>

class Cursor
{
public:
	Cursor();
	void Update(float time, sf::Vector2f l_pos);
	void Render(sf::RenderWindow& l_window);

private:
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	float currentFrame = 1;
};

