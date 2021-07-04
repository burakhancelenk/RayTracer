#ifndef PLANE_H
#define PLANE_H

#include "Object.h"
#include "Vector3.h"
#include "Ray.h"
#include "Material.h"
#include "Hit.h"


 
namespace Primitive {

	// An infinite 2D plane defined by its normal vector
	class Plane : public Object 
	{
		private:
			Vector3 m_center;
			Vector3 m_normal;
			Material m_material;

		public:
			//Default constructor
			Plane();

			/*
			* @param center, center point of the plane
			* @param normal, normal vector of the plane
			* Default material will be attached if it's used.
			*/
			Plane(const Vector3& center, const Vector3& normal);

			/*
			* @param center, center point of the plane
			* @param normal, normal vector of the plane
			* @param material, material attached to the plane
			*/
			Plane(const Vector3& center, const Vector3& normal, const Material& material);

			// override Object::intersect_first_image
			bool intersect_first_image(const Ray& ray) const override;

			// override Object::intersect
			Hit intersect(const Ray& ray) const override;

			// Returns normal vector
			Vector3 normal() const { return m_normal; }

			// Returns center point
			Vector3 center() const { return m_center; }

			// Debug
			friend std::ostream& operator<<(std::ostream& os, const Plane& plane) {
				os << "Plane(" 
					<< "center : " << plane.m_center << " , "
					<< "normal : " << plane.m_normal << " , "
					<< "material : " << plane.m_material << ")";
				return os;
			}
	};

}

#endif // !PLANE_H

