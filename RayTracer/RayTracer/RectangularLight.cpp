#include "RectangularLight.h"
#define PI 3.14159265

using namespace Core;


RectangularLight::RectangularLight() 
	: m_position(0,0,0)
	, m_direction(0,0,1)
	, m_upVector(0,1,0)
	, m_color(1,1,1)
	, m_width(2)
	, m_height(2)
	, m_minIntensity(0)
	, m_maxIntensity(5)
	, m_innerAngle(PI / 18.0f)
	, m_outerAngle(PI / 4.0f)
	, m_maxDistance(15)
{}


RectangularLight::RectangularLight(
	const Vector3& position,
	const Vector3& direction,
	const Vector3& upVector,
	const Vector3& color,
	float width,
	float height)

	: m_position(position)
	, m_direction(direction.unit_vector())
	, m_upVector(upVector.unit_vector())
	, m_color(color)
	, m_minIntensity(0)
	, m_maxIntensity(2)
	, m_width(width)
	, m_height(height)
	, m_innerAngle(PI / 18.0f)
	, m_outerAngle(PI / 4.0f)
	, m_maxDistance(15)
{}


RectangularLight::RectangularLight(
	const Vector3& position,
	const Vector3& direction,
	const Vector3& upVector,
	const Vector3& color,
	float minIntensity,
	float maxIntensity,
	float width,
	float height,
	float innerAngle,
	float outerAngle,
	float maxDistance) 

	: m_position(position)
	, m_direction(direction.unit_vector())
	, m_upVector(upVector.unit_vector())
	, m_color(color)
	, m_minIntensity(minIntensity)
	, m_maxIntensity(maxIntensity)
	, m_width(width)
	, m_height(height)
	, m_innerAngle(innerAngle)
	, m_outerAngle(outerAngle)
	, m_maxDistance(maxDistance)
{}


