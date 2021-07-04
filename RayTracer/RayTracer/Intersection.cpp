#include "Intersection.h"
#include <iostream>

using namespace Primitive;

Intersection::Intersection(
	ObjectPtr objectA,
	ObjectPtr objectB,
	const Material& material)

	: m_objectA(objectA)
	, m_objectB(objectB)
	, m_material(material)
{}

bool Intersection::intersect_first_image(const Ray& ray) const
{
	constexpr float eps = 1e-5f;
	Hit hitA = m_objectA->intersect(ray);
	Hit hitB = m_objectB->intersect(ray);

	if (!hitA.isValid || !hitB.isValid) {
		// At least one of the objects doesn't exist, no intersection
		return false;
	}

	if ((hitA.point - hitB.point).length() <= eps) {
		// Hit points are at the same location, intersection
		return true;
	}

	// For determine if objects are 3D like sphere or 2D like plane
	Ray subRayA(hitA.point + ray.direction * eps, ray.direction);
	Ray subRayB(hitB.point + ray.direction * eps, ray.direction);
	Hit hitAA = m_objectA->intersect(subRayA);
	Hit hitBB = m_objectB->intersect(subRayB);

	bool is_A_3D = hitAA.isValid;
	bool is_B_3D = hitBB.isValid;

	// One of the objects is 3D
	if (is_A_3D || is_B_3D) {
		Hit fartherHit;
		ObjectPtr nearObject;
		if (hitA.distance > hitB.distance) {
			fartherHit = hitA;
			nearObject = m_objectB;
		}
		else
		{
			fartherHit = hitB;
			nearObject = m_objectA;
		}

		Ray subRay(fartherHit.point, ray.direction);
		Ray subRayReversed(fartherHit.point, -ray.direction);
		Hit hit = nearObject->intersect(subRay);
		Hit hitReversed = nearObject->intersect(subRayReversed);
		if (hit.isValid && hitReversed.isValid) {
			return true;
		}
	}
	return false;
	/*
	*	If both objects are 2D, for an intersection hit points must be at
	*	the same location so we already checked that situation at the beginning
	*	of the function
	*/
}

Hit Intersection::intersect(const Ray& ray) const
{
	constexpr float eps = 1e-5f;
	Hit hitA = m_objectA->intersect(ray);
	Hit hitB = m_objectB->intersect(ray);

	if (!hitA.isValid || !hitB.isValid) {
		// At least one of the objects doesn't exist, no intersection
		return Hit();
	}

	if((hitA.point - hitB.point).length() <= eps){
		// Hit points are at the same location, intersection
		return Hit{
			true,
			hitA.point,
			hitA.normal,
			m_material,
			hitA.distance
		};
	}

	// For determine if objects are 3D like sphere or 2D like plane
	Ray subRayA(hitA.point + ray.direction * eps, ray.direction);
	Ray subRayB(hitB.point + ray.direction * eps, ray.direction);
	Hit hitAA = m_objectA->intersect(subRayA);
	Hit hitBB = m_objectB->intersect(subRayB);
	
	bool is_A_3D = hitAA.isValid;
	bool is_B_3D = hitBB.isValid;

	// One of the objects is 3D
	if (is_A_3D || is_B_3D) {
		Hit fartherHit;
		ObjectPtr nearObject;
		if (hitA.distance > hitB.distance) {
			fartherHit = hitA;
			nearObject = m_objectB;
		}
		else
		{
			fartherHit = hitB;
			nearObject = m_objectA;
		}

		Ray subRay(fartherHit.point, ray.direction);
		Ray subRayReversed(fartherHit.point, -ray.direction);
		Hit hit = nearObject->intersect(subRay);
		Hit hitReversed = nearObject->intersect(subRayReversed);
		if (hit.isValid && hitReversed.isValid) {
			return Hit{
			true,
			fartherHit.point,
			fartherHit.normal,
			m_material,
			fartherHit.distance
			};
		}
		
	}
	return Hit();
	/*	
	*	If both objects are 2D, for an intersection hit points must be at
	*	the same location so we already checked that situation at the beginning
	*	of the function
	*/
}