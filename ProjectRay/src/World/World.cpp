// this file contains the definition of the World class

//#include "wxraytracer.h"

#include "World.h"
#include "../Utils/Constants.h"

// geometric objects

#include "../Objects/Plane.h"
#include "../Objects/Sphere.h"

// tracers

//#include "SingleSphere.h"
//#include "MultipleObjects.h"

// utilities

#include "../Utils/Vector3D.h"
#include "../Utils/Point2D.h"
#include "../Utils/Point3D.h"
#include "../Utils/Normal.h"
#include "../Utils/ShadeRec.h"
#include "../Utils/Maths.h"
//#include "Ambient.h"




// build functions

//#include "BuildSingleSphere.cpp"
//#include "BuildMultipleObjects.cpp"
//#include "BuildBBCoverPic.cpp"


// -------------------------------------------------------------------- default constructor

World::World(void)
	: background_color(black),
	//tracer_ptr(NULL),
	camera_ptr(NULL)//,
	//ambient_ptr(new Ambient)
{
	primaryBuffer = new RGBColor[vp.vres * vp.hres];
}



//------------------------------------------------------------------ destructor

World::~World(void) {

	/*if (tracer_ptr) {
		delete tracer_ptr;
		tracer_ptr = NULL;
	}*/

	if (camera_ptr) {
		delete camera_ptr;
		camera_ptr = NULL;
	}
	/*
	if (ambient_ptr) {
		delete ambient_ptr;
		ambient_ptr = NULL;
	}*/

	if (primaryBuffer != NULL)
	{
		delete[] primaryBuffer;
		primaryBuffer = NULL;
	}


	//delete_objects();
}


//------------------------------------------------------------------ render_scene

// This uses orthographic viewing along the zw axis

void
World::render_scene(void){ //const {

	RGBColor	pixel_color;
	Ray			ray;
	int 		hres = vp.hres;
	int 		vres = vp.vres;
	float		s = vp.s;
	float		zw = 100.0;			// hardwired in
	int			n = 1;// (int)sqrt((float)vp.num_samples);	// Samples
	Point2D		sp;		// sample point in [0,1] x [0,1]
	Point2D		pp;		// sample point on a pixel
	int pixelIndex = 0;

	ray.d = Vector3D(0, 0, -1);

	for (int r = 0; r < vres; r++)			// up
		for (int c = 0; c < hres; c++) {	// across 					
			pixel_color = black;

			for (int p = 0; p < n; p++)			// going up the pixel
			{
				for (int q = 0; q < n; q++)		// going across the pixel
				{
					sp = Point2D(0, 0);//vp.sampler_ptr->sample_unit_square();
					pp.x = vp.s * (c - 0.5 * vp.hres + sp.x);
					pp.y = vp.s * (r - 0.5 * vp.vres + sp.y);
					ray.o = Point3D(pp.x, pp.y, zw);
					//pixel_color += tracer_ptr->trace_ray(ray);
					pixel_color += Trace(ray);

				}
			}

			//pixel_color /= vp.num_samples;	// Average colors
			//display_pixel(r, c, pixel_color);
			/*RGBColor mapped_color;
			
			if (vp.show_out_of_gamut)
				mapped_color = clamp_to_color(pixel_color);
			else
				mapped_color = max_to_one(pixel_color);
			
			if (vp.gamma != 1.0)
				mapped_color = mapped_color.powc(vp.inv_gamma);*/
			//primaryBuffer[pixelIndex++] = mapped_color;
			primaryBuffer[pixelIndex] = pixel_color;
			pixelIndex++;
		}
}


// ------------------------------------------------------------------ clamp

RGBColor
World::max_to_one(const RGBColor& c) const {
	float max_value = max(c.r, max(c.g, c.b));

	if (max_value > 1.0)
		return (c / max_value);
	else
		return (c);
}


// ------------------------------------------------------------------ clamp_to_color
// Set color to red if any component is greater than one

RGBColor
World::clamp_to_color(const RGBColor& raw_color) const {
	RGBColor c(raw_color);

	if (raw_color.r > 1.0 || raw_color.g > 1.0 || raw_color.b > 1.0) {
		c.r = 1.0; c.g = 0.0; c.b = 0.0;
	}

	return (c);
}

//void
//World::set_ambient_light(Ambient* amb) {
//	if (ambient_ptr) {
//		delete ambient_ptr;
//		ambient_ptr = NULL;
//	}
//
//	ambient_ptr = amb;
//}


// ---------------------------------------------------------------------------display_pixel

// raw_color is the pixel color computed by the ray tracer
// its RGB floating point components can be arbitrarily large
// mapped_color has all components in the range [0, 1], but still floating point
// display color has integer components for computer display
// the Mac's components are in the range [0, 65535]
// a PC's components will probably be in the range [0, 255]
// the system-dependent code is in the function convert_to_display_color
// the function SetCPixel is a Mac OS function


//void
//World::display_pixel(const int row, const int column, const RGBColor& raw_color) const {
//	RGBColor mapped_color;
//
//	if (vp.show_out_of_gamut)
//		mapped_color = clamp_to_color(raw_color);
//	else
//		mapped_color = max_to_one(raw_color);
//
//	if (vp.gamma != 1.0)
//		mapped_color = mapped_color.powc(vp.inv_gamma);
//
//	//have to start from max y coordinate to convert to screen coordinates
//	int x = column;
//	int y = vp.vres - row - 1;
//
//	paintArea->setPixel(x, y, (int)(mapped_color.r * 255),
//		(int)(mapped_color.g * 255),
//		(int)(mapped_color.b * 255));
//}

