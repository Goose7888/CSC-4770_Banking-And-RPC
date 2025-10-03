CXX = g++
CXXFLAGS = -Wall -Wextra -lsqlite3 -g

all				:	bank_server.out

bank_server.out	:	bank_server.o
	$(CXX) $(CXXFLAGS) -o bank_server.out bank_server.o

bank_server.o	: bank_server.cpp bank_server.h
	$(CXX) $(CXXFLAGS) -c -o bank_server.o bank_server.cpp

clean:
	rm -f *.o *.out

run: bank_server.out
	./bank_server.out --bank1
