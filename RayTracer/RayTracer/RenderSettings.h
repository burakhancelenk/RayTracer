#ifndef RENDERSETTINGS_H
#define RENDERSETTINGS_H

#include "Vector3.h"

using namespace Utility;


namespace Core {

	// Holds some important options for rendering
	struct RenderSettings
	{
		// Maximum number of recursive rays when materials are reflexive
		// (minimum is 0)
		int maxDepth = 3;

		// Color of the background, used when nothing is hit
		Vector3 backgroundColor = Vector3(1, 1, 1);

		// Foreground color used in the render_first_image
		Vector3 hitColor = Vector3(1, 0, 0);

		// If it's actived, all the lights using min/max intensity or max distance will calculate light intensity
		// according to this formula : 
		// intensity = max intensity * 1 / squared distance.
		// Otherwise, it will interpolate the intensity between min/max intensity according to this formula : 
		// intensity = min intensity + (max intensity - min intensity) * squared(max distance - distance) / squared(max distance)
		bool realLightBehaviour = true;

		// Whether a shadow ray is casted to check whether the light source is visible
		// from the shaded point.
		bool useShadows = true;

		// Works if and only if useShadows is true. set to true for cast soft shadows, false
		// for cast hard shadows. Casting soft shadows have an important impact on the rendering time.
		bool useSoftShadows = true;

		// Sample amount taken from the light source for soft shadows. We divide sample area
		// to 2 * sampleAmount sub areas and take sampleAmount samples from each sub area.
		// total number of samples = 2 * sampleAmount * sampleAmount + 1(one from the center of the sample area)
		// Make sense if and only if useSoftShadows is true.
		int sampleAmount = 5;

		// Square root of the number of camera rays per pixel
		// (minimum is 1, more improves antialiasing)
		int antialiasing = 3;

		// Advanced settings that you'll likely not change

		// Slight offset added to the location of a hit point before casting
		// a secondary ray, to prevent the new ray to hit again the same location.
		float eps = 1e-3f;
	};

}

#endif // !RENDERSETTINGS_H



