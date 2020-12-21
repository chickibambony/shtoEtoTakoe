#pragma once
#include <SFML/Graphics.hpp>

enum class menuStates {
	Main,
	Pause,
	Levels
};

enum class Levels {
	Test,
	Tension
};

enum class ProgramState {
	Menu,
	Game
};

class Menu
{
public:
	Menu();
	void SetSize(sf::Vector2u windowSize);
	void Update(float time);
	void Render(sf::RenderWindow& l_window);
	void Animation(float time);
	void InteractWithMenu(sf::Keyboard::Key l_key, ProgramState& l_state, Levels& l_levels);
	bool HasClosed();

private:
	bool isClosed = false;
	void CreateTextItems();
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	sf::Font m_font;
	int itemPointer = 0;
	float animationOffset;
	float animSpeed = 0.f;
	float animForce = 0.03f;
	sf::Vector2u m_windowSize = sf::Vector2u(800, 600);
	menuStates m_state = menuStates::Main;
	std::vector<sf::Text> levels;
	std::vector<sf::Text> levelShadows;
	std::vector<sf::Text> items;
	std::vector<sf::Text> itemShadows;
};

