CXX = g++
CXXFLAGS = -Wall -Wextra

all:		client.out

client.out:		client.o
	$(CXX) $(CXXFLAGS) client.o -o client.out

client.o:	client.h client.cpp
	$(CXX) $(CXXFLAGS) client.cpp -c -o client.o
