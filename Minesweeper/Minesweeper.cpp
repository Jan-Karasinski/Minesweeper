// Minesweeper.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Board.h"
#include <iostream>
#include <sstream>


/*
Board
	+ GameStatus : bool
	- Width		 : size_t
	- Height	 : size_t
	- Mines		 : size_t
	- fields	 : vector<vector<Field>

	----------------------------------------
	- CountMines(size_t, size_t)	: size_t
	- GetField(size_t, size_t)		: Field*
	- Reveal(size_t, size_t)		: void
	- GetCoordFromUser(const char&) : size_t

	+ Board(size_t, size_t, size_t)

	+ Draw()						: void
	+ GetInput()					: void

--------------------------------------------
Position
	+ x : size_t
	+ y : size_t

	----------------------------------------
	Position()
	Position(size_t, size_t)

--------------------------------------------
Field
	+ isMine				: bool
	+ isCovered				: bool
	+ isFlagged				: bool
	+ Coord(size_t, size_t) : Position
	+ MinesCount			: size_t
	
	----------------------------------------

*/

bool PlayAgain() {
	std::string str;
	std::cout << "Play again?\n(Y/N): "; std::cin >> str;
	std::cout << std::endl;
	if (str == "Y" || str == "y") {
		return 1;
	}
	return 0;
}

size_t GetParam(const char* d) {
	std::string str;
	std::cout << d << ": "; std::cin >> str;
	std::stringstream s{ str };
	size_t t{ 0 };
	s >> t;
	return t;
}

int main() {
	do {
		size_t width{ 0 }, height{ 0 }, mines{ 0 };
		while (width < 9 || width > 30
			|| height < 9 || height > 24
			|| !mines || mines >= width*height) {
			width  = GetParam("Width");
			height = GetParam("Height");
			mines  = GetParam("Mines");
			std::cout << std::endl;
		}

		Board board = Board{ width, height, mines };

		while (board.GameStatus) {
			board.Draw();
			board.GetInput();
		}
	} while (PlayAgain());
	std::cin.get();
	return 0;
}