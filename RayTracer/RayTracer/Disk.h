#ifndef DISK_H
#define DISK_H

#include "Material.h"
#include "Ray.h"
#include "Object.h"

namespace Primitive {

	// A simple 2D disk defined by its center, normal vector and radius
	class Disk: public Object 
	{
		private:
			Vector3 m_center;
			Vector3 m_normal;
			float m_radius;
			Material m_material;
			bool m_isBackFaceCulling = true;

		public:
			// Default constructor
			Disk();

			/*
			* @param center, center point of the disk
			* @param normal, normal vector of the disk
			* @param radius, radius value of the disk
			* @param isBackFaceCulling, determines that the disk will be rendered for both side.
			*/
			Disk(const Vector3& center, const Vector3& normal, float radius, bool isBackFaceCulling);

			/*
			* @param center, center point of the disk
			* @param normal, normal vector of the disk
			* @param radius, radius value of the disk
			* @param material, material attached to the disk
			* @param isBackFaceCulling, determines that the disk will be rendered for both side.
			*/
			Disk(const Vector3& center, const Vector3& normal, float radius, bool isBackFaceCulling, const Material& material);

			// override Object::intersectFirstImage
			bool intersect_first_image(const Ray& ray) const override;

			// override Object::intersect
			Hit intersect(const Ray& ray) const override;

			// Returns normal vector
			Vector3 normal() const { return m_normal; }

			// Returns center point
			Vector3 center() const { return m_center; }

			// Debug
			friend std::ostream& operator<<(std::ostream& os, const Disk& disk) {
				os << "Disk(" 
					<< "center : " << disk.m_center << " , "
					<< "normal : " << disk.m_normal << " , "
					<< "radius : " << disk.m_radius << " , "
					<< "bfc : " << disk.m_isBackFaceCulling << " , "
					<< "material : " << disk.m_material 
					<< ")" << std::endl;
				return os;
			}
	};

}

#endif // !DISK_H
