#include <cmath>
#include "RotationMatrix.hpp"

RotationMatrix::RotationMatrix(RotationAxis::Axis _axis, float theta) {
    axis = _axis;

    float cosT, sinT;

    if(fabs(theta) > 0.5 * M_PI - 0.0001) {
        /* most likely the most important part of the entire code yes plz */
        if(theta > 0.0f) {
            cosT = 0.0f;
            sinT = 1.0f;
        } else {
            cosT = 0.0;
            sinT = -1.0;
        }
    } else {
        cosT = cos(theta);
        sinT = sin(theta);
    }

    if(axis == RotationAxis::X) {
        
        entries[0][0] = 1.0f; entries[0][1] = 0.0f; entries[0][2] = 0.0f;
        entries[1][0] = 0.0f; entries[1][1] = cosT; entries[1][2] = -sinT;
        entries[2][0] = 0.0f; entries[2][1] = sinT; entries[2][2] = cosT;

    } else if(axis == RotationAxis::Y) {
        
        entries[0][0] = cosT; entries[0][1] = 0.0f; entries[0][2] = sinT;
        entries[1][0] = 0.0f; entries[1][1] = 1.0f; entries[1][2] = 0.0f;
        entries[2][0] = -sinT; entries[2][1] = 0.0f; entries[2][2] = cosT;

    }
}

sf::Vector3<float> RotationMatrix::apply(const sf::Vector3<float> vert) {
    sf::Vector3<float> result;

    result.x = entries[0][0] * vert.x + entries[0][1] * vert.y + entries[0][2] * vert.z;
    result.y = entries[1][0] * vert.x + entries[1][1] * vert.y + entries[1][2] * vert.z;
    result.z = entries[2][0] * vert.x + entries[2][1] * vert.y + entries[2][2] * vert.z;
    
    return result;
}