#ifndef HIT_H
#define HIT_H

#include "Vector3.h"
#include "Material.h"

using namespace Core;


namespace Utility {

	/*
	* Holds the information about a hit between a ray and an object.
	* This can also contain a "non hit". The default constructor creates an
	* instance meaning "there was no hit", which can be tested using isValid.
	*/
	struct Hit
	{
		public:
			bool isValid = false; // True if there is a hit between ray and object.

			// The following members make sense only when the hit is valid:
			Vector3 point; // Hit point
			Vector3 normal; // Normal vector of the hit surface. Always unitary
			Material material; // Material of the related object 
			float distance; // Used to sort multiple hit points

	};

}

#endif // !HIT_H


