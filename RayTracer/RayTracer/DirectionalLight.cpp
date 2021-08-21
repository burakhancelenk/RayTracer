#include "DirectionalLight.h"
#include <limits>

#define PI 3.14159265

using namespace Core;

DirectionalLight::DirectionalLight()
	: m_direction(1, -0.5, 1)
	, m_color(1,1,1)
	, m_intensity(1)
	, m_ssAngle(PI/18.0f)
{}

DirectionalLight::DirectionalLight(
	const Vector3& direction,
	const Vector3& color,
	float intensity,
	float ssAngle)

	: m_direction(direction)
	, m_color(color)
	, m_intensity(intensity)
	, m_ssAngle(ssAngle)
{}

void DirectionalLight::at(
	bool realLightBehaviour,
	const Vector3& position,
	Vector3& direction,
	Vector3& intensity,
	float& distance) const
{
	distance = std::numeric_limits<float>::infinity();
	direction = m_direction;
	intensity = m_color * m_intensity;
}

void DirectionalLight::get_sample_points(
	const Vector3& hitPoint,
	std::vector<Vector3>& samplePoints,
	int sampleAmount) const
{
	// We will calculate sample points from a reference disk with distance between
	// hit point and center of the disk equals to 1 and normal vector oriented to the hit point.

	// Rotation axis
	Vector3 rotAxis = m_direction;

	// The vector that we will rotate
	Vector3 rotAxisNormal = Vector3(-rotAxis.z, 0, -rotAxis.x).unit_vector();

	Vector3 refDiskPos = hitPoint - m_direction;
	float refDiskRadius = tan(m_ssAngle);

	// first sample point is the reference disk position
	samplePoints.push_back(refDiskPos);

	// For each degree we take @param sampleAmount sample points and we divided 360 degree to 2 * sampleAmount
	// at total 2 * sampleAmount * sampleAmount + 1 sample points
	for (int i = 1; i <= 2 * sampleAmount; i++)
	{
		for (int j = 1; j <= sampleAmount; j++) {
			samplePoints.push_back(rotAxisNormal * refDiskRadius * j / float(sampleAmount) + refDiskPos);
		}
		rotAxisNormal = Vector3::rotate(rotAxisNormal, rotAxis, PI / float(sampleAmount));
	}
}