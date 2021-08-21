#ifndef RENDER_H
#define RENDER_H

#include <string>
#include "Image.h"
#include "Scene.h"

namespace Core {

	// Holds all the necessary informations and functions for rendering 
	class Render 
	{
		private:
			Image m_render; // Save image after rendering process
			std::string m_filename; // Full path of the file
	
		public:
			// Default constructor
			Render();

			// @param filename, path and name of the output ppm file
			Render(const std::string& filename);

			// Assigns @param filename to m_filename
			void set_filename(const std::string filename);

			// Writes again the latest render to ppm file with same filename
			void write_last_render();

			// Draw a simple gradient to check that the Image file works as expected
			void gradient();

			/**
			* Core rendering function (Draw only silhouettes)
			* @param scene Scene to render
			* @return Image whose size match camera's width and height with the final render
			*/
			void render_first_image(const Scene& scene);

			/**
			* Core rendering function (Draw fully shaded scene)
			* @param scene Scene to render
			* @return Image whose size match camera's width and height with the final render
			*/
			void render(const Scene& scene);

			/**
			 * Advanced variant of render(), including anti-aliasing.
			*/
			void render_antialiased(const Scene& scene);

			/**
			* Core rendering function restricted to a single ray.
			* We need to pull this out of the main render function to enable recursive calls
			* @param scene Scene to render
			* @param scene Ray ray to cast onto the scene
			* @param depth Number of recursive calls that led to this one
			* @return The light coming from the opposite ray direction
			*/
			Vector3 render_ray(const Scene& scene, const Ray& ray, int depth = 0);
	};

}

#endif // !RENDER_H