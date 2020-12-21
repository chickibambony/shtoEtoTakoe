#include "Entity.h"

Entity::Entity(sf::IntRect l_hitbox) {
	m_hitbox = l_hitbox;
}

Entity::Entity() {
	m_hitbox = sf::IntRect(0, 0, 0, 0);
}

sf::IntRect Entity::GetHitbox() {
	return m_hitbox;
}

sf::Vector2f Entity::GetPosition() {
	return sf::Vector2f(m_hitbox.left + m_hitbox.width / 2, m_hitbox.top + m_hitbox.height / 2);
}
