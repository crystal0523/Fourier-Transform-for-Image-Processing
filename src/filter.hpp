#ifndef FILTER_HPP
#define FILTER_HPP

#include <iostream>
#include <cmath>
#define PI 3.14159265

using namespace std;

class GaussianKernel
{
public:
	int radius;
	int dim;
	double *matrix;
	double sigma;
	GaussianKernel(const int r, const double s):radius(r), sigma(s)
	{
		dim = 2 * radius + 1;
		matrix = new double [dim * dim];
	}
	~GaussianKernel()
	{
		cout << "call of GaussianKernel destructor" << endl;
		delete [] matrix;
	}
	void Calculation();
};

double gauss_2d(const int x,  const int y,  const double sigma);

#endif //FILTER_H