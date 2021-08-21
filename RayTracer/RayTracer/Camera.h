#ifndef CAMERA_H
#define CAMERA_H

#include "Ray.h"

using namespace Utility;

namespace Core {
	
	// Abstract class for camera models
	class Camera 
	{
		public:

			// Returns a ray passing through (X,Y) pixel coordinates
			virtual Ray pixel_to_ray(int pixelX, int pixelY) const = 0;

			// Overloaded version of the function above (for anti aliasing)
			virtual Ray pixel_to_ray(float pixelX, float pixelY) const = 0;

			// Returns number of pixels at horizontal axis
			virtual int get_width() const = 0;

			// Returns number of pixels at vertical axis
			virtual int get_height() const = 0;

			// Debug
			friend std::ostream& operator<<(std::ostream& os, const Camera& cam) {
				os << "Camera" << std::endl;
				return os;
			}
	};

}

using CameraPtr = std::shared_ptr<Core::Camera>;

#endif // !CAMERA_H

