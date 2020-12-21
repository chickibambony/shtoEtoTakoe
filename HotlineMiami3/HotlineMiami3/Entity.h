#pragma once
#include <SFML/Graphics.hpp>

class Entity{
public:
	Entity(sf::IntRect l_hitbox);
	Entity();
	sf::IntRect GetHitbox();
	sf::Vector2f GetPosition();
	sf::IntRect m_hitbox;
};

