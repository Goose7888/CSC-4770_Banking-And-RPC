
CLIENT = client
VBANK = virtual_bank

# user-created source files
VBANK_SOURCES_CLNT.cpp = client.cpp
VBANK_SOURCES_CLNT.h = client.h
VBANK_SOURCES_SVC.cpp = virtual_bank.cpp
VBANK_SOURCES_SVC.h = virtual_bank.h
VBANK_SOURCES.x = vbank.x

# rpcgen-generated source files
VBANK_TARGETS_CLNT.c = vbank_clnt.c
VBANK_TARGETS_SVC.c = vbank_svc.c
VBANK_TARGETS = vbank.h vbank_clnt.c vbank_svc.c

# objects defines from all source files
VBANK_OBJECTS_CLNT = $(VBANK_SOURCES_CLNT.c:%.c=%.o) $(VBANK_TARGETS_CLNT.c:%.c=%.o) $(VBANK_SOURCES_CLNT.cpp:%.cpp=%.o)
VBANK_OBJECTS_SVC = $(VBANK_SOURCES_SVC.c:%.c=%.o) $(VBANK_TARGETS_SVC.c:%.c=%.o) $(VBANK_SOURCES_SVC.cpp:%.cpp=%.o)

# compiler, linker, and rpcgen configuration
CC = gcc
CXX = g++
LINK.c = g++
CFLAGS += -g -I/usr/include/tirpc
CXXFLAGS += -g -Wall -Wextra -I/usr/include/tirpc
LDLIBS += -lnsl -ltirpc
RPCGENFLAGS =

# rules to make targets
all : $(CLIENT) $(VBANK)

$(VBANK_TARGETS) : $(VBANK_SOURCES.x)
	rpcgen $(RPCGENFLAGS) $(VBANK_SOURCES.x)

$(VBANK_OBJECTS_CLNT) : $(VBANK_SOURCES_CLNT.c) $(VBANK_SOURCES_CLNT.h) $(VBANK_TARGETS_CLNT.c)

$(VABNK_OBJECTS_SVC) : $(VBANK_SOURCES_SVC.c) $(VBANK_SOURCES_SVC.h) $(VBANK_TARGETS_SVC.c)

$(CLIENT) : $(VBANK_OBJECTS_CLNT)
	$(LINK.c) -o $(CLIENT) $(VBANK_OBJECTS_CLNT) $(LDLIBS)

$(VBANK) : $(VBANK_OBJECTS_SVC)
	$(LINK.c) -o $(VBANK) $(VBANK_OBJECTS_SVC) $(LDLIBS)

clean:
	$(RM) $(VBANK_TARGETS) $(VBANK_OBJECTS_CLNT) $(VBANK_OBJECTS_SVC) $(CLIENT) $(VBANK) *.o
