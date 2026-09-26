CFLAGS = -Wall -fPIC

GENERATES = prog prog-a prog-so liboutput_static.a liboutput.so
TRASH = *.o *~ o.*

all: prog prog-a prog-so liboutput_static.a liboutput.so

%.o: %.c
	cc $(CFLAGS) $< -c -o $@

prog: const.o fun.o prog.o
	cc $^ -o $@

liboutput_static.a: fun.o const.o
	ar -rcs $@ $^

liboutput.so: fun.o const.o
	cc -shared $^ -o $@

prog-a: prog.o liboutput_static.a
	cc -L. prog.o -loutput_static -o $@

prog-so: prog.o liboutput.so
	cc -L. prog.o -loutput -o $@

fun.o: outlib.h
prog.o: outlib.h

test: all
	./prog > o.prog0 2>&1
	./prog-a > o.proga0 2>&1
	LD_LIBRARY_PATH=. ./prog-so > o.progso0 2>&1
	cmp o.prog0 o.proga0
	cmp o.prog0 o.progso0

	./prog qwe > o.prog1 2>&1
	./prog-a qwe > o.proga1 2>&1
	LD_LIBRARY_PATH=. ./prog-so qwe > o.progso1 2>&1
	cmp o.prog1 o.proga1
	cmp o.prog1 o.progso1

	./prog qwe ert asd > o.prog3 2>&1
	./prog-a qwe ert asd > o.proga3 2>&1
	LD_LIBRARY_PATH=. ./prog-so qwe ert asd > o.progso3 2>&1
	cmp o.prog3 o.proga3
	cmp o.prog3 o.progso3

clean:
	rm -f $(TRASH) $(GENERATES)