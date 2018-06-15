// This file contains the definition of the class Matrix

#include <cassert>
#include "Utils/Matrix.h"

// ----------------------------------------------------------------------- default constructor
// a default matrix is an identity matrix

Matrix::Matrix()
{
	for (int x = 0; x < 4; x++) {
        for (int y = 0; y < 4; y++) {
            if (x == y)
                m[x][y] = 1.0;
            else
                m[x][y] = 0.0;
        }
    }
}


// ----------------------------------------------------------------------- copy constructor

Matrix::Matrix(const Matrix& mat)
{
	for (int x = 0; x < 4; x++)
		for (int y = 0; y < 4; y++)
			m[x][y] = mat.m[x][y];
}


// ----------------------------------------------------------------------- destructor

Matrix::~Matrix() = default;

// ----------------------------------------------------------------------- assignment operator

Matrix& Matrix::operator= (const Matrix& rhs)
{
	if (this == &rhs)
		return (*this);

	for (int x = 0; x < 4; x++)
		for (int y = 0; y < 4; y++)
			m[x][y] = rhs.m[x][y];

	return (*this);
}


// ----------------------------------------------------------------------- operator*
// multiplication of two matrices

Matrix Matrix::operator* (const Matrix& mat) const
{
	Matrix 	product;

	for (int y = 0; y < 4; y++)
		for (int x = 0; x < 4; x++) {
			double sum = 0.0;

			for (int j = 0; j < 4; j++)
				sum += m[x][j] * mat.m[j][y];

			product.m[x][y] = sum;
		}

	return (product);
}


// ----------------------------------------------------------------------- operator/
// division by a scalar

Matrix Matrix::operator/ (const double d)
{
	for (int x = 0; x < 4; x++)
		for (int y = 0; y < 4; y++)
			m[x][y] = m[x][y] / d;

	return (*this);
}

Matrix Matrix::scalar_mult(const double d)
{
	for (int x = 0; x < 4; x++)
		for (int y = 0; y < 4; y++)
			m[x][y] = m[x][y] * d;

	return (*this);
}



// ----------------------------------------------------------------------- set_identity
// set matrix to the identity matrix

void Matrix::set_identity()
{
	for (int x = 0; x < 4; x++) {
        for (int y = 0; y < 4; y++) {
            if (x == y)
                m[x][y] = 1.0;
            else
                m[x][y] = 0.0;
        }
    }
}

double* Matrix::operator[](int index)
{
    assert(index < 4 && index > -1);
    return m[index];
}

const double *Matrix::operator[](int index) const
{
    assert(index < 4 && index > -1);
    return m[index];
}

Matrix::Matrix(double m00, double m01, double m02, double m03,
               double m10, double m11, double m12, double m13,
               double m20, double m21, double m22, double m23,
               double m30, double m31, double m32, double m33)
{
    m[0][0] = m00; m[0][1] = m01; m[0][2] = m02; m[0][3] = m03;
    m[1][0] = m10; m[1][1] = m11; m[1][2] = m12; m[1][3] = m13;
    m[2][0] = m20; m[2][1] = m21; m[2][2] = m22; m[2][3] = m23;
    m[3][0] = m30; m[3][1] = m31; m[3][2] = m32; m[3][3] = m33;
}

Matrix::Matrix(float diagonal)
{
    m[0][0] = diagonal; m[0][1] =        0; m[0][2] =        0; m[0][3] =        0;
    m[1][0] =        0; m[1][1] = diagonal; m[1][2] =        0; m[1][3] =        0;
    m[2][0] =        0; m[2][1] =        0; m[2][2] = diagonal; m[2][3] =        0;
    m[3][0] =        0; m[3][1] =        0; m[3][2] =        0; m[3][3] = diagonal;
}






