#include "GameOfLife.h"

/*
Less than 2 Neighbors: Die
More than 3 Neighbors: Die
Exactly 3 Neighbors:   Become alive
2-3 Neighbors:         Stay Living
*/

void GameOfLife::advance()
{
	generation++;

	auto nextBoard = board;

	for (int i = 0; i < nextBoard.size(); i++)
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

		if (board[i] && (neighbors < 2 || neighbors > 3))
		{
			nextBoard[i] = false;
			population--;
		}
		if (!board[i] && neighbors == 3)
		{
			nextBoard[i] = true;
			population++;
		}
	}

	board = nextBoard;
}

void GameOfLife::draw() const
{
	for (int i = 0; i < GRID_CELL_COUNT + 1; i++)
	{
		DrawLine(i * GRID_CELL_SIZE, 0, i * GRID_CELL_SIZE, GRID_CELL_SIZE * GRID_CELL_COUNT, WHITE);
		DrawLine(0, i * GRID_CELL_SIZE, GRID_CELL_SIZE * GRID_CELL_COUNT, i * GRID_CELL_SIZE, WHITE);
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