#ifndef CONE_H
#define CONE_H

#include "Object.h"
#include "Disk.h"
#include "math.h"


namespace Primitive {

	// A simple 3D cone defined by its center, direction, height and radius or by its top point, angle and height.
	class Cone : public Object
	{
		private:
			Vector3 m_center;
			Vector3 m_direction;
			float m_radius;
			float m_height;
			Material m_material;

			Vector3 m_topPoint;
			float m_angle;
			Disk m_bottom;

		public:

			// Default constructor
			Cone();

			/*
			* @param center, center point of the cone's bottom disk
			* @parma direction, direction of the cone
			* @param radius, radius value of the cone
			* @param height, height value of the cone
			* Default material will be attached if it's used.
			*/
			Cone(const Vector3& center, const Vector3& direction, float radius, float height);

			/*
			* @param topPoint, top point of the cone
			* @param angle, angle(radians) value of the cone
			* @parma direction, direction from the top point to the bottom center
			* @param height, height value of the cone
			* Default material will be attached if it's used.
			*/
			Cone(const Vector3& topPoint, float angle, const Vector3& direction, float height);

			/*
			* @param center, center point of the cone's bottom disk
			* @parma direction, direction of the cone
			* @param radius, radius value of the cone
			* @param height, height value of the cone
			* @param material, material attached to the cone
			*/
			Cone(const Vector3& center, const Vector3& direction, float radius, float height, const Material& material);

			/*
			* @param topPoint, top point of the cone
			* @param angle, angle(radians) value between the direction and edge of the cone
			* @parma direction, direction from the top point to the bottom center
			* @param height, height value of the cone
			* @param material, material attached to the cone
			*/
			Cone(const Vector3& topPoint, float angle, const Vector3& direction, float height, const Material& material);

			// override Object::intersectFirstImage
			bool intersect_first_image(const Ray& ray) const override;

			// override Object::intersect
			Hit intersect(const Ray& ray) const override;

			// Returns center point of the cone's bottom disk
			Vector3 center() const { return m_center; }

			// Returns direction of the cone
			Vector3 direction() const { return m_direction; }

			// Returns radius value
			float radius() const { return m_radius; }

			// Returns height value
			float height() const { return m_height; }

			// Debug
			friend std::ostream& operator<<(std::ostream& os, const Cone& cone) {
				os << "Cone("
					<< "center : " << cone.m_center << " , "
					<< "direction : " << cone.m_direction << " , "
					<< "radius : " << cone.m_radius << " , "
					<< "height : " << cone.m_height << " , "
					<< "top point : " << cone.m_topPoint << " , "
					<< "angle : " << cone.m_angle << " , "
					<< "material : " << cone.m_material 
					<< ")" << std::endl;
				return os;
			}
	};

}

#endif // !CONE_H

