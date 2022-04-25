#pragma once
#include"RGB.h"
#include"Display.h"

class Gradient
{
public:
	Gradient(RGB*, Dimension);
	~Gradient();
	uint16_t* getPixels() { return pixels; }

private:
	uint16_t* pixels;
	static uint16_t* generate_gradient(RGB, RGB, int);
};