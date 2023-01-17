PROG = odot
VERSION ?= 0.2.1

SHELL = /bin/bash

DESTDIR ?= 
PREFIX ?= $(DESTDIR)/usr
BINDIR ?= $(PREFIX)/bin
LIBDIR ?= $(PREFIX)/lib
MANDIR ?= $(PREFIX)/share/man/man1

FILES ?= $(wildcard *.c) 
HEADERS ?= $(wildcard *.h)
OBJECTS ?= $(wildcard *.o)

CC ?= gcc
CFLAGS += -O2 -std=c17 -pipe
WARNINGS ?= -Werror -Wall -Wextra -Wpedantic -Wno-unused
CPPFLAGS += -I . 
LDFLAGS += -L .
LDLIBS +=
ALL_FLAGS = $(CPPFLAGS) $(CFLAGS) $(WARNINGS) $(LDFLAGS) $(LDLIBS)

.PHONY: all
all: $(FILES) $(HEADERS)
	$(CC) $(FILES) $(ALL_FLAGS) -o $(PROG)

.PHONY: install
install: $(PROG) $(PROG).1
	install -CDTm 755 $(PROG) $(BINDIR)/$(PROG)
	[[ -e $(PROG).1 ]] && gzip -fc $(PROG).1 > $(MANDIR)/$(PROG).1.gz

.PHONY: tar
tar: $(FILES) $(HEADERS) $(PROG).1 Makefile README LICENSE
	tar -g gzip -cf $(PROG)-$(VERSION).tar.gz $(FILES) $(HEADERS) $(PROG).1 Makefile README LICENSE

.PHONY: compile
compile: $(FILES)
	$(CC) $(FILES) $(ALL_FLAGS) -c

.PHONY: link
link: $(OBJECTS)
	$(CC) $(OBJECTS) $(ALL_FLAGS) -o $(PROG)

.PHONY: assemble
assemble: $(FILES)
	$(CC) $(FILES) $(ALL_FLAGS) -S

.PHONY: debug
debug: $(FILES)
	$(CC) $(FILES) $(ALL_FLAGS) -ggdb3 -Og -o $(PROG)

.PHONY: clean
clean: 
	[[ -f $(BINDIR)/$(PROG) ]] && rm $(BINDIR)/$(PROG)
	[[ -f $(PROG) ]] && rm $(PROG)

