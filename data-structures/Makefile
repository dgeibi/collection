VPATH := graph:vendor:queue
CC := g++
CFLAGS := -Wall -std=gnu++11
objects := graph.o queue.o dg_test.o

all : dg_test.out

dg_test.out : $(objects)
	$(CC) $(CFLAGS) -o $@ $^

$(objects) : miniunit.h queue.h

graph.o dg_test.o : graph.h

%.o : %.cpp
	$(CC) $(CFLAGS) -o $@ -c $<

.PHONY : clean
clean :
	rm $(objects) *.out
