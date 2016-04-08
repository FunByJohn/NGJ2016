#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "Line.hpp"

typedef sf::Vector3<float> Vertex;

class Application {
	public:
		Application();
		int run();

	private:
		void tick(sf::Time dt);
		void render();


	private:
		sf::RenderWindow renderWindow;

		std::vector<Vertex> verts;
		std::vector<Line> lines;

		int playerPosition = 0;
		sf::CircleShape player;

		sf::Time time;
		float pos;
};


