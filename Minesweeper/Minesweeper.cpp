#include "stdafx.h"
#include "Board.h"
#include <iostream>
#include <sstream>
#include <limits>

/*
Board
	+ GameStatus : bool
	+ Win		 : bool
	
	- Width		 : size_t
	- Height	 : size_t
	- Mines		 : size_t

	- fields	 : vector<vector<Field>

	----------------------------------------
	- CountMines(size_t, size_t)	: size_t
	- GetField(size_t, size_t)		: Field*
	- Reveal(size_t, size_t)		: void
	- UncoverAll(void)				: void
	- OnlyMinesLeft(void)			: bool

	+ Board(size_t, size_t, size_t)

	+ Draw()						: void
	+ GetInput()					: void

--------------------------------------------
Position
	+ x : size_t
	+ y : size_t

	----------------------------------------
	+ Position()
	+ Position(size_t, size_t)

--------------------------------------------
Field
	+ isMine				: bool
	+ isCovered				: bool
	+ isFlagged				: bool
	+ Coord(size_t, size_t) : Position
	+ MinesCount			: size_t
	
	----------------------------------------

*/

namespace {
	const size_t MAX_BOARD_SIZE{ 35 };
	const size_t MIN_BOARD_SIZE{ 9 };

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
		std::cin.ignore(std::cin.rdbuf()->in_avail());
		std::string str;
		std::cout << d << ": "; std::getline(std::cin, str);
		std::stringstream s{ str };
		size_t t{ 0 };
		s >> t;
		return t;
	}
}

int main() {
	do {
		size_t width{ 0 }, height{ 0 }, mines{ 0 };
		while (width  < MIN_BOARD_SIZE || width  > MAX_BOARD_SIZE
			|| height < MIN_BOARD_SIZE || height > MAX_BOARD_SIZE
			|| !mines || mines >= width*height)
		{
			width  = GetParam("Width");
				if (std::cin.fail()) {
					std::cin.clear();
					std::cin.ignore(std::cin.rdbuf()->in_avail());
					continue;
				}
			height = GetParam("Height");
				if (std::cin.fail()) {
					std::cin.clear();
					std::cin.ignore(std::cin.rdbuf()->in_avail());
					continue;
				}
			mines  = GetParam("Mines");
				if (std::cin.fail()) {
					std::cin.clear();
					std::cin.ignore(std::cin.rdbuf()->in_avail());
					continue;
				}
			std::cout << '\n';
		}

		std::cout << "To reveal a field write X Y\n"
				<< "To flag a field write X Y f\n";

		Board board = Board{ width, height, mines };

		while (board.GameStatus) {
			board.Draw();
			board.GetInput();
		}

		if (board.Win) {
			std::cout << "\nYou won!\n";
		}
		else {
			std::cout << "\nGame Over\n";
		}

	} while (PlayAgain());
	std::cin.get();
	return 0;
}