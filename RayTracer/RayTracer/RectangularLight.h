#ifndef RECTANGULARLIGHT_H
#define RECTANGULARLIGHT_H

#include "Light.h";

namespace Core {

	// Illuminates rectangle shaped area in the scene. (ex. LED panels)
	// This light type only works if soft shadows is active.
	class RectangularLight : public Light
	{
		private:
			float m_minIntensity;
			float m_maxIntensity;
			float m_width;
			float m_height;
			float m_innerAngle;
			float m_outerAngle;
			float m_maxDistance;
			Vector3 m_position;
			Vector3 m_direction;
			Vector3 m_upVector;
			Vector3 m_color;

		public:
			// Default constructor
			RectangularLight();

			/* @param position, position of the rectangular light
			*  @param direction, unit vector telling in which direction the light source is
			*  @param upVector, unit vector telling the up direction of light source, perpendicular to the direction.
			*  @param color, RGB color value of the light source
			*  @param width, width of the light source
			*  @param height, height of the light source
			*/
			RectangularLight(const Vector3& position,
							 const Vector3& direction,
							 const Vector3& upVector,
							 const Vector3& color,
							 float width,
							 float height);

			/* @param minIntensity, intensity value of the light source for outer radius
			*  @param maxIntesity, intensity value of the light source for inner radius
			*  @param innerAngle(radians), defines the angle between the inner rectangle(where the intensity value at max)
			*  and direction.
			*  @param outerAngle(radians), defines the angle between the outer rectangle(where the intensity takes a value
			*  between min and max intensity according to the distance) and direction.
			*  @param maxDistance, max distance where the light rays can reach
			*/
			RectangularLight(const Vector3& position,
							 const Vector3& direction,
							 const Vector3& upVector,
							 const Vector3& color,
							 float minIntensity,
							 float maxIntensity,
							 float width,
							 float height,
							 float innerAngle,
							 float outerAngle,
							 float maxDistance);

			// override Light::at
			void at(bool realLightBehaviour,
					const Vector3& position,
					Vector3& direction,
					Vector3& intensity,
					float& distance) const override;

			// override Light::get_sample_points
			void get_sample_points(const Vector3& hitPoint,
									std::vector<Vector3>& samplePoints,
									int sampleAmount) const override;

			// Debug
			friend std::ostream& operator<<(std::ostream& os, const RectangularLight& rl) {
				os << "RectangularLight("
					<< "Position : " << rl.m_position << " , "
					<< "Direction : " << rl.m_direction << " , "
					<< "Up Vector : " << rl.m_upVector << " , "
					<< "Color : " << rl.m_color << " , "
					<< "Min Intensity : " << rl.m_minIntensity << " , "
					<< "Max Intensity : " << rl.m_maxIntensity << " , "
					<< "Inner Angle : " << rl.m_innerAngle << " , "
					<< "Outer Angle : " << rl.m_outerAngle << " , "
					<< "Max Distance : " << rl.m_maxDistance
					<< ")" << std::endl;
				return os;
			}
	};

}

#endif // !RECTANGULARLIGHT_H
