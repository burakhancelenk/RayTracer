#ifndef CAMERA_H
#define CAMERA_H

#include "Ray.h"

using namespace Utility;

namespace Core {
	
	// Perspective camera model
	class Camera 
	{
		private:
			float m_sensorWidth = 36;
			float m_focalLength;
			int m_width;
			int m_height;
			Vector3 m_position;
			Vector3 m_target;
			Vector3 m_up;
		
		public:
			// Default constructor
			Camera();

			/*
			* @param width, number of pixels at horizontal axis
			* @param height, number of pixels at vertical axis
			* @param focalLength, focal length of the camera
			* @param position, position of the camera
			* @param target, direction where the camera is looking at
			* @param up, up direction of the camera
			*/
			Camera(	int width,
					int height,
					float focalLength,
					const Vector3& position,
					const Vector3& target,
					const Vector3& up);

			// Returns a ray where the origin is set to camera position
			// and the direction is set to specified pixels.
			Ray pixel_to_ray(int pixelX, int pixelY) const;

			// Overloaded version of the function above (for anti aliasing)
			Ray pixel_to_ray(float pixelX, float pixelY) const;

			// Returns width
			int get_width() const;

			// Returns height
			int get_height() const;

			// Debug
			friend std::ostream& operator<<(std::ostream& os, const Camera& cam) {
				os << "Camera(" << "Position : " << cam.m_position << " , " 
					<< "Direction : " << cam.m_target << " , " 
					<< "Up Direction : " << cam.m_up << " , "
					<< "Pixel width : " << cam.m_width << " , "
					<< "Pixel height : " << cam.m_height << " , "
					<< "Focal length : " << cam.m_focalLength << " , "
					<< "Sensor width : " << cam.m_sensorWidth << ")";
				return os;
			}
	};

}

#endif // !CAMERA_H

