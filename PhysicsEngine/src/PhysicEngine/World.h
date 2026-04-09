#pragma once

#include "Body.h"
#include <vector>

class Effector;

class World {
public:
	Vector2 gravity{ 0, 9.81f };
	std::vector<Body> bodies;
	std::vector<Effector*> effectors;

public:
	World();
	void Step(float deltaTime);
	void Draw();
	void AddBody(const Body& body);
	void AddEffector(Effector* effector);
};