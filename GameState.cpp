#include <cmath>
#include <cstdlib>

#include "GameState.hpp"

#include "LineShape.hpp"

#include "Consts.hpp"
#include "Util.hpp"

GameState::GameState(Context& context)
	: State(context),
	player(playerRadius, 64),
	level("level.txt", context),
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
				level.rotate(event);
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

	// Screenshake
	if(level.getCurrentAction() == GameplayAction::Moving) {
		float x = (rand() % 10000) / 2000.f, y = (rand() % 10000) / 2000.f;
		view.setCenter(sf::Vector2f(x, y));
	} else {
		view.setCenter(sf::Vector2f());
	}
}

void GameState::render() {
	sf::RenderWindow& renderWindow = context.window;
	renderWindow.setView(view);

	level.render(context.window);
}


