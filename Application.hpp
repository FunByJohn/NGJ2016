#pragma once

#include <SFML/Graphics.hpp>

class Application {
	public:
		Application();
		int run();

	private:
		void tick(sf::Time dt);
		void render();


	private:
		sf::CircleShape circle;
		sf::RenderWindow renderWindow;
};


