#include "image.hpp"

void Image::image_load() 
{
	//Read image info
	FILE *file = fopen(IFile, "r");
	if(fscanf(file, "%s", header)!=1){ 
		cout << "read header error" << endl;
		exit(1);
	}
	if(fscanf(file, "%d %d %d", &(width), &(height), &(color_depth))!=3){
		cout << "read info error" << endl;
		exit(1);
	}

	// Alocate memory for pixels
	pixels = new Pixel*[height];
	for(int i = 0; i < height; i++)
		pixels[i] = new Pixel[width];

	// Read pixels
	for(int i = 0; i < height; i++)
		for(int j = 0; j < width; j++){
			if(fscanf(file, "%c%c%c", &(pixels[i][j].R), &(pixels[i][j].G), &(pixels[i][j].B))!=3){
				cout << "read pixel error" << endl;
				exit(1);
			}
		}
			
	// Close file
	fclose(file);

}


void Image::check()
{
	for(int i = 0; i < height; i++)
		for(int j = 0; j < width; j++)
			cout << "r: "<< pixels[i][j].R << " g: "<< pixels[i][j].G << " b: " << pixels[i][j].B;
}


//Apply a filter to the image
void Image::apply_to_pixel(const int x, const int y, const GaussianKernel& kernel)
{
	if(x < kernel.radius || y < kernel.radius || x >= width - kernel.radius || y >= height - kernel.radius) return;

	Pixel res;
	res.R = res.G = res.B = 0;
	double fil;

	for(int i = -kernel.radius; i <= kernel.radius; i++) 
		for(int j = -kernel.radius; j <= kernel.radius; j++) 
		{
			fil = kernel.matrix[i + kernel.radius][j + kernel.radius];
			res.R += fil * pixels[y + i][x + j].R;
			res.G += fil * pixels[y + i][x + j].G;
			res.B += fil * pixels[y + i][x + j].B;
		}
	
	pixels[y][x].R = res.R;
	pixels[y][x].G = res.G;
	pixels[y][x].B = res.B;
}	

void Image::GaussianFliter(const GaussianKernel& kernel)
{
	for(int y = 0; y < height; y++)
		for(int x = 0; x < width; x++)
			apply_to_pixel(x, y, kernel);
}


void Image::image_write()
{
	FILE *file = fopen(OFile, "w");
	fprintf(file, "%s\n%d %d\n%d", header, width, height, color_depth);
	
	for(int i = 0; i < height; i++)
		for(int j = 0; j < width; j++)
			fprintf(file, "%c%c%c", pixels[i][j].R, pixels[i][j].G, pixels[i][j].B);
		
	fprintf(file, "%d", EOF);
	fclose(file);
}
	



