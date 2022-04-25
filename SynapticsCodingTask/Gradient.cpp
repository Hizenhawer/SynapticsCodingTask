#include "Gradient.h"

Gradient::Gradient(RGB* rgbs, Dimension dim)
{
	pixels = new uint16_t[dim.height * dim.width];
	uint16_t* columnFirst = generate_gradient(rgbs[0], rgbs[2], dim.height - 2);
	uint16_t* columnLast = generate_gradient(rgbs[1], rgbs[3], dim.height - 2);
	pixels[0] = rgbs[0].getRGB();
	pixels[dim.width - 1] = rgbs[1].getRGB();
	pixels[(dim.width * dim.height) - dim.width] = rgbs[2].getRGB();
	pixels[(dim.width * dim.height) - 1] = rgbs[3].getRGB();
	for (int i = 1; i < dim.height - 1; i++)
	{
		pixels[i * dim.width] = columnFirst[i - 1];
		pixels[(i * dim.width) + (dim.width - 1)] = columnLast[i - 1];
	}
	for (int i = 0; i < dim.height; i++)
	{
		uint16_t* row = generate_gradient(RGB(pixels[i * dim.width]), RGB(pixels[(i * dim.width) + (dim.width - 1)]), dim.width - 2);
		for (int j = 1; j < dim.width - 1; j++)
		{
			pixels[(i * dim.width) + j] = row[j - 1];
		}
	}
}

Gradient::~Gradient() {
	delete pixels;
}

uint16_t* Gradient::generate_gradient(RGB from, RGB to, int inbetween) {
	uint16_t* gradient = new uint16_t[inbetween];
	double rInc = ((double)to.getR() - (double)from.getR()) / ((double)inbetween + 1.0);
	double gInc = ((double)to.getG() - (double)from.getG()) / ((double)inbetween + 1.0);
	double bInc = ((double)to.getB() - (double)from.getB()) / ((double)inbetween + 1.0);
	for (int i = 0; i < inbetween; i++)
	{
		RGB tmp = RGB(from.getR() + (uint16_t)round((i + 1) * rInc),
			from.getG() + (uint16_t)round((i + 1) * gInc),
			from.getB() + (uint16_t)round((i + 1) * bInc));
		gradient[i] = tmp.getRGB();
	}
	return gradient;
}