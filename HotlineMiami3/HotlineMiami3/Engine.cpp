#include "Engine.h"
#include <iostream>

Engine::Engine(std::vector<Enemy>* l_enemies, Player* l_player, Map* l_map, std::vector<Bullet>* l_playerBullets, std::vector<Bullet>* l_enemiesBullets, std::vector<Drop>* l_drop) {
	m_enemies = l_enemies;
	m_player = l_player;
	m_map = l_map;
	m_enemiesBullets = l_enemiesBullets;
	m_playerBullet = l_playerBullets;
	m_drop = l_drop;
}	

void Engine::Update(float time) {
	MelleAttackPhisic();
	BulletsPhysic();	
	DropPhysic();
}

void Engine::SetExecuteProcess(sf::Texture& l_texture) {
	EnemyFinishing(l_texture);
}

void Engine::EnemyFinishing(sf::Texture& l_texture) {
	for (int i = 0; i < m_enemies->size(); i++) {
		if (m_player->CheckInteractZone(m_enemies->at(i).GetPosition()) && m_enemies->at(i).isBashed) {
			if (m_player->GetWeaponType() == WeaponType::FireArm) {
				m_drop->push_back(Drop(l_texture, m_player->GetPosition(), m_player->GetTakenWeapon(), m_player->bulletCounter));
				m_player->Drop();
			}
			m_player->SetPos(m_enemies->at(i).GetPosition());
			m_player->SetRotation(m_enemies->at(i).GetRotation());

			if (m_enemies->at(i).isLeaning) {
				m_player->Execution(true);
			}
			else {
				m_player->Execution(false);
			}
			m_enemies->at(i).Finishing(m_player->GetTakenWeapon());
			break;
		}
	}
}

void Engine::InteractWithWeapon(sf::Texture& l_texture, sf::Vector2f pos) {
	if (m_player->GetTakenWeapon() != WeaponTaken::Unarmed && m_player->isAlive && !m_player->isExecuting) {
		m_drop->push_back(Drop(l_texture, m_player->GetPosition(), pos, m_player->GetTakenWeapon(), m_player->bulletCounter));
		m_player->Drop();
	}
	for (int i = 0; i < m_drop->size(); i++) {
		if (m_player->CheckInteractZone(m_drop->at(i).GetPosition()) && m_drop->at(i).speed == 0 && m_player->isAlive) {
			m_player->SetWeapon(m_drop->at(i).GetTakenWeapon(), m_drop->at(i).GetBulletNum());
			m_drop->erase(m_drop->begin() + i);
			break;
		}
	}
}

void Engine::DropPhysic() {
	for (int i = 0; i < m_drop->size(); i++) {
		if (m_drop->at(i).speed > 0) {
			for (int j = 0; j < m_enemies->size(); j++) {
				if (m_drop->at(i).GetHitBox().intersects(m_enemies->at(j).GetHitbox())) {
					if (m_enemies->at(j).isAlive && !m_enemies->at(j).isBashed && !m_enemies->at(j).isLeaning) {
						m_drop->at(i).speed = 0;
					}
					if (m_enemies->at(j).GetTakenWeapon() != WeaponTaken::Unarmed && m_enemies->at(j).isAlive) {
						m_drop->push_back(Drop(m_textureholder.weaponTexture, m_enemies->at(j).GetPosition(), m_enemies->at(j).GetTakenWeapon(), m_enemies->at(j).bulletCounter));
					}
					m_enemies->at(j).Bashing(m_drop->at(i).GetPosition());
				}
			}
		}
	}
}

