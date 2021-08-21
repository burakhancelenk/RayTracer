#ifndef PLANE_H
#define PLANE_H

#include "Object.h"
#include "Vector3.h"
#include "Ray.h"
#include "Material.h"
#include "Hit.h"


 
namespace Primitive {

	// A 2D plane defined by its normal vector, width and height
	class Plane : public Object 
	{
		private:
			Vector3 m_center;
			Vector3 m_normal;
			Vector3 m_upVector;
			Vector3 m_sideVector;
			Material m_material;
			float m_width;
			float m_height;
			bool m_isBackFaceCulling = true;
			
		public:
			//Default constructor
			Plane();

			/*
			* @param center, center point of the plane
			* @param normal, normal vector of the plane
			* @param width, width of the plane
			* @param height, height of the plane
			* Default material will be attached if it's used.
			*/
			Plane(const Vector3& center,
				  const Vector3& normal,
				  const Vector3& upVector,
				  float width,
				  float height,
				  bool isBackFaceCulling);

			/*
			* @param center, center point of the plane
			* @param normal, normal vector of the plane
			* @param width, width of the plane
			* @param heigth, height of the plane
			* @param isBackFaceCulling, determines that the plane will be rendered for both side.
			* @param material, material attached to the plane
			*/
			Plane(const Vector3& center,
				  const Vector3& normal,
				  const Vector3& upVector,
				  float width,
				  float height,
				  bool isBackFaceCulling,
				  const Material& material);

			// override Object::intersect_first_image
			bool intersect_first_image(const Ray& ray) const override;

			// override Object::intersect
			Hit intersect(const Ray& ray) const override;

			// Returns normal vector
			Vector3 normal() const { return m_normal; }

			// Returns up vector
			Vector3 up_vector() const { return m_upVector; }

			// Returns center point
			Vector3 center() const { return m_center; }

			// Returns width of the plane
			float width() const { return m_width; }

			// Returns height of the plane
			float height() const { return m_height; }

			// Debug
			friend std::ostream& operator<<(std::ostream& os, const Plane& plane) {
				os << "Plane(" 
					<< "center : " << plane.m_center << " , "
					<< "normal : " << plane.m_normal << " , "
					<< "width : " << plane.m_width << " , "
					<< "height : " << plane.m_height << " , "
					<< "bfc : " << plane.m_isBackFaceCulling << " , "
					<< "material : " << plane.m_material 
					<< ")" << std::endl;
				return os;
			}
	};

}

#endif // !PLANE_H

