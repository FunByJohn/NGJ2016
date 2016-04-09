#include "SoundPlayer.hpp"

// Load sounds
SoundPlayer::SoundPlayer() {
	buffers[Sound::SWOOSH].loadFromFile("res/sounds/swoosh.wav");
	buffers[Sound::TURN].loadFromFile("res/sounds/turn.wav");
	buffers[Sound::PING].loadFromFile("res/sounds/ping.wav");
}


void SoundPlayer::tick(sf::Time dt) {
	for(auto it = sounds.begin(); it != sounds.end();) {
		if(it->getStatus() == sf::Sound::Stopped)
			it = sounds.erase(it);
		else
			it++;
	}
}

#include <iostream>
sf::Sound& SoundPlayer::play(Sound::ID id) {
	if(buffers.find(id) == buffers.end())
		std::cout << "Couldn't find sound!" << std::endl;

	sounds.emplace_back(buffers[id]);
	sf::Sound& sound = sounds.back();
	sound.play();

	return sound;
}

