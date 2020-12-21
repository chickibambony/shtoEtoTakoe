#include "Drop.h"

Drop::Drop(sf::Texture &l_texture, sf::Vector2f l_pos, sf::Vector2f direction, WeaponTaken l_weapon, int l_bulletNum) {
    SetHitbox(l_pos, l_weapon);
    m_sprite.setTexture(l_texture);
    m_sprite.setTextureRect(sf::IntRect(60 * (static_cast<int>(l_weapon) - 1), 0, 60, 60));
    m_sprite.setOrigin(30, 30);
    m_sprite.setPosition(sf::Vector2f(m_hitbox.left + 30, m_hitbox.top + 30));

    m_spriteShadow.setTexture(l_texture);
    m_spriteShadow.setTextureRect(sf::IntRect(60 * (static_cast<int>(l_weapon) - 1), 60, 60, 60));
    m_spriteShadow.setOrigin(30, 30);
    m_spriteShadow.setPosition(sf::Vector2f(m_hitbox.left + 30, m_hitbox.top + 30));
    
    speed = 1.f / 1.6f;
    m_weapon = l_weapon;
    bulletNum = l_bulletNum;

    float gippotinuse = sqrt((direction.x - GetPosition().x) * (direction.x - GetPosition().x) + (direction.y - GetPosition().y) * (direction.y - GetPosition().y));
    dx = (direction.x - GetPosition().x) / gippotinuse;
    dy = (direction.y - GetPosition().y) / gippotinuse;
}

Drop::Drop(sf::Texture& l_texture, sf::Vector2f l_pos, WeaponTaken l_weapon, int l_bulletNum) {
    SetHitbox(l_pos, l_weapon);
    m_sprite.setTexture(l_texture);
    m_sprite.setTextureRect(sf::IntRect(60 * (static_cast<int>(l_weapon) - 1), 0, 60, 60));
    m_sprite.setOrigin(30, 30);
    m_sprite.setPosition(sf::Vector2f(m_hitbox.left + 30, m_hitbox.top + 30));

    m_spriteShadow.setTexture(l_texture);
    m_spriteShadow.setTextureRect(sf::IntRect(60 * (static_cast<int>(l_weapon) - 1), 60, 60, 60));
    m_spriteShadow.setOrigin(30, 30);
    m_spriteShadow.setPosition(sf::Vector2f(m_hitbox.left + 30, m_hitbox.top + 30));

    speed = 0.2f;
    m_weapon = l_weapon;
    bulletNum = l_bulletNum;

    float angle = rand() % (180 - (-180) + 1) - 180;
    dx = cos(angle / 180 * 3.14);
    dy = sin(angle / 180 * 3.14);
}

Drop::Drop(sf::Texture& l_texture, sf::Vector2f l_pos, WeaponTaken l_weapon) {
    SetHitbox(l_pos, l_weapon);
    m_sprite.setTexture(l_texture);
    m_sprite.setTextureRect(sf::IntRect(60 * (static_cast<int>(l_weapon) - 1), 0, 60, 60));
    m_sprite.setOrigin(30, 30);
    m_sprite.setPosition(sf::Vector2f(m_hitbox.left + 30, m_hitbox.top + 30));

    m_spriteShadow.setTexture(l_texture);
    m_spriteShadow.setTextureRect(sf::IntRect(60 * (static_cast<int>(l_weapon) - 1), 60, 60, 60));
    m_spriteShadow.setOrigin(30, 30);
    m_spriteShadow.setPosition(sf::Vector2f(m_hitbox.left + 30, m_hitbox.top + 30));

    speed = 0;
    dx = dy = 0;
    m_weapon = l_weapon;
    
    if (l_weapon == WeaponTaken::DoubleBarrel) {
        bulletNum = 2;
    }
    else if (l_weapon == WeaponTaken::Shotgun) {
        bulletNum = 8;
    }
    else if (l_weapon == WeaponTaken::Silenser) {
        bulletNum = 13;
    }
    else if (l_weapon == WeaponTaken::M16) {
        bulletNum = 24;
    }
    else if (l_weapon == WeaponTaken::MP5) {
        bulletNum = 30;
    }
    else {
        bulletNum = 0;
    }
}

