
CLIENT = virtual_bank_bank1
SERVER = bank1

# user-created source files
SOURCES_CLNT.cpp =
SOURCES_CLNT.h =
SOURCES_SVC.cpp =
SOURCES_SVC.h =
SOURCES_SVC.hpp =
SOURCES.x = bank1.x

# rpcgen-generated source files
TARGETS_CLNT.c = bank1_clnt.c
TARGETS_SVC.c = bank1_svc.c
TARGETS = bank1.h bank1_clnt.c bank1_svc.c

# objects defines from all source files
OBJECTS_CLNT = $(SOURCES_CLNT.c:%.c=%.o) $(TARGETS_CLNT.c:%.c=%.o) $(SOURCES_CLNT.cpp:%.cpp=%.o)
OBJECTS_SVC = $(SOURCES_SVC.c:%.c=%.o) $(TARGETS_SVC.c:%.c=%.o) $(SOURCES_SVC.cpp:%.cpp=%.o)

# compiler, linker, and rpcgen configuration
CC = gcc
CXX = g++
LINK.c = g++
CFLAGS += -g -I/usr/include/tirpc
CXXFLAGS += -g -Wall -Wextra -I/usr/include/tirpc
LDLIBS += -lnsl -ltirpc -lsqlite3
RPCGENFLAGS =

# rules to make targets
all : $(CLIENT) $(SERVER)

$(TARGETS) : $(SOURCES.x)
	rpcgen $(RPCGENFLAGS) $(SOURCES.x)

$(OBJECTS_CLNT) : $(SOURCES_CLNT.c) $(SOURCES_CLNT.h) $(TARGETS_CLNT.c)

$(OBJECTS_SVC) : $(SOURCES_SVC.c) $(SOURCES_SVC.h) $(TARGETS_SVC.c)

$(CLIENT) : $(OBJECTS_CLNT)
	$(LINK.c) -o $(CLIENT) $(OBJECTS_CLNT) $(LDLIBS)

$(SERVER) : $(OBJECTS_SVC)
	$(LINK.c) -o $(SERVER) $(OBJECTS_SVC) $(LDLIBS)

clean:
	$(RM) $(TARGETS) $(OBJECTS_CLNT) $(OBJECTS_SVC) $(CLIENT) $(SERVER) *.o
