SHELL = /bin/zsh
PROG = todo
PREFIX ?= /usr/local/bin
TODOLIST = $(HOME)/.local/share/odot/todo

install : main.c input.c file.c dialogue.c func.c
	gcc *.c -o '$(PREFIX)/$(PROG)'
	[[ ! -d $(TODOLIST) ]] && mkdir -p $(TODOLIST)

header : todo.h
	gcc *.h

clean : 
	rm *.gch
	rm "$(PREFIX)/$(PROG)"

