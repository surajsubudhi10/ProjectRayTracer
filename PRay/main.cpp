
#include "World/World.h"

#include <iostream>
#include <cstdlib>

#include <cmath>

int main() {

	World w;
	w.build();
	const char* fileName = "AmbientOcclusion1000e.bmp";
	//w.render_scene();
	std::cout << "RayTracing.." << std::endl;

    w.camera_ptr->render_scene(w);
    w.Savebmp(fileName);
    std::cout << "RayTracing Completed." << std::endl;

    system(fileName);
	//system("pause");
	return 0;
}