SHELL = /bin/zsh
PROG = odot
PREFIX ?= /usr/local/bin
ODOT = /home/huck/.local/share/odot
TODOLIST = $(ODOT)/todo

install : main.c input.c file.c 
	[[ ! -d $(TODOLIST) ]] && mkdir -p $(ODOT)
	gcc *.c -o '$(PREFIX)/$(PROG)'

header : odot.h
	gcc *.h

clean : 
	rm *.gch
	rm "$(PREFIX)/$(PROG)"

