#pragma once

//----------------------------------------- class Matrix

class Matrix
{

public:
	double	m[4][4];								// elements

	Matrix();										// default constructor
	Matrix(const Matrix& mat);						// copy constructor
	Matrix(double m00, double m01, double m02, double m03,
           double m10, double m11, double m12, double m13,
           double m20, double m21, double m22, double m23,
           double m30, double m31, double m32, double m33);

	Matrix(float diagonal);

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

const static Matrix Identity = Matrix(1.0f);