void Engine::BulletsPhysic() {
	for (int i = 0; i < m_playerBullet->size(); i++) {
		for (int j = 0; j < m_enemies->size(); j++) {
			if (m_playerBullet->at(i).GetHitBox().intersects(m_enemies->at(j).GetHitbox()) && (m_enemies->at(j).isAlive || m_enemies->at(j).isSliding)) {
				if (m_enemies->at(j).GetTakenWeapon() != WeaponTaken::Unarmed && m_enemies->at(j).isAlive && m_enemies->at(j).GetTakenWeapon() != WeaponTaken::Unarmed) {
					m_drop->push_back(Drop(m_textureholder.weaponTexture, m_enemies->at(j).GetPosition(), m_enemies->at(j).GetTakenWeapon(), m_enemies->at(j).bulletCounter));
				}
				m_enemies->at(j).SelfTerminated(m_player->GetTakenWeapon(), m_player->GetPosition());
				m_playerBullet->at(i).isAlive = false;
				break;
			}
		}					
		if (!m_playerBullet->at(i).isAlive) {
			m_playerBullet->erase(m_playerBullet->begin() + i);
		}		
	}

	for (int i = 0; i < m_enemiesBullets->size(); i++) {
		if (m_enemiesBullets->at(i).GetHitBox().intersects(m_player->GetHitbox()) && m_player->isAlive) {
			m_player->SelfTerminated(WeaponTaken::Shotgun, m_enemiesBullets->at(i).GetPosition());
			m_enemiesBullets->at(i).isAlive = false;
		}
		if (!m_enemiesBullets->at(i).isAlive) {
			m_enemiesBullets->erase(m_enemiesBullets->begin() + i);
		}
	}
}

void Engine::MelleAttackPhisic() {
	for (int i = 0; i < m_enemies->size(); i++) {		
		if (m_player->GetAttackZone().intersects(m_enemies->at(i).GetHitbox()) && m_player->isAttacking && m_player->GetTakenWeapon() == WeaponTaken::Unarmed) {
			if (m_enemies->at(i).GetTakenWeapon() != WeaponTaken::Unarmed) {
				m_drop->push_back(Drop(m_textureholder.weaponTexture, m_enemies->at(i).GetPosition(), m_enemies->at(i).GetTakenWeapon(), m_enemies->at(i).bulletCounter));
			}
			m_enemies->at(i).Bashing(m_player->GetPosition());
		}
		else if (m_player->GetAttackZone().intersects(m_enemies->at(i).GetHitbox()) && m_player->isAttacking && m_player->GetWeaponType() == WeaponType::ColdSteel) {
			if (m_enemies->at(i).GetTakenWeapon() != WeaponTaken::Unarmed && m_enemies->at(i).isAlive) {
				m_drop->push_back(Drop(m_textureholder.weaponTexture, m_enemies->at(i).GetPosition(), m_enemies->at(i).GetTakenWeapon(), m_enemies->at(i).bulletCounter));
			}
			m_enemies->at(i).SelfTerminated(m_player->GetTakenWeapon(), m_player->GetPosition());
		}
		if (m_enemies->at(i).GetAttackZone().intersects(m_player->GetHitbox()) && m_enemies->at(i).isAttacking && m_enemies->at(i).GetWeaponType() == WeaponType::ColdSteel) {
			m_player->SelfTerminated(m_enemies->at(i).GetTakenWeapon(), m_enemies->at(i).GetPosition());
		}
	}
}

void Engine::Attack(sf::Vector2f pos) {
	if (m_player->GetWeaponType() == WeaponType::FireArm && !m_player->isAttacking && m_player->bulletCounter > 0) {
		AddBullets(pos);
	}
	m_player->Attack();
}

void Engine::AddBullets(sf::Vector2f pos) {
	if (m_player->GetTakenWeapon() == WeaponTaken::Shotgun) {
		for (int i = 0; i < 8; i++) {
			m_playerBullet->push_back(Bullet(m_textureholder.bulletTexture, m_player->GetBulletPos(), pos, m_player->GetTakenWeapon()));
		}
	}
	else if (m_player->GetTakenWeapon() == WeaponTaken::DoubleBarrel) {
		for (int i = 0; i < 14; i++) {
			m_playerBullet->push_back(Bullet(m_textureholder.bulletTexture, m_player->GetBulletPos(), pos, m_player->GetTakenWeapon()));
		}
	}
	else {
		m_playerBullet->push_back(Bullet(m_textureholder.bulletTexture, m_player->GetBulletPos(), pos, m_player->GetTakenWeapon()));
	}
}