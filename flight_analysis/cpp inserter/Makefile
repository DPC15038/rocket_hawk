CXX =g++
CXXFLAGS = -Wall --std=c++11 -g
OBJECTS = main.o
all: myproject

myproject:$(OBJECTS)
	$(CXX) $(CXXFLAGS) -o myproject $(OBJECTS)

main.o: html_inserter.cpp html_inserter.hpp
	$(CXX) $(CXXFLAGS) -c html_inserter.cpp -o main.o

clean:
	rm myproject $(OBJECTS)
