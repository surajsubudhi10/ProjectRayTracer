#pragma once


#include "Matrix.h"

class Normal;
class Point3D;

//----------------------------------------- class Vector3D

class Vector3D {
public:

	double	x, y, z;

public:

	Vector3D(void);											// default constructor
	Vector3D(double a);										// constructor
	Vector3D(double _x, double _y, double _z);				// constructor
	Vector3D(const Vector3D& v);							// copy constructor
	Vector3D(const Normal& n);								// constructs a vector from a Normal
	Vector3D(const Point3D& p);								// constructs a vector from a point

	~Vector3D(void);										// destructor

	Vector3D& operator= (const Vector3D& rhs);				// assignment operator
	Vector3D& operator= (const Normal& rhs);
	Vector3D& operator= (const Point3D& rhs);

	double length(void);
	double len_squared(void) const;
	void normalize(void);
	Vector3D& hat(void);

	Vector3D operator- (void) const;
	Vector3D operator- (const Vector3D& v) const;
	Vector3D operator* (const double a) const;
	Vector3D operator/ (const double a) const;
	Vector3D operator+ (const Vector3D& v) const;
	Vector3D& operator+= (const Vector3D& v);

	// fot product
	double operator* (const Vector3D& b) const;
	// cross product				
	Vector3D operator^ (const Vector3D& v) const;
	
	double dot(const Vector3D& b) const;
	Vector3D cross(const Vector3D& v) const;
};


// inlined member functions

// ------------------------------------------------------------------------ unary minus

inline Vector3D Vector3D::operator- (void) const 
{
	return (Vector3D(-x, -y, -z));
}


// ---------------------------------------------------------------------  len_squared
// the square of the length

inline double Vector3D::len_squared(void) const 
{
	return (x * x + y * y + z * z);
}


// ----------------------------------------------------------------------- operator*
// multiplication by a double on the right

inline Vector3D Vector3D::operator* (const double a) const 
{
	return (Vector3D(x * a, y * a, z * a));
}

// ----------------------------------------------------------------------- operator/
// division by a double

inline Vector3D Vector3D::operator/ (const double a) const 
{
	return (Vector3D(x / a, y / a, z / a));
}


// ----------------------------------------------------------------------- operator+
// addition

inline Vector3D Vector3D::operator+ (const Vector3D& v) const 
{
	return (Vector3D(x + v.x, y + v.y, z + v.z));
}


// ----------------------------------------------------------------------- operator-
// subtraction

inline Vector3D Vector3D::operator- (const Vector3D& v) const 
{
	return (Vector3D(x - v.x, y - v.y, z - v.z));
}


// ----------------------------------------------------------------------- operator*
// dot product

inline double Vector3D::dot (const Vector3D& v) const
{
	return (x * v.x + y * v.y + z * v.z);
}

inline double Vector3D::operator* (const Vector3D& v) const 
{
	return dot(v);
}



// ----------------------------------------------------------------------- operator^
// cross product

inline Vector3D Vector3D::cross (const Vector3D& v) const
{
	return (Vector3D(y * v.z - z * v.y, z * v.x - x * v.z, x * v.y - y * v.x));
}

inline Vector3D Vector3D::operator^ (const Vector3D& v) const 
{
	return cross(v);
}


// ---------------------------------------------------------------------  operator+=
// compound addition

inline Vector3D& Vector3D::operator+= (const Vector3D& v) 
{
	x += v.x; y += v.y; z += v.z;
	return (*this);
}




// inlined non-member function

// ----------------------------------------------------------------------- operator*
// multiplication by a double on the left

Vector3D operator* (const double a, const Vector3D& v);

inline Vector3D operator* (const double a, const Vector3D& v) 
{
	return (Vector3D(a * v.x, a * v.y, a * v.z));
}



// non-inlined non-member function

// ----------------------------------------------------------------------- operator* 
// multiplication by a matrix on the left

Vector3D operator* (const Matrix& mat, const Vector3D& v);




