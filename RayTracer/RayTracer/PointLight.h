#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include "Light.h"

namespace Core {

	// Illuminates spherical area in the scene. (ex. light bulb)
	class PointLight : public Light 
	{
		private:
			float m_intensity;
			Vector3 m_position;
			Vector3 m_color;
			
		public:
			// Default constructor
			PointLight();

			// @param position, position of the light source
			// @param color, RGB color value of the light source
			// @parma intensity, intensity value of the light source
			PointLight(const Vector3& position, const Vector3& color, float intensity);

			// override Light::at
			void at(const Vector3& position, Vector3& direction, Vector3& intensity, float& distance) const override;

			// Debug
			friend std::ostream& operator<<(std::ostream& os, const PointLight& pl) {
				os << "PointLight(" << "Position : " << pl.m_position << " , " 
					<< "Intensity : " << pl.m_intensity 
					<< "Color : " << pl.m_color << ")";
				return os;
			}
	};

}

#endif // !POINTLIGHT_H


