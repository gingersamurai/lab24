main : main.o token.o
	gcc main.o token.o -o main

main.o : main.c
	gcc -c main.c -o main.o

token.o : token.c
	gcc -c token.c -o token.o

clean :
	rm -f main -f main.o -f token.o