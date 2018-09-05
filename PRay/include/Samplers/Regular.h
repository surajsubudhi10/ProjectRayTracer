#pragma once

#include "Sampler.h"

class Regular : public Sampler
{
public:
	Regular();
	explicit Regular(int num);
	Regular(const Regular& u);
	Regular& operator= (const Regular& rhs);
	SamplerPtr clone() const override;
	~Regular() override;
	void generate_samples() override;
};

typedef std::shared_ptr<Regular> RegularPtr;