#ifndef SPOTLIGHT_H
#define SPOTLIGHT_H

#include "Light.h";

namespace Core {

	// Illuminates cone shaped area in the scene. (ex. flashlight)
	class SpotLight : public Light 
	{
		private:
			float m_minIntensity;
			float m_maxIntensity;
			float m_innerRadius;
			float m_outerRadius;
			float m_maxDistance;
			Vector3 m_position;
			Vector3 m_direction;
			Vector3 m_color;

		public:
			// Default constructor
			SpotLight();

			/* @param position, position of the spot light
			*  @param direction, unit vector telling in which direction the light source is
			*  @param color, RGB color value of the light source
			*/
			SpotLight(const Vector3& position,
					  const Vector3& direction,
					  const Vector3& color);

			/* @param minIntensity, intensity value of the light source for outer radius
			*  @param maxIntesity, intensity value of the light source for inner radius
			*  @param innerRadius, defines the radius of the inner cone where the intensity value at max
			*  @param outerRadius, defines the radius of the outer cone where the intensity takes a value
			*  between min and max intensity according to the distance.
			*  @param maxDistance, max distance where the light rays can reach
			*/
			SpotLight(const Vector3& position, 
					  const Vector3& direction,
					  const Vector3& color,
					  float minIntensity,
					  float maxIntensity,
					  float innerRadius,
					  float outerRadius,
					  float maxDistance);

			// override Light::at
			void at(const Vector3& position, Vector3& direction, Vector3& intensity, float& distance) const override;

			// Debug
			friend std::ostream& operator<<(std::ostream& os, const SpotLight& sl) {
				os << "SpotLight(" 
					<< "Position : " << sl.m_position << " , "
					<< "Direction : " << sl.m_direction
					<< "Color : " << sl.m_color 
					<< "Min Intensity : " << sl.m_minIntensity
					<< "Max Intensity : " << sl.m_maxIntensity
					<< "Inner Radius : " << sl.m_innerRadius
					<< "Outer Radius : " << sl.m_outerRadius
					<< "Max Distance : " << sl.m_maxDistance
					<< ")";
				return os;
			}
	};

}

#endif // !SPOTLIGHT_H
