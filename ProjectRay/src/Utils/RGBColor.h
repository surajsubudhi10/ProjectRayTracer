#pragma once


// This file contains the declaration of the class RGBColor

//------------------------------------------------------------ class RGBColor

class RGBColor {

public:

	float	r, g, b;

public:

	RGBColor(void);										// default constructor
	RGBColor(float c);									// constructor
	RGBColor(float _r, float _g, float _b);				// constructor
	RGBColor(const RGBColor& c); 						// copy constructor

	~RGBColor(void);									// destructor

	RGBColor& operator= (const RGBColor& rhs);			// assignment operator
	RGBColor operator+ (const RGBColor& c) const;		// addition
	RGBColor& operator+= (const RGBColor& c);			// compound addition
	RGBColor operator* (const float a) const;			// multiplication by a float on the right
	RGBColor& operator*= (const float a);				// compound multiplication by a float on the right
	RGBColor operator/ (const float a) const;			// division by a float
	RGBColor& operator/= (const float a);				// compound division by a float
	bool operator== (const RGBColor& c) const;			// are two RGBColours the same?
		
	RGBColor operator* (const RGBColor& c) const;		// component-wise multiplication
	RGBColor powc(float p) const;						// raise components to a power
	float average(void) const;							// the average of the components

	static RGBColor clamp_color(const RGBColor& raw_color);
	static RGBColor max_to_one(const RGBColor& c);

};



// inlined member functions

// ----------------------------------------------------------------------- operator+
// addition of two colors

inline RGBColor RGBColor::operator+ (const RGBColor& c) const 
{
	return (RGBColor(r + c.r, g + c.g, b + c.b));
}


// ----------------------------------------------------------------------- operator+=
// compound addition of two colors

inline RGBColor& RGBColor::operator+= (const RGBColor& c) 
{
	r += c.r; g += c.g; b += c.b;
	return (*this);
}


// ----------------------------------------------------------------------- operator*
// multiplication by a float on the right

inline RGBColor RGBColor::operator* (const float a) const 
{
	return (RGBColor(r * a, g * a, b * a));
}


// ----------------------------------------------------------------------- operator*=
// compound multiplication by a float on the right

inline RGBColor& RGBColor::operator*= (const float a) 
{
	r *= a; g *= a; b *= a;
	return (*this);
}


// ----------------------------------------------------------------------- operator/
// division by float

inline RGBColor RGBColor::operator/ (const float a) const 
{
	return (RGBColor(r / a, g / a, b / a));
}


// ----------------------------------------------------------------------- operator/=
// compound division by float

inline RGBColor& RGBColor::operator/= (const float a) 
{
	r /= a; g /= a; b /= a;
	return (*this);
}



// ----------------------------------------------------------------------- operator*
// component-wise multiplication of two colors

inline RGBColor RGBColor::operator* (const RGBColor& c) const 
{
	return (RGBColor(r * c.r, g * c.g, b * c.b));
}


// ----------------------------------------------------------------------- operator==
// are two RGBColors the same?

inline bool RGBColor::operator== (const RGBColor& c) const 
{
	return (r == c.r && g == c.g && b == c.b);
}


// ----------------------------------------------------------------------- average
// the average of the three components

inline float RGBColor::average(void) const 
{
	return (0.333333333333 * (r + g + b));
}




// inlined non-member function

// ----------------------------------------------------------------------- operator*
// multiplication by a float on the left

RGBColor operator* (const float a, const RGBColor& c);

inline RGBColor operator* (const float a, const RGBColor& c) 
{
	return (RGBColor(a * c.r, a * c.g, a * c.b));
}



