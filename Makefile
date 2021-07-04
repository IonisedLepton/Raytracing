CXX=g++
CXXFLAGS=-std=c++11 -g -O2

TARGETS=exec/main.exe

$(TARGETS): src/main.cpp
	$(CXX) $($CXXFLAGS) -o $(@) $<

run: $(TARGETS)
	./$(TARGETS) > output/triangle.ppm
