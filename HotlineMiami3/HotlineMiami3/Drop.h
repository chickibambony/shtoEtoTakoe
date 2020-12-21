#pragma once
#include <SFML/Graphics.hpp>
#include "Tile.h"
#include "Weapon.h"
#include <vector>

class Drop
{
public:
	Drop(sf::Texture& l_texture, sf::Vector2f l_pos, sf::Vector2f direction, WeaponTaken l_weapon, int bulletNum);
	Drop(sf::Texture& l_texture, sf::Vector2f l_pos, WeaponTaken l_weapon, int bulletNum);
	Drop(sf::Texture& l_texture, sf::Vector2f l_pos, WeaponTaken l_weapon);
	void Update(float time, const std::vector<Tile>* l_map);
	void Render(sf::RenderWindow& l_window);
	int GetBulletNum();
	sf::IntRect GetHitBox();
	WeaponTaken GetTakenWeapon();
	sf::Vector2f GetPosition();
	float speed;

private:
	sf::IntRect m_hitbox;
	sf::Sprite m_sprite;
	sf::Sprite m_spriteShadow;
	sf::RectangleShape test;
	float animSpeed = 0.f;
	float animForce = -0.03f;
	int bulletNum;
	float dx, dy;
	WeaponTaken m_weapon;

	void SetHitbox(sf::Vector2f l_hitbox, WeaponTaken l_weapon);
	void ResolveCollision(int dir, const std::vector<Tile>* l_map);
	void Reflect(int dir);
	void Animation(float time);
};

