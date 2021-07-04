#include "AmbientLight.h"

using namespace Core;

AmbientLight::AmbientLight()
	: m_color(1, 1, 1)
	, m_intensity(1)
{}

AmbientLight::AmbientLight(const Vector3& color, float intensity)
	: m_color(color)
	, m_intensity(intensity)
{}

void AmbientLight::at(
	const Vector3& position,
	Vector3& direction,
	Vector3& intensity,
	float& distance) const 
{
	distance = std::numeric_limits<float>::infinity();
	intensity = m_color * m_intensity;
}
