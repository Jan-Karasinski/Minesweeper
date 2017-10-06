// Minesweeper.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include "Board.h"
#include <iostream>

//#include <vector>
//#include <random>
//#include <iostream>
//#include <string>
//#include <sstream>
//#include <array>
//#include <queue>
//
//bool end{ 0 };
//
//struct Field {
//	bool Mine{ 0 };
//	bool Covered{ 1 };
//	bool Flag{ 0 };
//	char symbol{ '?' };
//	size_t MinesCount;
//	size_t x, y;
//
//	size_t test_id{ 0 };
//
//	Field() = default;
//};
//
//auto rng = std::default_random_engine();
//
//class Board {
//	size_t width;
//	size_t height;
//	size_t mines;
//	
//	std::vector<Field> fields;
//
//	Field* GetField(size_t x, size_t y) {
//		return &fields[y * height + y];
//	}
//public:
//	Board(size_t w, size_t h, size_t m)
//		: width(w), height(h), mines(m)
//	{
//		fields.resize(width * height);
//		
//		size_t mines_left = mines-1;
//		for (size_t y = 0; y < width * height; y++) {
//			fields[y].Mine = 1;
//			if (!mines_left) break;
//			else mines_left--;
//		}
//		std::shuffle(fields.begin(), fields.end(), rng);
//
//		size_t x{ 0 }, y{ 0 };
//		for (auto f : fields) {
//			f.x = x; f.y = y;
//			f.MinesCount = CountMines(x, y);
//			if (x++ + 1 >= width) {
//				x = 0; y++;
//			}
//		}
//	}
//
//public:
//	size_t CountMines(size_t x, size_t y) {
//		size_t count{ 0 };
//		//top
//		if (y != 0) {
//			//top-left
//			if (x != 0) {
//				if (fields[y * height + x - width - 1].Mine) count++;
//				printf("\n%d ", fields[y * height + x - width - 1].test_id);
//			}
//			//top-middle // always possible
//			if (fields[y * height + x - width].Mine) count++;
//			printf("| %d ", fields[y * height + x - width].test_id);
//			//top-right
//			if (x != width-1) {
//				if (fields[y * height + x - width + 1].Mine) count++;
//				printf("| %d", fields[y * height + x - width + 1].test_id);
//			}
//		}
//		//middle
//			//mid-left
//			if (x > 0) {
//				if (fields[y * height + x - 1].Mine) count++;
//				printf("\n%d ", fields[y * height + x - 1].test_id);
//			}
//			//mid-mid // always possible
//			if (fields[x*height + y].Mine) count++;
//			printf("| %d ", fields[y * height + x].test_id);
//			//mid-right
//			if (x < width - 1) {
//				if (fields[y * height + x + 1].Mine) count++;
//				printf("| %d", fields[y * height + x + 1].test_id);
//			}
//		//bottom
//		if (y < height - 1) {
//			//btm-left
//			if (x > 0) {
//				if (fields[y * height + x + width - 1].Mine) count++;
//				printf("\n%d ", fields[y * height + x + width - 1].test_id);
//			}
//			//btm-mid // always possible
//			if (fields[y * height + x + width].Mine) count++;
//			printf("| %d ", fields[y * height + x + width].test_id);
//			//btm-right
//			if (x < width - 1) {
//				if (fields[y * height + x + width + 1].Mine) count++;
//				printf("| %d", fields[y * height + x + width + 1].test_id);
//			}
//		}
//		return count;
//	}
//
//	void RevealBoard(size_t x, size_t y) {
//		std::queue<Field*> q;
//		while (!q.empty()) {
//			if (!q.front()->Covered) {
//				q.pop();
//				continue;
//			}
//
//		}
//	}
//
//	void Reveal(size_t x, size_t y) {
//		Field* field = GetField(x, y);
//		if (!field->Flag) {
//			size_t mines_nearby = CountMines(x, y);
//			if (!field->MinesCount) {
//				field->symbol = ' '; field->Covered = 0;
//				RevealBoard(x, y);
//			}
//			else {
//				field->symbol = mines_nearby + 48 /*convert to char*/;
//			}
//		}
//	}
//
//	void test_print() {
//		size_t y{ 0 }, x{ 0 };
//		for (size_t i = 0; i < height*width; i++) {
//			printf(" %zd ", fields[i].Mine ? 1 : 0);
//			fields[i].test_id = i;
//			if (x++ == width - 1) {
//				std::cout << std::endl;
//				x = 0; y++;
//			}
//		}
//		x = 0, y = 0;
//		printf("\n\n");
//		for (size_t i = 0; i < height*width; i++) {
//			printf(" %zd ", y * height + x);
//			if (i < 10) printf(" ");
//			if (x++ == width - 1) {
//				std::cout << std::endl;
//				x = 0; y++;
//			}
//		}
//		//x = 4 - 1/* indexing */, y = 3 - 1/* indexing */;
//		
//
//		printf("\n\n%zd - count\n\n", CountMines(4 - 1, 2 - 1));
//		printf("\n\n%zd - count\n\n", CountMines(5 - 1, 6 - 1));
//		printf("\n\n%zd - count\n\n", CountMines(8 - 1, 7 - 1));
//
//		printf("\n\n(1, 1) x = %zd, y = %zd\n", GetField(0, 0)->x + 1, GetField(0, 0)->y + 1);
//		printf("\n\n(9, 9) x = %zd, y = %zd\n", GetField(8, 8)->x + 1, GetField(8, 8)->y + 1);
//	}
//
//	void Draw() {
//		printf("? - unknown, E - empty, M - mine\n  ");
//		for (size_t i = 1; i <= width; i++) {
//			printf("%d ", i);
//		}
//		size_t col = 1;
//		printf("\n%d ", col++);
//		for (size_t f = 0; f < width * height; f++) {
//			printf("%c ", fields[f].symbol);
//			if ((f + 1) % width == 0 && f < width * height -1) {
//				printf("\n%d ", col++);
//			}
//		}
//		printf("\n");
//	}
//	
//	size_t GetCoord(std::string msg) {
//		std::string temp; 
//		std::cout << '\n' + msg + ": "; std::cin >> temp;
//		std::stringstream stream(temp);
//		size_t x;
//		stream >> x;
//		return x;
//	}
//
//	void GetInput() {
//		size_t x{ GetCoord("X") - 1 }, y{ GetCoord("Y") - 1 };
//		//Coords are decremented becouse of indexing
//		if (x > width || y > height) return;
//		else if (fields[y * height + x].Mine) {
//			end = true;
//			std::cout << "\nGame over";
//		}
//		else {
//			//std::cout << "\n[" << x << "/" << y << "] = " << fields[y * height + x].id;
//			Reveal(x, y);
//		}
//	}
//
//	bool OnlyMinesLeft() {
//		for (auto f : fields) {
//			if (f.Covered) {
//				if (!f.Mine) return false;
//			}
//		}
//		return true;
//	}
//};
//
//int main()
//{
//	Board board(9, 9, 8);
//
//	board.test_print();
//
//	while (!board.OnlyMinesLeft() && !end) {
//		board.Draw();
//		
//		board.GetInput();
//		std::cin.ignore();
//		std::cin.get();
//	}
//
//	std::cin.get();
//	
//    return 0;
//}
//
// Diagrams
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
Field
	+ isMine				: bool
	+ isCovered				: bool
	+ isFlagged				: bool
	+ Coord(size_t, size_t) : Position
	+ MinesCount			: size_t
	
	----------------------------------------

*/

int main() {
	Board board(9,9,5);
	do {
		while (board.GameStatus) {
			board.Draw();
			board.GetInput();
		}
	} while (0);
	std::cin.get();
	return 0;
}