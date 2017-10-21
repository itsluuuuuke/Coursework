all: ushell

ushell: example.o parser.o
	gcc -g -Wall  -o ushell example.o parser.o
example.o: example.c parser.h
	gcc -g -Wall -c -o example.o example.c
parser.o: parser.c parser.h
	gcc -g -Wall -c -o parser.o parser.c 

clean:
	rm -rf *.o
