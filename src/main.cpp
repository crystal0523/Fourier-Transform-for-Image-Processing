#include "image.hpp"

using namespace std;

int main(int argc, char *argv[]) {

	// Original image file name
	string image_file_name= "../img/Lenna.png", result_file_name= "filter.png";
	int radius = 5;
	double sigma = 5;

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

	cout << "Appling Gaussian filter..." << endl;
	img.GaussianFliter(kernel);

	cout << "Appling to grey filter..." << endl;
	img.to_grey();
	
	cout << "Appling to sobel filter..." << endl;
	img.SobelFliter();
	
	cout << "Writing image to disk..." << endl;
	img.image_writeGrey();
	//img.image_writeRGB();
	cout << "DONE!"<< endl;

	return 0;
}
