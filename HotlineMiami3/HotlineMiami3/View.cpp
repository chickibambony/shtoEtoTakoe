#include "View.h"

View::View() {
	m_view.reset(sf::FloatRect(0, 0, 1920, 1080));
	m_view.zoom(0.3);
}

void View::Update(int x, int y) {
	m_view.setCenter(x, y);
}

sf::View& View::GetView() {
	return m_view;
}