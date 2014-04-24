all: rolodex stack

rolodex: rolodex.o
	g++ rolodex.o -o rolodex
stack: stack.o
	g++ stack.o -o stack
rolodex.o: rolodex.cc
	g++ -c rolodex.cc
stack.o: Stack.cc Stack.h
	g++ -c Stack.cc