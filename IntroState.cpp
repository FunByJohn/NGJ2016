#include "IntroState.hpp"
#include "GameState.hpp"

#include "Application.hpp"

#include "Consts.hpp"

IntroState::IntroState(Context& context) : State(context) {
	font.loadFromFile("res/title.ttf");
	text.setFont(font);
	text.setString(gameTitle);
	text.setCharacterSize(128);
	text.setColor(sf::Color::Black);

	auto bounds = text.getLocalBounds();
	text.setOrigin(bounds.width / 2, bounds.height / 2);

	text.setPosition(screenWidth / 2, screenHeight / 2);


	helpText.setFont(font);
	helpText.setString("PRESS SPACE TO START");
	helpText.setCharacterSize(48);
	helpText.setColor(sf::Color::Black);
	bounds = helpText.getLocalBounds();
	helpText.setOrigin(bounds.width / 2, bounds.height / 2);
	helpText.setPosition(screenWidth / 2, screenHeight * 0.75f);
}


void IntroState::handleInput(const sf::Event& event) {
	if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
		context.application->switchState(new GameState(context));
}

void IntroState::tick(sf::Time dt) {

}

void IntroState::render() {
	context.window.draw(text);
	context.window.draw(helpText);
}




