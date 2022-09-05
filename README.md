# Linux-Programs
Created 2 executable programs for Linux (Ubuntu) that perform several tasks. Attached both, executable and c language files.

How to compile files?

1) Program1.c file. 
You can compile code by yourself and create executable file on Ubuntu by typing command "gcc program1.c -o program1". This command will create "program1" executable file in same folder which you can call from System Terminal.

2) Program2.c file. 
As Program 2 works with threads, we have to mention it for Linker which participates in creating executable file. Type following command "gcc program2.c -o program2 -lpthread"

How to run existing (or compiled) executable file?
Open terminal in the same folder, then type "./program1" or "./program2" depending on which file you want to run.

Program 1 functionality:
Show/Create/Schedule/Kill processes

Program 2 functionality:
Demonstration of Race Condition and Critical Section Problem
Solution of Critical Section problem by adding Mutex Lock
Demonstration of Deadlock 
Demonstration of Starvation

Few screenshots from Program 1:

![image](https://user-images.githubusercontent.com/73297277/188369005-50f4ee73-0b34-4732-8364-c9ca8478d59d.png)

![image](https://user-images.githubusercontent.com/73297277/188368994-2ca67356-7f90-43f7-8303-4274c0d466f6.png)

![image](https://user-images.githubusercontent.com/73297277/188368495-f4699e32-8da1-49f7-8dd2-babc214f27ac.png)

![image](https://user-images.githubusercontent.com/73297277/188368531-c1f17be6-1d5f-4ff2-b7e1-09b27ff13da8.png)

![image](https://user-images.githubusercontent.com/73297277/188368555-c722a099-7487-4f29-86ca-5ae4ec13e1d8.png)

Screenshots from Program 2:

![image](https://user-images.githubusercontent.com/73297277/188368646-d99fd6b0-a7b5-4110-95bb-5a3821c31215.png)

![image](https://user-images.githubusercontent.com/73297277/188368664-292b24d7-9f27-45bf-a5ef-c35222c607f8.png)

![image](https://user-images.githubusercontent.com/73297277/188369146-5157820f-16c5-42cd-bec3-012e756832b2.png)

![image](https://user-images.githubusercontent.com/73297277/188368695-3c0d72d4-007a-4070-b66d-8d0287d56c16.png)

![image](https://user-images.githubusercontent.com/73297277/188368740-10d661a2-fe74-4a70-827e-0e7ee4a23659.png)



To get better understanding of programs concepts you can check document below.

[Specification.pdf](https://github.com/rasul-isk/Linux-Programs/files/9482800/Specification.pdf)
