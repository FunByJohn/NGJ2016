#pragma once

#include <SFML/Graphics.hpp>

#include <vector>
#include <string>

#include "Consts.hpp"
#include "Line.hpp"
#include "RotationMatrix.hpp"

typedef sf::Vector3<float> Vertex;

namespace GameplayAction {
	enum State {
		Idle,
		Rotating,
		Moving,
		Completed
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
		sf::Vector2f tempPerspective(Vertex v);

		std::vector<Vertex> verts;
		std::vector<Vertex> tempVerts;
		std::vector<Line> lines;

		int completedLines;

	private:
		bool testClosePoints(const Vertex& v1, const Vertex& v2);

		float timer;
		GameplayAction::State currentAction;

		/* rotation */
		float perspective;
		float rotationTime = 0.0f;
		float rotationDuration = 0.0f;
		float rotationDirection = 0.0f;
		RotationAxis::Axis rotationAxis;

		/* player */
		int playerVertex;
		int playerTargetVertex;
		int playerTraversedLine;
		float playerPosition;
		float playerAnimationTimer;
		float playerAnimationDuration;

		/* graphics stuff */
		sf::CircleShape playerShape;
		sf::CircleShape thinCircle;
		sf::CircleShape thickCircle;
};