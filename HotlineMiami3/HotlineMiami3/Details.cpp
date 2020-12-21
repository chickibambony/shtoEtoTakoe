#include "Details.h"
#include <iostream>

Details::Details(sf::Texture* l_texture) {
	m_texture = l_texture;
}

void Details::AddPoll(sf::Vector2f l_pos) {
	BloodPoll* temp = new BloodPoll(*m_texture, l_pos);
	m_bloodPools.push_back(*temp);
}

void Details::AddPiece(sf::Vector2f l_pos, float angle, int partOfBody) {
	m_pieces.push_back(BodyPiece(*m_texture, l_pos, angle ,partOfBody));
}

void Details::AddSplat(sf::Vector2f l_pos, WeaponTaken l_weapon) {
	int nums = (rand() % (20 - 10 + 1) + 10);
	BloodSplat* temp;
	for (int i = 0; i < nums; i++) {
		temp = new BloodSplat(*m_texture, l_pos);
		m_bloodSplats.push_back(*temp);
	}
}

void Details::AddSquirt(sf::Vector2f l_pos) {
	float angle;
	BloodSquirt* temp;
	for (int i = 0; i < 3; i++) {
		angle = rand() % (180 - (-180) + 1) - 180;
		temp = new BloodSquirt(*m_texture, l_pos, angle);
		m_bloodSquirts.push_back(*temp);
	}
}

void Details::AddSmoke(sf::Vector2f l_pos, sf::Vector2f l_damageSourcePos, WeaponTaken l_weapon) {
	float angle = atan2f(l_damageSourcePos.y - l_pos.y, l_damageSourcePos.x - l_pos.x) * 180 / 3.14;
	BloodSmoke* temp = new BloodSmoke(*m_texture, l_pos, angle + 180);
	m_bloodSmokes.push_back(*temp);
	temp = new BloodSmoke(*m_texture, l_pos, angle + 150);
	m_bloodSmokes.push_back(*temp);
	temp = new BloodSmoke(*m_texture, l_pos, angle + 210);
	m_bloodSmokes.push_back(*temp);
	if (l_weapon == WeaponTaken::Shotgun || l_weapon == WeaponTaken::DoubleBarrel) {
		temp = new BloodSmoke(*m_texture, l_pos, angle);
		m_bloodSmokes.push_back(*temp);
		temp = new BloodSmoke(*m_texture, l_pos, angle - 30);
		m_bloodSmokes.push_back(*temp);
		temp = new BloodSmoke(*m_texture, l_pos, angle + 30);
		m_bloodSmokes.push_back(*temp);
	}
}

void Details::Update(float time) {
	for (int i = 0; i < m_bloodPools.size(); i++) {
		m_bloodPools.at(i).Animation(time);
	}

	for (int i = 0; i < m_bloodSplats.size(); i++) {
		m_bloodSplats.at(i).Animation(time);
	}

	for (int i = 0; i < m_bloodSquirts.size(); i++) {
		if (!m_bloodSquirts.at(i).isAlive) {
			m_bloodSquirts.erase(m_bloodSquirts.begin() + i);
		}
	}
	for (int i = 0; i < m_bloodSquirts.size(); i++) {
		m_bloodSquirts.at(i).Animation(time);
	}

	for (int i = 0; i < m_bloodSmokes.size(); i++) {
		if (!m_bloodSmokes.at(i).isAlive) {
			m_bloodSmokes.erase(m_bloodSmokes.begin() + i);
		}
	}
	for (int i = 0; i < m_bloodSmokes.size(); i++) {
		m_bloodSmokes.at(i).Animation(time);
	}
	for (int i = 0; i < m_pieces.size(); i++) {
		m_pieces.at(i).Animation(time);
	}
}

void Details::Render(sf::RenderWindow& l_window) {
	for (int i = 0; i < m_bloodPools.size(); i++) {
		m_bloodPools.at(i).Render(l_window);
	}
	for (int i = 0; i < m_bloodSquirts.size(); i++) {
		m_bloodSquirts.at(i).Render(l_window);
	}
	for (int i = 0; i < m_bloodSmokes.size(); i++) {
		m_bloodSmokes.at(i).Render(l_window);
	}
	for (int i = 0; i < m_bloodSplats.size(); i++) {
		m_bloodSplats.at(i).Render(l_window);
	}
	for (int i = 0; i < m_pieces.size(); i++) {
		m_pieces.at(i).Render(l_window);
	}
}

void Details::Clear() {
	m_bloodPools.clear();
	m_bloodSmokes.clear();
	m_bloodSplats.clear();
	m_bloodSquirts.clear();
	m_pieces.clear();
}

BloodPoll::BloodPoll(sf::Texture& l_texture, sf::Vector2f l_pos) {
	m_sprite.setTexture(l_texture);
	m_sprite.setOrigin(40, 40);
	m_sprite.setPosition(l_pos);
	currentFrame = 1;
	m_sprite.setTextureRect(sf::IntRect(int(currentFrame) * 80, 0, 80, 80));
}

