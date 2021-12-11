#include "image.hpp"
#include <iostream>
#define NAME_WIDTH 100

using namespace std;

int main(int argc, char *argv[]) {

	// Original image file name
	char image_file_name[NAME_WIDTH] = "visit0000.ppm", result_file_name[NAME_WIDTH]="happy1.ppm", header[3];
	int radius=5;
	double sigma=0.5;

	/*cout << "Original image name: " << endl;
	cin >> image_file_name;
	
	cout << "Result image name: " << endl;
	cin >> result_file_name;
    
	cout << "Radius: " << endl;  
	cin >> radius;
	
	cout << "Sigma:" << endl;
	cin >> sigma;*/

	GaussianKernel kernel(radius,sigma);
	kernel.Calculation();
	cout << "Loading image..." << endl;
	
    Image img(image_file_name, result_file_name);

	img.image_load();
	img.check();
	// Apply filter
	cout << "Appling filter..." << endl;
	img.GaussianFliter(kernel);

	// Write image to disk
	cout << "Writing image to disk..." << endl;
	img.image_write();


	printf("DONE!\n");

	return 0;
}
