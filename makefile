CXX = g++

CXXFLAGS = -std=c++11 -Wall -Wextra -O2

TARGET = generator

SOURCES = generator.cpp

all: $(TARGET)

$(TARGET): $(SOURCES)
	$(CXX) $(CXXFLAGS) -o $(TARGET) $(SOURCES)

clean:
	rm -f $(TARGET)

.PHONY: all clean