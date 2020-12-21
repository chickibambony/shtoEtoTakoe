#include "Menu.h"
#include <iostream>

Menu::Menu() {
	m_texture.loadFromFile("content/Textures/Menu.jpg");
	m_sprite.setTexture(m_texture);
	m_sprite.setPosition(0, 0);

	m_font.loadFromFile("content/Fonts/MenuFont.ttf");
	CreateTextItems();
}

void Menu::CreateTextItems() {
	//menu buttons
	items.push_back(sf::Text("START GAME", m_font, 60));
	items.push_back(sf::Text("CHAPTER", m_font, 60));
	items.push_back(sf::Text("EXIT", m_font, 60));
	for (int i = 0; i < items.size(); i++) {
		items.at(i).setFillColor(sf::Color(0, 240, 228));
		items.at(i).setOutlineThickness(2);
		items.at(i).setOutlineColor(sf::Color::Black);
	}

	itemShadows.push_back(sf::Text("START GAME", m_font, 60));
	itemShadows.push_back(sf::Text("CHAPTER", m_font, 60));
	itemShadows.push_back(sf::Text("EXIT", m_font, 60));
	for (int i = 0; i < itemShadows.size(); i++) {
		itemShadows.at(i).setFillColor(sf::Color(0, 0, 0, 50));
	}

	//levelsButtons
	levels.push_back(sf::Text("Test Level", m_font, 60));
	levels.push_back(sf::Text("Tension", m_font, 60));
	for (int i = 0; i < levels.size(); i++) {
		levels.at(i).setFillColor(sf::Color(0, 240, 228));
		levels.at(i).setOutlineThickness(2);
		levels.at(i).setOutlineColor(sf::Color::Black);
	}

	levelShadows.push_back(sf::Text("Test Level", m_font, 60));
	levelShadows.push_back(sf::Text("Tension", m_font, 60));
	for (int i = 0; i < levelShadows.size(); i++) {
		levelShadows.at(i).setFillColor(sf::Color(0, 0, 0, 50));
	}
}

void Menu::SetSize(sf::Vector2u l_windowSize) {
	m_windowSize = l_windowSize;
	for (int i = 0; i < items.size(); i++) {
		items.at(i).setPosition(m_windowSize.x / 2 - items.at(i).getGlobalBounds().width / 2, 400 + 100 * i);
	}
	for (int i = 0; i < itemShadows.size(); i++) {
		itemShadows.at(i).setPosition(m_windowSize.x / 2 - itemShadows.at(i).getGlobalBounds().width / 2 + 10, 400 + 100 * i + 10);
	}

	for (int i = 0; i < levels.size(); i++) {
		levels.at(i).setPosition((m_windowSize.x / 2 - levels.at(i).getGlobalBounds().width / 2), m_windowSize.y / 2 - levels.at(i).getGlobalBounds().height / 2);
	}
	for (int i = 0; i < levelShadows.size(); i++) {
		levelShadows.at(i).setPosition((m_windowSize.x / 2 - levelShadows.at(i).getGlobalBounds().width / 2) + 10, m_windowSize.y / 2 - levelShadows.at(i).getGlobalBounds().height / 2 + 10);
	}
}

void Menu::InteractWithMenu(sf::Keyboard::Key l_key, ProgramState& l_state, Levels& l_levels) {
	if (m_state == menuStates::Main) {
		if (l_key == sf::Keyboard::S) {
			itemPointer++;
		}
		else if (l_key == sf::Keyboard::W) {
			itemPointer--;
		}
		else if (l_key == sf::Keyboard::Enter) {
			if (itemPointer == 0) {
				l_state = ProgramState::Game;
			}
			else if (itemPointer == 1) {
				m_state = menuStates::Levels;
				itemPointer = 0;
			}
			else if (itemPointer == 2) {
				isClosed = true;
			}
		}

		if (itemPointer < 0) {
			itemPointer = items.size() - 1;
		}
		if (itemPointer >= items.size()) {
			itemPointer = 0;
		}
	}
	else if(m_state == menuStates::Levels){
		if (l_key == sf::Keyboard::D) {
			itemPointer++;
		}
		else if (l_key == sf::Keyboard::A) {
			itemPointer--;
		}
		else if (l_key == sf::Keyboard::Enter) {
			l_levels = static_cast<Levels>(itemPointer);
			l_state = ProgramState::Game;
		}
		else if (l_key == sf::Keyboard::Escape) {
			m_state = menuStates::Main;
			itemPointer = 0;
		}

		if (itemPointer < 0) {
			itemPointer = 0;
		}
		if (itemPointer >= levels.size()) {
			itemPointer = levels.size() - 1;
		}
	}
}

void Menu::Update(float time) {
	if (m_state == menuStates::Main) {
		for (int i = 0; i < items.size(); i++) {
			if (i != itemPointer) {
				items.at(i).setFillColor(sf::Color(0, 240, 228));
				items.at(i).setPosition(m_windowSize.x / 2 - items.at(i).getGlobalBounds().width / 2, 400 + 100 * i);
				itemShadows.at(i).setPosition(m_windowSize.x / 2 - itemShadows.at(i).getGlobalBounds().width / 2 + 10, 400 + 100 * i + 10);
			}
		}
		items.at(itemPointer).setFillColor(sf::Color(255, 0, 240));
	}
	else if(m_state == menuStates::Levels){
		
	}
	
}

void Menu::Animation(float time) {
	
	
}

void Menu::Render(sf::RenderWindow& l_window) {
	l_window.draw(m_sprite);

	if (m_state == menuStates::Main) {
		for (int i = 0; i < itemShadows.size(); i++) {
			l_window.draw(itemShadows.at(i));
		}
		for (int i = 0; i < items.size(); i++) {
			l_window.draw(items.at(i));
		}
	}
	else if (m_state == menuStates::Levels) {
		l_window.draw(levelShadows.at(itemPointer));
		l_window.draw(levels.at(itemPointer));
	}
}

bool Menu::HasClosed() {
	return isClosed;
}