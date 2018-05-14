
#include "World/World.h"

#include <iostream>
#include <cstdlib>

int main() {

	World w;
	w.build();
	//w.render_scene();
	w.camera_ptr->render_scene(w);

	std::cout << "RayTracing.." << std::endl;
	w.Savebmp("testBareBoneRaytracer.bmp");
	std::cout << "RayTracing Completed." << std::endl;

	system("testBareBoneRaytracer.bmp");
	//system("pause");
	return 0;
}