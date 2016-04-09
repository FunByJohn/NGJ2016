#pragma once

#include <SFML/Graphics.hpp>

namespace RotationAxis {
    enum Axis {
        X,
        Y
    };
}

class RotationMatrix {
private:
    RotationAxis::Axis axis;
    float entries[3][3];
public:
    RotationMatrix(RotationAxis::Axis _axis, float theta);
    sf::Vector3<float> apply(const sf::Vector3<float>& vert);
};