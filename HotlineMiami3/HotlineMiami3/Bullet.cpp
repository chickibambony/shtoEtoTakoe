#include "Bullet.h"

Bullet::Bullet(sf::Texture& l_texture, sf::Vector2f bulletCoords, sf::Vector2f direction, WeaponTaken l_weapon) {
    m_hitBox.left = bulletCoords.x;
    m_hitBox.top = bulletCoords.y;
    m_hitBox.width = m_hitBox.height = 10;
    
    m_sprite.setTexture(l_texture);
    m_sprite.setTextureRect(sf::IntRect(0, 0, 80, 80));
    m_sprite.setOrigin(m_sprite.getLocalBounds().width / 2, m_sprite.getLocalBounds().height / 2);
    m_sprite.setPosition(sf::Vector2f(m_hitBox.left + m_hitBox.width/ 2, m_hitBox.top + m_hitBox.height / 2));
    this->direction = direction;
    SetDispersion(l_weapon);
    SetSpeed(l_weapon);

    float angle = atan2(direction.y - m_hitBox.top, direction.x - m_hitBox.left) * 180 / 3.14;
    angle += rand() % (dispersion * 2  + 1) - dispersion;

    dx = cos(angle / 180 * 3.14);
    dy = sin(angle / 180 * 3.14);
    m_sprite.setRotation(atan2(dy, dx) * 180.f / 3.14f);
}

void Bullet::Update(float time, const std::vector<Tile>* l_map) {
    Animation(time);
    m_hitBox.left += speed * time * dx;
    ResolveCollision(0, l_map);
    m_hitBox.top += speed * time * dy;
    ResolveCollision(1, l_map);
    m_sprite.setPosition(sf::Vector2f(m_hitBox.left + m_hitBox.width / 2, m_hitBox.top + m_hitBox.height / 2));

    lifeTime -= time;
    if (lifeTime <= 0) {
        isAlive = false;
    }
}

void Bullet::ResolveCollision(int dir, const std::vector<Tile>* l_map) {
    for (int i = 0; i < (*l_map).size(); i++) {     
        if (m_hitBox.intersects((*l_map).at(i).m_hitbox) && (*l_map).at(i).isCollidable) {
            currentFrame = 4;
            isCollided = true;
            m_sprite.rotate(180);
            speed = 0;
            if (dx > 0 && dir == 0) {
                m_hitBox.left = (*l_map).at(i).m_hitbox.left - m_hitBox.width;
            }
            else if (dx < 0 && dir == 0) {
                m_hitBox.left = (*l_map).at(i).m_hitbox.left + (*l_map).at(i).m_hitbox.width;
            }

            if (dy > 0 && dir == 1) {
                m_hitBox.top = (*l_map).at(i).m_hitbox.top - m_hitBox.height;
            }
            else if (dy < 0 && dir == 1) {
                m_hitBox.top = (*l_map).at(i).m_hitbox.top + (*l_map).at(i).m_hitbox.height;
            }
        }
    }
}

void Bullet::Animation(float time) {    
    if (!isCollided) {
        currentFrame += 0.01f * time;
        if (currentFrame > 4) {
            currentFrame = 0;
        }
    }
    else {
        currentFrame += 0.03f * time;
        if (currentFrame > 14) {
            isAlive = false;
        }
    }
    m_sprite.setTextureRect(sf::IntRect(int(currentFrame) * 80, 0, 80, 80));
}

sf::IntRect Bullet::GetHitBox() {
    return m_hitBox;
}

void Bullet::Render(sf::RenderWindow& l_window) {
    l_window.draw(m_sprite);
}

void Bullet::SetDispersion(WeaponTaken l_weapon) {
    if (l_weapon == WeaponTaken::DoubleBarrel) {
        dispersion = 10;
    }
    else if (l_weapon == WeaponTaken::Shotgun) {
        dispersion = 3;
    }
    else if (l_weapon == WeaponTaken::Silenser || l_weapon == WeaponTaken::MP5) {
        dispersion = 2;
    }
    else {
        dispersion = 5;
    }
}

void Bullet::SetSpeed(WeaponTaken l_weapon) {
    speed += (rand() % (2 * 1 + 1) - 1) / 7.f;
}

sf::Vector2f Bullet::GetPosition() {
    return sf::Vector2f(m_hitBox.left + m_hitBox.width / 2, m_hitBox.top + m_hitBox.height / 2);
}