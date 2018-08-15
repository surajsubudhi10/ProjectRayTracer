
#include "World/World.h"

#include <iostream>
#include <cstdlib>
#include <ctime>

int main() {
    const auto startTime = clock();
	World w;
	w.build();
    const auto fileName = "CustomMesh.bmp";
	//w.render_scene();
	std::cout << "RayTracing.." << std::endl;

    w.camera_ptr->render_scene(w);
    w.Savebmp(fileName);
    const auto endTime = clock();
    const auto totalTime = (static_cast<float>(endTime) - static_cast<float>(startTime)) / CLOCKS_PER_SEC;
    std::cout << "RayTracing Completed in " << totalTime << " Seconds" << std::endl;

    system(fileName);
	system("pause");
	return 0;
}