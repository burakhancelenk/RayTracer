#include "IsometricCamera.h"

using namespace Core;

IsometricCamera::IsometricCamera() 
	: m_width(500)
	, m_height(282)
	, m_position(0,0,0)
	, m_target(1,0,0)
	, m_up(0,0,1)
{}

IsometricCamera::IsometricCamera(
	float screenWidth,
	int width,
	int height,
	const Vector3& position,
	const Vector3& target,
	const Vector3& up)

	: m_screenWidth(screenWidth)
	, m_width(width)
	, m_height(height)
	, m_position(position)
	, m_target(target)
	, m_up(up)
{}

Ray IsometricCamera::pixel_to_ray(int pixelX, int pixelY) const
{
	return pixel_to_ray(
		static_cast<float>(pixelX) + 0.5f,
		static_cast<float>(pixelY) + 0.5f
	);
}

Ray IsometricCamera::pixel_to_ray(float pixelX, float pixelY) const
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
	Vector3 direction = -z_cam;
	Vector3 position = m_position + x_cam * m_screenWidth * u / 2.0f + y_cam * ratio * m_screenWidth * v / 2.0f;

	return Ray(position, direction);
}