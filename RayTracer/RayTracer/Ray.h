#ifndef RAY_H
#define RAY_H

#include "Vector3.h"

namespace Utility {

	// A simple ray structure defined by an origin point and direction
	struct Ray
	{
		public:
			Vector3 origin;
			Vector3 direction;
		
			// Default constructor
			Ray();

			// @param _origin is the origin point of the ray
			// @param _direction is assumed to be normalized
			Ray(const Vector3 & _origin, const Vector3 & _direction);

			// Returns a point on the ray's direction @param t units away
			Vector3 at(const float t) const;

			// debug
			friend std::ostream& operator<<(std::ostream& os, const Ray& ray) {
				os << "Ray(" 
					<< "origin : " << ray.origin << " , " 
					<< "direction : " << ray.direction 
					<< ")" << std::endl;
				return os;
			}
	};

}

#endif
