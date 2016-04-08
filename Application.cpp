#include "Application.hpp"
#include "LineShape.hpp"
#include <iostream>
#include <cmath>

#include "Util.hpp"
#include "Consts.hpp"

Application::Application()
	: renderWindow(sf::VideoMode(screenWidth, screenHeight), "NGJ2016"),
	player(playerRadius),
	level("level.txt") {

	player.setFillColor(sf::Color::Blue);
	centerOrigin(player);
}

int Application::run() {
	sf::Clock clock;

	sf::Time frameTime = sf::seconds(1.f / 60.f);
	sf::Time acc = sf::Time::Zero;
	sf::Time dt = sf::Time::Zero;
	while(renderWindow.isOpen()) {
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


void Application::handleInput(const sf::Event& event) {
	if(event.type == sf::Event::KeyPressed) {
		switch(event.key.code) {
			case sf::Keyboard::A:
			case sf::Keyboard::D:
			case sf::Keyboard::W:
			case sf::Keyboard::S:
				level.rotate(event);
				break;

			default:
				move(event.key.code);
		}
	}
}

void Application::tick(sf::Time dt) {
	time += dt;

	soundPlayer.tick(dt);

	level.verts[0].x = 400 + sin(time.asSeconds()) * 400;
	level.verts[1].y = 300 + cos(time.asSeconds()) * 150;
}

void Application::move(sf::Keyboard::Key keyCode) {
	soundPlayer.play(Sound::SWOOSH);
}

void Application::render() {
	renderWindow.clear(sf::Color::Black);

	auto& lines = level.lines;
	auto& verts = level.verts;

	for(int i = 0; i < lines.size(); i++) {
		Line& l = lines[i];

		float thickness = (l.traversable ? thickLineThickness : thinLineThickness);
		sf::Vector3<float> a = verts[l.a], b = verts[l.b];
		LineShape line(sf::Vector2f(a.x, a.y), sf::Vector2f(b.x, b.y), sf::Color::Yellow, thickness);
		renderWindow.draw(line);

		// Draw rounded line endpoints -- Should probably just draw all verts once
		sf::CircleShape c(thickness / 2.f);
		centerOrigin(c);
		c.setFillColor(sf::Color::Yellow);

		c.setPosition(a.x, a.y);
		renderWindow.draw(c);

		c.setPosition(b.x, b.y);
		renderWindow.draw(c);
	}

	auto vert = verts[playerPosition];
	player.setPosition(vert.x, vert.y);
	renderWindow.draw(player);

	//renderWindow.draw(circle);

	//renderWindow.draw(arr);

	renderWindow.display();
}

