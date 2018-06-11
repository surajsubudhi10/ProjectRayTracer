
#include "World/World.h"

#include <iostream>
#include <cstdlib>
#include <cmath>
#include <ctime>

int main() {

	clock_t startTime, endTime;
	startTime = clock();
	World w;
	w.build();
	const char* fileName = "AmbientOcclusion1000e.bmp";
	//w.render_scene();
	std::cout << "RayTracing.." << std::endl;

    w.camera_ptr->render_scene(w);
    w.Savebmp(fileName);
    endTime = clock();
    auto totalTime = ((float)endTime - (float)startTime) / CLOCKS_PER_SEC;
    std::cout << "RayTracing Completed in " << totalTime << " Seconds" << std::endl;

    system(fileName);
	//system("pause");
	return 0;
}