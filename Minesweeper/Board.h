#pragma once
#include <vector>

//struct Field;
#include "Field.h"

class Board {
public:
	bool GameStatus{ 1 };

private:
	size_t Width;
	size_t Height;
	size_t Mines;

	std::vector<std::vector<Field>> fields{ Height };

	size_t CountMines(size_t, size_t);
	Field* GetField(size_t, size_t);
	void Reveal(size_t, size_t);
	size_t GetCoordFromUser(const char&);
public:
	Board(size_t, size_t, size_t);
	void Draw();
	void GetInput();
};