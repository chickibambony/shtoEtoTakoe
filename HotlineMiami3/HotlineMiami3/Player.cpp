#include "Player.h"
#include <iostream>

Player::Player(sf::Texture& l_texture, sf::Vector2f l_pos, Details* l_details) : MovableEntity(l_texture, l_pos, l_details) {
    m_hitRect.setOutlineColor(sf::Color::Red);
}

void Player::Update(float time, const std::vector<Tile>* l_map, sf::Vector2f l_mousePos) {
    if ((dx != 0 || dy != 0) && isAlive && !isExecuting) {
        isMoving = true;
    }
    else {
        isMoving = false;
    }

    if (!isExecuting && isAlive) {
        m_hitbox.left += speed * time * dx;
        ResolveCollision(0, l_map);
        m_hitbox.top += speed * time * dy;
        ResolveCollision(1, l_map);
    }
    if (isSliding) {
        Sliding(time, l_map);
    }
    BodyAnimation(time);
    LegsAnimation(time);
    if (isAlive && !isExecuting) {
        m_sprite.setRotation(atan2(l_mousePos.y - m_sprite.getPosition().y, l_mousePos.x - m_sprite.getPosition().x) * 180.f / 3.14f);
        m_attackZone.setRotation(atan2(l_mousePos.y - m_attackZone.getPosition().y, l_mousePos.x - m_attackZone.getPosition().x) * 180.f / 3.14f);    
    }

    m_hitRect.setPosition(m_hitbox.left, m_hitbox.top);
    m_center.setPosition(m_hitbox.left + m_hitbox.width / 2, m_hitbox.top + m_hitbox.height / 2);
    m_sprite.setPosition(GetPosition());
    m_spriteLegs.setPosition(GetPosition());
    m_attackZone.setPosition(GetPosition());
    m_temp.setPosition(GetPosition());
    dx = dy = 0; 
}

void Player::Execution(bool isLeaning) {
    if (isAlive && !isExecuting) {
        if ((isLeaning == true || c_weapon.GetWeaponType(m_weapon) == WeaponType::ColdSteel) && isAlive) {
            if (m_weapon == WeaponTaken::Bat) {
                executingNums = 1;
                textureYOffset = 18;
                lastTile = 24;
            }
            if (m_weapon == WeaponTaken::Axe) {
                executingNums = 1;
                textureYOffset = 19;
                lastTile = 9;
            }
            if (m_weapon == WeaponTaken::Knife) {
                executingNums = 1;
                textureYOffset = 22;
                lastTile = 8;
            }
            if (m_weapon == WeaponTaken::Machete) {
                executingNums = 1;
                textureYOffset = 17;
                lastTile = 23;
            }
            if (m_weapon == WeaponTaken::Pipe) {
                executingNums = 1;
                textureYOffset = 21;
                lastTile = 24;
            }
            if (m_weapon == WeaponTaken::Sword) {
                executingNums = 1;
                textureYOffset = 20;
                lastTile = 16;
            }
            if (m_weapon == WeaponTaken::Unarmed) {
                executingNums = 1;
                textureYOffset = 23;
                lastTile = 9;
            }
            if (isLeaning) {
                executingNums = 1;
                textureYOffset = 24;
                lastTile = 10;
            }
            currentFrameBody = 0;
            m_spriteLegs.setTextureRect(sf::IntRect(0, 12 * 80, 80, 80));
            isExecuting = true;
        }
    }
}

void Player::BodyAnimation(float time) {
    if (isAlive) {
        if (isExecuting) {
            ExecutingAnimation(time);
        }
        else if (isAttacking) {
            AttackAnimation(time);
        }
        else if (isMoving) {
            WalkingAnimation(time);
        }
    }
}

void Player::ExecutingAnimation(float time) {
    currentFrameBody += 0.01f * time;
    if (currentFrameBody > lastTile) {
        if (executingCounter >= executingNums - 1) {
            currentFrameBody = 0;
            isExecuting = false;
            m_sprite.setTextureRect(sf::IntRect(int(currentFrameBody) * 80, 80 * c_weapon.GetOffsetOnTexture(m_weapon), 80, 80));
            return;
        }
        else {
            executingCounter++;
        }
        currentFrameBody = 0;
    }
    m_sprite.setTextureRect(sf::IntRect(int(currentFrameBody) * 80, textureYOffset * 80, 80, 80));
}

void Player::Attack() {
    if (GetWeaponType() == WeaponType::FireArm && bulletCounter <= 0) {
        return;
    }
    if (isAlive && !isExecuting) {
        if (!isAttacking) {
            currentFrameBody = 8;
            isAttacking = true;
            if (GetWeaponType() == WeaponType::FireArm) {
                bulletCounter--;
            }
        }
    }
}

