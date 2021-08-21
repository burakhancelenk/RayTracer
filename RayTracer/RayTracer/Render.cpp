#include "Render.h"
#include "Material.h"
#include "Hit.h"
#include "PointLight.h"
#include "SpotLight.h"
#include "DirectionalLight.h"
#include "AmbientLight.h"
#include "Sphere.h"
#include "Plane.h"
#include "Union.h"
#include "Intersection.h"
#include <string>


using namespace Primitive;
using namespace Core;

Render::Render()
	: m_filename("C:/Untitled.ppm")
	, m_render()
{}

Render::Render(const std::string& filename) 
	: m_filename(filename)
	, m_render()
{}

void Render::set_filename(const std::string filename) 
{
	m_filename = filename;
}

void Render::write_last_render()
{
	m_render.write(m_filename);
}

void Render::gradient()
{
	Image img(256, 128);
	// The output gradient goes from blue to yellow:
	Vector3 blue(0, 0, 1);
	Vector3 yellow(1, 1, 0);

	// Iterate over all rows, and for each row over all columns
	for (int j = 0; j < img.get_height(); ++j) {
		for (int i = 0; i < img.get_width(); ++i) {
			// 't' is the interpolation factor between blue and yellow
			float t = i / (float)(img.get_width() - 1);

			// a * (1 - t) + b * t is a standard linear interpolation.
			// This operation is sometimes called 'mix' or 'lerp'
			img.set_pixel(i, j, blue * (1 - t) + yellow * t);
		}
	}

	m_render = img;
	img.write(m_filename);
}

void Render::render_first_image(const Scene& scene)
{
	// A const reference is basically a read only alias to avoid
	// writing "scene.get_camera()" many times without introducing neither overhead
	// nor useless memory copying.
	const CameraPtr& camera = scene.get_camera();
	const RenderSettings& settings = scene.get_render_settings();

	Image img(camera->get_width(), camera->get_height());

	// Define ray and color here ahead of the loop to avoid freeing and
	// reallocating it many times (even though in this case the compiler
	// would most likely detect that and optimize).
	Ray ray;
	Vector3 color;

	// Like for the gradient, iterate through all pixels
	for (int j = 0; j < img.get_height(); ++j) {
		for (int i = 0; i < img.get_width(); ++i) {
			// Each pixel correspond to a different ray to cast
			ray = camera->pixel_to_ray(i, j);

			color = settings.backgroundColor;
			// Test each object
			for (const ObjectPtr& obj : scene.get_objects()) {
				// The intersect() method
				if (obj->intersect_first_image(ray)) {
					color = settings.hitColor;
					break;
				}
			}

			// Fill the image's pixel with the predefined color
			img.set_pixel(i, j, color);
		}
	}

	m_render = img;
	img.write(m_filename);
}

void Render::render(const Scene& scene)
{
	const CameraPtr& camera = scene.get_camera();

	Image img(camera->get_width(), camera->get_height());

	Ray ray;

	for (int j = 0; j < img.get_height(); ++j) {
		for (int i = 0; i < img.get_width(); ++i) {
			ray = camera->pixel_to_ray(i, j);
			img.set_pixel(i, j, render_ray(scene, ray));
		}
	}
	m_render = img;
	img.write(m_filename);
}

void Render::render_antialiased(const Scene& scene)
{
	const CameraPtr& camera = scene.get_camera();
	const RenderSettings& settings = scene.get_render_settings();

	Image img(camera->get_width(), camera->get_height());

	Vector3 color;
	Ray ray;
	float scale = 1 / static_cast<float>(settings.antialiasing * settings.antialiasing);

	for (int j = 0; j < img.get_height(); ++j) {
		for (int i = 0; i < img.get_width(); ++i) {
			color = Vector3(0, 0, 0);
			for (int ii = 0; ii < settings.antialiasing; ++ii)
			{
				float x = static_cast<float>(i) + (static_cast<float>(ii) + 0.5f) / settings.antialiasing;
				for (int jj = 0; jj < settings.antialiasing; ++jj)
				{
					float y = static_cast<float>(j) + (static_cast<float>(jj) + 0.5f) / settings.antialiasing;

					ray = camera->pixel_to_ray(x, y);
					color = color + render_ray(scene, ray);
				}
			}
			img.set_pixel(i, j, color * scale);
		}
	}

	m_render = img;
	img.write(m_filename);
}

