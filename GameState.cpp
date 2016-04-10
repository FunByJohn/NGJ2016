#include <cmath>
#include <cstdlib>

#include "GameState.hpp"
#include "Application.hpp"

#include "LineShape.hpp"

#include "Consts.hpp"
#include "Util.hpp"

GameState::GameState(Context& context)
	: State(context),
	player(playerRadius, 64),
	level(levels[levelIndex++], context),
	view(sf::Vector2f(0.f, 0.f), sf::Vector2f(screenWidth, screenHeight)) {

	player.setFillColor(sf::Color::Black);
	centerOrigin(player);

	filledRect.setSize(sf::Vector2f(15.0f, 15.0f));
    filledRect.setFillColor(sf::Color::Black);
    filledRect.setOrigin(0.0f, 0.0f);
    unfilledRect.setSize(sf::Vector2f(15.0f, 15.0f));
    unfilledRect.setOutlineColor(sf::Color::Black);
    unfilledRect.setOutlineThickness(2.0f);
    unfilledRect.setOrigin(0.0f, 0.0f);
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

			case sf::Keyboard::R:
				if(!done) {
					done = true;
					levelIndex--;
					context.application->switchState(new GameState(context));
				}
				break;
		}
	}
}

void GameState::tick(sf::Time dt) {
	time += dt;
	level.update(dt);

	if(level.getCurrentAction() == GameplayAction::Faded) {
		if(levelIndex < levels.size() && !done) {
			context.application->switchState(new GameState(context));
			done = true;
		}
	}

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

	// UI
	renderWindow.setView(renderWindow.getDefaultView());

	const int uiPadding = 15;
    const int uiSpacing = 5;
    const int uiBoxSize = 15;

	for(int i = 0; i < level.lines.size(); i++) {
	    float uiX = uiPadding + uiBoxSize * i + uiSpacing * i;
	    float uiY = uiPadding;

	    if(i <= level.completedLines - 1) {
	        filledRect.setPosition(uiX, uiY);
	        renderWindow.draw(filledRect);
	    } else {
	        unfilledRect.setPosition(uiX, uiY);
	        renderWindow.draw(unfilledRect);
	    }
	}

	renderWindow.setView(view);

	level.render(context.window);
}


