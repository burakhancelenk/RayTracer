#include "Image.h"

using namespace Utility;

Image::Image()
	: m_width(1024)
	, m_height(768)
{
	m_pixels.resize(1024*768);
}

Image::Image(const int& imageWidth, const int& imageHeight)
	: m_width(imageWidth)
	, m_height(imageHeight) 
{
	m_pixels.resize(m_width * m_height);
}

void Image::set_pixel(int x, int y, const Vector3& color) 
{
	m_pixels[y * m_width + x] = color; 
}

static char convert_color_to_8bit(float color) {
	// float [0,1] -> byte [0,255]
	return (char)std::min(std::max(0.0f, color * 255), 255.0f);
}

bool Image::write(const std::string& filename) const {

	// Terminate the program if the size is different from width*height
	assert(m_pixels.size() == m_width * m_height);

	// Write to a file in ppm format
	std::ofstream file;
	file.open(filename, std::ios::binary);
	if (!file.is_open()) {
		std::cerr << "Could not open file '" << filename << "' for writing";
		return false;
	}
	file << "P6 " << m_width << " " << m_height << " 255\n";
	char pixel8bit[3];
	for (int j = 0; j < m_height; ++j) {
		for (int i = 0; i < m_width; ++i) {
			const Vector3& pixel = m_pixels[i + j * m_width];
			pixel8bit[0] = convert_color_to_8bit(pixel.x);
			pixel8bit[1] = convert_color_to_8bit(pixel.y);
			pixel8bit[2] = convert_color_to_8bit(pixel.z);
			file.write(pixel8bit, sizeof(pixel8bit));
		}
	}
	file.close();

	// File has been written successfully 
	return true;
}