#pragma once
#include <string>

class RGB
{
public:
	RGB(uint16_t);
	RGB(uint16_t, uint16_t, uint16_t);
	std::string to_string();
	uint16_t getR() { return r; }
	uint16_t getG() { return g; }
	uint16_t getB() { return b; }
	uint16_t getRGB() { return rgb; }

private:
	uint16_t rgb;
	uint16_t r;
	uint16_t g;
	uint16_t b;
};