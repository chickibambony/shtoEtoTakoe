#include "Cursor.h"

Cursor::Cursor() {
	m_texture.loadFromFile("content/Textures/Cursor.png");
	m_sprite.setTexture(m_texture);
	m_sprite.setOrigin(40, 40);
}

void Cursor::Update(float time, sf::Vector2f l_pos) {
	m_sprite.setPosition(l_pos);

	currentFrame += time / 60;
	if (currentFrame > 12) {
		currentFrame = 1;
	}
	m_sprite.setTextureRect(sf::IntRect(int(currentFrame) * 80, 0, 80, 80));
}

void Cursor::Render(sf::RenderWindow& l_window) {
	l_window.draw(m_sprite);
}
