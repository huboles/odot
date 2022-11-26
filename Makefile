SHELL = /bin/bash
PROG = odot
PREFIX ?= /usr
BINDIR ?= $(PREFIX)/bin
SHAREDIR ?= $(HOME)/.local/share


install : main.c
	sudo gcc main.c -o '$(BINDIR)/$(PROG)'
	[[ ! -d '$(SHAREDIR)/$(PROG))' ]] && mkdir -p '$(SHAREDIR)/$(PROG)'

clean : 
	rm -rf '$(SHAREDIR)/$(PROG)'

