#include "OutroState.hpp"

#include "Consts.hpp"

OutroState::OutroState(Context& context) : State(context) {
	font.loadFromFile("res/title.ttf");
	text.setFont(font);
	text.setString("FUNBYJOHN N ZII");
	text.setCharacterSize(86);
	text.setColor(sf::Color::Black);

	auto bounds = text.getLocalBounds();
	text.setOrigin(bounds.width / 2, bounds.height / 2);

	text.setPosition(screenWidth / 2, screenHeight / 2);


	helpText.setFont(font);
	helpText.setString("MADE FOR NGJ2016");
	helpText.setCharacterSize(48);
	helpText.setColor(sf::Color::Black);
	bounds = helpText.getLocalBounds();
	helpText.setOrigin(bounds.width / 2, bounds.height / 2);
	helpText.setPosition(screenWidth / 2, screenHeight * 0.75f);
}


void OutroState::handleInput(const sf::Event& event) {
}

void OutroState::tick(sf::Time dt) {

}

void OutroState::render() {
	context.window.setView(context.window.getDefaultView());
	context.window.draw(text);
	context.window.draw(helpText);
}




