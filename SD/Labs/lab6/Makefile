INSTALL=sudo apt-get install

all: build run

build: lab06

lab06: schelet.c
	gcc schelet.c -o lab06

run: build
	./lab06

install:
	$(INSTALL) graphviz

clean:
	rm -rf *.png
	rm -rf *.dot
	rm -rf *.txt
	rm -rf lab07