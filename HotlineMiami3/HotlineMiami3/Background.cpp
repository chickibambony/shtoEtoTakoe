#include "Background.h"
#include <iostream>

Background::Background() {
	m_texture.loadFromFile("content/Textures/Background.png");
	m_sprite.setTexture(m_texture);
	m_sprite.setTextureRect(sf::IntRect(0, 0, 960, 540));
	//m_sprite.setScale(2, 2);
	m_sprite.setPosition(-576, -324);
	primaryPos = m_sprite.getPosition();
}

void Background::Update(float time, sf::Vector2f offset) {
	m_sprite.setPosition(offset.x + primaryPos.x, offset.y + primaryPos.y);
	currentFrame += time / 80;
	if (currentFrame > 3) {
		currentFrame = 0;
	}
	if (int(currentFrame) == 0) {
		m_sprite.setTextureRect(sf::IntRect(0, 0, 960, 540));
	}
	else if(int(currentFrame) == 1){
		m_sprite.setTextureRect(sf::IntRect(960, 0, 960, 540));
	}
	else if(int(currentFrame) == 2){
		m_sprite.setTextureRect(sf::IntRect(0, 540, 960, 540));
	}
}

void Background::Render(sf::RenderWindow& l_window) {
	l_window.draw(m_sprite);
}