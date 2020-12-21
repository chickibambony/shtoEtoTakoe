#pragma once
#include "TextureHolder.h"
#include "Map.h"
#include "Player.h"
#include "Enemy.h"
#include "Bullet.h"
#include "Weapon.h"
#include "View.h"
#include "Engine.h"
#include "ArtificialIntelect.h"
#include "Drop.h"
#include "Hood.h"
#include "Details.h"
#include "Door.h"
#include "Menu.h"
#include "Background.h"
#include "Cursor.h"
#include <fstream>

class Game
{
public:
	Game();
	~Game();

	void Run();

private:
	void HandleInput();
	void Update(float time);
	void Render();	
	void LoadLevel();
	void LoadEnemies();
	void LoadDrop();
	void LoadPlayer();
	void LoadMap();
	void Restart();

	sf::RenderWindow m_window;
	ArtificialIntelect m_artificialIntellect;
	Engine m_engine;
	TextureHolder m_textureHolder;
	Menu m_menu;
	View m_view;
	Map m_map;
	Player m_player;
	Hood m_hood;
	Background m_back;
	Cursor m_cursor;
	std::vector<Enemy> m_enemies;
	std::vector<Bullet> m_playerBullets;
	std::vector<Bullet> m_enemyBullets;
	Details m_details;
	std::vector<Drop> m_drop;
	Levels m_level = Levels::Test;
	ProgramState m_state = ProgramState::Menu;
	sf::String m_levelPath;
	sf::Vector2f cursorPos;
};