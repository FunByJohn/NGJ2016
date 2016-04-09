#include "Application.hpp"
#include "LineShape.hpp"
#include <iostream>
#include <cmath>

#include "GameState.hpp"

#include "Consts.hpp"

Application::Application()
	: renderWindow(sf::VideoMode(screenWidth, screenHeight), "NGJ2016"),
	context(this, renderWindow, soundPlayer, particleSystem) {

	currentState = new GameState(context);
}

int Application::run() {
	sf::Clock clock;

	sf::Time frameTime = sf::seconds(1.f / 60.f);
	sf::Time acc = sf::Time::Zero;
	sf::Time dt = sf::Time::Zero;

	while(renderWindow.isOpen()) {
		// check if we should switch state
		if(nextState) {
			delete currentState;
			currentState = nextState;
			nextState = nullptr;
		}

		sf::Event event;
		while(renderWindow.pollEvent(event)) {
			switch(event.type) {
			case sf::Event::Closed:
				renderWindow.close();
				break;

			default:
				handleInput(event);
				break;
			}
		}

		while(acc <= frameTime) {
			dt = clock.restart();
			acc += dt;

			tick(dt);
		}

		acc -= frameTime;

		render();
	}
}


void Application::switchState(State* state) {
	nextState = state;
}


void Application::handleInput(const sf::Event& event) {
	currentState->handleInput(event);
}

void Application::tick(sf::Time dt) {
	soundPlayer.tick(dt);
	particleSystem.tick(dt);

	currentState->tick(dt);
}

void Application::render() {
	renderWindow.clear(sf::Color::White);

	currentState->render();

	renderWindow.draw(particleSystem);

	renderWindow.display();
}

