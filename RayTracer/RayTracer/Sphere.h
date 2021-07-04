#ifndef SPHERE_H
#define SPHERE_H

#include "Object.h"
#include "math.h"


namespace Primitive {

	// A simple 3D sphere defined by its center and radius
	class Sphere : public Object 
	{
		private:
			Vector3 m_center;
			float m_radius;
			Material m_material;

		public:

			// Default constructor
			Sphere();
			
			/*
			* @param center, center point of the sphere
			* @param radius, radius value of the sphere
			* Default material will be attached if it's used.
			*/
			Sphere(const Vector3& center, float radius);

			/*
			* @param center, center point of the sphere
			* @param radius, radius value of the sphere
			* @param material, material attached to the sphere
			*/
			Sphere(const Vector3& center, float radius, const Material& material);

			// override Object::intersectFirstImage
			bool intersect_first_image(const Ray& ray) const override;

			// override Object::intersect
			Hit intersect(const Ray& ray) const override;

			// Returns radius value
			float radius() const { return m_radius; }

			// Returns center point
			Vector3 center() const { return m_center; }

			// Debug
			friend std::ostream& operator<<(std::ostream& os, const Sphere& sphere) {
				os << "Sphere(" << "center : " << sphere.m_center << " , " 
					<< "radius : " << sphere.m_radius << "material : " << sphere.m_material << ")";
				return os;
			}
	};

}

#endif // !SPHERE_H

