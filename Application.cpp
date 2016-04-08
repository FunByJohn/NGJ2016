#include "Application.hpp"
#include <iostream>

Application::Application()
	: renderWindow(sf::VideoMode(800, 600), "NGJ2016"),
	circle(50) {

	circle.setFillColor(sf::Color::Green);
}

int Application::run() {
	sf::Clock clock;

	sf::Time frameTime = sf::seconds(1.f / 60.f);
	sf::Time acc = sf::Time::Zero;
	sf::Time dt = sf::Time::Zero;
	while(renderWindow.isOpen()) {
		sf::Event event;
		while(renderWindow.pollEvent(event)) {
			if(event.type == sf::Event::Closed)
				renderWindow.close();
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


void Application::tick(sf::Time dt) {
	circle.setPosition(dt.asMicroseconds(), 0);
}

void Application::render() {
	renderWindow.clear(sf::Color::Black);

	renderWindow.draw(circle);

	renderWindow.display();
}