void RectangularLight::at(
	bool realLightBehaviour,
	const Vector3& position,
	Vector3& direction,
	Vector3& intensity,
	float& distance) const 
{
	// Rectangular light only works if soft shadows is active. 
	// So we make sure that no illumination will be added.
	distance = std::numeric_limits<float>::infinity();
	direction = Vector3(0,0,0);

	// Unit vector perpendicular to direction and up vector.
	Vector3 leftVector = Vector3::cross(m_upVector, m_direction).unit_vector();

	Vector3 corners[4];
	corners[0] = (position - (m_position + leftVector * m_width / 2.0f + m_upVector * m_height / 2.0f));
	corners[1] = (position - (m_position + leftVector * m_width / 2.0f - m_upVector * m_height / 2.0f));
	corners[2] = (position - (m_position - leftVector * m_width / 2.0f - m_upVector * m_height / 2.0f));
	corners[3] = (position - (m_position - leftVector * m_width / 2.0f + m_upVector * m_height / 2.0f));

	float shortestSqrDistance = corners[0].length_squared();
	int shortestIndice = 0;
	for (int i = 1; i < 4; i++)
	{
		if (corners[i].length_squared() < shortestSqrDistance) {
			shortestSqrDistance = corners[i].length_squared();
			shortestIndice = i;
		}
	}

	// Local coordinate system for determine the point is in range
	Vector3 xAxis, yAxis;
	Vector3 zAxis = m_direction;

	switch (shortestIndice)
	{
	case 0:
		xAxis = leftVector;
		yAxis = m_upVector;
		break;
	case 1:
		xAxis = leftVector;
		yAxis = -m_upVector;
		break;
	case 2:
		xAxis = -leftVector;
		yAxis = -m_upVector;
		break;
	case 3:
		xAxis = -leftVector;
		yAxis = m_upVector;
		break;
	}

	float prj_xAxis = Vector3::dot(xAxis, corners[shortestIndice]);
	float prj_yAxis = Vector3::dot(yAxis, corners[shortestIndice]);
	float prj_zAxis = Vector3::dot(zAxis, corners[shortestIndice]);

	if (prj_zAxis <= 0) {
		// Light is looking at opposite direction
		intensity = Vector3(0, 0, 0);
		return;
	}

	if (prj_xAxis <= 0 && prj_yAxis <= 0)
	{
		// The point is absolutely in the inner area
		if (realLightBehaviour) {
			intensity = m_color * m_maxIntensity / pow(prj_zAxis, 2);
		}
		else {
			intensity = m_color * m_maxIntensity * pow(m_maxDistance - prj_zAxis, 2) / pow(m_maxDistance, 2);
		}

		return;
	}

	// Projection vectors of shortest corner onto the axis
	Vector3 prjV_xAxis = xAxis * prj_xAxis;
	Vector3 prjV_yAxis = yAxis * prj_yAxis;
	Vector3 prjV_zAxis = zAxis * prj_zAxis;

	// Cosine of angles for determine in which area the point is
	float zx_cosAngle = Vector3::dot(zAxis, (prjV_xAxis + prjV_zAxis).unit_vector());
	float zy_cosAngle = Vector3::dot(zAxis, (prjV_yAxis + prjV_zAxis).unit_vector());

	float minIntensity, innerAngle, outerAngle;
	if (realLightBehaviour) {
		minIntensity = 0;
		innerAngle = 0;
		outerAngle = PI / 2.0f;
	}
	else
	{
		minIntensity = m_minIntensity;
		innerAngle = m_innerAngle;
		outerAngle = m_outerAngle;
	}

	// Distance to closest light point
	float dist;
	// lerped intensity according to m_innerAngle and m_outerAngle
	float lerpedIntensity;

	if (prj_xAxis <= 0) {
		dist = sqrt(pow(prj_yAxis, 2) + pow(prj_zAxis, 2));

		if (zy_cosAngle >= cos(innerAngle)) {
			// The point is in the inner area.
			lerpedIntensity = m_maxIntensity;
		}
		else if (zy_cosAngle >= cos(outerAngle)) {
			// The point is in the outer area, lerp the intensity according to the angle
			lerpedIntensity = ((zy_cosAngle - cos(outerAngle)) / (cos(innerAngle) - cos(outerAngle)))
							* (m_maxIntensity - minIntensity) + minIntensity;
		}
		else
		{
			// The point is out of range
			intensity = Vector3(0, 0, 0);
			return;
		}
	}
	else if (prj_yAxis <= 0) {
		// Distance to closest light point
		dist = sqrt(pow(prj_xAxis, 2) + pow(prj_zAxis, 2));

		if (zx_cosAngle > cos(innerAngle)) {
			// The point is in the inner area.
			lerpedIntensity = m_maxIntensity;
		}
		else if (zx_cosAngle > cos(outerAngle)) {
			// The point is in the outer area, lerp the intensity according to the angle
			lerpedIntensity = ((zx_cosAngle - cos(outerAngle)) / (cos(innerAngle) - cos(outerAngle)))
							* (m_maxIntensity - minIntensity) + minIntensity;
		}
		else
		{
			// The point is out of range
			intensity = Vector3(0, 0, 0);
			return;
		}
	}
	else
	{
		// Distance to closest light point
		dist = corners[shortestIndice].length();
		// Angle between light direction and vector(direction from closest light point to hit point)
		float cosAngle = Vector3::dot(corners[shortestIndice].unit_vector(), m_direction);

		if (cosAngle > cos(innerAngle)) {
			// The point is in the inner area
			lerpedIntensity = m_maxIntensity;
		}
		else if (cosAngle < cos(outerAngle))
		{
			// The point is out of range
			intensity = Vector3(0, 0, 0);
			return;
		}
		else
		{
			// The point is in the outer area. lerp the intensity according to the angle
			lerpedIntensity = ((cosAngle - cos(outerAngle)) / (cos(innerAngle) - cos(outerAngle)))
				* (m_maxIntensity - minIntensity) + minIntensity;
		}

	}

	// Determine the intensity by using lerped intensity and closest distance
	if (realLightBehaviour) {
		intensity = m_color * lerpedIntensity / pow(dist, 2);
	}
	else {
		intensity = m_color * lerpedIntensity * pow(m_maxDistance - dist, 2) / pow(m_maxDistance, 2);
	}
}


void RectangularLight::get_sample_points(
	const Vector3& hitPoint,
	std::vector<Vector3>& samplePoints,
	int sampleAmount) const 
{
	// Find perpendiclar vector to light direction and up vector
	Vector3 leftVector = Vector3::cross(m_upVector, m_direction).unit_vector();

	Vector3 shortSideVector;
	Vector3 longSideVector;
	float shortSideLength;
	float longSideLength;

	// Determine short/long side of the rectangle
	if (m_width >= m_height) 
	{
		shortSideVector = m_upVector;
		longSideVector = leftVector;
		shortSideLength = m_height;
		longSideLength = m_width;
	}
	else
	{
		shortSideVector = leftVector;
		longSideVector = m_upVector;
		shortSideLength = m_width;
		longSideLength = m_height;
	}

	// First sample point is light position
	samplePoints.push_back(m_position);

	// Set the starting point to bottom right corner
	Vector3 startingPoint = m_position - leftVector * m_width/2.0f - m_upVector * m_height/2.0f;

	// Divide the rectangle to sub-areas (2*sampleAmount for long side, sampleAmount for short side)
	// and iterate sampling process until reach upper left corner.
	for (int i = 0; i < 2*sampleAmount; i++)
	{
		for (int j = 0; j < sampleAmount; j++)
		{
			samplePoints.push_back(startingPoint + shortSideVector * shortSideLength * j / (sampleAmount - 1)
									+ longSideVector * longSideLength * i / (2 * sampleAmount - 1));				
		}
	}
}