#include "Weapon.h"

Weapon::Weapon() {
	m_offsetOnTexture = { 0, 1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};
	m_animationLength = { 7, 9, 9, 7, 7, 9, 8, 2, 3, 3, 5, 12};
	m_weaponType = { WeaponType::ColdSteel, WeaponType::ColdSteel, WeaponType::ColdSteel, WeaponType::ColdSteel, WeaponType::ColdSteel,
		WeaponType::ColdSteel, WeaponType::ColdSteel, WeaponType::FireArm, WeaponType::FireArm, WeaponType::FireArm ,WeaponType::FireArm,
		WeaponType::FireArm, WeaponType::FireArm };
}

int Weapon::GetAnimationLength(WeaponTaken l_weapon) {
	return m_animationLength.at(static_cast<int>(l_weapon));
}

int Weapon::GetOffsetOnTexture(WeaponTaken l_weapon) {
	return m_offsetOnTexture.at(static_cast<int>(l_weapon));
}

WeaponType Weapon::GetWeaponType(WeaponTaken l_weapon) {
	return m_weaponType.at(static_cast<int>(l_weapon));
}