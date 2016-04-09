#pragma once

#include <SFML/Audio.hpp>
#include <map>
#include <list>

#include "Sounds.hpp"

class SoundPlayer {
	public:
		SoundPlayer();
		void tick(sf::Time dt);

		sf::Sound& play(Sound::ID id);

	private:
		std::map<Sound::ID, sf::SoundBuffer> buffers;
		std::list<sf::Sound> sounds;
};

