# Compiler and flags
CXX = clang++
CXXFLAGS = -std=c++17 -Wall `pkg-config --cflags opencv4`
LDFLAGS = `pkg-config --libs opencv4`

# Targets
all: image_processing

image_processing: main.o ImageProcessor.o
	$(CXX) $(CXXFLAGS) -o image_processing main.o ImageProcessor.o $(LDFLAGS)

main.o: main.cpp ImageProcessor.h
	$(CXX) $(CXXFLAGS) -c main.cpp

ImageProcessor.o: ImageProcessor.cpp ImageProcessor.h
	$(CXX) $(CXXFLAGS) -c ImageProcessor.cpp

clean:
	rm -f *.o image_processing
