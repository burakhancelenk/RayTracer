#ifndef PERSPECTIVECAMERA_H
#define PERSPECTIVECAMERA_H

#include "Ray.h"
#include "Camera.h"

using namespace Utility;

namespace Core {

	// Perspective camera model
	class PerspectiveCamera : public Camera
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
			PerspectiveCamera();

			/*
			* @param width, number of pixels at horizontal axis
			* @param height, number of pixels at vertical axis
			* @param focalLength, focal length of the camera
			* @param position, position of the camera
			* @param target, position where the camera is looking at
			* @param up, up direction of the camera
			*/
			PerspectiveCamera(int width,
							  int height,
							  float focalLength,
							  const Vector3& position,
							  const Vector3& target,
							  const Vector3& up);

			// override Camera::pixel_to_ray
			// Returns a ray where the origin is set to camera position
			// and the direction is set to specified pixels.
			Ray pixel_to_ray(int pixelX, int pixelY) const override;

			// override Camera::pixel_to_ray
			// Overloaded version of the function above (for anti aliasing)
			Ray pixel_to_ray(float pixelX, float pixelY) const override;

			// override Camera::get_width
			// Returns number of pixels at horizontal axis
			int get_width() const override { return m_width; }

			// override Camera::get _height
			// Returns number of pixels at vertical axis
			int get_height() const override { return m_height; }

			// Debug
			friend std::ostream& operator<<(std::ostream& os, const PerspectiveCamera& cam) {
				os << "Camera(" 
					<< "Position : " << cam.m_position << " , "
					<< "Target position : " << cam.m_target << " , "
					<< "Up Direction : " << cam.m_up << " , "
					<< "Pixel width : " << cam.m_width << " , "
					<< "Pixel height : " << cam.m_height << " , "
					<< "Focal length : " << cam.m_focalLength << " , "
					<< "Sensor width : " << cam.m_sensorWidth 
					<< ")" << std::endl;
				return os;
			}
	};

}

#endif // !PERSPECTIVECAMERA_H

