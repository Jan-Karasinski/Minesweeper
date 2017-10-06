#pragma once

struct Position {
	size_t x, y;

	Position() = default;
	Position(size_t, size_t);
};

struct Field {
	bool isMine{ 0 };
	bool isCovered{ 1 };
	bool isFlagged{ 0 };
	Position Coord;
	size_t MinesCount{ 0 };

	Field() = default;
};