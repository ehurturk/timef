INSTALL_PATH?=/usr/local

all : timef

timef: timef.c
	gcc -o timef timef.c 

install:
	@echo "\033[0;32mChecking bin directory in the system...\033[0m"
	mkdir -p $(INSTALL_PATH)/bin
	@echo "\033[0;32mFound the bin directory, installing the binary output...\033[0m"
	cp ./timef $(INSTALL_PATH)/bin/
	@echo "\033[1;32mSuccessfully installed the executable into the system\033[0m"

uninstall:
	rm -rf $(INSTALL_PATH)/bin/timef
