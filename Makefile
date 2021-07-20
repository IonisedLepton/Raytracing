CXX=g++
CXXFLAGS=-std=c++11 -g -O2
WARNINGS = -Wall -Wextra

SOURCES=src/main.cpp
OBJECTS=$(patsubst src/%.cpp,exec/%.o,$(SOURCES))
DEPENDS=$(patsubst src/%.cpp,exec/%.d,$(SOURCES))
TARGETS=exec/main.exe

.PHONY: all clean

all: $(TARGETS)

$(TARGETS): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(WARNINGS) $^ -o $@

-include $(DEPENDS)

exec/%.o: src/%.cpp
	$(CXX) $(CXXFLAGS) -MMD -MP -c $< -o $@

clean:
	rm -rf $(OBJECTS) $(DEPENDS) $(TARGETS)
