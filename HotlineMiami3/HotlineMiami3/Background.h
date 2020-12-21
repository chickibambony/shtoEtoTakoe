#pragma once
#include <SFML/Graphics.hpp>

class Background{
public:
	Background();
	void Update(float time, sf::Vector2f offset);
	void Render(sf::RenderWindow& l_window);

private:
	float currentFrame = 0;
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	sf::Vector2f primaryPos;
};

