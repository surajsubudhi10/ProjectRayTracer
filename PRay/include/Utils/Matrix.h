#pragma once

//----------------------------------------- class Matrix

class Matrix
{

public:
	double	m[4][4];								// elements

	Matrix();										// default constructor
	Matrix(const Matrix& mat);						// copy constructor
	~Matrix();										// destructor

	// assignment operator
	Matrix& operator= (const Matrix& rhs);
	// multiplication of two matrices
	Matrix operator* (const Matrix& mat) const;
	Matrix scalar_mult(double m);
	Matrix operator/ (double d);
	void set_identity();

	double* operator[](int index);
	const double* operator[](int index) const;
};






