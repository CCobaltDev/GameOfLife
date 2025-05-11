#ifndef GAMEOFLIFE_H
#define GAMEOFLIFE_H

#define GRID_CELL_SIZE 20
#define GRID_CELL_COUNT 50

#include <array>
#include "raylib.h"

class GameOfLife
{
public:
	void advance();
	void draw() const;
	void set(int x, int y);

	std::array<bool, GRID_CELL_COUNT * GRID_CELL_COUNT> board{};
	int generation{0};
	int population{0};
};

#endif