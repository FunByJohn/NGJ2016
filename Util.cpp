#include "Util.hpp"

void centerOrigin(sf::Shape& s) {
	auto bounds = s.getLocalBounds();

	s.setOrigin(bounds.width / 2.f, bounds.height / 2.f);
}

