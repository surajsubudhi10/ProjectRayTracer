#pragma once

#include <stdlib.h>
#include "Constants.h"
#include "RGBColor.h"


// prototypes

double min(double x0, double x1);

double max(double x0, double x1);

int rand_int(void);

float rand_float(void);

void set_rand_seed(const int seed);

float rand_float(int l, float h);

int rand_int(int l, int h);

double clamp(const double x, const double min, const double max);

int SolveQuadric(double c[3], double s[2]);

int SolveCubic(double c[4], double s[3]);

int SolveQuartic(double c[5], double s[4]);



// inlined functions

// ----------------------------------------------------------------- min

inline double min(double x0, double x1) 
{
	return ((x0 < x1) ? x0 : x1);
}


// ----------------------------------------------------------------- max

inline double max(double x0, double x1) 
{
	return ((x0 > x1) ? x0 : x1);
}


// ---------------------------------------------------- rand_int
// a wrapper for rand()

inline int rand_int(void) 
{
	return(rand());
}


// ---------------------------------------------------- rand_float

inline float rand_float(void) 
{
	return((float)rand_int() * invRAND_MAX);
}


// ---------------------------------------------------- set_rand_seed

inline void set_rand_seed(const int seed) 
{
	srand(seed);
}


// ---------------------------------------------------- rand_float with arguments

inline float rand_float(int l, float h) 
{
	return (rand_float() * (h - l) + l);
}

// ---------------------------------------------------- rand_int with arguments

inline int rand_int(int l, int h) 
{
	return ((int)(rand_float(0, h - l + 1) + l));
}


// ---------------------------------------------------- clamp

inline double clamp(const double x, const double min, const double max) 
{
	return (x < min ? min : (x > max ? max : x));
}
