#ifndef IMAGE_HPP
#define IMAGE_HPP
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "pixel.hpp"
#include "filter.hpp"
#include <opencv2/opencv.hpp>

using namespace std;
using namespace cv;
class Image
{

public:

	string input_file, output_file;
	int width, height, channel;
	Pixel* pixelsRGB;
	unsigned char * pixelsGrey;
	Mat img;
	Image(string input_file, string output_file):input_file(input_file), output_file(output_file){};
	
	~Image()
	{
		cout << "call of Image destructor" << endl;
		if(channel==1)
		{
			delete [] pixelsRGB;
		}
		else if(channel==3)
		{
			delete [] pixelsGrey;
		}
		
	}
	Image(Image const &) = default;
	Image(Image      &&) = default;
    Image & operator= (Image const &) = default;
	Image & operator= (Image      &&) = default;

	unsigned char* set_Grey_buffer();
	Pixel* set_RGB_buffer();
	
	void image_load();
	
	//void check();

	void to_grey();

	void apply_to_pixelRGB(const int x, const int y, const GaussianKernel& kernel);
	void apply_to_pixelGrey(const int x, const int y, const GaussianKernel& kernel);
	
	void GaussianFliter(const GaussianKernel& kernel);

	void SobelFliter_axis(const vector<int>& sobel_kernel);
	void SobelFliter_axisXY(const vector<int>& sobel_kernelX, const vector<int>& sobel_kernelY);

	// img need to transform to greyscale first
	void SobelFliter(); 

	void image_writeRGB();
	void image_writeGrey();
};

#endif //IMAGE_H
