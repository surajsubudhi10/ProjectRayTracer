// This file contains the definition of the class RGBColor

#include <math.h>
#include "Maths.h"
#include "RGBColor.h"

// -------------------------------------------------------- default constructor

RGBColor::RGBColor(void)
	: r(0.0), g(0.0), b(0.0)
{}


// -------------------------------------------------------- constructor

RGBColor::RGBColor(float c)
	: r(c), g(c), b(c)
{}


// -------------------------------------------------------- constructor

RGBColor::RGBColor(float _r, float _g, float _b)
	: r(_r), g(_g), b(_b)
{}


// -------------------------------------------------------- copy constructor

RGBColor::RGBColor(const RGBColor& c)
	: r(c.r), g(c.g), b(c.b)
{}


// -------------------------------------------------------- destructor

RGBColor::~RGBColor(void)
{}


// --------------------------------------------------------assignment operator

RGBColor& RGBColor::operator= (const RGBColor& rhs) 
{
	if (this == &rhs)
		return (*this);

	r = rhs.r;
	g = rhs.g;
	b = rhs.b;

	return (*this);
}


// -------------------------------------------------------- powc
// raise each component to the specified power
// used for color filtering in Chapter 28

RGBColor RGBColor::powc(float p) const 
{
	return (RGBColor(pow(r, p), pow(g, p), pow(b, p)));
}


RGBColor RGBColor::clamp_color(const RGBColor& raw_color)
{
	RGBColor c(raw_color);
	if (raw_color.r > 1.0 || raw_color.g > 1.0 || raw_color.b > 1.0)
	{
		c.r = 1.0;
		c.g = 0.0;
		c.b = 0.0;
	}
	return (c);
}

RGBColor RGBColor::max_to_one(const RGBColor& c)
{
	float max_value = max(c.r, max(c.g, c.b));

	if (max_value > 1.0)
		return (c / max_value);
	else
		return (c);
}