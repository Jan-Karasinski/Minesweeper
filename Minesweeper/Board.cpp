#include "stdafx.h"
#include <random>
#include <iostream>
#include <exception>
#include <sstream>
#include "Board.h"
//#include "Field.h"

//#define TEST
#define DISPLAY_FIELD_INFO
#define DEBUG_REVEAL

auto rng = std::default_random_engine();

size_t Board::CountMines(size_t x, size_t y) {
	size_t count{ 0 }; Field* field;
	//top-left
	field = GetField(x - 1, y - 1);
	if (field != nullptr && field->isMine) {
		count++;
	}
	//top-mid
	field = GetField(x, y - 1);
	if (field != nullptr && field->isMine) {
		count++;
	}
	//top-right
	field = GetField(x + 1, y - 1);
	if (field != nullptr && field->isMine) {
		count++;
	}
	//mid-left
	field = GetField(x - 1, y);
	if (field != nullptr && field->isMine) {
		count++;
	}
	//mid-right
	field = GetField(x + 1, y);
	if (field != nullptr && field->isMine) {
		count++;
	}
	//bottom-left
	field = GetField(x - 1, y + 1);
	if (field != nullptr && field->isMine) {
		count++;
	}
	//bottom-mid
	field = GetField(x, y + 1);
	if (field != nullptr && field->isMine) {
		count++;
	}
	//bottom-right
	field = GetField(x + 1, y + 1);
	if (field != nullptr && field->isMine) {
		count++;
	}
	return count;
}

Field* Board::GetField(size_t x, size_t y) {
	if (--x < Width && --y < Height) {
		return &fields[y][x];
	}
	return nullptr;
}

void Board::Reveal(size_t x, size_t y) {
	x--; y--;
}

size_t Board::GetCoordFromUser(const char& c)
{
	std::string str;
	std::cout << '\n' << c << ": "; std::cin >> str;
	std::stringstream stream{ str };
	size_t co;
	stream >> co;
	return co;
}

Board::Board(size_t w, size_t h, size_t m) : Width(w), Height(h), Mines(m)
{
	//plant mines and perform a random shuffle
	std::vector<Field> tmp; tmp.resize(Width * Height);
	size_t mines_left = Mines;
	for (auto it = tmp.begin(); it != tmp.end(); it++) {
		it->isMine = 1;
		if (!--mines_left) break;
	}
	std::shuffle(tmp.begin(), tmp.end(), rng);
	
	//convert 1d to 2d for simplicity
	size_t y{ 1 }, x{ 1 }; /*Indexing fixed in GetField()*/
	for (const auto f : tmp) {
		fields[y-1].push_back(tmp[(y - 1) * Height + x - 1]);
		GetField(x, y)->Coord.x = x;
		GetField(x, y)->Coord.y = y;
		if (++x > Width) {
			x = 1; y++;
		}
	}

	//set number of mines around a field
	for (y = 1; y <= Height; y++) {
		for (x = 1; x <= Width; x++) {
			GetField(x, y)->MinesCount = CountMines(x, y);
		}
	}
}

void Board::Draw() {
	std::cout << ' ';
	for (size_t i = 1; i <= Width; i++) {
		std::cout << ' ' << i;
	}
	std::cout << '\n';
	Field* field;
	for (size_t y = 1; y <= Width; y++) {
		std::cout << y;
		for (size_t x = 1; x <= Width; x++) {
			field = GetField(x, y);
#ifdef TEST
			std::cout << ' ' << field->isMine ? ' ' : '1';
#else
			if (field->isCovered) {
				std::cout << ' ' << field->isFlagged ? 'F' : '?';
			}
			else if (field->isMine) {
#ifdef DEBUG_REVEAL
				std::cout << " B";
#else
				throw std::exception("Error: uncovered mine didn't stop the game!");
#endif // DEBUG_REVEAL
			}
			else {
				std::cout << ' ';
				if (field->MinesCount == size_t{ 0 }) {
					std::cout << ' ';
				}
				else std::cout << field->MinesCount;
			}
#endif // TEST
		}
		std::cout << '\n';
	}
	
}

void Board::GetInput() {
	size_t x{ GetCoordFromUser('X') }, y{ GetCoordFromUser('Y') };
	if (x <= Width || y <= Height) {
#ifdef DISPLAY_FIELD_INFO
		std::cout << "\n----------DISPLAY_FIELD_INFO----------" <<
			"\nX = " << GetField(x, y)->Coord.x <<
			"\nY = " << GetField(x, y)->Coord.y <<
			"\nisMine = " << GetField(x, y)->isMine <<
			"\nMinesCount = " << GetField(x, y)->MinesCount <<
			"\n----------DISPLAY_FIELD_INFO----------\n\n";
#ifdef DEBUG_REVEAL
		GetField(x, y)->isCovered = 0;
#endif // DEBUG_REVEAL

#endif // DISPLAY_FIELD_INFO

		//reveal()
	}

	
}
