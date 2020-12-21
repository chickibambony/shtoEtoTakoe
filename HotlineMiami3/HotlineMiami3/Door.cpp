#include "Door.h"
#include <iostream>

Door::Door(int x, int y) {
	m_sprite.setFillColor(sf::Color::Red);
	m_sprite.setSize(sf::Vector2f(32, 5));
	m_sprite.setOrigin(0, 3);
	m_sprite.setPosition(x, y);
	dir = 0;
	speed = 0;
}

void Door::Update(float time) {
	m_sprite.rotate(time * dir * speed);
	if (m_sprite.getRotation() > 135 && m_sprite.getRotation() < 225 && dir == 1) {
		m_sprite.setRotation(135);
	}
	if (m_sprite.getRotation() > 135 && m_sprite.getRotation() < 225 && dir == -1) {
		m_sprite.setRotation(225);
	}
	speed -= 0.2f;
	if (speed < 0) {
		speed = 0;
	}
}

void Door::SetRotationDir(float dir) {
	speed = 1.f;
	this->dir = dir;
}

void Door::Render(sf::RenderWindow& l_window) {
	l_window.draw(m_sprite);
}

float Door::GetRotation() {
	return m_sprite.getRotation();
}

sf::IntRect Door::GetHitbox() {
	return static_cast<sf::IntRect>(m_sprite.getGlobalBounds());
}