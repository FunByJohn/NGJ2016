#include <cmath>

#include "GameState.hpp"

#include "LineShape.hpp"

#include "Consts.hpp"
#include "Util.hpp"

GameState::GameState(Context& context)
	: State(context),
	player(playerRadius, 64),
	level("level2.txt", context.particleSystem),
	view(sf::Vector2f(0.f, 0.f), sf::Vector2f(screenWidth, screenHeight)) {

	player.setFillColor(sf::Color::Black);
	centerOrigin(player);
}


void GameState::handleInput(const sf::Event& event) {
	if(event.type == sf::Event::KeyPressed) {
		switch(event.key.code) {
			case sf::Keyboard::A:
			case sf::Keyboard::D:
			case sf::Keyboard::W:
			case sf::Keyboard::S:
				if(level.rotate(event))
					context.soundPlayer.play(Sound::TURN);
				break;

			case sf::Keyboard::Left:
			case sf::Keyboard::Up:
			case sf::Keyboard::Right:
			case sf::Keyboard::Down:
				level.move(event);
				break;
		}
	}
}

void GameState::tick(sf::Time dt) {
	time += dt;
	level.update(dt);
}

void GameState::render() {
	sf::RenderWindow& renderWindow = context.window;
	renderWindow.setView(view);

	level.render(context.window);
}


