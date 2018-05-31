
#include "World/World.h"

#include <iostream>
#include <cstdlib>

int main() {

	World w;
	w.build();
	const char* fileName = "AmbientOcclusion1000e.bmp";
	//w.render_scene();
	std::cout << "RayTracing.." << std::endl;

	double coeff[5] = {24, -50, 35, -10, 1};
	double roots[4];

	auto num = SolveQuartic(coeff, roots);
	cout << "Num of Roots : " << num << "\n";
	for(auto i = 0; i < num; i++){
	    cout << "Root " << i + 1  <<" -> " << roots[i] << "\n";
	}

    w.camera_ptr->render_scene(w);
    w.Savebmp(fileName);
    std::cout << "RayTracing Completed." << std::endl;

    system(fileName);
	//system("pause");
	return 0;
}