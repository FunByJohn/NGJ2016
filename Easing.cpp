#include "Easing.hpp"


namespace Easing {
	float sineInOut(float t) {
	    return -0.5f * (cos(M_PI * t) - 1.0f);
	};
}

