#include "World.h"
#include "raymath.h"

World::World()
    : gravity{ 0, 9.81f }
{
    bodies.reserve(1000);
}

void World::AddBody(const Body& body)
{
    bodies.push_back(body);
}

void World::ApplyGravity()
{
    Vector2 gravityForce = Vector2Scale(gravity, 100.0f);
    for (auto& body : bodies)
    {
        body.AddForce(gravityForce);
    }
}

void World::ApplyAttraction(Vector2 position, float radius, float strength)
{
    for (auto& body : bodies)
    {
        Vector2 direction = Vector2Subtract(position, body.position);
        float distance = Vector2Length(direction);
        
        if (distance <= radius)
        {
            Vector2 force = Vector2Scale(Vector2Normalize(direction), strength);
            body.AddForce(force);
        }
    }
}

void World::HandleCollisions()
{
    int screenWidth = GetScreenWidth();
    int screenHeight = GetScreenHeight();

    for (auto& body : bodies)
    {
        if (body.position.x + body.size > screenWidth || body.position.x - body.size <= 0)
        {
            body.velocity.x *= -1.0f;
        }

        if (body.position.y + body.size > screenHeight || body.position.y - body.size <= 0)
        {
            body.velocity.y *= -1.0f;
        }
    }
}

void World::Step(float deltaTime)
{
    // Apply forces
    ApplyGravity();
    
    // Update all bodies
    for (auto& body : bodies)
    {
        body.Step(deltaTime);
    }
    
    // Handle collisions
    HandleCollisions();
}

void World::Draw() const
{
    for (const auto& body : bodies)
    {
        body.Draw();
    }
}