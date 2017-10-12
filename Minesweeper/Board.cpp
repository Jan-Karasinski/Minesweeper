#include "stdafx.h"
#include <random>
#include <iostream>
#include <sstream>
#include <limits>
#include <queue>
#include <deque>
#include "Board.h"

namespace {
	std::random_device rd;
	std::mt19937 rng(rd());
}

size_t Board::CountMines(size_t x, size_t y) {
	size_t count{ 0 };
	
	//top-left
	Field* field{ GetField(x - 1, y - 1) };
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
	if (x < Width && y < Height) {
		return &fields[y][x];
	}
	return nullptr;
}

void Board::Reveal(size_t x, size_t y) {
	if (Field* field{ GetField(x, y) }) {
		std::queue<Field*> q;
		
		if (field->isMine) {
			GameStatus = 0;
			Win = 0;
			UncoverAll();
			Draw();
			return;
		}
		
		field->isCovered = 0;
		q.push(GetField(x, y));
		while (!q.empty()) {
			field = q.front(); q.pop();

			if (!field->MinesCount) {
				size_t _x{ field->Coord.x-1 }, _y{ field->Coord.y-1 };
				
				//top-left
				field = GetField(_x - 1, _y - 1);
				if (field && field->isCovered && !field->isFlagged) {
					field->isCovered = 0;
					q.push(field);
				}
				//top-mid
				field = GetField(_x, _y - 1);
				if (field && field->isCovered && !field->isFlagged) {
					field->isCovered = 0;
					q.push(field);
				}
				//top-right
				field = GetField(_x + 1, _y - 1);
				if (field && field->isCovered && !field->isFlagged) {
					field->isCovered = 0;
					q.push(field);
				}

				//mid-left
				field = GetField(_x - 1, _y);
				if (field && field->isCovered && !field->isFlagged) {
					field->isCovered = 0;
					q.push(field);
				}
				//mid-right
				field = GetField(_x + 1, _y);
				if (field && field->isCovered && !field->isFlagged) {
					field->isCovered = 0;
					q.push(field);
				}

				//bottom-left
				field = GetField(_x - 1, _y + 1);
				if (field && field->isCovered && !field->isFlagged) {
					field->isCovered = 0;
					q.push(field);
				}
				//bottom-mid
				field = GetField(_x, _y + 1);
				if (field && field->isCovered && !field->isFlagged) {
					field->isCovered = 0;
					q.push(field);
				}
				//bottom-right
				field = GetField(_x + 1, _y + 1);
				if (field && field->isCovered && !field->isFlagged) {
					field->isCovered = 0;
					q.push(field);
				}
			}
		}
		if (OnlyMinesLeft()) {
			GameStatus = 0;
			Win = 1;
			UncoverAll();
			Draw();
		}
	}
}

void Board::UncoverAll() {
	for (size_t y = 0; y < Height; y++) {
		for (size_t x = 0; x < Width; x++) {
			fields[y][x].isCovered = 0;
		}
	}
}

bool Board::OnlyMinesLeft() {
	for (size_t y = 0; y < Height; y++) {
		for (size_t x = 0; x < Height; x++) {
			if (fields[y][x].isCovered && !fields[y][x].isMine) {
				return 0;
			}
		}
	}
	return 1;
}

Board::Board(width w, height h, mines m) : Width(w), Height(h), Mines(m)
{
	//plant mines and perform a random shuffle
	std::deque<Field> tmp; tmp.resize(Width * Height);
	size_t mines_left = Mines;
	for (auto it = tmp.begin(); it != tmp.end(); it++) {
		it->isMine = 1;
		if (!--mines_left) break;
	}
	std::shuffle(tmp.begin(), tmp.end(), rng);
	
	//convert 1d to 2d for simplicity
	size_t y{ 0 }, x{ 0 }; /*Indexing fixed in GetField()*/
	while (!tmp.empty()) {
		fields[y].push_back(tmp.front());
		tmp.pop_front();
		fields[y][x].Coord.x = x+1;
		fields[y][x].Coord.y = y+1;
		if (++x >= Width) {
			x = 0; y++;
		}
	}

	//set number of mines around a field
	for (y = 0; y < Height; y++) {
		for (x = 0; x < Width; x++) {
			fields[y][x].MinesCount = CountMines(x, y);
		}
	}
}

void Board::Draw() {
	std::cout << "\n";

	// alignment of tens of col indexes
	if (Height > 9) {
		std::cout << ' ';
	}
	// for col indexes < 10
	for (size_t i = 0; i < 10; i++) {
		std::cout << "  ";
	}
	// tens of col indexes
	for (size_t i = 10; i <= Width; i++) {
		std::cout << (i/10)%10 << ' ';
	}
	std::cout << '\n';

	//spaces before units of col indexes (for alignment)
	if (Height > 9) {
		std::cout << "  ";
	}
	else std::cout << ' ';
	//units of col indexes
	for (size_t i = 1; i <= Width; i++) {
		std::cout << ' ' << i%10;
	}
	std::cout << "\n\n";

	Field* field{ nullptr };
	for (size_t y = 0; y < Height; y++) {
		// alignment for row idx < 10
		if(Height > 9 && y < 9) {
			std::cout << ' ';
		}
		// row idx
		std::cout << y+1;
		
		for (size_t x = 0; x < Width; x++) {
			field = GetField(x, y);
			
			if (!GameStatus) {
				if (field->isMine) {
					std::cout << " *";
				}
				else {
					std::cout << "  ";
				}
				continue;
			}

			if (field->isCovered) {
				if (field->isFlagged) {
					std::cout << " F";
				}
				else {
					std::cout << " ?";
				}
			}
			else {
				std::cout << ' ';
				if (!field->MinesCount) {
					std::cout << ' ';
				}
				else std::cout << field->MinesCount;
			}
		}
		std::cout << '\n';
	}
	
}

void Board::GetInput() {
	size_t x{ 0U - 1 }, y{ 0U - 1 };
	char mode{ 'u' };

	std::cout << "Input: ";

	std::string input;
	std::cin.ignore(std::cin.rdbuf()->in_avail());
	std::getline(std::cin, input);
	
	if (std::cin.fail()) {
		std::cin.clear();
		std::cin.ignore(std::cin.rdbuf()->in_avail());
		return;
	}

	std::stringstream str{ input };
	str >> x >> y >> mode;

	if (Field* field{ GetField(--x, --y) }) {
		if (mode == 'f') {
			field->isFlagged = !field->isFlagged;
		}
		else if (!field->isFlagged && field->isCovered) {
			Reveal(x, y);
		}
	}
}