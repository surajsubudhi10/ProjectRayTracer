#pragma once

#include "Sampler.h"

class MultiJittered : public Sampler {
public:

	MultiJittered();
	explicit MultiJittered(int num_samples);
	MultiJittered(int num_samples, int m);
	MultiJittered(const MultiJittered& mjs);
	MultiJittered& operator= (const MultiJittered& rhs);
	MultiJittered* clone() const override;
	~MultiJittered() override;

private:
	void generate_samples() override;
};

typedef std::shared_ptr<MultiJittered> MultiJitteredPtr;

