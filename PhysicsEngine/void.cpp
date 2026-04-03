#include "Body.h"

void Body::AddForce(Vector2 force)
{
    acceleration.x += force.x / mass;
    acceleration.y += force.y / mass;
}

void Body::Step(float deltaTime)
{
    // Semi-implicit Euler integration
    velocity.x += acceleration.x * deltaTime;
    velocity.y += acceleration.y * deltaTime;
    position.x += velocity.x * deltaTime;
    position.y += velocity.y * deltaTime;
    
    // Reset acceleration
    acceleration = Vector2{ 0, 0 };
}

void Body::Draw() const
{
    DrawCircleV(position, size, RED);
}