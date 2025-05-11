#include <iostream>
#include <algorithm>
#include <string>
#include "raylib.h"
#include "GameOfLife.h"

#define WIDTH 1280
#define HEIGHT 720

int main()
{
	InitWindow(WIDTH, HEIGHT, "Conway's Game Of Life");
	SetTargetFPS(60);

	Camera2D cam = {0};
	cam.offset = {WIDTH / 2, HEIGHT / 2};
	cam.zoom = 0.25f;

	GameOfLife sim;

	const std::array pos{2, 0, 0, 1, 2, 1, 1, 2, 2, 2};

	for (int i = 0; i < pos.size(); i += 2)
	{
		sim.set(GRID_CELL_COUNT / 2 + pos[i], GRID_CELL_COUNT / 2 + pos[i + 1]);
	}

	std::string generation = "Generation: ";
	std::string population = "Population: ";
	float speed = 5.0f;
	float prevTime = GetTime();

	while (!WindowShouldClose())
	{
		if (IsKeyDown(KEY_D))
			cam.target.x += speed / cam.zoom;
		if (IsKeyDown(KEY_A))
			cam.target.x -= speed / cam.zoom;
		if (IsKeyDown(KEY_W))
			cam.target.y -= speed / cam.zoom;
		if (IsKeyDown(KEY_S))
			cam.target.y += speed / cam.zoom;

		if (IsKeyDown(KEY_Q))
			cam.zoom -= 0.001f * speed;
		if (IsKeyDown(KEY_E))
			cam.zoom += 0.001f * speed;

		cam.zoom = std::clamp(cam.zoom, 0.1f, 5.0f);

		if (IsKeyPressed(KEY_LEFT_SHIFT))
			speed = 10.0f;
		if (IsKeyReleased(KEY_LEFT_SHIFT))
			speed = 5.0f;

		if (IsKeyDown(KEY_SPACE) && GetTime() - prevTime > 0.025f)
		{
			sim.advance();
			prevTime = GetTime();
		}

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