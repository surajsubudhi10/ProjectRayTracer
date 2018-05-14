#pragma once


#include <vector>
#include "../Utils/Point2D.h"
#include "../Utils/Maths.h"
#include "../Utils/Point3D.h"


class Sampler
{
public:
	//constructors, access functions, etc
	Sampler();
	explicit Sampler(int num);
	Sampler(int samples, int sets);

	Sampler& operator= (const Sampler& rhs);
	virtual ~Sampler();
	virtual Sampler* clone() const = 0;
	virtual void generate_samples() = 0;				// generate sample patterns in a unit square
	void map_samples_to_unit_disk();					// mapping samples to a disk/circle
	void map_samples_to_hemisphere(float e);			// mapping samples to a hemisphere
	void setup_shuffled_indices();						// set up the randomly shuffled indices
	void shuffle_samples();								// randomly shuffle the samples in each pattern

	Point2D	sample_unit_square();		// get next sample on unit square
	Point2D	sample_unit_disk();			// get next sample on unit disk
	Point3D	sample_hemisphere();		// get next sample on hemisphere

	int	get_num_samples();				// get the number of samples
	void map_samples_to_sphere();
	Point3D	sample_sphere();			// get next sample on unit sphere

protected:

	int num_samples;									// the number of sample points in a pattern
	int num_sets;										// the number of sample sets (patterns) stored
	std::vector <Point2D> samples;						//sample points on a unit square
	std::vector <Point2D> disk_samples;					//sample points on a unit disk
	std::vector <Point3D> hemisphere_samples;			//sample points on a hemisphere disk
	std::vector<Point3D>  sphere_samples;				// sample points on a unit sphere
	std::vector <int> shuffled_indices;					// shuffled samples array indices
	unsigned long count;								//current number of sample points used
	int jump;											//random index jump
};

inline int Sampler::get_num_samples() {
	return num_samples;
}