#pragma once

#include <SFML/Graphics.hpp>

class LineShape : public sf::Drawable {
public:
    LineShape(const sf::Vector2f& point1, const sf::Vector2f& point2, sf::Color color = sf::Color::Yellow, float thickness = 2.f);
    void draw(sf::RenderTarget &target, sf::RenderStates states) const;


private:
    sf::Vertex vertices[4];
    float thickness;
    sf::Color color;
};

