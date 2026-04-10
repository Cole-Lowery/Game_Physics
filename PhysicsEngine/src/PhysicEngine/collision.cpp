#include "collision.h"
#include "raymath.h"

bool Intersects(const Body& bodyA, const Body& bodyB)
{
	float distance = Vector2Distance(bodyA.position, bodyB.position);
	float radius = bodyA.size + bodyB.size;

	return (distance <= radius);
}

void CreateContacts(std::vector<Body>& bodies, std::vector<Contact>& contacts)
{
	for (size_t i = 0; i < bodies.size(); i++)
	{
		for (size_t j = i + 1; j < bodies.size(); j++)
		{
			Body& bodyA = bodies[i];
			Body& bodyB = bodies[j];

			if (bodyA.bodyType != BodyType::DYNAMIC && bodyB.bodyType != BodyType::DYNAMIC) continue;

			if (Intersects(bodyA, bodyB))
			{
				Contact contact;
				contact.bodyA = &bodyA;
				contact.bodyB = &bodyB;

				Vector2 direction = Vector2Subtract(bodyA.position, bodyB.position);
				float distance = Vector2Length(direction);
				float radius = bodyA.size + bodyB.size;
				contact.depth = radius - distance;
				contact.normal = Vector2Normalize(direction);
				contact.restitution = (bodyA.restitution + bodyB.restitution) * 0.5f;

				contacts.push_back(contact);
			}
		}
	}
}

void SeparateContacts(std::vector<Contact>& contacts)
{
	for (auto& contact : contacts)
	{
		float totalInverseMass = contact.bodyA->inverseMass + contact.bodyB->inverseMass;
		Vector2 separation = Vector2Scale(contact.normal, contact.depth / totalInverseMass);
		contact.bodyA->position = Vector2Add(contact.bodyA->position, Vector2Scale(separation, contact.bodyA->inverseMass));
		contact.bodyB->position = Vector2Subtract(contact.bodyB->position, Vector2Scale(separation, contact.bodyB->inverseMass));
	}
}

void ResolveContacts(std::vector<Contact>& contacts)
{
	for (auto& contact : contacts)
	{
		// compute relative velocity
		Vector2 rv = Vector2Subtract(contact.bodyA->velocity, contact.bodyB->velocity);
		// project relative velocity onto the contact normal
		float nv = Vector2DotProduct(rv, contact.normal);

		// skip if bodies are separating
		if (nv > 0) continue;

		// total inverse mass = (1/mA + 1/mB)
		float totalInverseMass = contact.bodyA->inverseMass + contact.bodyB->inverseMass;
		// impulse scalar = -(1 + restitution) * vn / (1/mA + 1/mB)
		float impulseMagnitude = -(1 + contact.restitution) * nv / totalInverseMass;

		// impulse vector along contact normal
		Vector2 impulse = Vector2Scale(contact.normal, impulseMagnitude);

		// apply equal and opposite impulses
		contact.bodyA->AddForce(impulse, ForceMode::IMPULSE);
		contact.bodyB->AddForce(Vector2Negate(impulse), ForceMode::IMPULSE);
	}
}
