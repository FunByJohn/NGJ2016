#pragma once

#include <SFML/Graphics.hpp>

#include <vector>
#include <string>

#include "Line.hpp"
#include "RotationMatrix.hpp"

typedef sf::Vector3<float> Vertex;

namespace GameplayAction {
	enum State {
		Idle,
		Intro,
		Rotating,
		Moving
	};
}

class Level {
	public:
		Level(const std::string& filename);

		void rotate(const sf::Event& event);
		void move(const sf::Event& event);
		void update(sf::Time dt);
		void render(sf::RenderWindow& renderWindow);
		void postRotateSeekPosition();

		std::vector<Vertex> verts;
		std::vector<Vertex> tempVerts;
		std::vector<Line> lines;

		int playerVertex;

	private:
		GameplayAction::State currentAction;

		/* rotation */
		float rotationTime = 0.0f;
		float rotationDuration = 0.0f;
		float rotationDirection = 0.0f;
		RotationAxis::Axis rotationAxis;

		/* player */
		int playerTargetVertex;
		float playerPosition;
		float playerAnimationTimer;
		float playerAnimationDuration;
};