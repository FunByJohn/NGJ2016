#include "Consts.hpp"

float screenWidth = 800;
float screenHeight = 800;

float thinLineThickness = 10.0f;
float thickLineThickness = 20.0f;

float playerRadius = 30.0f;

std::string gameTitle = "NYVINKEL";

sf::Color traversedColor = sf::Color(0, 0, 0, 128);
sf::Color notTraversedColor = sf::Color::Black;

int levelIndex = 0;
std::vector<std::string> levels = {
	// pres
	"level_first_depth.txt",
	"level.txt",
	"level_stairs.txt",
	"level_plus.txt",
	"level_boxes.txt",
	"level_depth.txt"

	// regular
	/*"level_first.txt",
	"level_first_depth.txt",
	"level.txt",
	"level3.txt",
	"level_uni.txt",
	"level_stairs.txt",
	"level_depth.txt",
	"level_boxes.txt",
	"level_plus.txt",
	"level_trickster.txt"*/
};