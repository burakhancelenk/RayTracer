#ifndef VECTOR4_H
#define VECTOR4_H

#include <iostream>

namespace Utility {

	// Represents anything with 4 components (ex. RGBA color)
	class Vector4
	{
		public:
			// 4 components
			float x, y, z, w;

			// Default constructor
			Vector4();

			// @param _x,_y,_z,_w represent anything which have 4 component
			Vector4(float _x, float _y, float _z, float _w);

			// OPERATOR OVERLOADINGS
			Vector4 operator+(const Vector4& vector) const;

			Vector4 operator+(float value) const;

			Vector4 operator-(const Vector4& vector) const;

			Vector4 operator-(float value) const;

			Vector4 operator*(const Vector4& vector) const;

			Vector4 operator*(float value) const;

			Vector4 operator/(const Vector4& vector) const;

			Vector4 operator/(float value) const;
	
			Vector4 operator- () const;

			bool operator ==(const Vector4& vector) const;
			// END OPERATOR OVERLOADINGS

			// Dot product
			static float dot(const Vector4& u, const Vector4& v);

			// Debug
			friend std::ostream& operator<<(std::ostream& os, const Vector4& vector)
			{
				os << "Vector4(" 
					<< "x : " << vector.x << " , " 
					<< "y : " << vector.y << " , "
					<< "z : " << vector.z << " , " 
					<< "w : " << vector.w << ")";
				return os;
			}

	};
}

#endif // !VECTOR4_H
