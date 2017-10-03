
#include "Sampler.h"
#include "../Utils/Point3D.h"
#include <algorithm>

Sampler::Sampler(void)
	: num_samples(1), num_sets(83), count(0), jump(0) 
{

	samples.reserve(num_samples * num_sets);
	setup_shuffled_indices();
}

Sampler::Sampler(const int num)
	: num_samples(num),	num_sets(83), count(0),	jump(0) 
{
	samples.reserve(num_samples * num_sets);
	setup_shuffled_indices();
}

Sampler::Sampler(const int samples, const int sets)
	: num_samples(samples), num_sets(sets),	count(0), jump(0)
{
	this->samples.reserve(num_samples * num_sets);
	setup_shuffled_indices();
}

Sampler& Sampler::operator= (const Sampler& rhs) 
{
	if (this == &rhs)
		return (*this);

	num_samples = rhs.num_samples;
	num_sets = rhs.num_sets;
	samples = rhs.samples;
	shuffled_indices = rhs.shuffled_indices;
	disk_samples = rhs.disk_samples;
	hemisphere_samples = rhs.hemisphere_samples;
	//	sphere_samples		= rhs.sphere_samples;
	count = rhs.count;
	jump = rhs.jump;

	return (*this);
}

Sampler::~Sampler(void)
{
}

Point2D Sampler::sample_unit_square(void) 
{
	if (count % num_samples == 0)	// start of new pixel
	{
		jump = (rand_int() % num_sets) * num_samples;
	}

	return (samples[jump + shuffled_indices[jump + count++ % num_samples]]);
}

Point2D Sampler::sample_unit_disk(void) 
{
	if (count % num_samples == 0)	// start of new pixel
	{
		jump = (rand_int() % num_sets) * num_samples;
	}

	return (disk_samples[jump + shuffled_indices[jump + count++ % num_samples]]);
}

Point3D Sampler::sample_hemisphere(void) 
{
	if (count % num_samples == 0)	// start of new pixel
	{
		jump = (rand_int() % num_sets) * num_samples;
	}

	return (hemisphere_samples[jump + shuffled_indices[jump + count++ % num_samples]]);
}

void Sampler::setup_shuffled_indices(void) 
{
	shuffled_indices.reserve(num_samples * num_sets);
	std::vector<int> indices;

	for (int j = 0; j < num_samples; j++)
		indices.push_back(j);

	for (int p = 0; p < num_sets; p++) {
		random_shuffle(indices.begin(), indices.end());

		for (int j = 0; j < num_samples; j++)
			shuffled_indices.push_back(indices[j]);
	}
}

void Sampler::map_samples_to_unit_disk(void) 
{
	int size = samples.size();
	float r, phi;	//polar coordinates
	Point2D sp;	// sample point on unit disk

	disk_samples.reserve(size);

	for (int j = 0; j < size; j++) {
		// map sample point to [-1, 1]

		sp.x = 2.0 * samples[j].x - 1.0;
		sp.y = 2.0 * samples[j].y - 1.0;

		if (sp.x > -sp.y) {						// sectors 1 and 2
			if (sp.x > sp.y) {					// sector 1
				r = sp.x;
				phi = sp.y / sp.x;
			}
			else {								// sector 2
				r = sp.y;
				phi = 2 - sp.x / sp.y;
			}
		}
		else {									//sectors 3 and 4
			if (sp.x < sp.y) {					// sector 3
				r = -sp.x;
				phi = 4 + sp.y / sp.x;
			}
			else {								// sector 4
				r = -sp.y;
				if (sp.y != 0.0)				// BAD! / by 0 at origin
					phi = 6 - sp.x / sp.y;
				else
					phi = 0.0;
			}
		}

		phi *= PI / 4.0;		// common to all sectors

		disk_samples[j].x = r * cos(phi);
		disk_samples[j].y = r * sin(phi);
	}
}

void Sampler::map_samples_to_hemisphere(const float e) // mapping samples to a hemisphere
{
	int size = samples.size();
	hemisphere_samples.reserve(num_samples * num_sets);

	for (int j = 0; j < size; j++) {
		float cos_phi = cos(2.0 * PI * samples[j].x);
		float sin_phi = sin(2.0 * PI * samples[j].x);
		float cos_theta = pow((1.0 - samples[j].y), 1.0 / (e + 1.0));
		float sin_theta = sqrt(1.0 - cos_theta * cos_theta);
		float pu = sin_theta * cos_phi;
		float pv = sin_theta * sin_phi;
		float pw = cos_theta;

		hemisphere_samples.push_back(Point3D(pu, pv, pw));
	}
}

void Sampler::map_samples_to_sphere(void) 
{
	float r1, r2;
	float x, y, z;
	float r, phi;

	sphere_samples.reserve(num_samples * num_sets);

	for (int j = 0; j < num_samples * num_sets; j++) {
		r1 = samples[j].x;
		r2 = samples[j].y;
		z = 1.0 - 2.0 * r1;
		r = sqrt(1.0 - z * z);
		phi = TWO_PI * r2;
		x = r * cos(phi);
		y = r * sin(phi);
		sphere_samples.push_back(Point3D(x, y, z));
	}
}

Point3D Sampler::sample_sphere(void) 
{
	if (count % num_samples == 0)  									// start of a new pixel
		jump = (rand_int() % num_sets) * num_samples;

	return (sphere_samples[jump + shuffled_indices[jump + count++ % num_samples]]);
}
