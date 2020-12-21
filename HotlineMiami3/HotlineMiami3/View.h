#pragma once
#include<SFML/Graphics.hpp>

class View
{
public:
	View();
	sf::View& GetView();
	void Update(int x, int y);

private:
	sf::View m_view;
};

