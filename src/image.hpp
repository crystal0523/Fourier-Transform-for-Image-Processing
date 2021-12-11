#ifndef IMAGE_HPP
#define IMAGE_HPP
#include <iostream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include "pixel.hpp"
#include "filter.hpp"
using namespace std;

class Image
{

public:

	char *IFile, *OFile, *header;
	int width, height, color_depth;
	Pixel** pixels;
	Image(char *input_file, char* output_file):IFile(input_file), OFile(output_file){};

	~Image()
	{
		cout << "call of Image destructor" << endl;
		for(int i = 0; i < height; i++)
			delete [] pixels[i];
		delete [] pixels;
	}
	Image(Image const &) = default;
	Image(Image      &&) = default;
    Image & operator= (Image const &) = default;
	Image & operator= (Image      &&) = default;

	void image_load();
	
	void check();
	//Apply a filter to the image
	void apply_to_pixel(const int x, const int y, const GaussianKernel& kernel);
	
	void GaussianFliter(const GaussianKernel& kernel);

	void image_write();
	
};

#endif //IMAGE_H
