#pragma once

struct Line {
	int a, b;
	bool traversable;
	bool traversed;

	Line(int a, int b, bool traversable);
};

