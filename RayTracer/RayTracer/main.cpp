#include <iostream>
#include "Render.h"
#include "Union.h"
#include "Sphere.h"
#include "Disk.h"
#include "Intersection.h"
#include "Plane.h"
#include "PointLight.h"
#include "DirectionalLight.h"
#include "SpotLight.h"
#include "AmbientLight.h"

#include <string>


using namespace Core;
using namespace Primitive;
// Main
int main()
{
	bool firstImage = false;
	std::string output = "C:/tmp/render.ppm";
	
	// Define the example scene
	Camera camera(640, 360, 50, Vector3(3, 0, 0.5f), Vector3(0, 0, 0), Vector3(0, 0, 1));
	Scene scene(camera);
	MaterialParameters whiteClayParam = {
		{1, 1, 1},          // kd
		{0.5f, 0.5f, 0.5f}, // ks
		{0.15f, 0.15f, 0.15f}, // ka 
		0.0f,               // kr
		2.0f,                // ns
	};
	Material whiteClay(whiteClayParam);
	MaterialParameters redPlasticParam = {
		{1, 0, 0},
		{1, 1, 1},
		{0.2f, 0.2f, 0.2f},
		0.0f,
		8.0f,
	};
	Material redPlastic(redPlasticParam);
	MaterialParameters grayMarbleParam = {
		{0.1f, 0.1f, 0.1f},
		{1, 1, 1},
		{0.2f, 0.2f, 0.2f},
		0.1f,
		36.0f,
	};
	Material grayMarble(grayMarbleParam);
	MaterialParameters orangeMetalParam = {
		{1.0f, 0.6f, 0.0f},
		{1.0f, 0.8f, 0.5f},
		{0.1f, 0.06f, 0.0f},
		0.4f,
		16.0f,
	};
	Material orangeMetal(orangeMetalParam);

	// We use (shared) pointers in order to be able to mix instances of different
	// types into the same vector.
	
	
	auto geometry = std::make_shared<Union>(std::vector<ObjectPtr>{
		std::make_shared<Disk>(Vector3(0, 0, 0), Vector3(0, 0, 1), 1.5 , whiteClay),
			std::make_shared<Sphere>(Vector3(0, -1, 0.2f), 0.2f, redPlastic),
			std::make_shared<Sphere>(Vector3(0, 0.0f, 0.2f), 0.2f, orangeMetal),
			std::make_shared<Sphere>(Vector3(0, 1, 0.2f), 0.2f, grayMarble),
	});

	scene.add(geometry);

	scene.add(std::make_shared<PointLight>(Vector3(2, 2, 4), Vector3(1, 1, 1), 10));
	//scene.add(std::make_shared<PointLight>(Vector3(5, -2, 2), Vector3(0.9f, 0.95f, 1.0f), 10));
	scene.add(std::make_shared<DirectionalLight>(Vector3(-2, 1, -1).unit_vector(), Vector3(1.0f, 0.95f, 0.9f), 0.5f));
	scene.add(std::make_shared<SpotLight>(Vector3(0, 0, 3), Vector3(0, 0, -1), Vector3(1, 1, 1)));

	scene.get_render_settings().backgroundColor = Vector3(0.2f, 0.2f, 0.2f);

	Render renderer(output);
	if (firstImage) {
		renderer.render_first_image(scene);
	}
	else if (scene.get_render_settings().antialiasing <= 1)
	{
		renderer.render(scene);
	}
	else
	{
		renderer.render_antialiased(scene);
	}

	return EXIT_SUCCESS;
}