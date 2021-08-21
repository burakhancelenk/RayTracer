#ifndef IMAGE_H
#define IMAGE_H

#include <string>
#include <vector>
#include "Vector3.h"
#include <iostream>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <cassert>

namespace Utility {

	// Represents a 2D image as [width x height]
	class Image 
	{
		private:
			int m_width, m_height;
			std::vector<Vector3> m_pixels;

		public:
			// Default constructor
			Image();

			// @param width, number of pixels at horizontal axis
			// @param height, number of pixels at vertical axis
			Image(const int& width, const int& height);

			// Returns width
			int get_width() { return m_width; }

			// Returns height
			int get_height() { return m_height; }

			// Writes pixel values to a ppm(file format) file
			bool write(const std::string& filename) const;

			// Adds @param color to the pixel coordinates(@param x, @param y) in m_pixels
			void set_pixel(int x, int y, const Vector3& color);

			// Returns all pixel values
			const std::vector<Vector3>& get_pixels() const { return m_pixels; };

			// Debug
			friend std::ostream& operator<<(std::ostream& os, const Image& image) {
				os << "Image(" 
					<< "width : " << image.m_width << " , " 
					<< "height : " << image.m_height 
					<< ")" << std::endl;
				return os;
			}
	};

}

#endif

