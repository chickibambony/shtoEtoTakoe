#pragma once
#include "Entity.h"
#include "Map.h"
#include "Bullet.h"
#include <vector>
#include "Weapon.h"
#include "Details.h"

class MovableEntity : public Entity
{
public:
    MovableEntity(sf::Texture& l_texture, sf::Vector2f l_pos, Details *l_details);
    void SetWeapon(WeaponTaken weapon, int bulletNum);    
    void Render(sf::RenderWindow& l_window);
    sf::Vector2f GetBulletPos();
    void Drop();
    sf::IntRect GetAttackZone();
    WeaponType GetWeaponType();
    WeaponTaken GetTakenWeapon();
    bool CheckInteractZone(sf::Vector2f target);

    bool isAttacking = false;
    bool isAlive = true;
    int bulletCounter = 0;

protected:
    void WalkingAnimation(float time);
    void AttackAnimation(float time);
    void LegsAnimation(float time);
    void SetLegDirection();
    void ResolveCollision(int dir, const std::vector<Tile>* l_map);
    Details* m_details;

    Weapon c_weapon;
    sf::Sprite m_sprite;
    sf::Sprite m_spriteLegs;
    sf::RectangleShape m_attackZone;
    //test
        sf::RectangleShape m_hitRect;
        sf::CircleShape m_center;
    //
    float speed = 0.17f;
    float currentFrameBody, currentFrameLegs;
    float dx = 0, dy = 0;
    bool isMoving = false;
    WeaponTaken m_weapon = WeaponTaken::Unarmed;
};

