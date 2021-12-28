#ifndef FILTER_HPP
#define FILTER_HPP

#include <iostream>
#include <cmath>
#define PI 3.14159265

using namespace std;


double gauss_2d(const int x,  const int y,  const double sigma)
{
	double result = 1.0 / (2 * PI * sigma * sigma);
	result *= exp(-(x*x+y*y)/(2 * sigma * sigma));
	return result;
}


class GaussianKernel
{
public:
	
	GaussianKernel(const int r, const double s):radius(r), sigma(s)
	{
		dim = 2 * radius + 1;
		if(dim)
		{
			matrix = new double[dim * dim];
			for(int i=0;i<dim;++i)
			{
				for(int j=0;j<dim;++j)
				{
					matrix[i*dim+j] = 0;
				}
			}
		}
		else matrix = nullptr;
	}
	/*
	GaussianKernel(GaussianKernel const & other)
    {
		cout << "call of copy constructor" << endl;
        for (size_t i=0; i<dim; ++i)
        {
            for (size_t j=0; j<dim; ++j)
            {
                (*this).matrix[i*dim+j] = other.matrix[i*dim+j];
            }
        }
    }

    GaussianKernel & operator=(GaussianKernel const & other)
    {
		cout << "call of copy assignment" << endl;
        if (this == &other) { return *this; }
        
        for (size_t i=0; i<dim; ++i)
        {
            for (size_t j=0; j<dim; ++j)
            {
                (*this).matrix[i*dim+j] = other.matrix[i*dim+j];
            }
        }
       
        return *this;
    }

    GaussianKernel(GaussianKernel && other)
    {
		cout << "call of move constructor" << endl;
        std::swap(matrix, other.matrix);
    }

    GaussianKernel & operator=(GaussianKernel && other)
    {
		cout << "call of move assignment" << endl;
        if (this == &other) { return *this; }
        std::swap(matrix, other.matrix);
        return *this;
    }*/

	~GaussianKernel()
	{
		cout << "call of GaussianKernel destructor" << endl;
		delete [] matrix;
	}
	double operator() (int row, int col) const { return matrix[row * dim + col]; }
	
	void PrintKernel()
	{
		for(int i = 0; i < dim; i++)
		{
			for(int j = 0; j < dim; j++)
			{
				cout<< matrix[i * dim + j] << " ";
			}
			cout << endl;
		}

	}
	
	void Calculation()
	{
		double sum = 0.0;
		for(int i = -radius; i <= radius; i++)
			for(int j = -radius; j <= radius; j++) {
				matrix[(i + radius ) * dim + j + radius] = gauss_2d(j, i, sigma);
				sum += matrix[(i + radius) * dim + j +radius];
			}
		cout << endl;
		// normalization
		for(int i = 0; i < dim; i++)
			for(int j = 0; j < dim; j++)
			{
				matrix[i * dim + j] /= sum;
			}

	}
	

	int radius;
	int dim;
	double* matrix = nullptr;
	double sigma;

	
};



#endif //FILTER_H