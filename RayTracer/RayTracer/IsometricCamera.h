#ifndef ISOMETRICCAMERA_H
#define ISOMETRICCAMERA_H

#include "Ray.h"
#include "Camera.h"

using namespace Utility;

namespace Core {

	// Isometric camera model
	class IsometricCamera : public Camera
	{
		private:
			float m_screenWidth = 36;
			int m_width;
			int m_height;
			Vector3 m_position;
			Vector3 m_target;
			Vector3 m_up;

		public:
			// Default constructor
			IsometricCamera();

			/*
			* @param screenWidth, screen width of the camera
			* @param width, number of pixels at horizontal axis
			* @param height, number of pixels at vertical axis
			* @param position, position of the camera
			* @param target, position where the camera is looking at
			* @param up, up direction of the camera
			*/
			IsometricCamera(float screenWidth,
							int width,
							int height,
							const Vector3& position,
							const Vector3& target,
							const Vector3& up);

			// Returns a ray where the origin is set to specified pixel
			// and the direction is set to camera direction.
			Ray pixel_to_ray(int pixelX, int pixelY) const override;

			// Overloaded version of the function above (for anti aliasing)
			Ray pixel_to_ray(float pixelX, float pixelY) const override;

			// Returns width
			int get_width() const override { return m_width; }

			// Returns height
			int get_height() const override { return m_height; }
	
			// Debug
			friend std::ostream& operator<<(std::ostream& os, const IsometricCamera& cam) {
				os << "Camera(" 
					<< "Position : " << cam.m_position << " , "
					<< "Target position : " << cam.m_target << " , "
					<< "Up Direction : " << cam.m_up << " , "
					<< "Pixel width : " << cam.m_width << " , "
					<< "Pixel height : " << cam.m_height << " , "
					<< "Screen width : " << cam.m_screenWidth 
					<< ")" << std::endl;
				return os;
			}
	};

}

#endif // !ISOMETRICCAMERA_H

