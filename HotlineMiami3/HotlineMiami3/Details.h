#pragma once
#include <SFML/Graphics.hpp>
#include "Weapon.h"
#include "Tile.h"
#include <vector>

class BloodPoll;
class BloodSquirt;
class BloodSmoke;
class BloodSplat;
class BodyPiece;

class Details {
public:
	Details(sf::Texture* l_texture);
	void Update(float time);
	void Render(sf::RenderWindow& l_window);
	void AddPoll(sf::Vector2f l_pos);
	void AddSquirt(sf::Vector2f l_pos);
	void AddSmoke(sf::Vector2f l_pos, sf::Vector2f l_damageSourcePos, WeaponTaken l_weapon);
	void AddPiece(sf::Vector2f l_pos, float angle, int partOfBody);
	void AddSplat(sf::Vector2f l_pos, WeaponTaken l_weapon);
	void Clear();

private:
	std::vector<BloodSquirt> m_bloodSquirts;
	std::vector<BloodPoll> m_bloodPools;
	std::vector<BloodSmoke> m_bloodSmokes;
	std::vector<BloodSplat> m_bloodSplats;
	std::vector<BodyPiece> m_pieces;
	std::vector<sf::Sprite> m_squitsSplats;
	sf::Texture *m_texture;
};

class BloodPoll
{
public:
	BloodPoll(sf::Texture& l_texture, sf::Vector2f l_pos);
	void Animation(float time);
	void Render(sf::RenderWindow& l_window);

private:
	sf::Sprite m_sprite;
	bool isAnimated = true;
	int bloodPoll = 0;

	float currentFrame;
};

class BloodSquirt
{
public:
	BloodSquirt(sf::Texture& l_texture, sf::Vector2f l_pos, float angle);
	void Animation(float time);
	void Render(sf::RenderWindow& l_window);
	bool isAlive;

private:
	sf::Sprite m_sprite;
	int offsetY;
	float currentFrame;
};

class BloodSmoke {
public:
	BloodSmoke(sf::Texture& l_texture, sf::Vector2f l_pos, float angle);
	void Animation(float time);
	void Render(sf::RenderWindow& l_window);
	bool isAlive;

private:
	sf::Sprite m_sprite;
	int offsetY;
	float currentFrame;
	float AnimationSpeed;
};

class BloodSplat {
public:
	BloodSplat(sf::Texture& l_texture, sf::Vector2f l_pos);
	void Animation(float time);
	void Render(sf::RenderWindow& l_window);

private:
	float dx, dy;
	sf::Sprite m_sprite;
	float speed;
	float currentFrame;
};

class BodyPiece {
public:
	BodyPiece(sf::Texture& l_texture, sf::Vector2f l_pos, float angle, int partOfBody);
	void Animation(float time);
	void Update(float time, const std::vector<Tile>* l_map);
	void Render(sf::RenderWindow& l_window);

private:
	float dx, dy;
	sf::Sprite m_sprite;
	float speed;
};