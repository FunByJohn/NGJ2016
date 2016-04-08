#pragma once

#include <SFML/Graphics.hpp>

#include <vector>
#include <string>

#include "Line.hpp"

typedef sf::Vector3<float> Vertex;

class Level {
	public:
		Level(const std::string& filename);

		std::vector<Vertex> verts;
		std::vector<Line> lines;

};
