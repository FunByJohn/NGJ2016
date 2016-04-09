#pragma once

#include <SFML/Graphics.hpp>
#include <functional>

#include "SoundPlayer.hpp"
#include "ParticleSystem.hpp"

class Application;

class Context {
public:
	Application* application;

	sf::RenderWindow& window;
	SoundPlayer& soundPlayer;
	ParticleSystem& particleSystem;

	Context(Application* application, sf::RenderWindow& window, SoundPlayer& soundPlayer, ParticleSystem& particleSystem);
};

class State {
	public:
		State(Context& context);
		virtual ~State();

		virtual void handleInput(const sf::Event& event) = 0;
		virtual void tick(sf::Time dt) = 0;
		virtual void render() = 0;

	protected:
		Context& context;

};

