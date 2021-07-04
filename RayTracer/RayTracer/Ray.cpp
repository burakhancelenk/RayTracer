#include "Ray.h"

using namespace Utility;

Ray::Ray() 
	: origin()
	, direction(0,0,1)
{}

Ray::Ray(const Vector3 & _origin, const Vector3 & _direction)
	: origin(_origin)
	, direction(_direction)
{}

Vector3 Ray::at(const float& t) const {
	return origin + direction * t;
}
