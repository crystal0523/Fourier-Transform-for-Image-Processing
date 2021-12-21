#include "image.hpp"


unsigned char* Image::set_Grey_buffer()
{
	unsigned char *pixels = new unsigned char [height * width];
	
	return pixels;
}


Pixel* Image::set_RGB_buffer()
{
	Pixel* pixels = new Pixel[height * width];
	
	return pixels;
}


void Image::image_load() 
{

	img = imread(input_file);
	if(img.empty())
	{
		cout << "file open error " << endl;
	}
    height = img.rows;
	width = img.cols;
	channel = img.channels();
	
	cout << "width: " << width << " height: "<< height << endl;
	
	// color image
	if(channel==3)
	{
		pixelsRGB = set_RGB_buffer();

		// Read pixels
		for(int i = 0; i < height; i++)
		{
			for(int j = 0; j < width; j++)
			{
				Vec3b &color = img.at<Vec3b>(i,j);//BGR
				pixelsRGB[i * width + j].R = color[2];
				pixelsRGB[i * width + j].G = color[1];
				pixelsRGB[i * width + j].B = color[0];
			}	
		}
	}
	// greyscale image
	else if(channel==1)
	{
		pixelsGrey = set_Grey_buffer();
		for(int i = 0; i < height; i++)
		{
			for(int j = 0; j < width; j++)
			{
				pixelsGrey[i * width + j] = img.at<uchar>(i,j);
			}	
		}
	}
	
}


/*void Image::check()
{
	for(int i = 0; i < height; i++)
		for(int j = 0; j < width; j++)
			cout << "r: "<< pixels[i][j].R << " g: "<< pixels[i][j].G << " b: " << pixels[i][j].B;
}*/



void Image::to_grey()
{

	pixelsGrey = set_Grey_buffer();
	for(int i = 0; i < height; i++)
	{
		for(int j = 0; j < width; j++)
		{
			pixelsGrey[i * width + j] = pixelsRGB[i * width + j].R * 0.3333 + pixelsRGB[i * width + j].G * 0.3333 
			+ pixelsRGB[i * width + j].B * 0.3333;
		}	
	}
	channel = 1;

}

//Apply a filter to the image
void Image::apply_to_pixelRGB(const int x, const int y, const GaussianKernel& kernel)
{
	if(x < kernel.radius || y < kernel.radius || x >= width - kernel.radius || y >= height - kernel.radius) return;

	Pixel res;
	res.R = res.G = res.B = 0;
	double fil;

	for(int i = -kernel.radius; i <= kernel.radius; i++) 
		for(int j = -kernel.radius; j <= kernel.radius; j++) 
		{
			fil = kernel.matrix[(i + kernel.radius) * kernel.dim + j + kernel.radius];
			res.R += fil * pixelsRGB[(y + i) * width + x + j].R;
			res.G += fil * pixelsRGB[(y + i) * width + x + j].G;
			res.B += fil * pixelsRGB[(y + i) * width + x + j].B;
		}
	
	pixelsRGB[y * width + x].R = res.R;
	pixelsRGB[y * width + x].G = res.G;
	pixelsRGB[y * width + x].B = res.B;
}	


void Image::apply_to_pixelGrey(const int x, const int y, const GaussianKernel& kernel)
{
	if(x < kernel.radius || y < kernel.radius || x >= width - kernel.radius || y >= height - kernel.radius) return;

	unsigned char res = 0;
	double fil;

	for(int i = -kernel.radius; i <= kernel.radius; i++) 
		for(int j = -kernel.radius; j <= kernel.radius; j++) 
		{
			fil = kernel.matrix[(i + kernel.radius) * kernel.dim + j + kernel.radius];
			res+= fil * pixelsGrey[(y + i) * width + x + j];
		
		}
	
	pixelsGrey[y*width+x]= res;
	
}	


void Image::GaussianFliter(const GaussianKernel& kernel)
{
	for(int y = 0; y < height; y++)
		for(int x = 0; x < width; x++)
		{
			if(channel==1)apply_to_pixelGrey(x, y, kernel);
			else if(channel==3)apply_to_pixelRGB(x, y, kernel);
		}
			
}


void Image::SobelFliter_axis(const vector<int>& sobel_kernel)
{	
	int kernel_size = 3;      
  
	unsigned char * tmp = set_Grey_buffer();
	int size = width * height * sizeof(unsigned char);
	memcpy(tmp, pixelsGrey,size);

	for (int row = 0; row < height; row++) 
	{
		for (int col = 0; col < width ; col ++) 
		{

			if (row <= kernel_size/2 || row >= height-kernel_size/2 ||
					col <= kernel_size/2 || col >= width-kernel_size/2)
			{
				pixelsGrey[row * width + col] = 0;
				continue;
			}
			int sum = 0;
			int k_ind = 0;
			for (int k_row = -kernel_size / 2; k_row <= kernel_size / 2; ++k_row)
			{
				for (int k_col = -kernel_size / 2; k_col <= kernel_size / 2; ++k_col) 
				{
					sum += sobel_kernel[k_ind] * tmp[width * (row + k_row) + col + k_col];
					k_ind ++;
				}
			}
			pixelsGrey[width * row + col] = max(min(sum, 255), 0);
		}
	}
}

void Image::SobelFliter_axisXY(const vector<int>& sobel_kernelX, const vector<int>& sobel_kernelY)
{
	
    int kernel_size = 3;

	unsigned char * tmp = set_Grey_buffer();
	int size = width * height * sizeof(unsigned char);
	memcpy(tmp, pixelsGrey,size);

    for (int row = 0; row < height; ++row) 
	{
        for (int col = 0; col < width ; col += 1) 
		{

            if (row <= kernel_size/2 || row >= height-kernel_size/2 ||
                col <= kernel_size/2 || col >= width-kernel_size/2)
			{
                pixelsGrey[width * row + col] = 0;
                continue;
            }
            
            int sum_x = 0, sum_y = 0;
            int k_ind = 0;
            for (int k_row = -kernel_size/2; k_row <= kernel_size/2; ++k_row) 
			{
                for (int k_col = -kernel_size/2; k_col <= kernel_size/2; ++k_col) 
				{
                    sum_x += sobel_kernelX[k_ind] * tmp[width * (row+k_row) + col + k_col];
                    sum_y += sobel_kernelY[k_ind] * tmp[width * (row+k_row) + col + k_col];
                    k_ind++;
                }
            }
            int G = unsigned(sqrt(sum_x * sum_x + sum_y * sum_y));
            pixelsGrey[width * row + col] = min(G, 255);
        }
    }
}


void Image:: SobelFliter()
{
	vector<int>x = {1,0,-1,2,0,-2, 1,0,-1};
	vector<int>y = {1,2,1,0,0,0,-1,-2,-1};
	SobelFliter_axis(x);
	SobelFliter_axis(y);
	SobelFliter_axisXY(x, y);

}


void Image::image_writeRGB()
{

	
	for(int i = 0; i < height; i++){
		for(int j = 0; j < width; j++){
			Vec3b &color = img.at<Vec3b>(i,j);//BGR
			color[0] = pixelsRGB[i * width + j].B;
			color[1] = pixelsRGB[i * width + j].G;
			color[2] = pixelsRGB[i * width + j].R;
		}	
	}
    
	imwrite(output_file, img);

}


void Image::image_writeGrey()
{
	Mat output(height, width, CV_8UC1, pixelsGrey);
	imwrite(output_file, output);

}