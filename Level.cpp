#include "Level.hpp"
#include "Easing.hpp"

#include <iostream>
#include <fstream>

// Load level from file
Level::Level(const std::string& filename) {
    currentAction = GameplayAction::Idle;

    /*
        First line contains two numbers: N, K, where N is the number of vertices, and K is the number of lines.
        Then follow N lines, each line containing the (x,y,z) coordinates for a point.
        Then follow K lines, where each line contains (a,b,t) where a,b are indices into the vertex array, and t is whether the line is traversable or not.
        The final line contains the vertex S which the player starts at.
    */

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

    int S;
    file >> S;

    std::cout << "Start at: " << S << std::endl;

    playerVertex = S;
    playerTargetVertex = playerVertex;
    playerPosition = 0.0f;
    playerAnimationTimer = 0.0f;
    playerAnimationDuration = 0.1f;

	file.close();
}

void Level::rotate(const sf::Event& event) {
	if(currentAction == GameplayAction::Idle) {
    	currentAction = GameplayAction::Rotating;
    	rotationDuration = 0.3f;
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

void Level::move(const sf::Event& event) {
    if(currentAction == GameplayAction::Idle) {
        if(event.key.code == sf::Keyboard::Left) {

        }
    }
}

void Level::update(sf::Time dt) {
	switch(currentAction) {

        case GameplayAction::Idle:
        {
            break;
        }
        
        case GameplayAction::Rotating:
        {
            rotationTime += dt.asSeconds();

            float animationTime = Easing::sineInOut(rotationTime / rotationDuration);
            float currentAngle = 0.5 * M_PI * rotationDirection * animationTime;
            RotationMatrix rotation(rotationAxis, currentAngle);

            if(rotationTime >= rotationDuration) {
            	/* perform the final rotation on the actual vertices */
            	RotationMatrix finalRotation(rotationAxis, 0.5 * M_PI * rotationDirection);

                for(int i = 0; i < verts.size(); i++) {
                    verts[i] = finalRotation.apply(verts[i]);
                    tempVerts[i] = verts[i];
                }

                postRotateSeekPosition();
                currentAction = GameplayAction::Idle;
            } else {
            	/* rotation animation */
            	for(int i = 0; i < verts.size(); i++) {
    	            tempVerts[i] = rotation.apply(verts[i]);
    	        }
            }

            break;
        }

        default:
            break;
    }
}

void Level::render(sf::RenderWindow& renderWindow) {
    //std::cout << "render pls" << std::endl;
}

void Level::postRotateSeekPosition() {
	/*
        Find the point that matches our current (x,y) with the highest z.
    */

    const float proximity = 5.0f;

    int match = playerVertex;
    auto& current = verts[playerVertex];
    float matchZ = -1000000.0;

    for(int i = 0; i < verts.size(); i++) {
        auto& vert = verts[i];
        float dx = current.x - vert.x;
        float dy = current.y - vert.y;

        if(dx * dx + dy * dy <= proximity * proximity) {
            if(vert.z > matchZ) {
                match = i;
                matchZ = vert.z;
            }
        }
    }

    playerVertex = match;
}