build: encoder

encoder: encoder.o
	gcc -Wall encoder.o -o encoder
encoder.o: encoder.c
	gcc -Wall -c encoder.c
	
run: encoder
	./encoder
clean:
	rm -f encoder.o encoder