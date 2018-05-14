#pragma once


class Point2D {
public:

	float	x, y;

public:

	Point2D();												// default constructor
	explicit Point2D(float arg);							// constructor
	Point2D(float x1, float y1);							// constructor
	Point2D(const Point2D& p); 								// copy constructor
	~Point2D() = default;                                  // destructor

	Point2D& operator= (const Point2D& rhs); 				// assignment operator
	Point2D operator* (float a);						// multiplication on right by scalar
};

// scales the point by the float a
inline Point2D Point2D::operator* (const float a) {
	return (Point2D(a * x, a * y));
}