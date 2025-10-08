
SERVER = bank1

# user-created source files
SOURCES_SVC.cpp = bank1_server.cpp
SOURCES_SVC.h = bank1_server.h
SOURCES.x = ../shared/bank1.x

# rpcgen-generated source files
TARGETS_SVC.c = bank1_svc.c bank1_xdr.c
TARGETS = ../shared/bank1.h bank1_svc.c bank1_xdr.c

# objects defines from all source files
OBJECTS_SVC = $(TARGETS_SVC.c:%.c=%.o) $(SOURCES_SVC.cpp:%.cpp=%.o)

# compiler, linker, and rpcgen configuration
CC = gcc
CXX = g++
LINK.c = g++
CFLAGS += -g -I/usr/include/tirpc
CXXFLAGS += -g -Wall -Wextra -I/usr/include/tirpc
LDLIBS += -lnsl -ltirpc -lsqlite3
RPCGENFLAGS = -N

# rules to make targets
all : $(SERVER)

$(TARGETS) : $(SOURCES.x)
	rpcgen $(RPCGENFLAGS) $(SOURCES.x)
	mv ../shared/bank1_svc.c ../shared/bank1_xdr.c .
	$(RM) ../shared/bank1_clnt.c

$(OBJECTS_SVC) : $(SOURCES_SVC.c) $(SOURCES_SVC.h) $(TARGETS_SVC.c)

$(SERVER) : $(OBJECTS_SVC)
	$(LINK.c) -o $(SERVER) $(OBJECTS_SVC) $(LDLIBS)

clean:
	$(RM) $(TARGETS) $(OBJECTS_CLNT) $(OBJECTS_SVC) $(CLIENT) $(SERVER) *.o
