#ifndef AMBIENTLIGHT_H
#define AMBIENTLIGHT_H

#include "Light.h"

namespace Core {
 
	// Illuminates each object in the scene equally, regardless of their position and orientation.
	// It is unnecessary to add more than one ambient light.
	class AmbientLight: public Light
	{
		private:
			float m_intensity;
			Vector3 m_color;

		public:
			// Default constructor
			AmbientLight();

			// @param color, the color of the light in RGB format.
			// @param intensity, the intensity of the light.
			AmbientLight(const Vector3& color, float intensity);

			// override Light::at
			void at(const Vector3& position, Vector3& direction, Vector3& intensity, float& distance) const override;

			// Debug
			friend std::ostream& operator<<(std::ostream& os, const AmbientLight& al) {
				os << "AmbientLight(" << "Intensity : " << al.m_intensity 
					<< "Color : " << al.m_color << ")";
				return os;
			}
	};

}

#endif // !AMBIENTLIGHT_H

