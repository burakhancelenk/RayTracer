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

			// Soft shadow angle of the directional light. it makes sense if and only if soft shadows are active.
			// Otherwise illumination will be treated with only @param m_direction , no matter what the value of the @param m_ssAngle is.
			float m_ssAngle;

		public:
			// Default constructor
			DirectionalLight();

			// @param direction, unit vector telling in which direction the light source is
			// @param color, RGB color value of the light source
			// @param intensity, intensity value of the light source
			DirectionalLight(const Vector3& direction, const Vector3& color, float intensity, float ssAngle);

			// override Light::at
			void at(bool realLightBehaviour,
					const Vector3& position,
					Vector3& direction,
					Vector3& intensity,
					float& distance) const override;

			// override Light::get_sample_points
			void get_sample_points(const Vector3& hitPoint, std::vector<Vector3>& samplePoints, int sampleAmount) const override;

			// Debug
			friend std::ostream& operator<<(std::ostream& os, const DirectionalLight& dl) {
				os << "DirectionalLight(" 
					<< "Direction : " << dl.m_direction << " , " 
					<< "Intensity : " << dl.m_intensity << " , "
					<< "Color : " << dl.m_color 
					<< ")" << std::endl;
				return os;
			}
	};

}

#endif