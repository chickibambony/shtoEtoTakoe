#include "Game.h"
#include <iostream>

Game::Game() : m_player(m_textureHolder.playerTexture, sf::Vector2f(0, 0), &m_details), m_hood(m_view.GetView().getSize(), &m_player, &m_enemies),
m_engine(&m_enemies, &m_player, &m_map, &m_playerBullets, &m_enemyBullets, &m_drop), m_artificialIntellect(&m_enemies, &m_player, &m_enemyBullets),
m_details(&m_textureHolder.detailsTexture)
{
	m_window.create(sf::VideoMode(1920, 1080), "Hotline Miami 3", sf::Style::Fullscreen);
	m_window.setFramerateLimit(60);
	m_window.setMouseCursorVisible(false);
	m_artificialIntellect.CreateAI(m_map, m_map.GetCollidableTiles());
	m_menu.SetSize(m_window.getSize());
	//LoadLevel();
	
}

Game::~Game() {}

void Game::Run() {
	sf::Clock clock;
	float time;
	while (m_window.isOpen()) {
		sf::Vector2i pixelPos = sf::Mouse::getPosition(m_window);
		sf::Vector2f pos = m_window.mapPixelToCoords(pixelPos);
		time = clock.restart().asMicroseconds() / 800.f;
		sf::Event event;
		while (m_window.pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				m_window.close();
			}
			if (event.type == sf::Event::MouseButtonPressed && event.key.code == sf::Mouse::Right) {
				m_engine.InteractWithWeapon(m_textureHolder.weaponTexture, pos);
			}
			if (event.type == sf::Event::KeyPressed) {
				if (event.key.code == sf::Keyboard::Escape && m_state == ProgramState::Game) {
					m_state = ProgramState::Menu;
				}
				if (event.key.code == sf::Keyboard::R && m_state == ProgramState::Game) {
					Restart();
				}
				if (m_state == ProgramState::Menu) {
					m_menu.InteractWithMenu(event.key.code, m_state, m_level);
					if (m_state == ProgramState::Game) {
						Restart();
					}
				}
				
			}
		}
		if (m_menu.HasClosed()) {
			m_window.close();
		}

		if (m_state == ProgramState::Game) {
			m_window.setView(m_view.GetView());
		}
		else if (m_state == ProgramState::Menu) {
			m_window.setView(sf::View(sf::FloatRect(0, 0, 1920, 1080)));
		}
		cursorPos = m_window.mapPixelToCoords(sf::Mouse::getPosition(m_window));
		if (m_player.isAlive) {
			HandleInput();		
		}
		Update(time);
		Render();
	}
}

void Game::HandleInput() {
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
		m_player.Setdx(-1);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {
		m_player.Setdx(1);
	}	
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::W)) {
		m_player.Setdy(-1);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S)) {
		m_player.Setdy(1);
	}
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
		m_engine.SetExecuteProcess(m_textureHolder.weaponTexture);
	}
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		m_engine.Attack(cursorPos);
	}
}

void Game::Update(float time) {
	if (m_state == ProgramState::Game) {
		sf::Vector2i pixelPos = sf::Mouse::getPosition(m_window);
		sf::Vector2f pos = m_window.mapPixelToCoords(pixelPos);
		m_view.Update(m_player.GetHitbox().left, m_player.GetHitbox().top);
		m_engine.Update(time);
		m_artificialIntellect.Update(time);
		m_player.Update(time, m_map.GetCollidableTiles(), pos);

		for (int i = 0; i < m_playerBullets.size(); i++) {
			m_playerBullets.at(i).Update(time, m_map.GetCollidableTiles());
		}
		for (int i = 0; i < m_enemyBullets.size(); i++) {
			m_enemyBullets.at(i).Update(time, m_map.GetCollidableTiles());
		}
		for (int i = 0; i < m_enemies.size(); i++) {
			m_enemies.at(i).Update(time, m_map.GetCollidableTiles());
		}
		for (int i = 0; i < m_drop.size(); i++) {
			m_drop.at(i).Update(time, m_map.GetCollidableTiles());
		}
		m_details.Update(time);
		m_hood.Update(time, m_window.getView().getCenter(), m_player.bulletCounter);
		m_back.Update(time, m_window.getView().getCenter());
		m_cursor.Update(time, cursorPos);
	}
	else if (m_state == ProgramState::Menu) {
		m_menu.Update(time);
	}
	
}

