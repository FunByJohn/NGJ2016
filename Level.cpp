#include "Level.hpp"
#include "Easing.hpp"
#include "Util.hpp"
#include "LineShape.hpp"

#include <iostream>
#include <fstream>

// Load level from file
Level::Level(const std::string& filename, Context& context)
    : context(context),
    thinCircle(0.5 * thinLineThickness, 16),
    thickCircle(0.5 * thickLineThickness, 16),
    fader(sf::Vector2f(screenWidth, screenHeight)),
    currentAction(GameplayAction::NotStarted) {

    /*
        First line contains two numbers: N, K, where N is the number of vertices, and K is the number of lines.
        Then follow N lines, each line containing the (x,y,z) coordinates for a point.
        Then follow K lines, where each line contains (a,b) where a,b are indices into the vertex array.
        The final line contains the vertex S which the player starts at.
    */

    timer = 0.0f;
    perspective = 0.0f;
    completedLines = 0;

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

	while(K--) {
		file >> x >> y;
		lines.emplace_back(x, y);
	}

    int S;
    file >> S;

    playerVertex = S;
    playerTargetVertex = playerVertex;
    playerPosition = 0.0f;
    playerAnimationTimer = 0.0f;
    playerAnimationDuration = 0.1f;

	file.close();

    playerShape = sf::CircleShape(playerRadius, 64);
    playerShape.setFillColor(sf::Color::Black);
    centerOrigin(playerShape);

    centerOrigin(thinCircle);
    centerOrigin(thickCircle);

    thinCircle.setFillColor(sf::Color::Black);
    thickCircle.setFillColor(sf::Color::Black);

    centerOrigin(fader);
    fader.setFillColor(sf::Color(255, 255, 255, 255));
}

GameplayAction::State Level::getCurrentAction() { return currentAction; }

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

        context.soundPlayer.play(Sound::TURN);
	}
}

bool fuzzyEquals(float a, float b) {
    const float eps = 0.05f;
    return (fabs(a - b) <= eps);
}

void Level::move(const sf::Event& event) {
    if(currentAction == GameplayAction::Idle) {
        /*
            Select a line that satisfies the following:
            a) One of its end points lies on where the player currently is
            b) The direction to the other point matches that which the player just pressed

            In case of multiple matches:
            - Select the one with highest z
        */

        const float proximity = 5.0f;

        sf::Vector2<float> movement(0.0f, 0.0f);

        if(event.key.code == sf::Keyboard::Left) movement.x = -1.0f;
        if(event.key.code == sf::Keyboard::Right) movement.x = 1.0f;
        if(event.key.code == sf::Keyboard::Up) movement.y = -1.0f;
        if(event.key.code == sf::Keyboard::Down) movement.y = 1.0f;

        auto& player = verts[playerVertex];
        int match = -1; // the line's index
        float matchZ = -1000000.0;
        int matchEndpoint;

        for(int i = 0; i < lines.size(); i++) {
            auto& line = lines[i];

            if(!line.traversed) {
                auto& v1 = verts[line.a];
                auto& v2 = verts[line.b];

                bool close1 = testClosePoints(player, v1);
                bool close2 = testClosePoints(player, v2);

                if(close1 && close2)
                    continue; // Ignore lines pointing out/in

                if(!close1 && !close2)
                    continue; // Ignore unrelated lines

                // Exactly one of the points must be close
                int otherId;
                Vertex other;

                if(close1) {
                    other = v2;
                    otherId = line.b;
                } else {
                    other = v1;
                    otherId = line.a;
                }

                float dx = other.x - player.x;
                float dy = other.y - player.y;
                float d = sqrt(dx * dx + dy * dy);

                if(fuzzyEquals(dx / d, movement.x) &&
                   fuzzyEquals(dy / d, movement.y)) {

                    if(other.z > matchZ) {
                        match = i;
                        matchZ = other.z;
                        matchEndpoint = otherId;
                    }
                }
            }
        }

        if(match != -1) {
            // Found a match!
            const float distanceDuration = 0.1f;

            float dx = player.x - verts[matchEndpoint].x;
            float dy = player.y - verts[matchEndpoint].y;
            float d = sqrt(dx * dx + dy * dy);

            playerTargetVertex = matchEndpoint;
            playerPosition = 0.0f;
            playerAnimationTimer = 0.0f;
            playerAnimationDuration = d / 1000.0;
            currentAction = GameplayAction::Moving;
            playerTraversedLine = match;
        }
    }
}

