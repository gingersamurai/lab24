run : main
	./main
main : token.o tree.o main.o
	gcc main.o token.o tree.o -o main

token.o : token.c
	gcc -c token.c -o token.o

tree.o : tree.c
	gcc -c tree.c -o tree.o

main.o : main.c
	gcc -c main.c -o main.o

clean :
	rm -f main -f main.o -f token.o -f tree.o