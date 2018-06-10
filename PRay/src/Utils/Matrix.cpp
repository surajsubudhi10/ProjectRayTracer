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






