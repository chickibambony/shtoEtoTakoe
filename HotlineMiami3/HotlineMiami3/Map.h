#pragma once
#include <fstream>
#include <vector>
#include <SFML/Graphics.hpp>
#include "Tile.h"

class Map
{
public:
	Map();
	void Render(sf::RenderWindow& l_window);
	std::vector<Tile>* GetCollidableTiles();
	void LoadMap(std::string mapDirectory, sf::Texture& l_texture);	

private:
	std::vector<Tile> m_colidableTiles;
	std::vector<Tile> m_floorTiles;
	sf::Sprite mapTile;
};

