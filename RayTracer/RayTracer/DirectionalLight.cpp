#include "DirectionalLight.h"
#include <limits>

using namespace Core;

DirectionalLight::DirectionalLight()
	: m_direction(1, -0.5, 1)
	, m_color(1,1,1)
	, m_intensity(1)
{}

DirectionalLight::DirectionalLight(
	const Vector3& direction,
	const Vector3& color,
	float intensity)

	: m_direction(direction)
	, m_color(color)
	, m_intensity(intensity)
{}

void DirectionalLight::at(
	const Vector3& position,
	Vector3& direction,
	Vector3& intensity,
	float& distance) const
{
	distance = std::numeric_limits<float>::infinity();
	direction = m_direction;
	intensity = m_color * m_intensity;
}