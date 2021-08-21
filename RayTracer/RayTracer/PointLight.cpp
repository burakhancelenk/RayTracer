#include "PointLight.h"

#define PI 3.14159265

using namespace Core;

PointLight::PointLight()
	: m_position()
	, m_color(1,1,1)
	, m_intensity(1)
	, m_maxDistance(15)
	, m_radius(0.2)
{}

PointLight::PointLight(
	const Vector3& position,
	const Vector3& color,
	float intensity) 
	
	: m_position(position)
	, m_color(color)
	, m_intensity(intensity)
	, m_maxDistance(15)
	, m_radius(0.2)
{}

PointLight::PointLight(
	const Vector3& position,
	const Vector3& color,
	float intensity,
	float maxDistance,
	float radius) 

	: m_position(position)
	, m_color(color)
	, m_intensity(intensity)
	, m_maxDistance(maxDistance)
	, m_radius(radius)
{}

void PointLight::at(
	bool realLightBehaviour,
	const Vector3& position,
	Vector3& direction, Vector3& intensity,
	float& distance) const
{
	Vector3 v = m_position - position;
	distance = v.length();
	direction = v / distance;
	
	if (realLightBehaviour) {
		intensity = m_color * m_intensity / pow(distance, 2);
	}
	else
	{
		if (distance >= m_maxDistance) {
			intensity = m_color * 0;
			return;
		}
		intensity = m_color * m_intensity * (pow(m_maxDistance - distance, 2) / pow(m_maxDistance, 2));
	}
}

void PointLight::get_sample_points(
	const Vector3& hitPoint,
	std::vector<Vector3>& samplePoints,
	int sampleAmount) const
{

	// Rotation axis
	Vector3 rotAxis = (hitPoint - m_position).unit_vector(); 
	
	// The vector that we will rotate
	Vector3 rotAxisNormal = Vector3(-rotAxis.z, 0, -rotAxis.x).unit_vector();

	// first sample point is light position
	samplePoints.push_back(m_position);

	// For each degree we take @param sampleAmount sample points and we divided 360 degree to 2 * sampleAmount
	// at total 2 * sampleAmount * sampleAmount + 1 sample points
	for (int i = 1; i <= 2 * sampleAmount; i++)
	{
		for (int j = 1; j <= sampleAmount; j++) {
			samplePoints.push_back(rotAxisNormal * m_radius * j / float(sampleAmount) + m_position);
		}
		rotAxisNormal = Vector3::rotate(rotAxisNormal, rotAxis, PI / float(sampleAmount));
	}
}