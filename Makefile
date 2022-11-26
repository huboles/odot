SHELL = /bin/bash
PROG = odot
BINDIR ?= /bin
STATEDIR ?= $(HOME)/.local/state


install : main.c
	sudo gcc main.c -o '$(BINDIR)/$(PROG)'
	[[ ! -d '$(STATEDIR)/$(PROG))' ]] && mkdir -p '$(STATEDIR)/$(PROG)'

clean : 
	rm -rf '$(STATEDIR)/$(PROG)'

