VPATH := graph:vendor:queue:polish-notation
CC := g++
CFLAGS := -Wall -std=gnu++11
graph-objects := graph.o dg_test.o
pn-objects := pn_test.o polish-notation.o

all : dg_test pn_test

pn_test : $(pn-objects)
	$(CC) $(CFLAGS) -o $@ $^

dg_test : $(graph-objects) queue.o
	$(CC) $(CFLAGS) -o $@ $^

$(graph-objects) : miniunit.h queue.h graph.h

$(pn_objects) : miniunit.h polish-notation.h

queue.o : miniunit.h queue.h

%.o : %.cpp
	$(CC) $(CFLAGS) -o $@ -c $<

beautify: uncrustify.cfg
	find . -type f -name '*.cpp' -exec uncrustify -c $< --no-backup "{}" \;
	find . -type f -name '*.h' -exec uncrustify -c $< --no-backup "{}" \;

clean :
	rm -f *.o *.out *_test

.PHONY : clean beautify
