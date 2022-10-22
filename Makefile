SHELL = /bin/zsh
PROG = todo
PREFIX ?= /usr/local/bin
TODOLIST = $(HOME)/.local/share/odot/todo

install : main.c input.c file.c
	gcc *.c -o '$(PREFIX)/$(PROG)'

header : todo.h
	gcc *.h

clean : 
	rm *.gch
	rm "$(PREFIX)/$(PROG)"

test :
	todo
	todo -n something
	todo -d stuff to do now
	todo -ns stuff to do 
	todo -ds stuff to do
