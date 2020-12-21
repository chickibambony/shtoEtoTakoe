#pragma once
#include<vector>

enum class WeaponType {
    FireArm,
    ColdSteel
};

enum class WeaponTaken {
    Unarmed,
    Pipe,
    Bat,
    Axe,
    Sword,
    Knife,
    Machete,
    M16,
    MP5,
    Silenser,
    DoubleBarrel,
    Shotgun
};

class Weapon
{
public:
    Weapon();
    int GetAnimationLength(WeaponTaken l_weapon);
    int GetOffsetOnTexture(WeaponTaken l_weapon);
    WeaponType GetWeaponType(WeaponTaken l_weapon);

private:
    std::vector<int> m_animationLength;
    std::vector<int> m_offsetOnTexture;
    std::vector<WeaponType> m_weaponType;
};

