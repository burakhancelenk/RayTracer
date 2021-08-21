#ifndef OBJECT_H
#define OBJECT_H

#include "Material.h"
#include "Ray.h"
#include "Hit.h"

using namespace Utility;

namespace Core {

	// Abstract class for object types
	class Object 
	{ 
		public:
			// Checks for intersection, returns true if there is a hit.
			virtual bool intersect_first_image(const Ray& ray) const = 0;

			// Calculates the intersection, returns hit informations.
			virtual Hit intersect(const Ray& ray) const = 0;

			// Debug
			friend std::ostream& operator<<(std::ostream& os, const Object& object) {
				os << "Object" << std::endl;
				return os;
			}
	};

}

using ObjectPtr = std::shared_ptr<Object>;

#endif // !OBJECT_H

