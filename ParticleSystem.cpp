#include "ParticleSystem.hpp"
#include <cstdlib>

ParticleData::ParticleData(Particle* p) : p(p), t(sf::Time::Zero) {}


float genVel(int min) {
	return -min + (rand() % (2 * min * 1000)) / 1000.f;
}

void ParticleSystem::explode(sf::Vector2f position, sf::Color color) {
	int count = 2 + rand() % 3;

	for(int i = 0; i < count; i++) {
		sf::Vector2f vel = {genVel(2000.f), genVel(1900.f)};


		particles.emplace_back(new Particle(vel, position, color));
	}
}

void ParticleSystem::tick(sf::Time dt) {
	for(auto it = particles.begin(); it != particles.end();) {
		it->t += dt;
		if(it->t >= sf::seconds(1.f)) {
			delete it->p;
			it = particles.erase(it);
		} else {
			auto& p = it->p;
			p->p1 += 1.f * p->velocity * dt.asSeconds();
			p->p2 += 1.2f * p->velocity * dt.asSeconds();

			it++;
		}
	}
}


void ParticleSystem::draw(sf::RenderTarget& target, sf::RenderStates states) const {
	sf::VertexArray verts(sf::Lines, particles.size() * 2);

	int i = 0;
	for(const ParticleData& p : particles) {
		verts[2*i].position = p.p->p1;
		verts[2*i+1].position = p.p->p2;
		verts[2*i].color = p.p->color;
		verts[2*i+1].color = p.p->color;
		i++;
	}

	target.draw(verts, states);
}

