#include "Scene.h"

using namespace Core;

Scene::Scene(const CameraPtr& camera)
	: m_camera(camera)
{}

void Scene::add(const ObjectPtr& obj)
{
	m_objects.push_back(obj);
}

void Scene::add(const LightPtr& light)
{
	m_lights.push_back(light);
}

Hit Scene::intersect(const Ray& ray) const
{
	Hit hit, bestHit;

	// Compare ray-object intersections and take the closest one
	for (const ObjectPtr& obj : get_objects()) {
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