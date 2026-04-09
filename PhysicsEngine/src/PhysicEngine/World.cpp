#include "raylib.h"
#include "World.h"
#include "Effector.h"
#include "collision.h"


World::World() {
	bodies.reserve(1000);
}

void World::Step(float deltaTime) {
	Vector2 currentMousePosition = GetMousePosition();

	for (auto& body : bodies) body.acceleration = Vector2{ 0, 0 };
	for (auto& body : bodies) body.AddForce(gravity * body.gravityScale * 1000.0f);

	for (auto& effector : effectors) effector->Apply(bodies);

	// Attract
	if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
		for (auto& body : bodies) {
			Vector2 direction = currentMousePosition - body.position;
			if (Vector2Length(direction) <= 100.0f) {
				Vector2 force = Vector2Normalize(direction) * 10000.0f;
				body.AddForce(force);
			}
		}

		DrawCircleLinesV(currentMousePosition, 100, WHITE);
	}

	// Repel
	if (IsMouseButtonDown(MOUSE_BUTTON_MIDDLE)) {
		for (auto& body : bodies) {
			Vector2 direction = body.position - currentMousePosition;
			if (Vector2Length(direction) <= 100.0f) {
				Vector2 force = Vector2Normalize(direction) * 10000.0f;
				body.AddForce(force);
			}
		}
		DrawCircleLinesV(currentMousePosition, 100, WHITE);
	}

	for (auto& body : bodies) body.Step(deltaTime);

	UpdateCollision();
}

void World::Draw() {
	for (auto& body : bodies) body.Draw();
	for (auto& effector : effectors) effector->Draw();
}

void World::AddBody(const Body& body) {
	bodies.push_back(body);
}

void World::AddEffector(Effector* effector) {
	effectors.push_back(effector);
}

void World::UpdateCollision()
{
	contacts.clear();
	CreateContacts(bodies, contacts);
	SeparateContacts(contacts);

	for (auto& body : bodies)
	{
		if (body.position.x + body.size > GetScreenWidth())
		{
			body.position.x = GetScreenWidth() - body.size;
			body.velocity.x *= -body.restitution;
		}
		if (body.position.x - body.size < 0)
		{
			body.position.x = body.size;
			body.velocity.x *= -body.restitution;
		}
		if (body.position.y + body.size > GetScreenHeight())
		{
			body.position.y = GetScreenHeight() - body.size;
			body.velocity.y *= -body.restitution;
		}
		if (body.position.y - body.size < 0)
		{
			body.position.y = body.size;
			body.velocity.y *= -body.restitution;
		}
	}
}