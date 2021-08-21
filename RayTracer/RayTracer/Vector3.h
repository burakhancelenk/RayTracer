#ifndef VECTOR3_H
#define VECTOR3_H

#include <iostream>

namespace Utility {

	// Represents anything with 3 components (ex. coord in 3D space or RGB color)
	class Vector3
	{
		public:
			// 3 components
			float x, y, z;

			// Default constructor
			Vector3();

			// @param _x,_y,_z represent anything which have 3 component (ex. coordinates or rgb color)
			Vector3(float _x, float _y, float _z);

			// OPERATOR OVERLOADINGS
			Vector3 operator+(const Vector3& vector) const;

			Vector3 operator+(float value) const;

			Vector3 operator-(const Vector3& vector) const;

			Vector3 operator-(float value) const;

			Vector3 operator*(const Vector3& vector) const;

			Vector3 operator*(float value) const;

			Vector3 operator/(const Vector3& vector) const;

			Vector3 operator/(float value) const;

			Vector3 operator-() const;

			bool operator ==(const Vector3& vector) const;
			// END OPERATOR OVERLOADINGS

			// Returns reflected vector according to @param vector
			Vector3 reflect(const Vector3& vector) const;

			// Dot product
			static float dot(const Vector3& u, const Vector3& v);

			// Cross product
			static Vector3 cross(const Vector3& u, const Vector3& v);

			// Rotates @param vector @param angle radians around @param axis counter clockwise.
			// To rotate @param vector in clockwise direction, set the angle negative.
			static Vector3 rotate(const Vector3& vector, const Vector3& axis, float angle);

			// Vector length
			float length() const;

			// Squared version of the function above
			float length_squared() const;

			// Returns unit vector of the instance
			Vector3 unit_vector() const;

			// Debug
			friend std::ostream& operator<<(std::ostream& os, const Vector3& vector) {
				os << "Vector3(" 
					<< "x : " << vector.x << " , " 
					<< "y : " << vector.y << " , " 
					<< "z : " << vector.z 
					<< ")" << std::endl;
				return os;
			}
	};

}

#endif // !VECTOR3_H