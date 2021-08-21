#ifndef CYLINDER_H
#define CYLINDER_H

#include "Object.h"
#include "Disk.h"
#include "math.h"


namespace Primitive {

	// A simple 3D cylinder defined by its center, direction, height and radius
	class Cylinder : public Object
	{
		private:
			Vector3 m_center;
			Vector3 m_direction;
			float m_radius;
			float m_height;
			Material m_material;
			
			Disk m_top, m_bottom;

		public:

			// Default constructor
			Cylinder();

			/*
			* @param center, center point of the cylinder
			* @parma direction, direction of the cylinder
			* @param radius, radius value of the cylinder
			* @param height, height value of the cylinder
			* Default material will be attached if it's used.
			*/
			Cylinder(const Vector3& center, const Vector3& direction, float radius, float height);

			/*
			* @param center, center point of the cylinder
			* @parma direction, direction of the cylinder
			* @param radius, radius value of the cylinder
			* @param height, height value of the cylinder
			* @param material, material attached to the cylinder
			*/
			Cylinder(const Vector3& center, const Vector3& direction, float radius, float height, const Material& material);

			// override Object::intersectFirstImage
			bool intersect_first_image(const Ray& ray) const override;

			// override Object::intersect
			Hit intersect(const Ray& ray) const override;

			// Returns center point
			Vector3 center() const { return m_center; }

			// Returns direction of the cylinder
			Vector3 direction() const { return m_direction; }

			// Returns radius value
			float radius() const { return m_radius; }

			// Returns height value
			float height() const { return m_height; }

			// Debug
			friend std::ostream& operator<<(std::ostream& os, const Cylinder& cylinder) {
				os << "Cylinder(" 
					<< "center : " << cylinder.m_center << " , "
					<< "direction : " << cylinder.m_direction << " , "
					<< "radius : " << cylinder.m_radius << " , "
					<< "height : " << cylinder.m_height << " , "
					<< "material : " << cylinder.m_material 
					<< ")" << std::endl;
				return os;
			}
	};

}

#endif // !CYLINDER_H