void BloodPoll::Animation(float time) {
	if (isAnimated) {
		currentFrame += 0.01f * time;
		if (bloodPoll < 2 && currentFrame > 23) {
			bloodPoll++;
			currentFrame = 0;
		}
		else if (bloodPoll == 2 && currentFrame > 16) {
			isAnimated = false;
		}
		m_sprite.setTextureRect(sf::IntRect(int(currentFrame) * 80, bloodPoll * 80, 80, 80));
	}
}

void BloodPoll::Render(sf::RenderWindow& l_window) {
	l_window.draw(m_sprite);
}

BloodSquirt::BloodSquirt(sf::Texture& l_texture, sf::Vector2f l_pos, float angle) {
	offsetY = (rand() % 2) + 3;
	m_sprite.setTexture(l_texture);
	m_sprite.setPosition(l_pos);
	m_sprite.setOrigin(0, 40);
	m_sprite.setRotation(angle);
	currentFrame = 0;
	isAlive = true;
	m_sprite.setTextureRect(sf::IntRect(int(currentFrame) * 80, offsetY * 80, 80, 80));
}

void BloodSquirt::Animation(float time) {
	if (isAlive) {
		currentFrame += 0.01f * time;
		if (currentFrame > 8) {
			isAlive = false;
		}
		m_sprite.setTextureRect(sf::IntRect(int(currentFrame) * 80, offsetY * 80, 80, 80));
	}
}

void BloodSquirt::Render(sf::RenderWindow& l_window) {
	l_window.draw(m_sprite);
}

BloodSmoke::BloodSmoke(sf::Texture& l_texture, sf::Vector2f l_pos, float angle) {
	AnimationSpeed = (rand() % (5 - 3 + 1) + 3) / 100.f;
	offsetY = (rand() % 3) + 9;
	m_sprite.setTexture(l_texture);
	m_sprite.setOrigin(0, 40);
	m_sprite.setRotation(angle);
	m_sprite.setPosition(l_pos);
	currentFrame = 0;
	isAlive = true;
	m_sprite.setTextureRect(sf::IntRect(int(currentFrame) * 80, offsetY * 80, 80, 80));
}

void BloodSmoke::Animation(float time) {
	if (isAlive) {
		currentFrame += AnimationSpeed * time / 3;
		if (currentFrame > 10) {
			isAlive = false;
		}
		m_sprite.setTextureRect(sf::IntRect(int(currentFrame) * 80, offsetY * 80, 80, 80));
	}
}

void BloodSmoke::Render(sf::RenderWindow& l_window) {
	l_window.draw(m_sprite);
}

BloodSplat::BloodSplat(sf::Texture& l_texture, sf::Vector2f l_pos) {
	speed = (rand() % (20 - 15 + 1) + 15) / 120.f;
	m_sprite.setTexture(l_texture);
	m_sprite.setOrigin(40, 40);
	m_sprite.setPosition(l_pos);

	float angle = rand() % (180 - (-180) + 1) - 180;
	dx = cos(angle / 180 * 3.14);
	dy = sin(angle / 180 * 3.14);
	m_sprite.setRotation(atan2(dy, dx) * 180.f / 3.14f);
	currentFrame = 0;
	m_sprite.setTextureRect(sf::IntRect(int(currentFrame) * 80, 5 * 80, 80, 80));
}

void BloodSplat::Animation(float time) {	
	if (speed > 0) {
		speed -= time * 0.0002f;
		m_sprite.setTextureRect(sf::IntRect(int(currentFrame) * 80, 5 * 80, 80, 80));
		m_sprite.move(dx * speed * time, dy * speed * time);
	}
	else {
		speed = 0;
		currentFrame += 0.01f * time;
		if (currentFrame > 7) {
			currentFrame = 7;
		}
		m_sprite.setTextureRect(sf::IntRect(int(currentFrame) * 80, 6 * 80, 80, 80));
	}
}

void BloodSplat::Render(sf::RenderWindow& l_window) {
	l_window.draw(m_sprite);
}

BodyPiece::BodyPiece(sf::Texture& l_texture, sf::Vector2f l_pos, float angle, int partOfBody) {
	speed = 0.3f;
	m_sprite.setTexture(l_texture);
	m_sprite.setOrigin(40, 40);
	m_sprite.setPosition(l_pos);
	m_sprite.setRotation(angle);

	dx = cos(angle / 180 * 3.14);
	dy = sin(angle / 180 * 3.14);
	if (partOfBody == 0) {
		m_sprite.setTextureRect(sf::IntRect(0 * 80, 13 * 80, 80, 80));
		speed = 0.5f;
	}
	else if (partOfBody == 1) {
		m_sprite.setTextureRect(sf::IntRect(1 * 80, 13 * 80, 80, 80));
	}
	else if (partOfBody == 2) {
		m_sprite.setTextureRect(sf::IntRect(2 * 80, 13 * 80, 80, 80));
	}
	else if (partOfBody == 3) {
		m_sprite.setTextureRect(sf::IntRect((3 + (rand() % 2)) * 80, 13 * 80, 80, 80));
		speed = 0.5f;
	}
}

void BodyPiece::Animation(float time) {
	if (speed > 0) {
		speed -= time / 800;
		m_sprite.move(dx * speed * time, dy * speed * time);
	}
	else {
		speed = 0;
	}
}

void BodyPiece::Render(sf::RenderWindow& l_window) {
	l_window.draw(m_sprite);
}