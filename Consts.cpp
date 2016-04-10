#include "Consts.hpp"

float screenWidth = 800;
float screenHeight = 800;

float thinLineThickness = 10.0f;
float thickLineThickness = 20.0f;

float playerRadius = 30.0f;

std::string gameTitle = "Good game";

sf::Color traversedColor = sf::Color(0, 0, 0, 128);
sf::Color notTraversedColor = sf::Color::Black;

int levelIndex = 0;
std::vector<std::string> levels = {
	"level_stairs.txt",
	"level.txt",
	"level3.txt",
	"level_plus.txt",
	"level_trickster.txt"
};