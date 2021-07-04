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
		int maxDepth = 2;

		// Color of the background, used when nothing is hit
		Vector3 backgroundColor;

		// Foreground color used in the render_first_image
		Vector3 hitColor = Vector3(1, 0, 0);

		// Whether a shadow ray is casted to check whether the light source is visible
		// from the shaded point.
		bool useShadows = true;

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



