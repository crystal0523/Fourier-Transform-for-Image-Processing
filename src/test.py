import _image
import numpy as np
import pytest
import unittest
import cv2


class Test(unittest.TestCase):
    def make_kernel(self):
        kernel = _image.GaussianKernel(1,0.8)
        kernel.Calculation()

        return kernel


    def make_image(self):
        img = _image.Image("../img/8k.jpg", "Gfilter_8k.jpg")
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


    def test_Gaussian(self):
        img = self.make_image()
        kernel = self.make_kernel()
        img.to_grey()
        img.GaussianFilter(kernel)

        img1 = cv2.imread("../img/8k.jpg")
        img1 = cv2.cvtColor(img1, cv2.COLOR_BGR2GRAY)
        img1 = cv2.GaussianBlur(img1, (3, 3), 0.8)

        for i in range(img.height):
            for j in range(img.width):
                print(img1[i,j])
                print(img[i, j])
                assert img1[i,j] == img[i, j]
               

    """def test_Sobel(self):
        img = make_image()
        
       