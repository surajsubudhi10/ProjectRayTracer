#pragma once


#include <vector>
#include "../Utils/Point2D.h"
#include "../Utils/Maths.h"
#include "../Utils/Point3D.h"


class Sampler {

public:

	//constructors, access functions, etc

	Sampler(void);

	Sampler(const int num);

	Sampler(const int samples, const int sets);

	Sampler& operator= (const Sampler& rhs);

	virtual ~Sampler(void);

	virtual Sampler* clone(void) const = 0;

	virtual void generate_samples(void) = 0;				// generate sample patterns in a unit square

	void map_samples_to_unit_disk(void);					// mapping samples to a disk/circle
	void map_samples_to_hemisphere(const float e);			// mapping samples to a hemisphere
	void setup_shuffled_indices(void);						// set up the randomly shuffled indices
	void shuffle_samples(void);								// randomly shuffle the samples in each pattern
		

	Point2D	sample_unit_square(void);		// get next sample on unit square
	Point2D	sample_unit_disk(void);			// get next sample on unit disk
	Point3D	sample_hemisphere(void);		// get next sample on hemisphere
		

	int	get_num_samples(void);				// get the number of samples
	void map_samples_to_sphere(void);
	Point3D	sample_sphere(void);			// get next sample on unit sphere
		

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

inline int
Sampler::get_num_samples(void) {
	return num_samples;
}
