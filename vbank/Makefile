
VBANK = vbank

# user-created source files
SOURCES_VBANK.cpp = virtual_bank.cpp
SOURCES.h = virtual_bank.h
SOURCES_DIR.x = ../shared
SOURCES_VBANK.x = ../shared/vbank.x
SOURCES_BANK1.x = ../shared/bank1.x
SOURCES_BANK2.x = ../shared/bank2.x

# rpcgen-generated source files
TARGETS_VBANK.c = vbank_svc.c vbank_xdr.c
TARGETS_VBANK = ../shared/vbank.h vbank_svc.c vbank_xdr.c

# objects defines from all source files
OBJECTS_VBANK = $(TARGETS_VBANK.c:%.c=%.o) $(SOURCES_VBANK.cpp:%.cpp=%.o)
OBJECTS_BANK1 =
OBJECTS_BANK2 =

# compiler, linker, and rpcgen configuration
CC = gcc
CXX = g++
LINK.c = g++
CFLAGS += -g -I/usr/include/tirpc
CXXFLAGS += -g -I/usr/include/tirpc
LDLIBS += -lnsl -ltirpc
RPCGENFLAGS = -N

# rules to make targets
all : $(VBANK)

$(TARGETS_VBANK) : $(SOURCES_VBANK.x)
	rpcgen $(RPCGENFLAGS) $(SOURCES_VBANK.x)
	mv ../shared/vbank_svc.c ../shared/vbank_xdr.c .
	$(RM) ../shared/vbank_clnt.c

$(OBJECTS_VBANK) : $(SOURCES_VBANK.c) $(SOURCES_VBANK.h) $(TARGETS_VBANK.c)

$(VBANK) : $(OBJECTS_VBANK) $(OBJECTS_BANK1) $(OBJECTS_BANK2)
	$(LINK.c) -o $(VBANK) $(OBJECTS_VBANK) $(OBJECTS_BANK1) $(OBJECTS_BANK2) $(LDLIBS)

clean:
	$(RM) $(TARGETS) $(OBJECTS_VBANK) $(CLIENT) *.o