void Drop::Update(float time, const std::vector<Tile>* l_map) {
    Animation(time);
    m_hitbox.left += speed * time * dx;
    ResolveCollision(0, l_map);    
    m_hitbox.top += speed * time * dy;    
    ResolveCollision(1, l_map); 
    
    if (speed <= 0) {
        speed = 0;
    }
    else {
        speed -= 0.01f;
        m_sprite.setPosition(sf::Vector2f(m_hitbox.left + 30, m_hitbox.top));
        m_spriteShadow.setPosition(sf::Vector2f(m_hitbox.left + 30, m_hitbox.top));
    }
}

void Drop::ResolveCollision(int dir, const std::vector<Tile>* l_map) {
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
            Reflect(dir);
            speed /= 2;
        }
    }
}

void Drop::Reflect(int dir) { 
    if (dir == 0) {
        dx = -dx;
    }
    if (dir == 1) {
        dy = -dy;
    }
}

void Drop::Animation(float time) {
    if (speed > 0) {
        m_sprite.rotate(time * speed * 2);
        m_spriteShadow.rotate(time * speed * 2);
    }
    else {
        if (animSpeed < -0.6 || animSpeed > 0.6) {
            animForce = -animForce;
        }
        m_sprite.move(time * animSpeed / 100, time * animSpeed / 100);
        animSpeed += animForce;
    }
}

void Drop::Render(sf::RenderWindow& l_window) {
    l_window.draw(m_spriteShadow);
    l_window.draw(m_sprite);
}

sf::IntRect Drop::GetHitBox() {
    return m_hitbox;
}

WeaponTaken Drop::GetTakenWeapon() {
    return m_weapon;
}

int Drop::GetBulletNum() {
    return bulletNum;
}

void Drop::SetHitbox(sf::Vector2f l_pos, WeaponTaken l_weapon) {
    m_hitbox.left = l_pos.x - 30;
    m_hitbox.top = l_pos.y - 30;
    if (l_weapon == WeaponTaken::Axe) {
        m_hitbox.width = 28;
        m_hitbox.height = 12;
    }
    else if (l_weapon == WeaponTaken::Bat) {
        m_hitbox.width = 21;
        m_hitbox.height = 4;
    }
    else if (l_weapon == WeaponTaken::DoubleBarrel) {
        m_hitbox.width = 28;
        m_hitbox.height = 9;
    }
    else if (l_weapon == WeaponTaken::Knife) {
        m_hitbox.width = 12;
        m_hitbox.height = 3;
    }
    else if (l_weapon == WeaponTaken::M16) {
        m_hitbox.width = 31;
        m_hitbox.height = 1;
    }
    else if (l_weapon == WeaponTaken::Machete) {
        m_hitbox.width = 29;
        m_hitbox.height = 5;
    }
    else if (l_weapon == WeaponTaken::MP5) {
        m_hitbox.width = 21;
        m_hitbox.height = 12;
    }
    else if (l_weapon == WeaponTaken::Pipe) {
        m_hitbox.width = 21;
        m_hitbox.height = 3;
    }
    else if (l_weapon == WeaponTaken::Shotgun) {
        m_hitbox.width = 27;
        m_hitbox.height = 9;
    }
    else if (l_weapon == WeaponTaken::Silenser) {
        m_hitbox.width = 13;
        m_hitbox.height = 6;
    }
    else if (l_weapon == WeaponTaken::Sword) {
        m_hitbox.width = 32;
        m_hitbox.height = 3;
    }
    //m_hitbox.width /= 2;
    //m_hitbox.height /= 2;
}

sf::Vector2f Drop::GetPosition() {
    return sf::Vector2f(m_hitbox.left + m_hitbox.width / 2, m_hitbox.top + m_hitbox.height / 2);
}