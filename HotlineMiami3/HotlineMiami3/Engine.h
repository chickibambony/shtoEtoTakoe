#pragma once
#include "Enemy.h"
#include "Player.h"
#include "Map.h"
#include "Drop.h"
#include "Bullet.h"
#include "TextureHolder.h"
#include <vector>

class Engine
{
public:
	Engine(std::vector<Enemy>* l_enemies, Player* l_player, Map* l_map, std::vector<Bullet>* l_playerBullets, std::vector<Bullet>* l_enemiesBullets, std::vector<Drop>* l_drop);
	void Update(float time);
	void InteractWithWeapon(sf::Texture& l_texture, sf::Vector2f pos);
	void SetExecuteProcess(sf::Texture& l_texture);
	void EnemyFinishing(sf::Texture& l_texture);
	void Attack(sf::Vector2f pos);

private:
	//check colisions with player and enemies
	void BulletsPhysic();
	void MelleAttackPhisic();
	void DropPhysic();
	void AddBullets(sf::Vector2f pos);

	std::vector<Drop>* m_drop;
	std::vector<Bullet>* m_playerBullet;
	std::vector<Bullet>* m_enemiesBullets;
	std::vector<Enemy>* m_enemies;
	Player* m_player;
	Map* m_map;
	TextureHolder m_textureholder;
};

