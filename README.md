# odot
Todo manager written in C

Extremely basic to use, simply call ***odot*** with a task to add or
remove it from the list, or call ***odot*** all by iteself to see the
current todo list in alphabetical order.

* Usage:

    - Add new task to list:
 
            $ odot [new task not on list]  
    
    - Remove task from list:
    
            $ odot [task already on list] 
   
    - Show list:
 
            $ odot 
    
* Installation:

        $ git clone https://github.com/huboles/odot.git
        $ cd odot
        $ make install

***odot*** stores current and completed tasks in plaintext .txt files, located at
$HOME/.local/share/odot.

