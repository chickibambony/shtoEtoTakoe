#pragma once
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Enemy.h"
#include <vector>

class Hood
{
public:
	Hood(sf::Vector2f pos, Player* l_player, std::vector<Enemy>* l_enemies);
	void Render(sf::RenderWindow& l_window);
	void Update(float time, sf::Vector2f l_offset, int bulletNum);
	void Animation(float time);

private:
	void ScoreUpdate();
	void BulletUpdate();

	Player* m_player;
	std::vector<Enemy>* m_enemies;
	float dx, dy;
	sf::RectangleShape m_Score;
	sf::RectangleShape m_bulletCounter;
	sf::Vector2f primaryPosScore;
	sf::Vector2f primaryPosCounter;
	sf::Font m_font;
	sf::Text m_textCounter;
	sf::Text m_textCounterShadow;
	sf::Text m_textScore;
	sf::Text m_textScoreShadow;
	float angle = 0;
	float animSpeed = 0.05f;
	float animForse = 0.01f;
	float blinkingCounter = 0;
};

