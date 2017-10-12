#pragma once
#include <vector>
#include "Field.h"

typedef size_t width;
typedef size_t height;
typedef size_t mines;

class Board {
public:
	bool GameStatus{ 1 };
	bool Win{ 0 };

private:
	width  Width;
	height Height;
	mines  Mines;

	std::vector<std::vector<Field>> fields{ Height };

private:
	size_t CountMines(size_t, size_t);
	
	//index should start from 1
	Field* GetField(size_t, size_t);
	
	void Reveal(size_t, size_t);

	void UncoverAll();

	bool OnlyMinesLeft();

public:
	Board(width, height, mines);
	
	void Draw();
	
	void GetInput();
};