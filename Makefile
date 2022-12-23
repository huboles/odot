SHELL = /bin/bash
PREFIX = /usr
DESTDIR = $(PREFIX)/bin

PROG = odot

CFILE = $(PROG).c database.c
HEADER = $(PROG).h sqlite3.h
OBJECTS = $(PROG).o database.o task.o sqlite3.o
CFLAGS = -Wall -lpthread

sql: sqlite3.c
	gcc sqlite3.c $(CFLAGS) -c

header: $(HEADER)
	gcc $(HEADER) $(CFLAGS) -c

compile: $(CFILE)
	gcc $(CFILE) $(CFLAGS) -c

link: $(OBJECTS)
	gcc $(OBJECTS) $(CFLAGS) -o $(PROG)

build: $(CFILE) $(HEADER) sqlite3.c
	gcc $(CFILE) $(HEADER) sqlite3.c $(CFLAGS) -o $(PROG)

install: $(CFILE) $(HEADER) $(SQLFILE)
	gcc $(CFILE) $(HEADER) $(SQLFILE) $(CFLAGS) -o $(DESTDIR)/$(PROG)

debug: $(CFILE)
	gcc $(CFILE) sqlite3.o $(CFLAGS) -g -o $(PROG)

clean: 
	rm *.gch *.o
	[[ -f $(PROG) ]] && rm $(PROG)
	[[ -f $(DESTDIR)/$(PROG) ]] && sudo rm $(DESTDIR)/$(PROG)

dbclean:
	rm *.db

