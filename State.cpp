#include "State.hpp"

Context::Context(Application* application, sf::RenderWindow& window, SoundPlayer& soundPlayer, ParticleSystem& particleSystem)
	: application(application), window(window), soundPlayer(soundPlayer), particleSystem(particleSystem) {}

State::State(Context& context) : context(context) {}
State::~State() {}


