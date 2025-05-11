#include "GameOfLife.h"

void GameOfLife::advance()
{
	generation++;
	population = 0;

	auto nextBoard = board;

	for (int i = 0; i < board.size(); i++)
	{
		int neighbors = 0;
		const int x = i % GRID_CELL_COUNT;
		const int y = i / GRID_CELL_COUNT;
		const bool notLeftEdge = (x > 0);
		const bool notRightEdge = (x < GRID_CELL_COUNT - 1);
		const bool notTopEdge = (y > 0);
		const bool notBottomEdge = (y < GRID_CELL_COUNT - 1);

		if (notTopEdge)
		{
			if (notLeftEdge && board[i - GRID_CELL_COUNT - 1])
				neighbors++;
			if (board[i - GRID_CELL_COUNT])
				neighbors++;
			if (notRightEdge && board[i - GRID_CELL_COUNT + 1])
				neighbors++;
		}

		if (notLeftEdge && board[i - 1])
			neighbors++;
		if (notRightEdge && board[i + 1])
			neighbors++;

		if (notBottomEdge)
		{
			if (notLeftEdge && board[i + GRID_CELL_COUNT - 1])
				neighbors++;
			if (board[i + GRID_CELL_COUNT])
				neighbors++;
			if (notRightEdge && board[i + GRID_CELL_COUNT + 1])
				neighbors++;
		}

		nextBoard[i] = (neighbors == 3) || (board[i] && neighbors == 2);
	}

	board = nextBoard;

	for (int i = 0; i < board.size(); i++)
		if (board[i])
			population++;
}

void GameOfLife::draw() const
{
	for (int i = 0; i < GRID_CELL_COUNT + 1; i++)
	{
		DrawLine(i * GRID_CELL_SIZE, 0, i * GRID_CELL_SIZE, GRID_CELL_SIZE * GRID_CELL_COUNT, LIGHTGRAY);
		DrawLine(0, i * GRID_CELL_SIZE, GRID_CELL_SIZE * GRID_CELL_COUNT, i * GRID_CELL_SIZE, LIGHTGRAY);
	}

	for (int i = 0; i < board.size(); i++)
	{
		if (board[i])
		{
			int x = i % GRID_CELL_COUNT * GRID_CELL_SIZE;
			int y = i / GRID_CELL_COUNT * GRID_CELL_SIZE;
			DrawRectangle(x, y, GRID_CELL_SIZE, GRID_CELL_SIZE, WHITE);
		}
	}
}

void GameOfLife::set(int x, int y)
{
	int index = y * GRID_CELL_COUNT + x;
	population += (board[index] = !board[index]) ? 1 : -1;
}