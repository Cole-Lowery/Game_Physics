#pragma once
#include "Body.h"
#include <vector>

class World
{
public:
    World();
    
    void AddBody(const Body& body);
    void Step(float deltaTime);
    void Draw() const;
    void ApplyGravity();
    void ApplyAttraction(Vector2 position, float radius, float strength);
    void HandleCollisions();
    
    Vector2 gravity;

private:
    std::vector<Body> bodies;
};