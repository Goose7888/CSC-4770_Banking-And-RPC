TARGETS = client virtual_bank bank1 bank2
CLIENT_TARGETS = client virtual_bank_server.o
BANK1_TARGETS = virtual_bank_bank1.o bank1
BANK2_TARGETS = virtual_bank_bank2.o bank2

VBANK_OBJECTS = virtual_bank_server.o  vbank_svc.o virtual_bank.o
LD = g++
CXXFLAGS = -I/usr/include/tirpc
LDFLAGS = -ltirpc -lnsl

all : $(TARGETS)

$(VBANK_TARGETS) :
	$(MAKE) -C ./virtual_bank
	cp $(VBANK_TARGETS) .

$(BANK1_TARGETS) :
	$(MAKE) -C . -f Makefile.bank1

$(BANK2_TARGETS) :
	$(MAKE) -C . -f Makefile.bank2

clean :
	$(MAKE) -C virtual_bank clean
	$(MAKE) -C . -f ./Makefile.bank1 clean
	$(MAKE) -C . -f ./Makefile.bank2 clean
