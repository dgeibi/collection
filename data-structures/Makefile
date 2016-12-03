VPATH := graph:vendor:queue:polish-notation
CC := g++
CFLAGS := -Wall -std=gnu++11
graph-objects := graph.o queue.o dg_test.o
pn-objects := pn_test.o polish-notation.o

all : beautify dg_test.out pn_test.out

pn_test.out : $(pn-objects)
	$(CC) $(CFLAGS) -o $@ $^

dg_test.out : $(graph-objects)
	$(CC) $(CFLAGS) -o $@ $^

$(graph-objects) : miniunit.h queue.h

graph.o dg_test.o : graph.h

%.o : %.cpp
	$(CC) $(CFLAGS) -o $@ -c $<

beautify: uncrustify.cfg
	find . -type f -name '*.cpp' -exec uncrustify -c $< --no-backup "{}" \;
	find . -type f -name '*.h' -exec uncrustify -c $< --no-backup "{}" \;

clean :
	rm -f *.o *.out

.PHONY : clean beautify
