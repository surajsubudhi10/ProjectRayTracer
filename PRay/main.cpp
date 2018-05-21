
#include "World/World.h"

#include <iostream>
#include <cstdlib>

int main() {

	World w;
	w.build();
	//w.render_scene();
	std::cout << "RayTracing.." << std::endl;

	w.camera_ptr->render_scene(w);
	w.Savebmp("AmbientOcclusion.bmp");
	std::cout << "RayTracing Completed." << std::endl;

	system("AmbientOcclusion.bmp");
	//system("pause");
	return 0;
}