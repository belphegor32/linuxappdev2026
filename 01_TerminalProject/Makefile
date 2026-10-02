DESTDIR =

Show: Show.c
	cc Show.c -o Show -lncursesw

install: Show
	install -D Show $(DESTDIR)/usr/bin/Show

clean:
	rm -f *~ *.o Show a.out