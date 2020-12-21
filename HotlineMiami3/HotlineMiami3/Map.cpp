#include "Map.h"

Map::Map() {
	
}

void Map::LoadMap(std::string mapDirectory, sf::Texture& l_texture) {
	std::ifstream in;
	in.open(mapDirectory);
	Tile temp;
	m_colidableTiles.clear();
	m_floorTiles.clear();

	while (!in.eof()) {
		in >> temp.m_hitbox.left;
		in >> temp.m_hitbox.top;
		in >> temp.m_hitbox.width;
		in >> temp.m_hitbox.height;
		in >> temp.spriteX;
		in >> temp.spriteY;
		in >> temp.isCollidable;
		if (temp.isCollidable) {
			m_colidableTiles.push_back(temp);		
		}
		else {
			m_floorTiles.push_back(temp);
		}
	}
	in.close();

	mapTile.setTexture(l_texture);
}

void Map::Render(sf::RenderWindow& l_window) {
	for (int i = 0; i < m_floorTiles.size(); i++) {
		mapTile.setTextureRect(sf::IntRect(m_floorTiles.at(i).spriteX * 16, m_floorTiles.at(i).spriteY * 16, 16, 16));
		mapTile.setPosition(m_floorTiles.at(i).m_hitbox.left, m_floorTiles.at(i).m_hitbox.top);
		l_window.draw(mapTile);
	}
	for (int i = 0; i < m_colidableTiles.size(); i++) {
		mapTile.setTextureRect(sf::IntRect(m_colidableTiles.at(i).spriteX * 16, m_colidableTiles.at(i).spriteY * 16, 16, 16));
		mapTile.setPosition(m_colidableTiles.at(i).m_hitbox.left, m_colidableTiles.at(i).m_hitbox.top);
		l_window.draw(mapTile);
	}
}

std::vector<Tile>* Map::GetCollidableTiles() {
	return &m_colidableTiles;
}