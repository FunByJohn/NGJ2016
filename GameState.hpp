#pragma once

#include "State.hpp"

#include "Level.hpp"

class GameState : public State {
	public:
		GameState(Context& context);

		void handleInput(const sf::Event& event);
		void tick(sf::Time dt);
		void render();

		void move(sf::Keyboard::Key keyCode);

	private:
		Level level;

		int playerPosition = 0;
		sf::CircleShape player;

		sf::Time time;
		float pos;

};

