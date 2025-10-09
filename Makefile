TARGETS = client.out vbank.out bank1.out

all : $(TARGETS)

client.out :
	$(MAKE) -C client
	cp client/client client.out

vbank.out :
	$(MAKE) -C vbank
	cp vbank/vbank vbank.out

bank1.out :
	$(MAKE) -C bank1
	cp bank1/bank1 bank1.out

clean :
	#$(MAKE) -C client clean
	#$(MAKE) -C vbank clean
	#$(MAKE) -C bank1 clean
	#$(MAKE) -C bank2 clean
	$(RM) *.out
