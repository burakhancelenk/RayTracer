#ifndef BOX_H
#define BOX_H

#include "Object.h"
#include "math.h"
#include "Plane.h"
#include <vector>


namespace Primitive {

	// A simple 3D box defined by its center, width and height
	class Box : public Object
	{
		private:
			Vector3 m_center;
			Vector3 m_upVector;
			Vector3 m_frontVector;
			float m_width;
			float m_height;
			float m_depth;
			Material m_material;
			std::vector<Plane> m_surfaces;

		public:

			// Default constructor
			Box();

			/*
			* @param center, center point of the box
			* @param upVector, up direction of the box
			* @param frontVector, front direction of the box
			* @param width, box width (from center to the side)
			* @param height, box height (from center to the side)
			* @param depth, box depth (from center to the side)
			* Default material will be attached if it's used.
			*/
			Box(const Vector3& center,
				const Vector3& upVector,
				const Vector3& frontVector,
				float width,
				float height,
				float depth);

			/*
			* @param center, center point of the box
			* @param upVector, up direction of the box
			* @param frontVector, front direction of the box
			* @param width, box width (from center to the side)
			* @param height, box height (from center to the side)
			* @param depth, box depth (from center to the side)
			* @param material, material attached to the box
			*/
			Box(const Vector3& center,
				const Vector3& upVector,
				const Vector3& frontVector,
				float width,
				float height,
				float depth,
				const Material& material);

			// override Object::intersectFirstImage
			bool intersect_first_image(const Ray& ray) const override;

			// override Object::intersect
			Hit intersect(const Ray& ray) const override;

			// Returns width value
			float width() const { return m_width; }

			// Returns height value
			float height() const { return m_height; }

			// Returns depth value
			float depth() const { return m_depth; }

			// Returns center point
			Vector3 center() const { return m_center; }

			// Debug
			friend std::ostream& operator<<(std::ostream& os, const Box& box) {
				os << "Box(" << "center : " << box.m_center << " , "
					<< "width : " << box.m_width << " , "
					<< "height : " << box.m_height << " , "
					<< "depth : " << box.m_depth << " , "
					<< "material : " << box.m_material 
					<< ")" << std::endl;
				return os;
			}
	};

}

#endif // !BOX_H
