#ifndef SCENE_H
#define SCENE_H

#include "Object.h"
#include "Light.h"
#include "Camera.h"
#include "RenderSettings.h"
#include "Hit.h"
#include <vector>


namespace Core {

	/*
	* A scene contains a camera, some geometry to render and light sources.
	* It also includes a render settings struct to easily tune some options.
	* NB: In a truly physical scene, there is no distinction between a light
	* source and an element of geometry, but being that general requires to
	* cast too many secondary rays.
	*/
	class Scene 
	{
		private:
			/*
			* We use (shared) pointers be able to mix instances of different
			* types into the same vector, provided they all derive from the same base
			* (namely Object and Light). ObjectPtr is an alias for std::shared_ptr<Object>
			*/
			std::vector<ObjectPtr> m_objects;
			std::vector<LightPtr> m_lights;
			Camera m_camera;
			RenderSettings m_renderSettings;

		public:
			// There cannot be a scene without a camera, so to ensure this
			// we require one in the constructor.
			Scene(const Camera& camera);

			// Adds an object to the scene
			void add(const ObjectPtr& obj);

			// Adds a light to the scene
			void add(const LightPtr& light);

			// Returns the list of objects as a readonly (const) reference
			const std::vector<ObjectPtr>& get_objects() const { return m_objects; }

			// Returns the list of lights as a readonly (const) reference
			const std::vector<LightPtr>& get_lights() const { return m_lights; }

			// Returns the camera added to the scene
			const Camera& get_camera() const { return m_camera; }

			/*
			* Common pattern: we return a reference in both cases, but when
			* the Scene object is read only (const) then the RenderSettings
			* reference is read only too, and otherwise it is writable.
			*/
			const RenderSettings& get_render_settings() const { return m_renderSettings; }
			RenderSettings& get_render_settings() { return m_renderSettings; }

			/*
			* Equivalent of Object::intersect but applied to all objects of the scene
			* Find the closest hit to the camera.
			*/
			Hit intersect(const Ray& ray) const;

			// Debug
			friend std::ostream& operator<<(std::ostream& os, const Scene& scene) {
				const std::vector<ObjectPtr>& objects = scene.get_objects();
				const std::vector<LightPtr>& lights = scene.get_lights();
				os << "Scene(Total Objects:" << objects.size() 
					<< " , Total Lights:" << lights.size() << ")\n{";
				
				for(ObjectPtr obj : objects)
				{
					os <<"\t" << obj << "\n";
				}
				
				for (LightPtr light : lights)
				{
					os << "\t" << light << "\n";
				}
				os << "}";
				return os;
			}
	};

}

#endif // !SCENE_H

