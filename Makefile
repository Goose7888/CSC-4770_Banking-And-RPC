TARGETS = client virtual_bank bank1 bank2
CLIENT_TARGETS = client .o
BANK1_TARGETS = virtual_bank_bank1.o bank1
BANK2_TARGETS = virtual_bank_bank2.o bank2

VBANK_OBJECTS = virtual_bank_server.o  vbank_svc.o virtual_bank.o
LD = g++
CXXFLAGS = -I/usr/include/tirpc
LDFLAGS = -ltirpc -lnsl

all : $(TARGETS)

$(CLIENT_TARGETS) :
	$(MAKE) -C ./virtual_bank_server
	for f in $(CLIENT_TARGETS); do cp ./virtual_bank_server/$$f .; done

$(BANK1_TARGETS) :
	$(MAKE) -C . -f Makefile.bank1

$(BANK2_TARGETS) :
	$(MAKE) -C . -f Makefile.bank2

virtual_bank : $(VBANK_OBJECTS)
	$(LD) -o virtual_bank $(CXXFLAGS) $(LDFLAGS) $(VBANK_OBJECTS)

clean :
	$(MAKE) -C virtual_bank_server clean
	$(MAKE) -C . -f ./Makefile.bank1 clean
	$(MAKE) -C . -f ./Makefile.bank2 clean
	$(RM) $(TARGETS) $(CLIENT_TARGETS) $(BANK1_TARGETS) $(BANK2_TARGETS) $(VBANK_OBJECTS)