Vector3 Render::render_ray(const Scene& scene, const Ray& ray, int depth)
{
	const RenderSettings& settings = scene.get_render_settings();

	Hit hit = scene.intersect(ray);

	if (!hit.isValid) return settings.backgroundColor;

	// Compute pixel color
	Vector3 color = Vector3(0, 0, 0);
	for (const LightPtr& light : scene.get_lights())
	{
		// Query light source (returns lightDirection and
		// incomingLightPower given the hit point)
		Vector3 lightDirection, incomingLightPower;
		float lightDistance;
		light->at(settings.realLightBehaviour, hit.point, lightDirection, incomingLightPower, lightDistance);
		
		// Ambient light contribution
		if (typeid(*light) == typeid(AmbientLight)) 
		{
			color = color + incomingLightPower*hit.material.get_params().get_ka();
			continue;
		}

		// Shadows
		if (settings.useShadows)
		{
			if (settings.useSoftShadows) 
			{
				// Initialize sample points
				std::vector<Vector3> samplePoints;
				samplePoints.reserve(2 * settings.sampleAmount * settings.sampleAmount + 1);
				light->get_sample_points(hit.point, samplePoints, settings.sampleAmount);
				
				Vector3 totalLightContribution = Vector3(0, 0, 0);

				for (Vector3 point : samplePoints)
				{
					// First of all, we will check whether the sample point is visible or not
					// We offset a bit the ray origin to avoid intersecting the very same point again
					Vector3 direction = (point - hit.point).unit_vector();
					Ray shadowRay(hit.point + direction * settings.eps, direction);
					Hit shadowHit = scene.intersect(shadowRay);

					if (shadowHit.isValid && (typeid(*light) == typeid(DirectionalLight)
						|| shadowHit.distance + settings.eps < (point - hit.point).length()))
					{
						// sample point is not visible, we skip its contribution
						continue;
						
					}

					// Lighting model, gives the proportion of incoming light
					// that gets reflected towards the camera
					Vector3 reflected = hit.material.get_params().reflected_proportion(
						direction,
						-ray.direction,
						hit.normal
					);

					// Accumulate sample points' contribution
					totalLightContribution = totalLightContribution + reflected * incomingLightPower;
					
				}

				// Take the avarage value of sample points contribution and add to the final color
				color = color + totalLightContribution / float(2 * settings.sampleAmount * settings.sampleAmount + 1);
			}
			else
			{
				// First of all, we will check whether the light source is visible or not
				// We offset a bit the ray origin to avoid intersecting the very same point again
				Ray shadowRay(hit.point + lightDirection * settings.eps, lightDirection);
				Hit shadowHit = scene.intersect(shadowRay);
				if (shadowHit.isValid && shadowHit.distance + settings.eps < lightDistance)
				{
					// Light is not visible, we skip its contribution
					continue;
				}

				// Lighting model, gives the proportion of incoming light
				// that gets reflected towards the camera
				Vector3 reflected = hit.material.get_params().reflected_proportion(
					lightDirection,
					-ray.direction,
					hit.normal
				);

				// Accumulate light
				color = color + reflected * incomingLightPower;
			}
		}

	}

	// Launch a secondary ray. The hit point acts like an extra light source
	float reflectionCoefficient = hit.material.get_params().get_kr();
	if (depth < settings.maxDepth && reflectionCoefficient > 0)
	{
		Vector3 newDirection = hit.normal.reflect(-ray.direction);
		// We offset a bit the ray origin to avoid intersecting the very same point again
		Ray secondaryRay(hit.point + newDirection * settings.eps, newDirection);

		Vector3 incoming = render_ray(scene, secondaryRay, depth + 1);
		// (ideally 'incoming' should be decayed by the distance from secondary
		// hit point to current hit point)

		// Same as for light sources:
		Vector3 reflected = hit.material.get_params().reflected_proportion(
			newDirection,
			-ray.direction,
			hit.normal
		);
		color = color * (1 - reflectionCoefficient) + reflected *  incoming * reflectionCoefficient;
	}

	return color;
}
