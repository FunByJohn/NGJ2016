#pragma once

#include <SFML/Graphics.hpp>


struct Particle {
	sf::Vector2f velocity;
	sf::Vector2f p1, p2;

	Particle(sf::Vector2f velocity, sf::Vector2f position);
};

