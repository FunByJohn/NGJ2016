#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "Line.hpp"
#include "Level.hpp"

class Application {
	public:
		Application();
		int run();

	private:
		void handleInput(const sf::Event& event);
		void tick(sf::Time dt);
		void render();


	private:
		sf::RenderWindow renderWindow;

		Level level;

		int playerPosition = 0;
		sf::CircleShape player;

		sf::Time time;
		float pos;
};


