all: count

count: main.o libcount.a
	gcc -g -Wall -o count main.o libcount.a

main.o: main.c readchar_R.h count_M.h
	gcc -g -Wall -o main.o main.c
readchar_R.o: readchar_R.c readchar_R.h
	gcc -g -Wall -o readchar_R.o readchar_R.c
count_M.o: count_M.c count_M.h
	gcc -g -Wall -o count_M.o count_M.c
libcount.a: readchar_R.o count_M.o 
	ar -r libcount.a readchar_R.o count_M.o

clean:
	rm -f main.o libcount.a count
	rm -f readchar_R.o 
	rm -f count_M.o
	rm -f *.swp
	
