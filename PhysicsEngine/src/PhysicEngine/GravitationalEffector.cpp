#include "GravitationalEffector.h"
#include "raymath.h"

void GravitationalEffector::Apply(std::vector<Body>& bodies)
{
	for (size_t i = 0; i < bodies.size(); i++)
	{
		for (size_t j = i + 1; j < bodies.size(); j++)
		{
			Body& bodyA = bodies[i];
			Body& bodyB = bodies[j];

			Vector2 direction = bodyA.position - bodyB.position;

			float distance = Vector2Length(direction);

			distance = fmaxf(distance, 1.0f);

			float forceMagnitude = strength * (bodyA.mass * bodyB.mass) / (distance * distance);

			Vector2 force = Vector2Scale(Vector2Normalize(direction), forceMagnitude);

			bodyA.AddForce(Vector2Negate(force));
			bodyB.AddForce(force);
		}
	}
}
