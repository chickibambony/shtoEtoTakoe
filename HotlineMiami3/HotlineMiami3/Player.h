#pragma once
#include "MovableEntity.h"

class Player : public MovableEntity{   
public:
    Player(sf::Texture& l_texture, sf::Vector2f l_pos, Details* l_details);

    sf::Vector2f GetDxDy() {
        return sf::Vector2f(dx, dy);
    }
    void Update(float time, const std::vector<Tile>* l_map, sf::Vector2f l_mousePos);
    void Attack();
    void Execution(bool isLeaning);
    void SetPos(sf::Vector2f l_pos);
    void SetRotation(float l_angle);
    void Setdx(float dx);
    void Setdy(float dx);
    void SelfTerminated(WeaponTaken l_weapon, sf::Vector2f l_point);
    bool isExecuting = false;

private:
    void ResolveBashCollision(int dir, const std::vector<Tile>* l_map);
    void Sliding(float time, const std::vector<Tile>* l_map);
    void BodyAnimation(float time);
    void ExecutingAnimation(float time);
    int executingCounter = 0;
    int executingNums;
    int lastTile;
    int deathTile;
    int textureYOffset;
    float slidingSpeed = 0;
    float slidingX, slidingY;
    bool isSliding = false;

    sf::RectangleShape m_temp;
};