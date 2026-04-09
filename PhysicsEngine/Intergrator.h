#pragma once
#include "Body.h"

inline void SemiImplicitEuler(Body& body, float deltaTime)
{
    body.velocity += body.acceleration * deltaTime;
    body.position += body.velocity * deltaTime;
    body.velocity *= (1.0f / (1.0f - body.damping));
}



