#include "Union.h"

using namespace Primitive;

Union::Union(const std::vector<ObjectPtr>& objects)
	: m_objects(objects)
{}

void Union::add(const ObjectPtr& obj)
{
	m_objects.push_back(obj);
}

bool Union::intersect_first_image(const Ray& ray) const
{
	bool hit;

	// Compare ray-object intersections and take the closest one
	for (const ObjectPtr& obj : objects()) {
		hit = obj->intersect_first_image(ray);
		if (hit)
		{
			return true;
		}
	}
}

Hit Union::intersect(const Ray& ray) const
{
	Hit hit, bestHit;

	// Compare ray-object intersections and take the closest one
	for (const ObjectPtr& obj : objects()) {
		hit = obj->intersect(ray);
		if (!hit.isValid) continue;

		if (!bestHit.isValid || hit.distance < bestHit.distance)
		{
			bestHit = hit;
		}
	}

	// Return the closest hit informations
	return bestHit;
}
