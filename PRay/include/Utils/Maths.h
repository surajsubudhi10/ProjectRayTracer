#pragma once

#include <cstdlib>
#include "Constants.h"
#include "RGBColor.h"


#define PI 3.14159

// prototypes

double min(double x0, double x1);

double max(double x0, double x1);

double Abs(double val);

int rand_int();

float rand_float();

void set_rand_seed(int seed);

float rand_float(int l, float h);

int rand_int(int l, int h);

double clamp(double x, double min, double max);

int SolveQuadric(double c[3], double s[2]);

int SolveCubic(double c[4], double s[3]);

int SolveQuartic(double c[5], double s[4]);

int SolveQuarticV2(double c[5], double s[4]);

float to_randian(float val);
float to_degree(float val);

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

inline int rand_int()
{
	return(rand());
}

// ---------------------------------------------------- rand_float

inline float rand_float()
{
	return((float)rand_int() * invRAND_MAX);
}

// ---------------------------------------------------- set_rand_seed

inline void set_rand_seed(int seed)
{
	srand(static_cast<unsigned int>(seed));
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

inline double Abs(double val)
{

    if(val > 0)
        return val;
    else
        return -1 * val;
}

inline float to_randian(float val)
{
    return static_cast<float>(val * PI / 180.0f);
}

inline float to_degree(float val)
{
    return static_cast<float>(val * 180.0f / PI);
}