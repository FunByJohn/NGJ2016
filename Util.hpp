#pragma once

#include <SFML/Graphics.hpp>

void centerOrigin(sf::Shape& s) {
	auto bounds = s.getLocalBounds();

	s.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

