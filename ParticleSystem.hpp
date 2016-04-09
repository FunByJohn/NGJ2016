#pragma once

#include <SFML/Graphics.hpp>
#include <cstdlib>
#include <list>

#include "Particle.hpp"

struct ParticleData {
	Particle* p;
	sf::Time t;

	ParticleData(Particle* p);
};

class ParticleSystem : public sf::Drawable {
	public:
		void explode(sf::Vector2f position, sf::Color color = sf::Color::White);
		void tick(sf::Time dt);

	private:
		void draw(sf::RenderTarget& target, sf::RenderStates states) const;

	private:
		std::list<ParticleData> particles;
};

