
CLIENT = client
VBANK = virtual_bank
BANK1 = bank1

# user-created source files
SOURCES_CLNT.cpp = client.cpp
SOURCES_CLNT.h = client.h
SOURCES_SVC.cpp = virtual_bank.cpp
SOURCES_SVC.h = virtual_bank.h
SOURCES.x = vbank.x

# rpcgen-generated source files
TARGETS_CLNT.c = vbank_clnt.c vbank_xdr.c
TARGETS_SVC.c = vbank_svc.c
TARGETS = vbank.h vbank_clnt.c vbank_svc.c vbank_xdr.c

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
RPCGENFLAGS = -N

# rules to make targets
all : $(CLIENT) $(VBANK) $(BANK1)

$(TARGETS) : $(SOURCES.x)
	rpcgen $(RPCGENFLAGS) $(SOURCES.x)

$(OBJECTS_CLNT) : $(SOURCES_CLNT.c) $(SOURCES_CLNT.h) $(TARGETS_CLNT.c)

$(OBJECTS_SVC) : $(SOURCES_SVC.c) $(SOURCES_SVC.h) $(TARGETS_SVC.c)

$(OBJECTS_BANK1) :

$(CLIENT) : $(OBJECTS_CLNT)
	$(LINK.c) -o $(CLIENT) $(OBJECTS_CLNT) $(LDLIBS)

$(VBANK) : $(OBJECTS_SVC)
	$(LINK.c) -o $(VBANK) $(OBJECTS_SVC) $(LDLIBS)

$(BANK1) : $(OBJECTS_BANK1)
	$(LINK.c) -o $(BANK1) $(OBJECTS_BANK1) $(LDLIBS)

clean:
	$(RM) $(TARGETS) $(OBJECTS_CLNT) $(OBJECTS_SVC) $(OBJECTS_BANK1) $(CLIENT) $(VBANK) $(BANK1) *.o
