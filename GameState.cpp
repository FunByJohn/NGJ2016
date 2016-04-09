#include <cmath>

#include "GameState.hpp"

#include "LineShape.hpp"

#include "Consts.hpp"
#include "Util.hpp"

GameState::GameState(Context& context)
	: State(context),
	player(playerRadius),
	level("level.txt") 	{

	player.setFillColor(sf::Color::Blue);
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

			case sf::Keyboard::Up:
				context.particleSystem.explode(sf::Vector2f(100.f, 100.f));
				break;

			default:
				move(event.key.code);
		}
	}
}

void GameState::tick(sf::Time dt) {
	time += dt;

	level.verts[0].x = 400 + sin(time.asSeconds()) * 400;
	level.verts[1].y = 300 + cos(time.asSeconds()) * 150;
}

void GameState::move(sf::Keyboard::Key keyCode) {
	context.soundPlayer.play(Sound::SWOOSH);
}

void GameState::render() {
	sf::RenderWindow& renderWindow = context.window;

	auto& lines = level.lines;
	auto& verts = level.verts;

	for(int i = 0; i < lines.size(); i++) {
		Line& l = lines[i];

		float thickness = (l.traversable ? thickLineThickness : thinLineThickness);
		sf::Vector3<float> a = verts[l.a], b = verts[l.b];
		LineShape line(sf::Vector2f(a.x, a.y), sf::Vector2f(b.x, b.y), sf::Color::Yellow, thickness);
		renderWindow.draw(line);
	}

	for(const auto& vert : verts) {
		sf::CircleShape c(thinLineThickness);
		centerOrigin(c);
		c.setFillColor(sf::Color::Yellow);
		c.setPosition(vert.x, vert.y);
		renderWindow.draw(c);
	}

	const auto& vert = verts[playerPosition];
	player.setPosition(vert.x, vert.y);
	renderWindow.draw(player);
}


