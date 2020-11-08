all: project
project: infix.o charstack.o stack.o list.o operations.o
	cc infix.o stack.o charstack.o list.o operations.o  -o project
operations.o: operations.c list.h operations.h
	cc -c operations.c 
infix.o: infix.c charstack.h stack.h operations.h
	cc -c infix.c 
stack.o: stack.c stack.h
	cc -c stack.c
charstack.o: charstack.c charstack.h
	cc -c charstack.c
list.o: list.c list.h
	cc -c list.c 
clean:
	rm *.o
