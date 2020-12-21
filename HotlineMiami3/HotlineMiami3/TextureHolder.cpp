#include "TextureHolder.h"

TextureHolder::TextureHolder() {
	mapTexture.loadFromFile("content/Textures/Tension.png");
	playerTexture.loadFromFile("content/Textures/PlayerTileset.png");
	enemyTexture.loadFromFile("content/Textures/EnemyTileset.png");
	bulletTexture.loadFromFile("content/Textures/Bullet.png");
	weaponTexture.loadFromFile("content/Textures/Weapon.png");
	detailsTexture.loadFromFile("content/Textures/Blood.png");
}