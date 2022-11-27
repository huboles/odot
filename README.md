# odot
Todo manager written in C

Extremely basic to use, simply call ***odot*** with a task to add or
remove it from the list, or call ***odot*** all by iteself to see the
current todo list in alphabetical order.

* Usage:

    - Add or remove a task from list:
 
            $ odot [task]  
    
    - Show list:
 
            $ odot 
    
* Installation:
    - Arch Linux: Available in the AUR

    - Manual Installation:

            $ git clone https://github.com/huboles/odot.git
            $ cd odot
            $ sudo cc main.c -o /usr/bin/odot
            $ mkdir $HOME/.local/state/odot

***odot*** stores current and completed tasks in plaintext .txt files, located at
$HOME/.local/state/odot.