void Game::Render() {
	m_window.clear(sf::Color::Black);
	if (m_state == ProgramState::Game) {
		m_back.Render(m_window);
		m_map.Render(m_window);
		m_details.Render(m_window);
		for (int i = 0; i < m_drop.size(); i++) {
			m_drop.at(i).Render(m_window);
		}
		for (int i = 0; i < m_enemies.size(); i++) {
			m_enemies.at(i).Render(m_window);
		}
		m_player.Render(m_window);
		for (int i = 0; i < m_playerBullets.size(); i++) {
			m_playerBullets.at(i).Render(m_window);
		}
		for (int i = 0; i < m_enemyBullets.size(); i++) {
			m_enemyBullets.at(i).Render(m_window);
		}
		m_artificialIntellect.Render(m_window);
		
		m_hood.Render(m_window);
		m_cursor.Render(m_window);
	}
	else if (m_state == ProgramState::Menu) {
		m_menu.Render(m_window);
	}
	m_window.display();
}

void Game::LoadLevel() {
	if (m_level == Levels::Test) {
		m_levelPath = "content/Levels/Test/";
	}
	else if (m_level == Levels::Tension) {
		m_levelPath = "content/Levels/Tension/";
	}
	LoadMap();
	LoadEnemies();
	LoadDrop();
	LoadPlayer();
}

void Game::LoadMap() {
	sf::String temp = m_levelPath + "map.txt";
	m_map.LoadMap(temp, m_textureHolder.mapTexture);
}

void Game::LoadEnemies() {
	std::ifstream in;
	sf::String temp = m_levelPath + "Enemies.txt";
	in.open(static_cast<std::string>(temp));

	float x, y;
	int weapon;
	WeaponTaken l_weapon;
	while (!in.eof()) {
		in >> x;
		in >> y;
		in >> weapon;
		if (weapon == 0) {
			l_weapon = WeaponTaken::Bat;
		}
		else if (weapon == 1) {
			l_weapon = WeaponTaken::DoubleBarrel;
		}
		else if (weapon == 2) {
			l_weapon = WeaponTaken::Knife;
		}
		else if (weapon == 3) {
			l_weapon = WeaponTaken::M16;
		}
		else if (weapon == 4) {
			l_weapon = WeaponTaken::Pipe;
		}
		else if (weapon == 5) {
			l_weapon = WeaponTaken::Shotgun;
		}
		else {
			l_weapon = WeaponTaken::Unarmed;
		}
		m_enemies.push_back(Enemy(m_textureHolder.enemyTexture, sf::Vector2f(x, y), &m_details, l_weapon));
	}
	in.close();
}

void Game::LoadDrop() {
	std::ifstream in;
	sf::String temp = m_levelPath + "Drop.txt";
	in.open(static_cast<std::string>(temp));

	sf::Vector2f pos;
	int weapon;
	WeaponTaken l_weapon;
	while (!in.eof()) {
		in >> pos.x;
		in >> pos.y;
		in >> weapon;
		if (weapon == 0) {
			l_weapon = WeaponTaken::Axe;
		}
		else if (weapon == 1) {
			l_weapon = WeaponTaken::Bat;
		}
		else if (weapon == 2) {
			l_weapon = WeaponTaken::DoubleBarrel;
		}
		else if (weapon == 3) {
			l_weapon = WeaponTaken::Knife;
		}
		else if (weapon == 4) {
			l_weapon = WeaponTaken::M16;
		}
		else if (weapon == 5) {
			l_weapon = WeaponTaken::Machete;
		}
		else if (weapon == 6) {
			l_weapon = WeaponTaken::MP5;
		}
		else if (weapon == 7) {
			l_weapon = WeaponTaken::Pipe;
		}
		else if (weapon == 8) {
			l_weapon = WeaponTaken::Shotgun;
		}
		else if (weapon == 9) {
			l_weapon = WeaponTaken::Silenser;
		}
		else if (weapon == 10) {
			l_weapon = WeaponTaken::Sword;
		}
		else {
			l_weapon = WeaponTaken::Bat;
		}
		m_drop.push_back(Drop(m_textureHolder.weaponTexture, pos, l_weapon));
	}
	in.close();
}

void Game::LoadPlayer() {
	std::ifstream in;
	sf::String temp = m_levelPath + "Player.txt";
	in.open(static_cast<std::string>(temp));

	float x, y;
	in >> x;
	in >> y;
	m_player = Player(m_textureHolder.playerTexture, sf::Vector2f(x, y), &m_details);
	in.close();
}

void Game::Restart() {
	if (m_state == ProgramState::Game) {
		m_drop.clear();
		m_enemies.clear();
		m_details.Clear();
		m_enemyBullets.clear();
		m_playerBullets.clear();
		LoadLevel();
	}
}