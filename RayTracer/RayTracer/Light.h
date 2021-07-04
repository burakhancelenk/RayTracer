#ifndef LIGHT_H
#define LIGHT_H

#include "Vector3.h"

using namespace Utility;

namespace Core {

	// Abstract class for light types
	class Light 
	{ 
		public:
			/*
			* @param position, position at which we query the light's influence
			* @param direction, reference where this functions write the
			*        direction in which this light is seen. This vector is
			*        normalized, going from point towards the light.
			* @param intensity, per color channel intensity of the light as seen
			*        from the query point (there is a decay with distance to
			*        the center of the point light).
			* @param distance, extra output value that I added when casting
			*        shadow rays. This distance is compared to the one to the
			*        closest hit point.
			*/
			virtual void at(const Vector3& position, Vector3& direction, Vector3& intensity, float& distance) const = 0;

			// Debug
			friend std::ostream& operator<<(std::ostream& os, const Light& object) {
				os << "Light";
				return os;
			}
	};

}

using LightPtr = std::shared_ptr<Core::Light>;

#endif // !LIGHT_H

