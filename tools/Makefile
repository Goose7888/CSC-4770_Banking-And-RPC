TARGET = init_db

SOURCES.cpp = bank_init.cpp
SOURCES = bank_init.cpp bank_init.h

OBJECTS = $(SOURCES.cpp:%.cpp=%.o)

CXX = g++
CXXFLAGS = -Wall -Wextra -g
LD = g++
LDFLAGS = -lsqlite3

all : $(TARGET)

$(TARGET) : $(OBJECTS)
	$(LD) -o $(TARGET) $(OBJECTS) $(LDFLAGS)

$(OBJECTS) : $(SOURCES)

clean :
	$(RM) $(TARGET) $(OBJECTS)
