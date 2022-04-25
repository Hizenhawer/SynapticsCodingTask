#include"RGB.h"

RGB::RGB(uint16_t color)
{
	r = (color & 0xF800) >> 11;
	g = (color & 0x07E0) >> 5;
	b = color & 0x001F;
	rgb = color;
}

RGB::RGB(uint16_t r, uint16_t g, uint16_t b) {
	this->r = r;
	this->g = g;
	this->b = b;
	rgb = (r << 11) | (g << 5) | b;
}

std::string RGB::to_string() {
	std::string str = "R: ";
	str += std::to_string((int)r);
	str += " G: ";
	str += std::to_string((int)g);
	str += " B: ";
	str += std::to_string((int)b);
	return str;
}