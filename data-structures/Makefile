VPATH := ./LinkQueue:./vendor:./DirectedGraph
CC := g++
objects := Graph.o LQueue.o dg_test.o

all : dg_test.out

dg_test.out : $(objects)
	$(CC) -o $@ $^

$(objects) : miniunit.h LQueue.h

Graph.o dg_test.o : Graph.h

.PHONY : clean
clean :
	rm $(objects) *.out
