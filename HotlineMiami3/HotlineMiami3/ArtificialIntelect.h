#pragma once
#include "Enemy.h"
#include "Player.h"
#include "TextureHolder.h"
#include "Map.h"
#include <vector>
#include <list>

class ArtificialIntelect
{
public:
	ArtificialIntelect(std::vector<Enemy>* l_enemies, Player* l_player, std::vector<Bullet>* l_enemyBullets);
	~ArtificialIntelect();
	void Render(sf::RenderWindow& l_window);
	void Update(float time);
	void MyDekster(int indexOfFirstPoint, int indexOfLastPoint);
	void FollowRoute();
	void CreateAI(Map& l_map, std::vector<Tile>* l_mapTest);
	int GetMeshPoint(sf::IntRect l_hitbox);

private:
	bool CheckWall(int enemyIndex, float time);
	void CreateMeshMap(Map& l_map);
	void CreateRoutes(Map& l_map);
	std::vector<Tile>* m_map;
	TextureHolder m_textureHolder;
	std::vector<Enemy>* m_enemies;
	std::vector<Bullet>* m_enemyBullets;
	Player* m_player;
	sf::VertexArray meshmap;
	sf::VertexArray testLine;
	int col, row;
	int size;

	int** a;
	int* minDistance;
	int* visitedVertecies;
	std::vector<sf::Vector2f> route;
	bool switcher = false;
	std::vector<sf::Vector2f> m_playerPos;
	
	//this is bitch
	int* ver;
};


