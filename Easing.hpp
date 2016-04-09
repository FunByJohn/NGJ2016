#pragma once

#include <cmath>

#ifndef M_PI
#define M_PI 3.14159265358979323846
#endif

namespace Easing {
	float sineInOut(float t) {
	    return -0.5f * (cos(M_PI * t) - 1.0f);
	};
}