SHELL = /bin/bash
PREFIX = /usr
DESTDIR = $(PREFIX)/bin

PROG = odot

CC = gcc
CFILE = $(PROG).c database.c
HEADER = $(PROG).h sqlite3.h
OBJECTS = $(PROG).o database.o task.o sqlite3.o
LDFLAGS = -L .
LDLIBS = -lpthread
CFLAGS = -Wall -Wextra -O2
CPPFLAGS = -I . 
ALL_CFLAGS = $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $(LDLIBS)

sql: sqlite3.c
	$(CC) sqlite3.c $(CFLAGS) -c

header: $(HEADER)
	$(CC) $(HEADER) $(CFLAGS) -c

compile: $(CFILE)
	$(CC) $(CFILE) $(CFLAGS) -c

link: $(OBJECTS)
	$(CC) $(OBJECTS) $(CFLAGS) -o $(PROG)

build: $(CFILE) $(HEADER) sqlite3.o
	$(CC) $(CFILE) sqlite3.o $(CFLAGS) -o $(PROG)

install: $(CFILE) $(HEADER) sqlite3.o
	$(CC) $(CFILE) sqlite3.o $(CFLAGS) -o $(DESTDIR)/$(PROG)

debug: $(CFILE)
	$(CC) $(CFILE) sqlite3.o $(CFLAGS) -ggdb3 -Og -o $(PROG)

clean: 
	rm *.gch *.o
	[[ -f $(PROG) ]] && rm $(PROG)
	[[ -f $(DESTDIR)/$(PROG) ]] && sudo rm $(DESTDIR)/$(PROG)

dbclean:
	rm *.db

