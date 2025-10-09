
CLIENT = client

# user-created source files
SOURCES_CLNT.cpp = client.cpp
SOURCES_CLNT.h = client.h
SOURCES_DIR.x = ../shared
SOURCES.x = ../shared/vbank.x

# rpcgen-generated source files
TARGETS_CLNT.c = vbank_clnt.c vbank_xdr.c
TARGETS = ../shared/vbank.h vbank_clnt.c vbank_xdr.c

# objects defines from all source files
OBJECTS_CLNT = $(SOURCES_CLNT.c:%.c=%.o) $(TARGETS_CLNT.c:%.c=%.o) $(SOURCES_CLNT.cpp:%.cpp=%.o)

# compiler, linker, and rpcgen configuration
CC = gcc
CXX = g++
LINK.c = g++
CFLAGS += -g -I/usr/include/tirpc
CXXFLAGS += -g -Wall -Wextra -I/usr/include/tirpc
LDLIBS += -lnsl -ltirpc
RPCGENFLAGS = -N

# rules to make targets
all : $(CLIENT)

$(TARGETS) : $(SOURCES.x)
	rpcgen $(RPCGENFLAGS) -l -o vbank_clnt.c $(SOURCES.x)
	rpcgen $(RPCGENFLAGS) -c -o vbank_xdr.c $(SOURCES.x)
	rpcgen $(RPCGENFLAGS) -h -o ../shared/vbank.h $(SOURCES.x)

$(OBJECTS_CLNT) : $(SOURCES_CLNT.c) $(SOURCES_CLNT.h) $(TARGETS_CLNT.c)

$(CLIENT) : $(OBJECTS_CLNT)
	$(LINK.c) -o $(CLIENT) $(OBJECTS_CLNT) $(LDLIBS)

clean:
	$(RM) $(TARGETS) $(OBJECTS_CLNT) $(CLIENT) *.o
