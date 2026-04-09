#pragma once

class SemiImplicitEulerIntegrator
{
public:
    static void Integrate(float& position, float& velocity, float acceleration, float deltaTime)
    {
        velocity += acceleration * deltaTime;
        position += velocity * deltaTime;
    }

    template<typename Vec3>
    static void Integrate(Vec3& position, Vec3& velocity, const Vec3& acceleration, float deltaTime)
    {
        velocity.x += acceleration.x * deltaTime;
        velocity.y += acceleration.y * deltaTime;
        velocity.z += acceleration.z * deltaTime;

        position.x += velocity.x * deltaTime;
        position.y += velocity.y * deltaTime;
        position.z += velocity.z * deltaTime;
    }
};


