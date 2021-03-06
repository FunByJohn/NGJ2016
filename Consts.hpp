#pragma once

#include <string>
#include <SFML/Graphics.hpp>
#include <vector>

extern float screenWidth;
extern float screenHeight;
extern bool fullscreen;

extern float thinLineThickness;
extern float thickLineThickness;

extern float playerRadius;

extern std::string gameTitle;

extern sf::Color traversedColor;
extern sf::Color notTraversedColor;

extern int levelIndex;
extern std::vector<std::string> levels;

