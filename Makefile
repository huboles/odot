SHELL = /bin/zsh
PROG = todo
PREFIX ?= /home/huck/.local/bin
TODOLIST = /home/huck/info/notes/todo

install : main.c input.c file.c
	gcc *.c -o '$(PREFIX)/$(PROG)'

header : todo.h
	gcc *.h

clean : 
	rm *.gch
	rm "$(PREFIX)/$(PROG)"
	cp $(TODOLIST).md $(TODOLIST)

test :
	todo
	todo -n something
	todo -d stuff to do now
	todo -ns stuff to do 
	todo -ds stuff to do
