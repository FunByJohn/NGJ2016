#include "Level.hpp"

#include <iostream>
#include <fstream>

// Load level from file

Level::Level(const std::string& filename) {
	std::fstream file;
	file.open(filename);

	int N, K;
	file >> N >> K;

	float x, y, z;
	while(N--) {
		file >> x >> y >> z;
		verts.emplace_back(x, y, z);
	}

	bool t;
	while(K--) {
		file >> x >> y >> t;
		lines.emplace_back(x, y, t);
	}

	file.close();
}

bool Level::isRotating() { return rotating; }

void Level::rotate(const sf::Event& event) {
	auto& vert = verts[2];
	switch(event.key.code) {
		case sf::Keyboard::Left:
			vert.x -= 10;
			break;

		case sf::Keyboard::Right:
			vert.x += 10;
			break;

		case sf::Keyboard::Up:
			vert.y -= 10;
			break;

		case sf::Keyboard::Down:
			vert.y += 10;
			break;
	}
}


