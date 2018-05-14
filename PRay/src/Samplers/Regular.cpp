
#include <math.h>
#include "Samplers/Regular.h"

// ---------------------------------------------------------------- default constructor

Regular::Regular()
	: Sampler()
{}


// ---------------------------------------------------------------- constructor

Regular::Regular(const int num)
	: Sampler(num)
{
	generate_samples();
}


// ---------------------------------------------------------------- copy constructor

Regular::Regular(const Regular& u)
	: Sampler(u)
{
	generate_samples();
}

// ---------------------------------------------------------------- assignment operator

Regular& Regular::operator= (const Regular& rhs) 
{
	if (this == &rhs)
		return (*this);

	Sampler::operator= (rhs);

	return (*this);
}

// ---------------------------------------------------------------- clone

Regular* Regular::clone() const
{
	return (new Regular(*this));
}

// ---------------------------------------------------------------- destructor			

Regular::~Regular() = default;


// ---------------------------------------------------------------- generate_samples	

void Regular::generate_samples()
{
	auto n = (int)sqrtf((float)num_samples);

	for (int j = 0; j < num_sets; j++)
		for (int p = 0; p < n; p++)
			for (int q = 0; q < n; q++)
				samples.emplace_back((q + 0.5) / n, (p + 0.5) / n);
}
