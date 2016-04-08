#pragma once

#include <SFML/Graphics.hpp>

#include <vector>
#include <string>

#include "Line.hpp"

typedef sf::Vector3<float> Vertex;

class Level {
	public:
		Level(const std::string& filename);

		bool isRotating();
		void rotate(const sf::Event& event);


		std::vector<Vertex> verts;
		std::vector<Line> lines;


	private:
		bool rotating = false;
};
