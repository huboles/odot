SHELL = /bin/bash
DESTDIR = 
PREFIX = $(DESTDIR)/usr
BINDIR = $(PREFIX)/bin
MANDIR = $(PREFIX)/share/man/man1

PROG = odot

CC = gcc
CFILE = $(PROG).c database.c actions.c function.c
HEADER = $(PROG).h sqlite3.h
OBJECTS = $(PROG).o database.o actions.o function.o sqlite3.o
LDFLAGS = -L .
LDLIBS = -lpthread
CFLAGS = -O2 
WARNINGS = -Werror -Wall -Wextra -Wpedantic -Wno-unused
CPPFLAGS = -I . 
ALL_CFLAGS = $(CFLAGS) $(CPPFLAGS) $(LDFLAGS) $(LDLIBS) $(WARNINGS)

sql: sqlite3.c
	$(CC) sqlite3.c $(ALL_CFLAGS) -c

header: $(HEADER)
	$(CC) $(HEADER) $(ALL_CFLAGS) -c

compile: $(CFILE)
	$(CC) $(CFILE) $(ALL_CFLAGS) -c

link: $(OBJECTS)
	$(CC) $(OBJECTS) $(ALL_CFLAGS) -o $(PROG)

build: $(CFILE) $(HEADER) sqlite3.c
	$(CC) $(CFILE) sqlite3.c $(ALL_CFLAGS) -o $(PROG)

install: $(CFILE) $(HEADER) sqlite3.c
	$(CC) $(CFILE) sqlite3.c $(ALL_CFLAGS) -o $(PROG)
	install -CDTm 755 $(PROG) $(BINDIR)/$(PROG)
	gzip -cf $(PROG).1 > $(PROG).1.gz
	install -CDTm 644 $(PROG).1.gz $(MANDIR)/$(PROG).1

debug: $(CFILE)
	$(CC) $(CFILE) sqlite3.o $(CFLAGS) -ggdb3 -Og -o $(PROG)

clean: 
	[[ -f $(PROG) ]] && rm $(PROG)
	[[ -f $(DESTDIR)/$(PROG) ]] && sudo rm $(BINDIR)/$(PROG)

dbclean:
	rm *.db

