#pragma once

#include <SFML/Graphics.hpp>
#include <vector>

#include "State.hpp"

#include "Line.hpp"
#include "Level.hpp"
#include "SoundPlayer.hpp"
#include "ParticleSystem.hpp"

class Application {
	public:
		Application();
		int run();

		void switchState(State* state);

	private:
		void handleInput(const sf::Event& event);
		void tick(sf::Time dt);
		void render();

	private:
		sf::RenderWindow renderWindow;
		SoundPlayer soundPlayer;
		ParticleSystem particleSystem;

		Context context;
		State* currentState;
		State* nextState = nullptr;

		sf::Music music;
};




