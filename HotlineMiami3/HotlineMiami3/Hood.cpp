#include "Hood.h"
#include <iostream>

Hood::Hood(sf::Vector2f pos, Player* l_player, std::vector<Enemy>* l_enemies) {
	m_Score.setSize(sf::Vector2f(140, 30));
	m_Score.setFillColor(sf::Color::Black);
	m_Score.setPosition(pos.x / 2 - m_Score.getSize().x, -pos.y / 2);
	primaryPosScore = m_Score.getPosition();

	m_bulletCounter.setSize(sf::Vector2f(140, 30));
	m_bulletCounter.setFillColor(sf::Color::Black);
	m_bulletCounter.setPosition(-pos.x / 2, pos.y / 2 - m_bulletCounter.getSize().y);
	primaryPosCounter = m_bulletCounter.getPosition();
	m_font.loadFromFile("content/Fonts/hood.ttf");

	m_textCounter.setFont(m_font);
	m_textCounter.setCharacterSize(26);
	m_textCounter.setFillColor(sf::Color(255, 0, 240));
	m_textCounter.setString("Bullets: 0");
	m_textCounter.setOrigin(m_textCounter.getGlobalBounds().width / 2, m_textCounter.getGlobalBounds().height / 2);

	m_textCounterShadow.setFont(m_font);
	m_textCounterShadow.setCharacterSize(26);
	m_textCounterShadow.setFillColor(sf::Color(0, 240, 228));
	m_textCounterShadow.setString("Bullets: 0");
	m_textCounterShadow.setOrigin(m_textCounter.getGlobalBounds().width / 2, m_textCounter.getGlobalBounds().height / 2);

	m_textScore.setFont(m_font);
	m_textScore.setCharacterSize(26);
	m_textScore.setFillColor(sf::Color(255, 0, 240));
	m_textScore.setOrigin(m_textCounter.getGlobalBounds().width / 2, m_textCounter.getGlobalBounds().height / 2);

	m_textScoreShadow.setFont(m_font);
	m_textScoreShadow.setCharacterSize(26);
	m_textScoreShadow.setFillColor(sf::Color(0, 240, 228));
	m_textScoreShadow.setOrigin(m_textCounter.getGlobalBounds().width / 2, m_textCounter.getGlobalBounds().height / 2);
	m_player = l_player;
	m_enemies = l_enemies;
}

void Hood::Update(float time, sf::Vector2f offset, int bulletNum) {
	m_Score.setPosition(offset.x + primaryPosScore.x, offset.y + primaryPosScore.y);
	m_bulletCounter.setPosition(offset.x + primaryPosCounter.x, offset.y + primaryPosCounter.y);
	BulletUpdate();
	ScoreUpdate();
	Animation(time);
}

void Hood::Animation(float time) {
	angle += 4.f;
	if (angle > 360) {
		angle = 0;
	}
	float x = cos(angle / 180 * 3.14) * 1.2;
	float y = sin(angle / 180 * 3.14) * 1.2;
	m_textCounter.setPosition(m_bulletCounter.getPosition().x + m_bulletCounter.getGlobalBounds().width / 2 + x, m_bulletCounter.getPosition().y  + y);
	m_textCounterShadow.setPosition(m_bulletCounter.getPosition().x + m_bulletCounter.getGlobalBounds().width / 2 - x, m_bulletCounter.getPosition().y - y);

	m_textScore.setPosition(m_Score.getPosition().x + m_Score.getLocalBounds().width / 3 + x, m_Score.getPosition().y + y);
	m_textScoreShadow.setPosition(m_Score.getPosition().x + m_Score.getLocalBounds().width / 3 - x, m_Score.getPosition().y - y);
}


void Hood::Render(sf::RenderWindow& l_window) {
	l_window.draw(m_Score);
	l_window.draw(m_bulletCounter);
	l_window.draw(m_textCounterShadow);
	l_window.draw(m_textCounter);
	l_window.draw(m_textScoreShadow);
	l_window.draw(m_textScore);
}

void Hood::ScoreUpdate() {
	int counter = 0;
	for (int i = 0; i < m_enemies->size(); i++) {
		if (m_enemies->at(i).isAlive) {
			counter++;
		}
	}

	if (!m_player->isAlive) {
		m_textScore.setString("You are dead");
		m_textScoreShadow.setString("You are dead");
	}
	else {
		if (counter > 0) {
			m_textScore.setString("Enemies: " + std::to_string(counter));
			m_textScoreShadow.setString("Enemies: " + std::to_string(counter));

		}
		else {
			m_textScore.setString("Level complite!");
			m_textScoreShadow.setString("Level complite!");
		}
	}
}

void Hood::BulletUpdate() {
	if (m_player->isAlive) {
		m_textCounter.setString("Bullets: " + std::to_string(m_player->bulletCounter));
		m_textCounterShadow.setString("Bullets: " + std::to_string(m_player->bulletCounter));
	}
	else {
		m_textCounter.setString("Press R");
		m_textCounterShadow.setString("Press R");
	}
	
}