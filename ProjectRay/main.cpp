
#include "src\World\World.h"

#include <iostream>

int main() {

	World w;
	w.build();
	w.render_scene();

	std::cout << "RayTracing.." << std::endl;
	w.Savebmp("testBareBoneRaytracer.bmp");
	std::cout << "RayTracing Completed." << std::endl;

	system("pause");
	return 0;
}