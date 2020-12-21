#include "ArtificialIntelect.h"
#include <iostream>
#include <windows.h>

ArtificialIntelect::ArtificialIntelect(std::vector<Enemy>* l_enemies, Player* l_player, std::vector<Bullet>* l_enemyBullets) {
	m_enemies = l_enemies;
	m_player = l_player;
	m_enemyBullets = l_enemyBullets;
    col = 50;
    row = 50;
    size = col * row;
    for (int i = 0; i < m_enemies->size(); i++) {
        m_playerPos.at(i) = sf::Vector2f(0, 0);
    }
}

ArtificialIntelect::~ArtificialIntelect() {
    for (int i = 0; i < col * row; i++) {
        delete[] a[i];
    }
    delete[] a;
    delete[] minDistance;
    delete[] visitedVertecies;
    delete[] ver;
}

void ArtificialIntelect::CreateAI(Map& l_map, std::vector<Tile>* l_mapTest) {
    m_map = l_mapTest;
    CreateMeshMap(l_map);
    CreateRoutes(l_map);
}

void ArtificialIntelect::CreateMeshMap(Map& l_map) {
    testLine.setPrimitiveType(sf::PrimitiveType::Points);
    testLine.resize(0);

    meshmap.setPrimitiveType(sf::PrimitiveType::Points);
    meshmap.resize(size);

    for (int i = 0; i < size; i++) {
        meshmap[i].position = sf::Vector2f(i % col * 16 + 16, i / col * 16 + 16);
        meshmap[i].color = sf::Color::Red;
        
        for (int j = 0; j < l_map.GetCollidableTiles()->size(); j++) {
            //if(sf::IntRect(l_map.GetCollidableTiles()->at(j).GetHitbox().left, l_map.GetCollidableTiles()->at(j).GetHitbox().top, 16, 16).contains(static_cast<sf::Vector2i>(meshmap[i].position)) && l_map.GetCollidableTiles()->at(j).isCollidable) {
            if(sf::IntRect(l_map.GetCollidableTiles()->at(j).GetHitbox().left, l_map.GetCollidableTiles()->at(j).GetHitbox().top, 16, 16).contains(static_cast<sf::Vector2i>(meshmap[i].position))) {
                meshmap[i].color = sf::Color::Cyan;
                break;
            }
        }
    }
    
}

void ArtificialIntelect::CreateRoutes(Map& l_map) {
    a = new int* [size];
    for (int i = 0; i < size; i++) {
        a[i] = new int[size] {0};
    }

    for (int i = 0; i < size; i++) {
        for (int j = i + 1; j < size; j++) {
            if (i - col - 1 == j && i % col != 0 && i > col) {
                a[i][j] = 3;
                a[j][i] = 3;
            }
            if (i - col == j && i > col) {
                a[i][j] = 2;
                a[j][i] = 2;
            }
            if (i - col + 1 == j && ((i + 1) % col != 0) && i > col) {
                a[i][j] = 3;
                a[j][i] = 3;
            }
            if (i - 1 == j && i % col != 0) {
                a[i][j] = 2;
                a[j][i] = 2;
            }
            if (i + 1 == j && ((i + 1) % col != 0)) {
                a[i][j] = 2;
                a[j][i] = 2;
            }
            if (i + col - 1 == j && i % col != 0 && i < size - col) {
                a[i][j] = 3;
                a[j][i] = 3;
            }
            if (i + col == j && i < size - col) {
                a[i][j] = 2;
                a[j][i] = 2;
            }
            if (i + col + 1 == j && ((i + 1) % col != 0) && i < size - col) {
                a[i][j] = 3;
                a[j][i] = 3;
            }
            if (meshmap[i].color == sf::Color::Cyan || meshmap[j].color == sf::Color::Cyan) {
                a[i][j] = 0;
                a[j][i] = 0;                
            }
        }
    }
}

void ArtificialIntelect::MyDekster(int indexOfFirstPoint, int indexOfLastPoint) {
    if (indexOfFirstPoint < 0 || indexOfFirstPoint >= size || indexOfLastPoint < 0 || indexOfLastPoint >= size) {
        return;
    }

    delete[] minDistance;
    delete[] visitedVertecies;
    delete[] ver;
    testLine.clear();
    route.clear();

    minDistance = new int[size];
    visitedVertecies = new int[size];
    ver = new int[size];

    for (int i = 0; i < size; i++) {
        minDistance[i] = 10000;
        visitedVertecies[i] = 1;
    }
    ver[0] = indexOfLastPoint;
    minDistance[indexOfFirstPoint] = 0;
    
    int temp, minIndex, min;    

    do {
        minIndex = 10000;
        min = 10000;
        for (int i = 0; i < size; i++){
            if ((visitedVertecies[i] == 1) && (minDistance[i] < min)) {
                min = minDistance[i];
                minIndex = i;
            }
        }
        if (minIndex != 10000){
            for (int i = 0; i < size; i++) {
                if (a[minIndex][i] > 0) {
                    temp = min + a[minIndex][i];
                    if (temp < minDistance[i]){
                        minDistance[i] = temp;
                    }
                }
            }
            visitedVertecies[minIndex] = 0;
        }
    } while (minIndex < 10000);

    
    int k = 1;
    int weight = minDistance[indexOfLastPoint];

    while (indexOfLastPoint != indexOfFirstPoint){
        for (int i = 0; i < size; i++) {
            if (a[i][indexOfLastPoint] != 0) {
                int temp = weight - a[i][indexOfLastPoint];
                if (temp == minDistance[i]) {
                    weight = temp;
                    indexOfLastPoint = i;
                    ver[k] = i;
                    k++;
                }
            }
        }
    }
    
    for (int i = k - 1; i >= 0; i--) {
        testLine.append(meshmap[ver[i]]);      
    }
    for (int i = 0; i < testLine.getVertexCount(); i++) {
        testLine[i].color = sf::Color::Yellow;
    }
    for (int i = 0; i < testLine.getVertexCount(); i++) {
        route.push_back(testLine[i].position);
    }
}

