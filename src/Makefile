CXX = g++
CFLAGS = -std=c++14 -O3 -m64

.PHONY: all, clean

all: target

target: main.cpp filter.cpp image.cpp
	$(CXX) $(CFLAGS) $^ -o $@


clean: 
	rm -rf *.o target


	
