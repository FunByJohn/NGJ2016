#include "SoundPlayer.hpp"

// Load sounds
SoundPlayer::SoundPlayer() {
	sf::SoundBuffer& buffer = buffers[Sound::SWOOSH];
	buffer.loadFromFile("res/sounds/swoosh.wav");


}


void SoundPlayer::tick(sf::Time dt) {
	for(auto it = sounds.begin(); it != sounds.end();) {
		if(it->getStatus() == sf::Sound::Stopped)
			it = sounds.erase(it);
		else
			it++;
	}
}


sf::Sound& SoundPlayer::play(Sound::ID id) {
	sounds.emplace_back(buffers[id]);
	sf::Sound& sound = sounds.back();
	sound.play();

	return sound;
}

