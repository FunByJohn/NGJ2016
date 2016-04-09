#include "Level.hpp"
#include "Easing.hpp"

#include <iostream>
#include <fstream>

// Load level from file
Level::Level(const std::string& filename) {
	std::fstream file;
	file.open(filename);

	int N, K;
	file >> N >> K;

	float x, y, z;
	while(N--) {
		file >> x >> y >> z;
		verts.emplace_back(x, y, z);
		tempVerts.emplace_back(x, y, z);
	}

	bool t;
	while(K--) {
		file >> x >> y >> t;
		lines.emplace_back(x, y, t);
	}

	file.close();
}

void Level::rotate(const sf::Event& event) {
	if(!isRotating) {
    	isRotating = true;
    	rotationDuration = 0.5f;
    	rotationTime = 0.0f;

    	if(event.key.code == sf::Keyboard::A) {
    	    rotationDirection = -1.0f;
    	    rotationAxis = RotationAxis::Y;
    	}

    	if(event.key.code == sf::Keyboard::D) {
    	    rotationDirection = 1.0f;
    	    rotationAxis = RotationAxis::Y;
    	}

    	if(event.key.code == sf::Keyboard::W) {
    	    rotationDirection = 1.0f;
    	    rotationAxis = RotationAxis::X;
    	}

    	if(event.key.code == sf::Keyboard::S) {
    	    rotationDirection = -1.0f;
    	    rotationAxis = RotationAxis::X;
    	}
	}
}

void Level::update(sf::Time dt) {
	if(isRotating) {
        rotationTime += dt.asSeconds();

        float animationTime = Easing::sineInOut(rotationTime / rotationDuration);
        float currentAngle = 0.5 * M_PI * rotationDirection * animationTime;
        RotationMatrix rotation(rotationAxis, currentAngle);

        if(rotationTime >= rotationDuration) {
        	/* perform the final rotation on the actual vertices */
        	RotationMatrix finalRotation(rotationAxis, 0.5 * M_PI * rotationDirection);

            for(int i = 0; i < verts.size(); i++) {
                verts[i] = rotation.apply(verts[i]);
                tempVerts[i] = verts[i];
            }

            isRotating = false;

            seekPosition();
        } else {
        	/* rotation animation */
        	for(int i = 0; i < verts.size(); i++) {
	            tempVerts[i] = rotation.apply(verts[i]);
	        }
        }
    }
}