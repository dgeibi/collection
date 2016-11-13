VPATH := graph:vendor:queue
CC := g++
objects := graph.o queue.o dg_test.o

all : dg_test.out

dg_test.out : $(objects)
	$(CC) -o $@ $^

$(objects) : miniunit.h queue.h

graph.o dg_test.o : graph.h

.PHONY : clean
clean :
	rm $(objects) *.out
