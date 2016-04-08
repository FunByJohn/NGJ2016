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

	while(K--) {
		file >> x >> y;
		lines.emplace_back(x, y);
	}

	file.close();
}

