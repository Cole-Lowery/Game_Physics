#include "raylib.h"
#include "Body.h"

void Body::Step(float deltaTime) {
	if (bodyType == BodyType::STATIC) return;

	velocity += acceleration * deltaTime;
	position += velocity * deltaTime;
}

void Body::Draw() {
	DrawCircleV(position, size, ORANGE);
	DrawCircleLinesV(position, size, WHITE);
}

void Body::AddForce(Vector2 force, ForceMode forceMode) {
	if (bodyType != BodyType::DYNAMIC) return;
	switch (forceMode) {
		case ForceMode::FORCE:
			acceleration += force * inverseMass;
			break;
		case ForceMode::IMPULSE:
		velocity += force * inverseMass;
		break;
		case ForceMode::ACCELERATION:
			acceleration += force;
			break;
		case ForceMode::VELOCITY_CHANGE:
			velocity += force;
			break;
	}
	

}