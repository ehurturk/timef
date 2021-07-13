INSTALL_PATH?=/usr/local

all : timef

timef: timef.c
	gcc -o timef timef.c 

install:
	echo "Checking bin directory in the system..."
	mkdir -p $(INSTALL_PATH)/bin
	echo "Found the bin directory, installing the binary output..."
	cp ./timef $(INSTALL_PATH)/bin/

uninstall:
	rm -rf $(INSTALL_PATH)/bin/timef
