# Linux-Programs
Created 2 executable programs for Linux (Ubuntu) that perform several tasks. Attached both, executable and c language files.

How to compile files?

1) Program1.c file. 
You can compile code by yourself and create executable file on Ubuntu by typing command "gcc program1.c -o program1". This command will create "program1" executable file in same folder which you can call from System Terminal.

2) Program2.c file. 
As program 2 works with thread, we have to mention it for Linker which participates in creating executable file. Type following command "gcc program2.c -o program2 -lpthread"

How to run existing (or compiled) executable file?
Open terminal in the same folder, then type "./program1" or "./program2" depending on which file you want to run.

Program 1 functionality:
Show/Create/Schedule/Kill processes

Program 2 functionality:
Demonstration of Race Condition and Critical Section Problem
Solution of Critical Section problem by adding Mutex Lock
Demonstration of Deadlock 
Demonstration of Starvation
