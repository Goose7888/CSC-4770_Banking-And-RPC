all:	client.out bank_server.out

client.out:
	$(MAKE) -C client
	cp client/client.out client.out

bank_server.out:
	$(MAKE) -C server
	cp server/bank_server.out bank_server.out

clean:
	$(MAKE) -C client clean
	$(MAKE) -C server clean
	rm -f *.out