ShadeRec
World::hit_objects(const Ray& ray) {
	ShadeRec	sr(*this);
	double		t;
	Normal		normal;
	Point3D		local_hit_point;
	float		tmin = kHugeValue;
	int			num_objects = objects.size();

	for (int j = 0; j < num_objects; j++)
		if (objects[j]->hit(ray, t, sr) && (t < tmin)) {
			sr.hit_an_object = true;
			tmin = t;
			//sr.material_ptr = objects[j]->get_material();
			//sr.hit_point = ray.o + t * ray.d;
			normal = sr.normal;
			local_hit_point = sr.local_hit_point;
		}

	if (sr.hit_an_object) {
		//sr.t = tmin;
		sr.normal = normal;
		sr.local_hit_point = local_hit_point;
	}

	return (sr);
}




// ----------------------------------------------------------------------------- hit_bare_bones_objects

ShadeRec
World::hit_bare_bones_objects(const Ray& ray) {
	ShadeRec	sr(*this);
	double		t;
	float		tmin = kHugeValue;
	int 		num_objects = objects.size();

	for (int j = 0; j < num_objects; j++)
		if (objects[j]->hit(ray, t, sr) && (t < tmin)) {
			sr.hit_an_object = true;
			tmin = t;
			sr.color = objects[j]->get_color();
		}

	return (sr);
}


//------------------------------------------------------------------ delete_objects

// Deletes the objects in the objects array, and erases the array.
// The objects array still exists, because it's an automatic variable, but it's empty 

void
World::delete_objects(void) {
	int num_objects = objects.size();

	for (int j = 0; j < num_objects; j++) {
		delete objects[j];
		objects[j] = NULL;
	}

	objects.erase(objects.begin(), objects.end());
}

//void
//World::delete_lights(void) {
//	int num_objects = lights.size();
//
//	for (int j = 0; j < num_objects; j++) {
//		delete lights[j];
//		lights[j] = NULL;
//	}
//
//	lights.erase(lights.begin(), lights.end());
//}





RGBColor World::Trace(Ray &primaryRay)
{
	ShadeRec sr(*this);
	double closestDistance = 20000.0f;
	int closestObj = -1;

	for (unsigned int i = 0; i < objects.size(); i++)
	{
		if (objects[i] == NULL)
			continue;

		double dist = 0;
		if (objects[i]->hit(primaryRay, dist, sr))
		{
			if (dist < closestDistance)
			{
				closestDistance = dist;
				closestObj = i;
				sr.hit_an_object = true;
				sr.color = objects[closestObj]->get_color();
			}
		}
	}

	if (closestObj != -1)
	{
		return objects[closestObj]->get_color();
	}

	return background_color;
}


void World::Savebmp(const char *filename) {//, int w, int h, int dpi){//, RGBType *data){
	FILE *f;
	int w = vp.hres;
	int h = vp.vres;
	int dpi = 72;
	int k = w * h;
	int s = 4 * k;
	int filesize = 54 + s;

	double factor = 39.375;
	int m = static_cast<int>(factor);

	int ppm = dpi * m;

	unsigned char bmpfileheader[14] = { 'B', 'M',  0,0,0,0, 0,0,0,0, 54,0,0,0 };
	unsigned char bmpinfoheader[40] = { 40,0,0,0, 0,0,0,0, 0,0,0,0,  1,0,24,0 };

	bmpfileheader[2] = (unsigned char)(filesize);
	bmpfileheader[3] = (unsigned char)(filesize >> 8);
	bmpfileheader[4] = (unsigned char)(filesize >> 16);
	bmpfileheader[5] = (unsigned char)(filesize >> 24);

	bmpinfoheader[4] = (unsigned char)(w);
	bmpinfoheader[5] = (unsigned char)(w >> 8);
	bmpinfoheader[6] = (unsigned char)(w >> 16);
	bmpinfoheader[7] = (unsigned char)(w >> 24);

	bmpinfoheader[8] = (unsigned char)(h);
	bmpinfoheader[9] = (unsigned char)(h >> 8);
	bmpinfoheader[10] = (unsigned char)(h >> 16);
	bmpinfoheader[11] = (unsigned char)(h >> 24);

	bmpinfoheader[21] = (unsigned char)(s);
	bmpinfoheader[22] = (unsigned char)(s >> 8);
	bmpinfoheader[23] = (unsigned char)(s >> 16);
	bmpinfoheader[24] = (unsigned char)(s >> 24);

	bmpinfoheader[25] = (unsigned char)(ppm);
	bmpinfoheader[26] = (unsigned char)(ppm >> 8);
	bmpinfoheader[27] = (unsigned char)(ppm >> 16);
	bmpinfoheader[28] = (unsigned char)(ppm >> 24);

	bmpinfoheader[29] = (unsigned char)(ppm);
	bmpinfoheader[30] = (unsigned char)(ppm >> 8);
	bmpinfoheader[31] = (unsigned char)(ppm >> 16);
	bmpinfoheader[32] = (unsigned char)(ppm >> 24);

	f = fopen(filename, "wb");

	fwrite(bmpfileheader, 1, 14, f);
	fwrite(bmpinfoheader, 1, 40, f);

	for (int i = 0; i < k; i++) {
		RGBColor rgb;
		//std::cout << primaryBuffer[i].r << "g : " << primaryBuffer[i].g << std::endl;
		rgb = primaryBuffer[i];

		double red = (primaryBuffer[i].r) * 255;
		double green = (primaryBuffer[i].g) * 255;
		double blue = (primaryBuffer[i].b) * 255;

		unsigned char color[3] = { (unsigned char)floor(blue), (unsigned char)floor(green), (unsigned char)floor(red) };
		fwrite(color, 1, 3, f);
	}

	fclose(f);
}