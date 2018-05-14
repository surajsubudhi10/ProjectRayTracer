#pragma once


#include "../Samplers/Sampler.h"

class ViewPlane {
public:
	int 			hres;   					// horizontal image resolution 
	int 			vres;   					// vertical image resolution
	float			s;							// pixel size

	int				image_hres;					// how big actual image should be
	int				image_vres;					// how big actual image should be

	float			gamma;						// gamma correction factor
	float			inv_gamma;					// the inverse of the gamma correction factor
	bool			show_out_of_gamut;			// display red if RGBColor out of gamut
	int				num_samples;				// number of samples per pixel
	Sampler*		sampler_ptr;				// pointer to the sampler we're using
	//int				max_depth;					// How many recursive levels for reflection



public:

	ViewPlane();   										// default Constructor
	ViewPlane(const ViewPlane& vp);						// copy constructor
	ViewPlane& operator= (const ViewPlane& rhs);		// assignment operator
	~ViewPlane();   									// destructor

	void set_hres(int h_res);
	void set_vres(int v_res);
	void set_image_hres(int h_res);
	void set_image_vres(int v_res);
	void set_pixel_size(float size);
	void set_gamma(float g);
	void set_gamut_display(bool show);
	void set_samples(int n);
	void set_sampler(Sampler* sp);

	/* void set_max_depth(int depth);*/
};

// ------------------------------------------------------------------------------ set_hres

inline void ViewPlane::set_hres(const int h_res) {
	hres = h_res;
	// kind of a hack for stereoscopy, don't want to break anything else though
	image_hres = h_res;
}

// ------------------------------------------------------------------------------ set_vres

inline void ViewPlane::set_vres(const int v_res) {
	vres = v_res;
	image_vres = v_res;
}

// ---

inline void ViewPlane::set_image_hres(const int h_res) {
	image_hres = h_res;
}

// ------------------------------------------------------------------------------ set_vres

inline void ViewPlane::set_image_vres(const int v_res) {
	image_vres = v_res;
}

// ------------------------------------------------------------------------------ set_pixel_size

inline void ViewPlane::set_pixel_size(const float size) {
	s = size;
}

// ------------------------------------------------------------------------------ set_gamma

inline void ViewPlane::set_gamma(const float g) {
	gamma = g;
	inv_gamma = 1.0f / gamma;
}

// ------------------------------------------------------------------------------ set_gamut_display

inline void ViewPlane::set_gamut_display(const bool show) {
	show_out_of_gamut = show;
}
//
//inline void
//ViewPlane::set_max_depth(int depth) {
//	max_depth = depth;
//}
