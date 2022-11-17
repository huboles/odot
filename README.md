# odot
Todo manager written in C

Usage:

  Add new task to list:
 
    $ odot [new task not on list]  
    
 Remove task from list:
  
    $ odot [task already on list] 
   
 Show list:
 
    $ odot 
    
Installation:

    $ git clone https://github.com/huboles/odot.git
    $ cd odot
    $ sudo gcc *.c -o /usr/bin/odot
    $ mkdir $HOME/.local/state/odot
