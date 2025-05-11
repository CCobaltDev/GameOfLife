#include <iostream>
#include <string>
#include "raylib.h"
#include "GameOfLife.h"

#define WIDTH 640
#define HEIGHT 360

int main()
{
	InitWindow(WIDTH, HEIGHT, "Conway's Game Of Life");
	SetTargetFPS(60);

	Camera2D cam = {0};
	cam.zoom = 1.0f;

	GameOfLife sim;
	sim.set(2, 0);
	sim.set(0, 1);
	sim.set(2, 1);
	sim.set(1, 2);
	sim.set(2, 2);

	std::string generation = "Generation: ";
	std::string population = "Population: ";

	while (!WindowShouldClose())
	{
		if (IsKeyDown(KEY_D))
			cam.target.x += 5.0f;
		if (IsKeyDown(KEY_A))
			cam.target.x -= 5.0f;
		if (IsKeyDown(KEY_W))
			cam.target.y -= 5.0f;
		if (IsKeyDown(KEY_S))
			cam.target.y += 5.0f;
		if (IsKeyPressed(KEY_SPACE))
			sim.advance();

		BeginDrawing();
		ClearBackground(BLACK);

		DrawText((generation + std::to_string(sim.generation)).c_str(), 0, 0, 24, WHITE);
		DrawText((population + std::to_string(sim.population)).c_str(), 0, 24, 24, WHITE);

		BeginMode2D(cam);
		sim.draw();
		EndMode2D();
		EndDrawing();
	}

	CloseWindow();
	return 0;
}