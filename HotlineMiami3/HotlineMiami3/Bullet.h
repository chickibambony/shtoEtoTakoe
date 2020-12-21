#pragma once
#include "Map.h"
#include "Tile.h"
#include "Weapon.h"
#include <SFML/Graphics.hpp>

class Bullet
{
public:
    Bullet(sf::Texture &l_texture, sf::Vector2f bulletCoords, sf::Vector2f direction, WeaponTaken l_weapon);
    void Update(float time, const std::vector<Tile>* l_map);
    void Render(sf::RenderWindow& l_window);
    sf::IntRect GetHitBox();
    sf::Vector2f GetPosition();
    bool isAlive = true;

private:    
    int dispersion;
    float speed = 0.7f;
    bool isCollided = false;
    float lifeTime = 2000.f;
    sf::Vector2f direction;
    sf::IntRect m_hitBox;
    sf::Sprite m_sprite;
    float dx, dy;
    float currentFrame = 0;

    void ResolveCollision(int dir, const std::vector<Tile>* l_map);
    void Animation(float time);
    void SetDispersion(WeaponTaken l_weapon);
    void SetSpeed(WeaponTaken l_weapon);
};

