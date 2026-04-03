#include "raylib.h"
#include "raymath.h"
#include "resource_dir.h"
#include "Body.h"
#include "World.h"
#include "Random.h"

int main()
{
    // Initialize world
    World world;

    SetRandomSeed(5);
    SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);
    InitWindow(1280, 800, "Hello Raylib");
    SearchAndSetResourceDir("resources");

    Texture wabbit = LoadTexture("wabbit_alpha.png");

    // Game loop
    while (!WindowShouldClose())
    {
        float deltaTime = GetFrameTime();

        // Input: Spawn bodies on left click
        if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
        {
            Body body = { 0 };
            body.position = GetMousePosition();

            float angle = GetRandomFloat() * (2 * PI);
            Vector2 direction;
            direction.x = cosf(angle);
            direction.y = sinf(angle);

            body.velocity = Vector2Scale(direction, GetRandomFloat(300.0f));
            body.acceleration = Vector2{ 0, 0 };
            body.size = (float)GetRandomValue(5, 20);
            body.restitution = 1.0f;
            body.mass = body.size * 10;

            world.AddBody(body);
        }

        // Input: Apply attraction force on right click
        if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
        {
            Vector2 position = GetMousePosition();
            world.ApplyAttraction(position, 100.0f, 30000.0f);
            DrawCircleLinesV(position, 100, GREEN);
        }

        // Update physics
        world.Step(deltaTime);

        // Draw
        BeginDrawing();
        ClearBackground(BLACK);

        DrawText("Hello Raylib", 200, 200, 20, WHITE);
        DrawTexture(wabbit, 400, 200, WHITE);

        world.Draw();

        EndDrawing();
    }

    UnloadTexture(wabbit);
    CloseWindow();

    return 0;
}