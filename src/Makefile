.PHONY: test agent server library clean

agent:
	$(MAKE) -C agent all

server:
	$(MAKE) -C server all

library:
	$(MAKE) -C library library
test:
	$(MAKE) -C test one

clean:
	$(MAKE) -C test clean
	$(MAKE) -C library clean
	$(MAKE) -C agent clean
	$(MAKE) -C server clean