void Level::update(sf::Time dt) {
    // rotation showcase thing
    //for(int i = 0; i < )
    //

	switch(currentAction) {
        case GameplayAction::NotStarted:
        {
            timer += dt.asSeconds();

            if(timer < fadeDuration.asSeconds()) {
                float alpha = 255 - 255 * (timer / fadeDuration.asSeconds());
                fader.setFillColor(sf::Color(255, 255, 255, alpha));
            } else {
                currentAction = GameplayAction::Idle;
                fader.setFillColor(sf::Color(255, 255, 255, 0));
            }

            break;
        }

        case GameplayAction::Idle:
        {
            completedLines = 0;

            for(int i = 0; i < lines.size(); i++) {
                if(lines[i].traversed)
                    completedLines++;
            }

            if(lines.size() == completedLines) {
                timer = 0;
                currentAction = GameplayAction::Completed;
                context.soundPlayer.play(Sound::VICTORY);
            }

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

        case GameplayAction::Moving:
        {
            playerAnimationTimer += dt.asSeconds();
            playerPosition = playerAnimationTimer / playerAnimationDuration;

            if(playerAnimationTimer >= playerAnimationDuration) {
                playerPosition = 1.0f;
                playerVertex = playerTargetVertex;
                currentAction = GameplayAction::Idle;
                lines[playerTraversedLine].traversed = true;

                auto& vert = verts[playerVertex];
                context.particleSystem.explode({vert.x, vert.y}, sf::Color::Black);
                context.soundPlayer.play(Sound::PING);
            }

            break;
        }

        case GameplayAction::Completed:
        {
            float add = dt.asSeconds();

            if(perspective < 1.0f) {
                perspective += 0.3f * add;
                playerShape.setRadius(playerRadius * (1.0f - perspective));
            } else {
                perspective = 1.0f;
                playerShape.setRadius(0.001f);
            }

            centerOrigin(playerShape);

            timer += add;

            RotationMatrix yRot(RotationAxis::Y, perspective * M_PI * add * sin(0.7 * timer));
            RotationMatrix xRot(RotationAxis::X, perspective * 0.7 * M_PI * add * cos(1.2 * timer));

            for(int i = 0; i < verts.size(); i++) {
                tempVerts[i] = xRot.apply(yRot.apply(verts[i]));
                verts[i] = tempVerts[i];
            }

            if(timer >= fadeTime.asSeconds()) {
                if(timer - fadeTime.asSeconds() < fadeDuration.asSeconds()) {
                    float alpha = (timer - fadeTime.asSeconds()) / fadeDuration.asSeconds();
                    alpha *= 255;

                    fader.setFillColor(sf::Color(255, 255, 255, alpha));
                } else {
                    fader.setFillColor(sf::Color(255, 255, 255, 255));
                    currentAction = GameplayAction::Faded;
                }
            }

            break;
        }

        default:
            break;
    }
}

sf::Vector2f Level::tempPerspective(Vertex v) {
    if(perspective <= 0.001f)
        return {v.x, v.y};

    sf::Vector2f newVert;

    float wantedX = v.x * ((v.z + 500.0) / 1000.0);
    float wantedY = v.y * ((v.z + 500.0) / 1000.0);

    newVert.x = v.x + (wantedX - v.x) * perspective;
    newVert.y = v.y + (wantedY - v.y) * perspective;

    return newVert;
}

void Level::render(sf::RenderWindow& renderWindow) {
    for(int i = 0; i < lines.size(); i++) {
        Line& l = lines[i];
        float thickness = (l.traversed ? thickLineThickness : thinLineThickness);
        sf::Vector3<float> a = tempVerts[l.a], b = tempVerts[l.b];
        LineShape line(tempPerspective(a), tempPerspective(b), sf::Color::Black, thickness);
        renderWindow.draw(line);

        if(!l.traversed) {
            thinCircle.setPosition(tempPerspective(a));
            renderWindow.draw(thinCircle);
            thinCircle.setPosition(tempPerspective(b));
            renderWindow.draw(thinCircle);
        } else {
            thickCircle.setPosition(tempPerspective(a));
            renderWindow.draw(thickCircle);
            thickCircle.setPosition(tempPerspective(b));
            renderWindow.draw(thickCircle);
        }
    }

    if(currentAction != GameplayAction::Moving) {
        const auto& vert = tempVerts[playerVertex];
        playerShape.setPosition(tempPerspective(vert));
    } else {
        auto& from = tempVerts[playerVertex];
        auto& to = tempVerts[playerTargetVertex];

        Vertex v = from + (to - from) * playerPosition;
        playerShape.setPosition(tempPerspective(v));

        LineShape connecting(tempPerspective(from), tempPerspective(v), sf::Color::Black, thickLineThickness);
        renderWindow.draw(connecting);

        thickCircle.setPosition(tempPerspective(from));
        renderWindow.draw(thickCircle);
    }

    renderWindow.draw(playerShape);

    renderWindow.draw(fader);
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

bool Level::testClosePoints(const Vertex& v1, const Vertex& v2) {
    const float proximity = 5.0f;

    float dx = v1.x - v2.x;
    float dy = v1.y - v2.y;

    return (dx * dx + dy * dy <= proximity);
}
