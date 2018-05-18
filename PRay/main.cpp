
#include "World/World.h"

#include <iostream>
#include <cstdlib>

int main() {

	World w;
	w.build();
	//w.render_scene();
	std::cout << "RayTracing.." << std::endl;

	w.camera_ptr->render_scene(w);
	w.Savebmp("AmbientOcclusionWithPoint.bmp");
	std::cout << "RayTracing Completed." << std::endl;

	system("AmbientOcclusionWithPoint.bmp");
	//system("pause");
	return 0;
}