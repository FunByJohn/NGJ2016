#pragma once

#include <SFML/Graphics.hpp>

#include <vector>
#include <string>

#include "Line.hpp"
#include "RotationMatrix.hpp"

typedef sf::Vector3<float> Vertex;

class Level {
	public:
		Level(const std::string& filename);

		void rotate(const sf::Event& event);
		void move(const sf::Event& event);
		void update(sf::Time dt);
		void seekPosition();

		std::vector<Vertex> verts;
		std::vector<Vertex> tempVerts;
		std::vector<Line> lines;

	private:
		bool isRotating = false;
		float rotationTime = 0.0f;
		float rotationDuration = 0.0f;
		float rotationDirection = 0.0f;
		RotationAxis::Axis rotationAxis;
};
