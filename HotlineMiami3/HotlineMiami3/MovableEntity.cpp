#include "MovableEntity.h"
#include <iostream>

MovableEntity::MovableEntity(sf::Texture& l_texture, sf::Vector2f l_pos, Details* l_details) {
    m_hitbox.left = l_pos.x;
    m_hitbox.top = l_pos.y;
    m_hitbox.height = m_hitbox.width = 25;
    m_details = l_details;

    m_sprite.setTexture(l_texture);
    m_sprite.setTextureRect(sf::IntRect(0, 80 * c_weapon.GetOffsetOnTexture(m_weapon), 80, 80));
    m_spriteLegs.setTexture(l_texture);
    m_spriteLegs.setTextureRect(sf::IntRect(0, 80 * 12, 80, 80));    

    m_sprite.setOrigin(m_sprite.getLocalBounds().width / 2, m_sprite.getLocalBounds().height / 2);
    m_spriteLegs.setOrigin(m_spriteLegs.getLocalBounds().width / 2, m_spriteLegs.getLocalBounds().height / 2);

    m_attackZone.setSize(sf::Vector2f(10, 5));
    m_attackZone.setOrigin(-m_hitbox.width / 2, m_attackZone.getSize().y / 2);
    m_attackZone.setPosition(m_hitbox.left + m_hitbox.width / 2, m_hitbox.top + m_hitbox.height / 2);

    m_hitRect.setSize(sf::Vector2f(25, 25));
    m_hitRect.setFillColor(sf::Color::Transparent);
    m_hitRect.setOutlineColor(sf::Color::Blue);
    m_hitRect.setOutlineThickness(-2);
    m_hitRect.setPosition(m_hitbox.left, m_hitbox.top);

    m_center.setRadius(3);
    m_center.setFillColor(sf::Color::Transparent);
    m_center.setOutlineColor(sf::Color::Blue);
    m_center.setOutlineThickness(-1);
    m_center.setOrigin(3, 3);
    m_center.setPosition(m_hitbox.left + m_hitbox.width / 2, m_hitbox.top + m_hitbox.height / 2);
    
}

void MovableEntity::ResolveCollision(int dir, const std::vector<Tile>* l_map) {
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
        }
    }
}

void MovableEntity::LegsAnimation(float time) {
    if (isAlive) {
        SetLegDirection();
        if (isMoving) {
            currentFrameLegs += 0.01f * time;
            if (currentFrameLegs > 14) {
                currentFrameLegs = 0;
            }
        }
        else {
            currentFrameLegs = 0;
        }
        m_spriteLegs.setTextureRect(sf::IntRect(int(currentFrameLegs) * 80, 80 * 12, 80, 80));
    }
}

void MovableEntity::SetLegDirection() {
    if (dx == -1) {
        m_spriteLegs.setRotation(180);
    }
    if (dx == 1) {
        m_spriteLegs.setRotation(0);
    }
    if (dy == -1) {
        m_spriteLegs.setRotation(270);
    }
    if (dy == 1) {
        m_spriteLegs.setRotation(90);
    }
    if (dx == -1 && dy == -1) {
        m_spriteLegs.setRotation(225);
    }
    if (dx == 1 && dy == -1) {
        m_spriteLegs.setRotation(315);
    }
    if (dx == 1 && dy == 1) {
        m_spriteLegs.setRotation(45);
    }
    if (dx == -1 && dy == 1) {
        m_spriteLegs.setRotation(135);
    }
}

sf::IntRect MovableEntity::GetAttackZone() {
    return (sf::IntRect)m_attackZone.getGlobalBounds();
}

void MovableEntity::SetWeapon(WeaponTaken l_weapon, int bulletNum) {
    this->m_weapon = l_weapon;
    bulletCounter = bulletNum;
    m_sprite.setTextureRect(sf::IntRect(int(currentFrameBody) * 80, 80 * c_weapon.GetOffsetOnTexture(m_weapon), 80, 80));
}

WeaponType MovableEntity::GetWeaponType() {
    return c_weapon.GetWeaponType(m_weapon);
}

WeaponTaken MovableEntity::GetTakenWeapon() {
    return m_weapon;
}

void MovableEntity::Drop() {
    SetWeapon(WeaponTaken::Unarmed, 0);
}

void MovableEntity::WalkingAnimation(float time) {
    currentFrameBody += 0.005f * time;
    if (currentFrameBody > 8) {
        currentFrameBody = 0;
    }
    m_sprite.setTextureRect(sf::IntRect(int(currentFrameBody) * 80, 80 * c_weapon.GetOffsetOnTexture(m_weapon), 80, 80));
}

void MovableEntity::AttackAnimation(float time) {
    currentFrameBody += 0.015f * time;
    if (currentFrameBody > c_weapon.GetAnimationLength(m_weapon) + 8) {
        currentFrameBody = 0;
        isAttacking = false;
        if (c_weapon.GetWeaponType(m_weapon) == WeaponType::ColdSteel) {
            m_sprite.setScale(m_sprite.getScale().x, -m_sprite.getScale().y);
        }
    }
    m_sprite.setTextureRect(sf::IntRect(int(currentFrameBody) * 80, 80 * c_weapon.GetOffsetOnTexture(m_weapon), 80, 80));
}

void MovableEntity::Render(sf::RenderWindow& l_window) {
    l_window.draw(m_spriteLegs);
    l_window.draw(m_sprite);
    l_window.draw(m_hitRect);
    l_window.draw(m_center);
}

bool MovableEntity::CheckInteractZone(sf::Vector2f target) {
    float gippotinuse = sqrt((target.x - GetPosition().x) * (target.x - GetPosition().x) + (target.y - GetPosition().y) * (target.y - GetPosition().y));
    if (gippotinuse <= 80) {
        return true;
    }
    else {
        return false;
    }
}

sf::Vector2f MovableEntity::GetBulletPos() {
    float x = cos(m_sprite.getRotation() / 180 * 3.14) * 10;
    float y = sin(m_sprite.getRotation() / 180 * 3.14) * 10;
    return sf::Vector2f(GetPosition().x + x, GetPosition().y + y);
}