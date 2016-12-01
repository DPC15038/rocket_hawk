CXX =g++
CXXFLAGS = -Wall --std=c++11 -g
OBJECTS = main.o
all: myproject

myproject:$(OBJECTS)
	$(CXX) $(CXXFLAGS) -o myproject $(OBJECTS)

main.o: daily2.cpp myheader.hpp
	$(CXX) $(CXXFLAGS) -c daily2.cpp -o main.o

clean:
	rm myproject $(OBJECTS)
