

#include "raylib.h"
#include "raymath.h"
#include "resource_dir.h" 

#include "Body.h"
#include "World.h"
#include "Random.h"
#include "GravitationalEffector.h"

int main ()
{
	World world;
	SetRandomSeed(5);

	world.AddEffector(new GravitationalEffector(1000.0f));

	SetConfigFlags(FLAG_VSYNC_HINT | FLAG_WINDOW_HIGHDPI);

	InitWindow(1280, 800, "Physics Engine");

	SearchAndSetResourceDir("resources");

	while (!WindowShouldClose())		
	{
		float deltaTime = GetFrameTime();
		Vector2 currentMousePosition = GetMousePosition();

		if (IsKeyDown(KEY_LEFT_SHIFT)) deltaTime = 0.0f;

		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || (IsKeyDown(KEY_LEFT_CONTROL) && IsMouseButtonDown(MOUSE_BUTTON_LEFT)) ) {
			Body body;

			body.bodyType =(IsKeyDown(KEY_LEFT_ALT)) ? BodyType::STATIC : BodyType::DYNAMIC;

			body.position = currentMousePosition;

			float angle = GetRandomFloat() * (2 * PI);

			Vector2 direction;
			direction.x = cosf(angle);
			direction.y = sinf(angle);

			body.velocity = Vector2{ 0, 0 };
			body.acceleration = Vector2{ 0, 0 };
			body.size = 5.0f + (GetRandomFloat() * 20.0f);
			body.restitution = 0.5f + (GetRandomFloat() * 0.5f);
			body.mass = body.size;
			body.damping = 0.01f;
			body.gravityScale = 0.0f;
			body.inverseMass = (body.bodyType == BodyType::STATIC) ? 0 : 1.0f / body.mass ;

			world.AddBody(body);
		}

		// UPDATE

		world.Step(deltaTime);

		// DRAW
		BeginDrawing();

		ClearBackground(BLACK);

		DrawText("Physics Engine", 200, 200, 20, WHITE);


		// Add world draw method here
		world.Draw();
		
		// end the frame and get ready for the next one  (display frame, poll input, etc...)
		EndDrawing();
	}


	// destroy the window and cleanup the OpenGL context
	CloseWindow();
	return 0;
}
