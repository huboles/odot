SHELL = /bin/bash
PREFIX = /usr
DESTDIR = $(PREFIX)/bin

PROG = odot

CC = gcc
CFILE = $(PROG).c database.c actions.c function.c
HEADER = $(PROG).h sqlite3.h
OBJECTS = $(PROG).o database.o actions.o function.o sqlite3.o
LDFLAGS = -L .
LDLIBS = -lpthread
CFLAGS = -O2
WARNINGS = -Werror -Wall -Wextra -Wpedantic -Wconversion -Wformat=2 -Wformat-signedness -Wstrict-prototypes -Wshadow -Wno-unused
CPPFLAGS = -I . 
ALL_CFLAGS = $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $(LDLIBS) $(WARNINGS)

sql: sqlite3.c
	$(CC) sqlite3.c $(CFLAGS) -c

header: $(HEADER)
	$(CC) $(HEADER) $(CFLAGS) -c

compile: $(CFILE)
	$(CC) $(CFILE) $(CFLAGS) -c

link: $(OBJECTS)
	$(CC) $(OBJECTS) $(CFLAGS) -o $(PROG)

build: $(CFILE) $(HEADER) sqlite3.c
	$(CC) $(CFILE) sqlite3.c $(CFLAGS) -o $(PROG)

install: $(CFILE) $(HEADER) sqlite3.c
	$(CC) $(CFILE) sqlite3.c $(CFLAGS) -o $(PROG)
	install -CDTm 755 $(PROG) $(DESTDIR)/$(PROG)

debug: $(CFILE)
	$(CC) $(CFILE) sqlite3.o $(CFLAGS) -ggdb3 -Og -o $(PROG)

clean: 
	rm *.gch *.o
	[[ -f $(PROG) ]] && rm $(PROG)
	[[ -f $(DESTDIR)/$(PROG) ]] && sudo rm $(DESTDIR)/$(PROG)

dbclean:
	rm *.db

