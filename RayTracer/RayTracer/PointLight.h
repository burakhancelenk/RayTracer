#ifndef POINTLIGHT_H
#define POINTLIGHT_H

#include "Light.h"

namespace Core {

	// Illuminates spherical area in the scene. (ex. light bulb)
	class PointLight : public Light 
	{
		private:
			float m_intensity;
			float m_maxDistance;
			Vector3 m_position;
			Vector3 m_color;

			// Radius of the spherical point light. it makes sense if and only if soft shadows are active.
			// Otherwise it will be treated as a point, no matter what the value of the radius is.
			float m_radius;
			
		public:
			// Default constructor
			PointLight();

			// @param position, position of the light source
			// @param color, RGB color value of the light source
			// @param intensity, intensity value of the light source
			PointLight(const Vector3& position, const Vector3& color, float intensity);

			/* 
			* @param position, position of the light source
			* @param color, RGB color value of the light source
			* @param intensity, intensity value of the light source
			* @param maxDistance, max distance value being illuminated
			* @param radius, radius value of the light source for soft shadows
			*/
			PointLight(const Vector3& position, const Vector3& color, float intensity, float maxDistance, float radius);

			// override Light::at
			void at(bool realLightBehaviour, 
					const Vector3& position,
					Vector3& direction,
					Vector3& intensity,
					float& distance) const override;

			// override Light::get_sample_points
			void get_sample_points(const Vector3& hitPoint, std::vector<Vector3>& samplePoints, int sampleAmount) const override;

			// Debug
			friend std::ostream& operator<<(std::ostream& os, const PointLight& pl) {
				os << "PointLight(" 
					<< "Position : " << pl.m_position << " , " 
					<< "Intensity : " << pl.m_intensity << " , "
					<< "Color : " << pl.m_color << " , "
					<< "Max Distance : " << pl.m_maxDistance << " , "
					<< "Radius : " << pl.m_radius
					<< ")" << std::endl;
				return os;
			}
	};

}

#endif // !POINTLIGHT_H


