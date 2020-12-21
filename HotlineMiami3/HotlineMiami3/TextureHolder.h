#pragma once
#include <SFML/Graphics.hpp>

class TextureHolder
{
public:
	TextureHolder();
	sf::Texture mapTexture;
	sf::Texture enemyTexture;
	sf::Texture playerTexture;
	sf::Texture bulletTexture;
	sf::Texture weaponTexture;
	sf::Texture detailsTexture;
};
