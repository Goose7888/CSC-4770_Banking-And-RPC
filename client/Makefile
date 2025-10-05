
CLIENT = client
SERVER = virtual_bank

# user-created source files
SOURCES_CLNT.cpp = client.cpp
SOURCES_CLNT.h = client.h
SOURCES_SVC.cpp = virtual_bank.cpp
SOURCES_SVC.h =
SOURCES_SVC.hpp = virtual_bank.hpp
SOURCES.x = vbank.x

# rpcgen-generated source files
TARGETS_CLNT.c = vbank_clnt.c
TARGETS_SVC.c = vbank_svc.c
TARGETS = vbank.h vbank_clnt.c vbank_svc.c

# objects defines from all source files
OBJECTS_CLNT = $(SOURCES_CLNT.c:%.c=%.o) $(TARGETS_CLNT.c:%.c=%.o) $(SOURCES_CLNT.cpp:%.cpp=%.o)
OBJECTS_SVC = $(SOURCES_SVC.c:%.c=%.o) $(TARGETS_SVC.c:%.c=%.o) $(SOURCES_SVC.cpp:%.cpp=%.o)

# compiler, linker, and rpcgen configuration
CC = gcc
CXX = g++
LINK.c = g++
CFLAGS += -g -I/usr/include/tirpc
CXXFLAGS += -g -Wall -Wextra -I/usr/include/tirpc
LDLIBS += -lnsl -ltirpc
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
