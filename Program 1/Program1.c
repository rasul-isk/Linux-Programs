#include <stdio.h>						// library for basic input output on C language
#include <stdlib.h> 					// for using "system" command
#include <stdbool.h> 					// for using bool variable, false/true declares
#include <string.h> 					// now we can add 2 strings
#include <unistd.h> 					// for cloning processes, getting PID and PPID
#include <sys/wait.h> 					// for scheduling tasks

void show() {
	system("ps -A");					// list all running processes
}

void create() {
	pid_t pid;							//pid_t - data type for any PID which we want to create
	pid = fork();						//clone parent process to create child process

	printf("\nChild Process created! \n");
	printf("PID: %d", getpid()); 		// PID - child process identifier
	printf("\nPPID: %d\n", getppid()); 	// PPID - parent's PID

}

void killProcess() {
	char processPID[10];
	char getName[30];
	char kill[20];

	printf("Enter the PID to Kill: ");
	scanf("%s", processPID);			// gets PID

	strcat(getName, "ps -p ");			// ps -p 
	strcat(getName, processPID);		// ps -p PID
	strcat(getName, " -o comm="); 		// ps -p PID -o comm=       RETURNS NAME OF PROCESS BY GETTING ITS PID

	strcat(kill, "kill ");				// kill	
	strcat(kill, processPID);			// kill PID
	system(kill);						// kills process by PID

	printf("\n\nThis program was killed!");

	system(getName);					// outputs name of killed process
}

void schedule() {
	char mins[5];
	char name[15];
	char command[60];

	printf("\n\n");
	printf("Insert name for text file:\n");
	printf("(should contain 1 solid word)\n");

	scanf("%s", name);

	strcat(command, "echo \"touch ");	// "echo "touch 
	strcat(command, name);  			// "echo "touch NAMEOFFILE
	strcat(command, " | date > "); 		// "echo "touch NAMEOFFILE | date > 
	strcat(command, name);				// "echo "touch NAMEOFFILE | date > NAMEOFFILE
	strcat(command, "\" | at now + "); 	// "echo "touch NAMEOFFILE | date > NAMEOFFILE" | at now + 

	printf("\n\n");
	printf("When you want to start it?");
	printf("\n\n");
	printf("Now:\t\t\tEnter \"0\"\n");
	printf("1 minute later:\t\tEnter \"1\"\n");
	printf("5 minutes later:\tEnter \"5\"\n");
	printf("15 minutes later:\tEnter \"15\"\n");

	scanf("%s", mins);

	strcat(command, mins);				// "echo "touch NAMEOFFILE | date > NAMEOFFILE" | at now + X
	strcat(command, " minutes"); 		// "echo "touch NAMEOFFILE | date > NAMEOFFILE" | at now + X minutes 

	system(command); 					// system, schedule given task!

	printf("\n\nJob scheduled!\n");

}

int main() {
	bool menu = true;
	int option = 0;

	while (menu) {					//Starting of User Interface for Main Menu

		printf("\n\n");
		printf("_________________________________________________\n");
		printf("|\t\t\t\t\t\t|\n");
		printf("|\tChoose Task Number\t\t\t|\n");
		printf("|\t\t\t\t\t\t|\n");
		printf("|\t1. Show All Processes\t\t\t|\n");
		printf("|\t2. Create a child process\t\t|\n");
		printf("|\t3. Schedule a process\t\t\t|\n");
		printf("|\t4. Kill a process\t\t\t|\n");
		printf("|\t\t\t\t\t\t|\n");
		printf("|\t! Enter other digit to exit program !\t|\n");
		printf("_________________________________________________\n\n");

		scanf("%d", &option);		//Choose option from menu

		switch (option)
		{
		default: 					// case which executes when "option" value is not 1 to 4
			menu = false;
			printf("Program Exiting...\n");
			break;

		case 1:
			show();
			break;

		case 2:
			create();
			break;

		case 3:
			schedule();
			break;

		case 4:
			killProcess();
			break;
		}
	}
}