#include "IntroState.hpp"
#include "GameState.hpp"

#include "Application.hpp"

#include "Consts.hpp"

IntroState::IntroState(Context& context) : State(context) {
	font.loadFromFile("res/title.otf");
	text.setFont(font);
	text.setString(gameTitle);
	text.setCharacterSize(24);
}


void IntroState::handleInput(const sf::Event& event) {
	if(event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Space)
		context.application->switchState(new GameState(context));
}

void IntroState::tick(sf::Time dt) {

}

void IntroState::render() {
	context.window.draw(text);
}




