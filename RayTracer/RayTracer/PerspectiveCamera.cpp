#include "PerspectiveCamera.h"

using namespace Core;

PerspectiveCamera::PerspectiveCamera()
	: m_width(500)
	, m_height(282)
	, m_focalLength(50)
	, m_position(0,0,0)
	, m_target(1,0,0)
	, m_up(0,0,1)
{}

PerspectiveCamera::PerspectiveCamera(
	int width,
	int height,
	float focalLength,
	const Vector3& position,
	const Vector3& target,
	const Vector3& up)

	: m_width(width)
	, m_height(height)
	, m_focalLength(focalLength)
	, m_position(position)
	, m_target(target)
	, m_up(up)
{}

Ray PerspectiveCamera::pixel_to_ray(int pixelX, int pixelY) const
{
	return pixel_to_ray(
		static_cast<float>(pixelX) + 0.5f,
		static_cast<float>(pixelY) + 0.5f
	);
}

Ray PerspectiveCamera::pixel_to_ray(float pixelX, float pixelY) const
{
	// Find the screen coordinates( in range (-1, 1)) of specified pixel
	float u = pixelX / static_cast<float>(m_width) * 2 - 1;
	float v = pixelY / static_cast<float>(m_height) * 2 - 1;

	// Flip vertically
	v = -v;
	Vector3 z_cam = (m_position - m_target).unit_vector();
	Vector3 up = m_up;

	if (Vector3::dot(up, z_cam) > .99f) {
		// Edge case, when camera is looking straight up or down
		up = Vector3(0, 1, 0);
	}
	// Find the local x,y axis of camera
	Vector3 x_cam = Vector3::cross(up, z_cam).unit_vector();
	Vector3 y_cam = Vector3::cross(z_cam, x_cam).unit_vector();
	// Screen ratio
	float ratio = m_height / (float)m_width;

	// Prepare the ray informations
	Vector3 direction = x_cam * u * m_sensorWidth + y_cam * v
		* m_sensorWidth * ratio - z_cam * m_focalLength;
	// m_position is also ray position, no need to create a variable

	return Ray(m_position, direction.unit_vector());
}
