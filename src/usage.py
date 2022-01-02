import _image

# initialize 
img = _image.Image("../img/Lenna.png", "GaussianFilter_Lenna.jpg")

# read image 
img.image_load()

# build gaussian kernel
kernel = _image.GaussianKernel(9,1)
kernel.Calculation()

# Apply gaussian filter
img.GaussianFilter(kernel)

"""
# initialize 
img = _image.Image("../img/Lenna.png", "SobelFilter_Lenna.jpg")

# read image 
img.image_load()

# transform RGB image to greyscale image
img.to_grey()

# Apply Sobel filter
img.SobelFilter()
# write image pixel to output
img.image_write()

"""
