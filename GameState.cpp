#include <cmath>

#include "GameState.hpp"

#include "LineShape.hpp"

#include "Consts.hpp"
#include "Util.hpp"

GameState::GameState(Context& context)
	: State(context),
	player(playerRadius, 64),
	level("level.txt"),
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

			/*case sf::Keyboard::Up:
				context.particleSystem.explode(sf::Vector2f(100.f, 100.f));
				break;*/

			case sf::Keyboard::Left:
			case sf::Keyboard::Up:
			case sf::Keyboard::Right:
			case sf::Keyboard::Down:
				level.move(event);
				break;

			default:
				move(event.key.code);
		}
	}
}

void GameState::tick(sf::Time dt) {
	time += dt;
	level.update(dt);
}

void GameState::move(sf::Keyboard::Key keyCode) {
	context.soundPlayer.play(Sound::SWOOSH);
}

sf::Vector2f tempPerspective(Vertex v) {
	sf::Vector2f newVert;

	newVert.x = v.x * ((v.z + 500.0) / 1000.0);
    newVert.y = v.y * ((v.z + 500.0) / 1000.0);

    return newVert;
}

void GameState::render() {
	sf::RenderWindow& renderWindow = context.window;
	renderWindow.setView(view);

	level.render(context.window);

	auto& lines = level.lines;
	auto& verts = level.tempVerts;

	for(int i = 0; i < lines.size(); i++) {
		Line& l = lines[i];

		float thickness = (l.traversable ? thickLineThickness : thinLineThickness);
		sf::Color color = (l.traversed ? traversedColor : notTraversedColor);
		sf::Vector3<float> a = verts[l.a], b = verts[l.b];
		LineShape line(tempPerspective(a), tempPerspective(b), color, thickness);
		renderWindow.draw(line);
	}

	for(const auto& vert : verts) {
		sf::CircleShape c(thinLineThickness);
		centerOrigin(c);
		c.setFillColor(sf::Color::Black);
		c.setPosition(tempPerspective(vert));
		renderWindow.draw(c);
	}

	const auto& vert = verts[level.playerVertex];
	player.setPosition(tempPerspective(vert));
	renderWindow.draw(player);
}


