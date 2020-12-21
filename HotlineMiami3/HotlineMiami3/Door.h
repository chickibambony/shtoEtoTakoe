#pragma once
#include <SFML/Graphics.hpp>

class Door
{
public:
	Door(int x, int y);
	void Render(sf::RenderWindow& l_window);
	void Update(float time);
	void SetRotationDir(float dir);
	float GetRotation();
	sf::IntRect GetHitbox();
private:
	sf::RectangleShape m_sprite;
	float dir;
	float speed;
};

