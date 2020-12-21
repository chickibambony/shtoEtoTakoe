#pragma once
#include "MovableEntity.h"

class Enemy : public MovableEntity{
public:
    Enemy(sf::Texture& l_texture, sf::Vector2f l_pos, Details* l_details, WeaponTaken l_weapon);
    void Update(float time, const std::vector<Tile>* l_map);
    void Attack();    
    bool GoToPoint(sf::Vector2f l_point);
    void CheckTriggerRange(sf::Vector2f l_point);
    void Bashing(sf::Vector2f l_point);
    void SelfTerminated(WeaponTaken l_weapon, sf::Vector2f l_point);
    void Finishing(WeaponTaken l_weapon);
    float GetRotation();
    bool isTrigerred = false;
    bool isFinishing = false;
    bool isLeaning = false;
    bool isBashed = false;
    bool isSliding = false;
    int TriggerRange = 350;
    float attackDelayCounter = 0;

private:
    void ResolveBashCollision(int dir, const std::vector<Tile>* l_map);
    void FinishingAnimation(float time);
    void BodyAnimation(float time);
    void BashedAnimation(float time);
    void Sliding(float time, const std::vector<Tile>* l_map);
    sf::Vector2f GetHeadPos();
    int finishingCounter = 0;
    int finishingNums;
    float bashCounter = 0;
    float slidingSpeed;
    float slidingX, slidingY;
    int textureYOffset;
    int lastTile;
    WeaponTaken m_executionWeapon;
};
