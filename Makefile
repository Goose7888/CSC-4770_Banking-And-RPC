TARGETS = client.out vbank.out bank1.out bank2.out init_db

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

bank2.out :
	$(MAKE) -C bank2
	cp bank2/bank2 bank2.out

init_db :
	$(MAKE) -C tools
	cp tools/init_db .

clean :
	$(MAKE) -C client clean
	$(MAKE) -C vbank clean
	$(MAKE) -C bank1 clean
	$(MAKE) -C bank2 clean
	$(MAKE) -C tools clean
	$(RM) $(TARGETS)

reset :
	$(MAKE) -C client clean
	$(MAKE) -C vbank clean
	$(MAKE) -C bank1 clean
	$(MAKE) -C bank2 clean
	$(MAKE) -C tools clean
	$(RM) $(TARGETS)
	$(RM) *.db

test : $(TARGETS) test_cases.sh
	$(RM) *.db
	./init_db --bank1
	./init_db --bank2
	./test_cases.sh
