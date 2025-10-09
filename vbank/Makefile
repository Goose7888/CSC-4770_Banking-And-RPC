
VBANK = vbank

# user-created source files
SOURCES_VBANK.cpp = virtual_bank.cpp
SOURCES_VBANK.h = virtual_bank.h
SOURCES_BANK1.cpp = ../bank1/bank1_server.cpp
SOURCES_BANK1.h = ../bank1/bank1_server.h
SOURCES_DIR.x = ../shared
SOURCES_VBANK.x = ../shared/vbank.x
SOURCES_BANK1.x = ../shared/bank1.x
SOURCES_BANK2.x = ../shared/bank2.x

# rpcgen-generated source files
TARGETS_VBANK.c = vbank_svc.c vbank_xdr.c
TARGETS_VBANK = ../shared/vbank.h vbank_svc.c vbank_xdr.c
TARGETS_BANK1.c = bank1_clnt.c bank1_xdr.c
TARGETS_BANK1 = ../shared/bank1.h bank1_clnt.c bank1_xdr.c

# objects defines from all source files
OBJECTS_VBANK = $(TARGETS_VBANK.c:%.c=%.o) $(SOURCES_VBANK.cpp:%.cpp=%.o)
OBJECTS_BANK1 = $(TARGETS_BANK1.c:%.c=%.o) $(SOURCES_BANK1.cpp:%.cpp=%.o)
OBJECTS_BANK2 =

# compiler, linker, and rpcgen configuration
CC = gcc
CXX = g++
LINK.c = g++
CFLAGS += -g -I/usr/include/tirpc
CXXFLAGS += -g -I/usr/include/tirpc
LDLIBS += -lnsl -ltirpc -lsqlite3
RPCGENFLAGS = -N

# rules to make targets
all : $(VBANK)

$(TARGETS_VBANK) : $(SOURCES_VBANK.x)
	rpcgen $(RPCGENFLAGS) $(SOURCES_VBANK.x)
	mv ../shared/vbank_svc.c ../shared/vbank_xdr.c .
	$(RM) ../shared/vbank_clnt.c

$(OBJECTS_VBANK) : $(SOURCES_VBANK.c) $(SOURCES_VBANK.h) $(TARGETS_VBANK.c) $(TARGETS_BANK1)

$(VBANK) : $(OBJECTS_VBANK) $(OBJECTS_BANK1) $(OBJECTS_BANK2)
	$(LINK.c) -o $(VBANK) $(OBJECTS_VBANK) $(OBJECTS_BANK1) $(OBJECTS_BANK2) $(LDLIBS)

$(TARGETS_BANK1) : $(SOURCES_BANK1.x)
	$(RM) $(TARGETS_BANK1)
	rpcgen $(RPCGENFLAGS) -l -o bank1_clnt.c $(SOURCES_BANK1.x)
	rpcgen $(RPCGENFLAGS) -c -o bank1_xdr.c $(SOURCES_BANK1.x)
	rpcgen $(RPCGENFLAGS) -h -o ../shared/bank1.h $(SOURCES_BANK1.x)

$(OBJECTS_BANK1) : $(SOURCES_BANK1.c) $(SOURCES_BANK1.h) $(TARGETS_BANK1)



clean:
	$(RM) $(TARGETS) $(OBJECTS_VBANK) $(CLIENT) *.o
