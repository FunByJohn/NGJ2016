#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "Line.hpp"
#include "Level.hpp"
#include "SoundPlayer.hpp"

class Application {
	public:
		Application();
		int run();

	private:
		void handleInput(const sf::Event& event);
		void tick(sf::Time dt);
		void render();

		void move(sf::Keyboard::Key keyCode);

	private:
		sf::RenderWindow renderWindow;
		SoundPlayer soundPlayer;
		Level level;

		int playerPosition = 0;
		sf::CircleShape player;

		sf::Time time;
		float pos;
};


