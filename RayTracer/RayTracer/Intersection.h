#ifndef INTERSECTION_H
#define INTERSECTION_H

#include "Object.h"
#include "Vector3.h"
#include "Ray.h"
#include "Material.h"
#include "Hit.h"
#include <vector>

namespace Primitive {

	// Object made of the intersection of others
	class Intersection : public Object 
	{
		private:
			ObjectPtr m_objectA;
			ObjectPtr m_objectB;
			Material m_material;

		public:
			// No need for default constructor
			// @param objectA, first object
			// @param objectB, second object
			// @param material, material of the intersection
			Intersection(ObjectPtr objectA, ObjectPtr objectB, const Material& material);

			// override Object::intersect_first_image
			bool intersect_first_image(const Ray& ray) const override;

			// override Object::intersect
			Hit intersect(const Ray& ray) const override;

			// Returns first object
			ObjectPtr objectA() const { return m_objectA; }

			// Returns second object
			ObjectPtr objectB() const { return m_objectB; }

			// Debug
			friend std::ostream& operator<<(std::ostream& os, const Intersection& intersection) {
				os << "Intersection(" 
					<< "Object1 : " << intersection.m_objectA << " , "
					<< "Object2 : " << intersection.m_objectB << " , "
					<< "Material : " << intersection.m_material
					<< ")" << std::endl;
				return os;
			}
	};

}

#endif // !INTERSECTION_H