void Player::Setdx(float dx) {
    if (isAlive) {
        this->dx = dx;
    }
}

void Player::Setdy(float dy) {
    if (isAlive) {
        this->dy = dy;
    }
}

void Player::SetRotation(float l_angle) {
    m_sprite.setRotation(l_angle);
    m_spriteLegs.setRotation(l_angle);
    m_attackZone.setRotation(l_angle);
}

void Player::SetPos(sf::Vector2f l_pos) {
    m_hitbox.left = l_pos.x - m_hitbox.width / 2;
    m_hitbox.top = l_pos.y - m_hitbox.height / 2;
    m_sprite.setPosition(m_hitbox.left + m_hitbox.width / 2, m_hitbox.top + m_hitbox.height / 2);
    m_spriteLegs.setPosition(m_hitbox.left + m_hitbox.width / 2, m_hitbox.top + m_hitbox.height / 2);
    m_attackZone.setPosition(m_hitbox.left + m_hitbox.width / 2, m_hitbox.top + m_hitbox.height / 2);
}


void Player::SelfTerminated(WeaponTaken l_weapon, sf::Vector2f l_point) {
    if (isAlive) {
        m_sprite.setRotation(atan2(l_point.y - GetPosition().y, l_point.x - GetPosition().x) * 180.f / 3.14f);
        m_sprite.rotate(180);
        if (l_weapon == WeaponTaken::Shotgun || l_weapon == WeaponTaken::DoubleBarrel || l_weapon == WeaponTaken::M16 || l_weapon == WeaponTaken::Silenser || l_weapon == WeaponTaken::MP5) {
            m_sprite.setTextureRect(sf::IntRect(rand() % 8 * 80, 13 * 80, 80, 80));
        }
        else if (l_weapon == WeaponTaken::Bat || l_weapon == WeaponTaken::Pipe) {
            m_sprite.setTextureRect(sf::IntRect(rand() % 9 * 80, 16 * 80, 80, 80));
        }
        else if (l_weapon == WeaponTaken::Machete || l_weapon == WeaponTaken::Knife || l_weapon == WeaponTaken::Sword || l_weapon == WeaponTaken::Axe) {
            m_sprite.setTextureRect(sf::IntRect(rand() % 3 * 80, 15 * 80, 80, 80));
        }

        m_spriteLegs.setTextureRect(sf::IntRect(0, 12 * 80, 80, 80));
        m_details->AddSmoke(GetPosition(), l_point, l_weapon);
        m_details->AddSplat(GetPosition(), l_weapon);
        m_details->AddPiece(GetPosition(), m_sprite.getRotation(), 3);

        float gippotinuse = sqrt((l_point.x - GetPosition().x) * (l_point.x - GetPosition().x) + (l_point.y - GetPosition().y) * (l_point.y - GetPosition().y));
        slidingX = -(l_point.x - GetPosition().x) / gippotinuse;
        slidingY = -(l_point.y - GetPosition().y) / gippotinuse;
        slidingSpeed = 0.4;
        isAlive = false;
        isSliding = true;
    }
}

void Player::ResolveBashCollision(int dir, const std::vector<Tile>* l_map) {
    for (int i = 0; i < (*l_map).size(); i++) {
        if (m_hitbox.intersects((*l_map).at(i).m_hitbox) && (*l_map).at(i).isCollidable) {
            if (dx > 0 && dir == 0) {
                m_hitbox.left = (*l_map).at(i).m_hitbox.left - m_hitbox.width;
            }
            else if (dx < 0 && dir == 0) {
                m_hitbox.left = (*l_map).at(i).m_hitbox.left + (*l_map).at(i).m_hitbox.width;
            }

            if (dy > 0 && dir == 1) {
                m_hitbox.top = (*l_map).at(i).m_hitbox.top - m_hitbox.height;
            }
            else if (dy < 0 && dir == 1) {
                m_hitbox.top = (*l_map).at(i).m_hitbox.top + (*l_map).at(i).m_hitbox.height;
            }
            slidingSpeed = 0;
        }
    }
}

void Player::Sliding(float time, const std::vector<Tile>* l_map) {
    if (slidingSpeed >= 0) {
        ResolveBashCollision(0, l_map);
        m_hitbox.left += slidingSpeed * time * slidingX;
        ResolveBashCollision(0, l_map);
        ResolveBashCollision(1, l_map);
        m_hitbox.top += slidingSpeed * time * slidingY;
        ResolveBashCollision(1, l_map);
        slidingSpeed -= 0.05;
    }
    else {
        isSliding = false;
        if (!isAlive) {
            m_details->AddPoll(GetPosition());
        }
    }
}