#ifndef DIRECTIONALLIGHT_H
#define DIRECTIONALLIGHT_H

#include "Light.h"

namespace Core {

	// Illuminates the scene in one direction. (ex. sun)
	class DirectionalLight : public Light
	{
		private:
			float m_intensity;
			Vector3 m_direction;
			Vector3 m_color;

		public:
			// Default constructor
			DirectionalLight();

			// @param direction, unit vector telling in which direction the source is
			// @param color, RGB color value of the light source
			// @param intensity, intensity value of the light source
			DirectionalLight(const Vector3& direction, const Vector3& color, float intensity);

			// override Light::at
			void at(const Vector3& position, Vector3& direction, Vector3& intensity, float& distance) const override;

			// Debug
			friend std::ostream& operator<<(std::ostream& os, const DirectionalLight& dl) {
				os << "DirectionalLight(" << "Direction : " << dl.m_direction 
					<< " , " << "Intensity : " << dl.m_intensity 
					<< "Color : " << dl.m_color << ")";
				return os;
			}
	};

}

#endif