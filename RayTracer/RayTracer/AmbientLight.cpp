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
	bool realLightBehaviour,
	const Vector3& position,
	Vector3& direction,
	Vector3& intensity,
	float& distance) const 
{
	distance = std::numeric_limits<float>::infinity();
	intensity = m_color * m_intensity;
}

void AmbientLight::get_sample_points(
	const Vector3& hitPoint,
	std::vector<Vector3>& samplePoints,
	int sampleAmount) const
{
	// There is no either hard or soft shadow support for ambient light, maybe later.
	samplePoints.reserve(0);
}
