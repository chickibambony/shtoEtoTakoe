#include "Enemy.h"

Enemy::Enemy(sf::Texture& l_texture, sf::Vector2f l_pos, Details* l_details, WeaponTaken l_weapon) : MovableEntity(l_texture, l_pos, l_details) {
    if (l_weapon == WeaponTaken::DoubleBarrel) {
        bulletCounter = 2;
    }
    else if (l_weapon == WeaponTaken::Shotgun) {
        bulletCounter = 8;
    }
    else if (l_weapon == WeaponTaken::Silenser) {
        bulletCounter = 13;
    }
    else if (l_weapon == WeaponTaken::M16) {
        bulletCounter = 24;
    }
    else if (l_weapon == WeaponTaken::MP5) {
        bulletCounter = 30;
    }
    else {
        bulletCounter = 0;
    }
    
    SetWeapon(l_weapon, bulletCounter);
}

void Enemy::Update(float time, const std::vector<Tile>* l_map) {
    if ((dx != 0 || dy != 0) && !isBashed && isAlive) {
        isMoving = true;
    }
    else {
        isMoving = false;
    }

    if (!isBashed && isAlive) {
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

    m_hitRect.setPosition(m_hitbox.left, m_hitbox.top);
    m_center.setPosition(m_hitbox.left + m_hitbox.width / 2, m_hitbox.top + m_hitbox.height / 2);
    m_sprite.setPosition(m_hitbox.left + m_hitbox.width / 2, m_hitbox.top + m_hitbox.height / 2);
    m_spriteLegs.setPosition(m_hitbox.left + m_hitbox.width / 2, m_hitbox.top + m_hitbox.height / 2);
    m_attackZone.setPosition(m_hitbox.left + m_hitbox.width / 2, m_hitbox.top + m_hitbox.height / 2);

    dx = dy = 0;
}

void Enemy::Sliding(float time, const std::vector<Tile>* l_map) {
    if (slidingSpeed >= 0) {
        m_hitbox.left += slidingSpeed * time * slidingX;
        ResolveBashCollision(0, l_map);
        m_hitbox.top += slidingSpeed * time * slidingY;
        ResolveBashCollision(1, l_map);
        if (isLeaning) {
            m_sprite.setTextureRect(sf::IntRect(80, 80 * 31, 80, 80));
        }
        slidingSpeed -= 0.05;
    }
    else {
        isSliding = false;
        if (!isAlive) {
            m_details->AddPoll(GetPosition());
        }
    }
}

void Enemy::ResolveBashCollision(int dir, const std::vector<Tile>* l_map) {
    for (int i = 0; i < (*l_map).size(); i++) {
        if (m_hitbox.intersects((*l_map).at(i).m_hitbox) && (*l_map).at(i).isCollidable) {
            slidingSpeed = 0;
            if (isBashed) {
                isLeaning = true;
            }
            if (slidingX > 0 && dir == 0) {
                m_hitbox.left = (*l_map).at(i).m_hitbox.left - m_hitbox.width;
                m_sprite.setRotation(0);
            }
            else if (slidingX < 0 && dir == 0) {
                m_hitbox.left = (*l_map).at(i).m_hitbox.left + (*l_map).at(i).m_hitbox.width;
                m_sprite.setRotation(180);
            }

            if (slidingY > 0 && dir == 1) {
                m_hitbox.top = (*l_map).at(i).m_hitbox.top - m_hitbox.height;
                m_sprite.setRotation(90);
            }
            else if (slidingY < 0 && dir == 1) {
                m_hitbox.top = (*l_map).at(i).m_hitbox.top + (*l_map).at(i).m_hitbox.height;
                m_sprite.setRotation(-90);
            }
        }
    }
}

void Enemy::Attack() {
    if (GetWeaponType() == WeaponType::FireArm && bulletCounter <= 0) {
        return;
    }
    if (isAlive && !isBashed) {
        if (!isAttacking) {
            currentFrameBody = 8;
            isAttacking = true;
        }
        if (GetWeaponType() == WeaponType::FireArm) {
            bulletCounter--;
        }
    }
}

void Enemy::Bashing(sf::Vector2f l_point) {
    if (isAlive && !isBashed) {
        Drop();
        m_sprite.setRotation(atan2(l_point.y - GetPosition().y, l_point.x - GetPosition().x) * 180.f / 3.14f);
        m_sprite.rotate(180);
        currentFrameBody = 1;
        m_sprite.setTextureRect(sf::IntRect(80, 80 * 30, 80, 80));
        m_spriteLegs.setTextureRect(sf::IntRect(0, 12 * 80, 80, 80));
        isBashed = true;

        float gippotinuse = sqrt((l_point.x - GetPosition().x) * (l_point.x - GetPosition().x) + (l_point.y - GetPosition().y) * (l_point.y - GetPosition().y));
        slidingX = -(l_point.x - GetPosition().x) / gippotinuse;
        slidingY = -(l_point.y - GetPosition().y) / gippotinuse;
        slidingSpeed = 0.4;
        isSliding = true;
    }
}

void Enemy::SelfTerminated(WeaponTaken l_weapon, sf::Vector2f l_point) {
    if (isAlive && isLeaning && l_weapon != WeaponTaken::Unarmed) {
        if (c_weapon.GetWeaponType(l_weapon) == WeaponType::ColdSteel) {
            m_sprite.setTextureRect(sf::IntRect(((rand() % 5) + 1) * 80, 18 * 80, 80, 80));
        }
        else {
            m_sprite.setTextureRect(sf::IntRect((rand() % 6) * 80, 17 * 80, 80, 80));
        }
        m_spriteLegs.setTextureRect(sf::IntRect(0, 12 * 80, 80, 80));
        isAlive = false;
        m_details->AddSmoke(this->GetPosition(), l_point, l_weapon);
        m_details->AddSplat(this->GetPosition(), l_weapon);
    }

    if (isAlive && !isBashed) {
        m_sprite.setRotation(atan2(l_point.y - GetPosition().y, l_point.x - GetPosition().x) * 180.f / 3.14f);
        m_sprite.rotate(180);
        if (l_weapon == WeaponTaken::Shotgun || l_weapon == WeaponTaken::DoubleBarrel) {
            m_sprite.setTextureRect(sf::IntRect(rand() % 8 * 80, 13 * 80, 80, 80));
        }
        else if (l_weapon == WeaponTaken::M16 || l_weapon == WeaponTaken::Silenser || l_weapon == WeaponTaken::MP5) {
            m_sprite.setTextureRect(sf::IntRect(rand() % 8 * 80, 14 * 80, 80, 80));
        }
        else if (l_weapon == WeaponTaken::Bat || l_weapon == WeaponTaken::Pipe) {
            m_sprite.setTextureRect(sf::IntRect(rand() % 16 * 80, 15 * 80, 80, 80));
        }
        else if (l_weapon == WeaponTaken::Machete || l_weapon == WeaponTaken::Knife) {
            m_sprite.setTextureRect(sf::IntRect(rand() % 11 * 80, 19 * 80, 80, 80));
        }
        else if (l_weapon == WeaponTaken::Sword || l_weapon == WeaponTaken::Axe) {
            int offsetX = rand() % 5;
            m_sprite.setTextureRect(sf::IntRect(offsetX * 80, 22 * 80, 80, 80));
            if (offsetX == 0) {
                m_details->AddPiece(GetHeadPos(), GetRotation(), 0);
            }
            else if (offsetX == 1) {
                m_details->AddPiece(GetHeadPos(), GetRotation(), 1);
            }
            else if (offsetX == 2) {
                m_details->AddPiece(GetHeadPos(), GetRotation(), 2);
            }
        }

        m_spriteLegs.setTextureRect(sf::IntRect(0, 12 * 80, 80, 80));
        isAlive = false;
        m_details->AddSmoke(this->GetPosition(), l_point, l_weapon);
        m_details->AddSplat(this->GetPosition(), l_weapon);

        float gippotinuse = sqrt((l_point.x - GetPosition().x) * (l_point.x - GetPosition().x) + (l_point.y - GetPosition().y) * (l_point.y - GetPosition().y));
        slidingX = -(l_point.x - GetPosition().x) / gippotinuse;
        slidingY = -(l_point.y - GetPosition().y) / gippotinuse;
        slidingSpeed = 0.4;
        isSliding = true;
    }
}

void Enemy::BodyAnimation(float time) {
    if (isAlive) {
        if (isFinishing) {
            FinishingAnimation(time);
        }
        else if (isBashed) {
            BashedAnimation(time);
        }
        else if (isAttacking) {
            AttackAnimation(time);
        }
        else if (isMoving) {
            WalkingAnimation(time);
        }
     } 
}

void Enemy::Finishing(WeaponTaken l_weapon) {
    m_executionWeapon = l_weapon;
    if (isAlive && isBashed && !isSliding && !isFinishing) {
        if (l_weapon == WeaponTaken::Bat || l_weapon == WeaponTaken::Pipe) {
            finishingNums = 3;
            textureYOffset = 25;
            lastTile = 7;
        }
        else if (l_weapon == WeaponTaken::Axe) {
            finishingNums = 1;
            textureYOffset = 24;
            lastTile = 7;
        }
        else if (l_weapon == WeaponTaken::Knife) {
            finishingNums = 1;
            textureYOffset = 33;
            lastTile = 8;
        }
        else if (l_weapon == WeaponTaken::Machete) {
            finishingNums = 1;
            textureYOffset = 32;
            lastTile = 23;
        }
        else if (l_weapon == WeaponTaken::Sword) {
            finishingNums = 1;
            textureYOffset = 27;
            lastTile = 7;
        }
        else if (l_weapon == WeaponTaken::Unarmed) {
            finishingNums = 1;
            textureYOffset = 26;
            lastTile = 9;
        }
        if (isLeaning) {
            finishingNums = 1;
            textureYOffset = 34;
            lastTile = 9;
        }
        currentFrameBody = 0;
        m_spriteLegs.setTextureRect(sf::IntRect(0, 12 * 80, 80, 80));
        isFinishing = true;
    }
}

void Enemy::FinishingAnimation(float time) {
    currentFrameBody += 0.01f * time;
    if (currentFrameBody >= lastTile * (finishingCounter + 1)) {
        if (finishingCounter >= finishingNums - 1) {
            isFinishing = false;
            isAlive = false;
            isBashed = false;
            m_details->AddSquirt(GetHeadPos());
            if (m_executionWeapon == WeaponTaken::Machete) {
                m_details->AddPiece(GetHeadPos(), GetRotation(), 0);
            }
            finishingCounter = 0;
        }
        else {
            finishingCounter++;
        }
    }
    m_sprite.setTextureRect(sf::IntRect(int(currentFrameBody) * 80, textureYOffset * 80, 80, 80));
}

void Enemy::BashedAnimation(float time) {
    if (bashCounter > 3000) {
        currentFrameBody += 0.01f * time;
        if (isAlive && isLeaning) {
            if (currentFrameBody > 5) {
                currentFrameBody = 0;
                bashCounter = 0;
                isBashed = false;
                isLeaning = false;
            }
            m_sprite.setTextureRect(sf::IntRect(int(currentFrameBody) * 80, 80 * 31, 80, 80));
        }
        else {
            if (currentFrameBody > 7) {
                currentFrameBody = 0;
                bashCounter = 0;
                isBashed = false;
            }
            m_sprite.setTextureRect(sf::IntRect(int(currentFrameBody) * 80, 80 * 30, 80, 80));
        }
    }
    else {
        bashCounter += time;
    }
}

float Enemy::GetRotation() {
    return m_sprite.getRotation();
}

bool Enemy::GoToPoint(sf::Vector2f l_point) {
    if (m_hitbox.contains(static_cast<sf::Vector2i>(l_point))) {
        dx = dy = 0;
        return true;
    }

    float gippotinuse = sqrt((l_point.x - m_hitbox.left) * (l_point.x - m_hitbox.left) + (l_point.y - m_hitbox.top) * (l_point.y - m_hitbox.top));
    dx = (l_point.x - m_hitbox.left) / gippotinuse;
    dy = (l_point.y - m_hitbox.top) / gippotinuse;
    if (m_weapon == WeaponTaken::Unarmed) {
        dx = -dx;
        dy = -dy;
    }
    if (!isBashed) {
        m_spriteLegs.setRotation(atan2(l_point.y - m_spriteLegs.getPosition().y, l_point.x - m_spriteLegs.getPosition().x) * 180.f / 3.14f);
        m_sprite.setRotation(atan2(l_point.y - m_sprite.getPosition().y, l_point.x - m_sprite.getPosition().x) * 180.f / 3.14f);
        m_attackZone.setRotation(atan2(l_point.y - m_attackZone.getPosition().y, l_point.x - m_attackZone.getPosition().x) * 180.f / 3.14f);
    }
    return false;
}

void Enemy::CheckTriggerRange(sf::Vector2f l_point) {
    float gippotinuse = sqrt((l_point.x - m_hitbox.left + m_hitbox.width / 2) * (l_point.x - m_hitbox.left + m_hitbox.width / 2) + (l_point.y - m_hitbox.top + m_hitbox.height) * (l_point.y - m_hitbox.top + m_hitbox.height));
    if (gippotinuse <= TriggerRange) {
        isTrigerred = true;
    }
    else {
        isTrigerred = false;
        attackDelayCounter = 0;
    }
}

sf::Vector2f Enemy::GetHeadPos() {
    float x = cos(m_sprite.getRotation() / 180 * 3.14) * 20;
    float y = sin(m_sprite.getRotation() / 180 * 3.14) * 20;
    return sf::Vector2f(GetPosition().x + x, GetPosition().y + y);
}