void ArtificialIntelect::FollowRoute() {
    if (m_enemies->at(0).isAlive && !m_enemies->at(0).isBashed) {
        if (m_enemies->at(0).GoToPoint(route.back())) {
            route.pop_back();
        }
    }
    if (route.size() == 0) {
        switcher = false;
    }
}

void ArtificialIntelect::Update(float time) {
    for (int i = 0; i < m_enemies->size(); i++) {
        if (m_enemies->at(i).isAlive && !m_enemies->at(i).isBashed) {
            m_enemies->at(i).CheckTriggerRange(m_player->GetPosition());
            if (m_enemies->at(i).isTrigerred) {
                if (!CheckWall(i, time) && m_player->isAlive && (m_enemies->at(i).attackDelayCounter > 0.5f || m_enemies->at(i).GetTakenWeapon() == WeaponTaken::Unarmed)) {
                    m_enemies->at(i).GoToPoint(m_player->GetPosition());       
                    if (m_enemies->at(i).GetWeaponType() == WeaponType::ColdSteel && m_enemies->at(i).GetAttackZone().intersects(m_player->GetHitbox()) && m_player->isAlive && m_enemies->at(i).GetTakenWeapon() != WeaponTaken::Unarmed) {
                        m_enemies->at(i).Attack();
                    }
                    if (m_enemies->at(i).GetWeaponType() == WeaponType::FireArm && m_enemies->at(i).bulletCounter > 0 && m_player->isAlive && !m_enemies->at(i).isAttacking) {
                        m_enemies->at(i).Attack();
                        if (m_enemies->at(i).GetTakenWeapon() == WeaponTaken::Shotgun) {
                            for (int j = 0; j < 8; j++) {
                                m_enemyBullets->push_back(Bullet(m_textureHolder.bulletTexture, m_enemies->at(i).GetBulletPos(), m_player->GetPosition(), m_enemies->at(i).GetTakenWeapon()));
                            }
                        }
                        else if (m_enemies->at(i).GetTakenWeapon() == WeaponTaken::DoubleBarrel) {
                            for (int j = 0; j < 14; j++) {
                                m_enemyBullets->push_back(Bullet(m_textureHolder.bulletTexture, m_enemies->at(i).GetBulletPos(), m_player->GetPosition(), m_enemies->at(i).GetTakenWeapon()));
                            }
                        }
                        else {
                            m_enemyBullets->push_back(Bullet(m_textureHolder.bulletTexture, m_enemies->at(i).GetBulletPos(), m_player->GetPosition(), m_enemies->at(i).GetTakenWeapon()));
                        }
                    }
                }
                
            }            
        }
    }
}

int ArtificialIntelect::GetMeshPoint(sf::IntRect l_hitbox) {
    for (int i = 0; i < meshmap.getVertexCount(); i++) {
        if (l_hitbox.contains(sf::Vector2i(meshmap[i].position.x, meshmap[i].position.y))) {
            return i;
        }
    }
    return 0;
}

bool ArtificialIntelect::CheckWall(int enemyIndex, float time) {
    sf::Vector2i point = static_cast<sf::Vector2i>(m_enemies->at(enemyIndex).GetPosition());
    int step = 4;
    float angle = atan2f(m_player->GetPosition().y - m_enemies->at(enemyIndex).GetPosition().y, m_player->GetPosition().x - m_enemies->at(enemyIndex).GetPosition().x);
    float dx = cos(angle);
    float dy = sin(angle);

    for (float length = 0; length <= m_enemies->at(enemyIndex).TriggerRange; length += step) {
        for (int i = 0; i < m_map->size(); i++) {
            if (m_map->at(i).GetHitbox().contains(point) && m_map->at(i).isCollidable) {
                m_enemies->at(enemyIndex).attackDelayCounter = 0;
                return true;
            }
            if (m_player->GetHitbox().contains(point)) {
                m_enemies->at(enemyIndex).attackDelayCounter += time / 800;
                return false;
            }
        }
        point.x += dx * step;
        point.y += dy * step;
    }
    m_enemies->at(enemyIndex).attackDelayCounter += time / 800;
    return false;
}

void ArtificialIntelect::Render(sf::RenderWindow& l_window) {
    //l_window.draw(meshmap);
    //l_window.draw(testLine);
}

