#include "stdafx.h"
#include <random>
#include <iostream>
#include <exception>
#include <sstream>
#include <queue>
#include <deque>
#include "Board.h"

int n_of_digits(size_t num) {
	int digits{ 0 };
	while (num) {
		num /= 10;
		digits++;
	}
	return digits;
}

auto rng = std::default_random_engine();

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
	if (--x < Width && --y < Height) {
		return &fields[y][x];
	}
	return nullptr;
}

void Board::Reveal(size_t x, size_t y) {
	Field* field{ GetField(x, y) };
	if (field) {
		std::queue<Field*> q;
		if (field->isMine) {
			GameStatus = 0;
			UncoverAll();
			Draw();
			std::cout << "\nGame Over\n";
		}
		else {
			field->isCovered = 0;
			
			q.push(GetField(x, y));
			
			while (!q.empty()) {
				field = q.front(); q.pop();

				if (!field->MinesCount) {
					size_t _x{ field->Coord.x }, _y{ field->Coord.y };
					
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
				UncoverAll();
				Draw();
				std::cout << "\nYou won!\n";
			}
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

size_t Board::GetCoordFromUser(const char& c) {
	std::string str;
	std::cout << '\n' << c << ": "; std::cin >> str;
	std::stringstream stream{ str };
	size_t co{ 0 };
	stream >> co;
	return co;
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
	size_t y{ 1 }, x{ 1 }; /*Indexing fixed in GetField()*/
	while (!tmp.empty()) {
		fields[y-1].push_back(tmp.front());
		tmp.pop_front();
		GetField(x, y)->Coord.x = x;
		GetField(x, y)->Coord.y = y;
		if (++x > Width) {
			x = 1; y++;
		}
	}

	////plant mines and perform a random shuffle
	//std::vector<Field> tmp; tmp.resize(Width * Height);
	//size_t mines_left = Mines;
	//for (auto it = tmp.begin(); it != tmp.end(); it++) {
	//	it->isMine = 1;
	//	if (!--mines_left) break;
	//}
	//std::shuffle(tmp.begin(), tmp.end(), rng);

	////convert 1d to 2d for simplicity
	//size_t y{ 1 }, x{ 1 }; /*Indexing fixed in GetField()*/
	//for (const auto f : tmp) {
	//	fields[y - 1].push_back(tmp[(y - 1) * Height + x - 1]); // if h > w bug
	//	GetField(x, y)->Coord.x = x;
	//	GetField(x, y)->Coord.y = y;
	//	if (++x > Width) {
	//		x = 1; y++;
	//	}
	//}

	//set number of mines around a field
	for (y = 1; y <= Height; y++) {
		for (x = 1; x <= Width; x++) {
			GetField(x, y)->MinesCount = CountMines(x, y);
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
	for (size_t y = 1; y <= Height; y++) {
		
		// alignment for row idx < 10
		if(Height > 9 && y < 10) {
			std::cout << ' ';
		}
		// row idx
		std::cout << y;
		for (size_t x = 1; x <= Width; x++) {
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
				if (field->MinesCount == size_t(0)) {
					std::cout << ' ';
				}
				else std::cout << field->MinesCount;
			}
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
		
		Reveal(x, y);
	}

	
}
