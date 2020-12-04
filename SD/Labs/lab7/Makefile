INSTALL=sudo apt-get install

all: build run

build: lab07

lab07: schelet.c
	gcc schelet.c -o lab07

run: build
	./lab07

install:
	$(INSTALL) graphviz

clean:
	rm -rf *.png
	rm -rf *.dot
	rm -rf *.txt
	rm -rf lab07