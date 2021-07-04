#include "PointLight.h"

using namespace Core;

PointLight::PointLight()
	: m_position()
	, m_color(1,1,1)
	, m_intensity(1)
{}

PointLight::PointLight(
	const Vector3& position,
	const Vector3& color,
	float intensity) 

	: m_position(position)
	, m_color(color)
	, m_intensity(intensity)
{}

void PointLight::at(
	const Vector3& position,
	Vector3& direction, Vector3& intensity,
	float& distance) const
{
	Vector3 v = m_position - position;
	distance = v.length();
	direction = v / distance;
	intensity = m_color * m_intensity / (v.length_squared());
}