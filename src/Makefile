CXX = clang++
CFLAGS = -std=c++11 -O3 -m64 -fPIC -shared
opencv = `pkg-config opencv --cflags --libs`


pybind11 = `python3 -m pybind11 --includes`
suffix = `python3-config --extension-suffix`

.PHONY: all, clean

all: _image

_image: bind.cpp
	$(CXX) $(CFLAGS) $(pybind11) $^ -o _image$(suffix) $(opencv)

clean: 
	rm -rf *.o _image


	
