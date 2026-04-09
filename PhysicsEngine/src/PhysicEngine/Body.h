#pragma once
#include "raymath.h"

enum class BodyType {
	STATIC,
	KINEMATIC,
	DYNAMIC
};

enum class ForceMode {
	IMPULSE,
	FORCE,
	ACCELERATION,
	VELOCITY_CHANGE
};

struct Body {
public:
	BodyType bodyType = BodyType::DYNAMIC;
	Vector2 acceleration{ 0,0 };
	Vector2 position { 0,0 };
	Vector2 velocity{ 0,0 };
	float mass = 1.0f;
	float size =1.0f;
	float restitution = 1.0f;
	float damping = 0.0f;
	float inverseMass = 1.0f;	
	float gravityScale = 1.0f;

public:
	void Step(float deltaTime);
	void Draw();
	void AddForce(Vector2 force, ForceMode mode = ForceMode::FORCE);
};