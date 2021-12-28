import _image
import numpy as np
import pytest
import unittest



class Test(unittest.TestCase):
    def make_kernel(self):
        kernel = _image.GaussianKernel(1,0.707)
        kernel.Calculation()

        return kernel


    def make_image(self):
        img = _image.Image("../img/Lenna.png", "filter.png")
        img.image_load()

        return img


    def test_kernel(self):
        # 3*3 Gaussian Fliter
        x, y = np.mgrid[-1:2, -1:2]
        gaussian_kernel = np.exp(-(x**2+y**2))
        #Normalization
        gaussian_kernel = gaussian_kernel / gaussian_kernel.sum()
        kernel = self.make_kernel()
        for i in range(3):
            for j in range(3):
                assert round(kernel[i,j], 3) == round(gaussian_kernel[i,j], 3)

    """def test_Gaussian():
        img = make_image()
        img.GaussianFliter(kernel)
    def test_Sobel():
        img = make_image()
        img.GaussianFliter(kernel)"""
       