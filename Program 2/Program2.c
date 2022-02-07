#include <stdio.h>					// library for basic input output on C language
#include <stdlib.h> 				// for using "system" command
#include <stdbool.h> 				// for using bool variable, false/true declares
#include <string.h> 				// now we can add 2 strings
#include <unistd.h>					// for cloning processes, getting PID and PPID
#include <sys/wait.h>				// for scheduling tasks
#include <pthread.h>				// for creating and playing with threads

int sharedInteger = 100;			// shared variable
int counterForDeadlock = 0;			// will be used in task 3


pthread_mutex_t MutexThread;		// creating mutex for locking threads || This thread is for demo of task 1, 2 
pthread_mutex_t MutexForDeadlock1;	// will be used for Deadlock & Starvation
pthread_mutex_t MutexForDeadlock2;	// will be used for Deadlock & Starvation

/// Method Name: Multiply
/// Purpose: To multiply shared digit by 10 -> sleep -> save changed result 
void* Multiply()
{
	int localValue;

	printf("\n\nThread #1 starts its work...\n");

	localValue = sharedInteger;
	printf("Thread #1 takes value of shared variable: %d\n", localValue);

	localValue *= 10;

	printf("Thread #1 updated local variable: %d\n", localValue);

	printf("Thread #1 goes to sleep...\n\n");
	sleep(0.5);						//Sends to sleep for 0.5 s Thread 1, now Thread 2 will continue
	printf("Thread #1 resumes its work...\n");

	sharedInteger = localValue;
	printf("Thread #1 finished work and updated shared integer: %d\n\n", sharedInteger);
}

/// Method Name: Divide
/// Purpose: To divide shared digit by 10 -> sleep -> save changed result 
void* Divide()
{
	int localValue;

	printf("Thread #2 starts its work...\n");

	localValue = sharedInteger;
	printf("Thread #2 takes value of shared variable: %d\n", localValue);

	localValue /= 10;

	printf("Thread #2 updated local variable: %d\n", localValue);

	printf("Thread #2 goes to sleep...\n\n\n");
	sleep(0.5);						//Sends to sleep for 0.5 s Thread 1, now Thread 2 will continue
	printf("Thread #2 resumes its work...\n");

	sharedInteger = localValue;
	printf("Thread #2 finished work and updated shared integer: %d\n\n", sharedInteger);
}

/// Method Name: MultiplyMutex
/// Purpose: To multiply shared digit by 10, but WITH THE USE OF MUTEX
void* MultiplyMutex()
{
	pthread_mutex_lock(&MutexThread); //lock this thread

	int localValue;

	printf("\n\nThread #1 starts its work...\n");

	localValue = sharedInteger;
	printf("Thread #1 takes value of shared variable: %d\n", localValue);

	localValue *= 10;

	printf("Thread #1 updated local variable: %d\n", localValue);

	printf("Thread #1 goes to sleep...\n\n");
	sleep(0.5);						 //Sends to sleep for 0.5 s Thread 1, now Thread 2 will continue
	printf("Thread #1 resumes its work...\n");

	sharedInteger = localValue;
	printf("Thread #1 finished work and updated shared integer: %d\n\n", sharedInteger);

	pthread_mutex_unlock(&MutexThread); //unlock this thread
}

/// Method Name: DivideMutex
/// Purpose: To divide shared digit by 10, but WITH THE USE OF MUTEX
void* DivideMutex()
{
	pthread_mutex_lock(&MutexThread);

	int localValue;

	printf("Thread #2 starts its work...\n");

	localValue = sharedInteger;
	printf("Thread #2 takes value of shared variable: %d\n", localValue);

	localValue /= 10;

	printf("Thread #2 updated local variable: %d\n", localValue);

	printf("Thread #2 goes to sleep...\n\n\n");
	sleep(0.5);  //Sends to sleep for 0.5 s Thread 1, now Thread 2 will continue
	printf("Thread #2 resumes its work...\n");

	sharedInteger = localValue;
	printf("Thread #2 finished work and updated shared integer: %d\n\n", sharedInteger);

	pthread_mutex_unlock(&MutexThread); //unlock this thread
}

/// Method Name: Race
/// Purpose: To demonstrate race condition | critical section Problem
/// How it works: Runs Multiply and Divide methods by order to demo wrong final result (100*10/10=100, but here you will get 10 OR 1000)
void Race()
{
	pthread_t thread1, thread2; //pthread_t - data type to uniquely identify a thread

	pthread_create(&thread1, NULL, Multiply, NULL);  //  thread creation (thread | attribute | name of Method | argument). It creates thread and assigns to it chosen method
	pthread_create(&thread2, NULL, Divide, NULL);

	pthread_join(thread1, NULL); //wait for thread termination, then can be used by other processes
	pthread_join(thread2, NULL);

	printf("Final Value of shared integer is %d\n", sharedInteger); //prints the last updated value of shared variable
}

/// Method Name: Mutex
/// Purpose: To demonstrate Critical Section problem soluton with the use of MUTEX
/// How it works: Runs MultiplyMutex and DivideMutex methods by order to demo right final result (100*10/10=100)
void Mutex()
{
	pthread_t thread1, thread2; //pthread_t - data type to uniquely identify a thread

	pthread_mutex_init(&MutexForDeadlock1, NULL);
	pthread_mutex_init(&MutexForDeadlock2, NULL);

	pthread_create(&thread1, NULL, MultiplyMutex, NULL);  //  thread creation (thread | attribute | name of Method | argument). It creates thread and assigns to it chosen method
	pthread_create(&thread2, NULL, DivideMutex, NULL);

	pthread_join(thread1, NULL);						  //wait for thread termination, then can be used by other processes
	pthread_join(thread2, NULL);

	printf("Final Value of shared integer is %d\n", sharedInteger); //prints the last updated value of shared variable
}

/// Method Name: deadlockProcess
/// Purpose: To demonstrate Deadlock example with the use of MUTEX
/// How it works: Thread #1 locks Mutex #1, Thread #2 locks Mutex #2. Then Thread #1 and #2 wait each other to lock each other's Mutex (#1 or #2)
void* deadlockProcess() {

	if (counterForDeadlock == 0)
	{
		printf("Thread #1 starts to work and locks Mutex #1\n");
		pthread_mutex_lock(&MutexForDeadlock1);

		counterForDeadlock++;							//now next thread will go to another if statement (which is below)

		printf("Thread #1 goes to sleep with locked Mutex #1...\n\n\n");
		sleep(1);

		printf("Thread #1 resumes its work and waits for access to Mutex #2...\n");
		pthread_mutex_lock(&MutexForDeadlock2);
	}
	if (counterForDeadlock == 1)
	{
		printf("Thread #2 starts to work and locks Mutex #2\n");
		pthread_mutex_lock(&MutexForDeadlock2);

		printf("Thread #2 goes to sleep with locked Mutex #2...\n\n\n");
		sleep(1);

		printf("Thread #2 resumes its work and waits for access to Mutex #1...\n");
		pthread_mutex_lock(&MutexForDeadlock1);
	}
}

/// Method Name: starvationProcess
/// Purpose: To demonstrate Starvation example with the use of MUTEX
/// How it works: Same steps as in deadlockProcess method, but there is Thread #3, which will unlock Mutex #1 and #2 -> threads will finish their work.
void* starvationProcess() {

	if (counterForDeadlock == 0)					//Thread #1 will enter this if statement
	{
		counterForDeadlock++;						//next thread will go to another if statement (which is below)

		printf("Thread #1 starts to work and locks Mutex #1\n");
		pthread_mutex_lock(&MutexForDeadlock1);

		printf("Thread #1 goes to sleep with locked Mutex #1...\n\n\n");
		sleep(1);

		printf("Thread #1 resumes its work and waits for access to Mutex #2...\n\n\n");
		pthread_mutex_lock(&MutexForDeadlock2);

		printf("Thread #1 finally accessed to Mutex #2\n");
		printf("Thread #1 finished its work...\n\n\n");
		pthread_mutex_unlock(&MutexForDeadlock2);
	}
	if (counterForDeadlock == 1)					//Thread #2 will enter this if statement
	{
		counterForDeadlock++;						//next thread will go to another if statement (which is below)

		printf("Thread #2 starts to work and locks Mutex #2\n");
		pthread_mutex_lock(&MutexForDeadlock2);

		printf("Thread #2 goes to sleep with locked Mutex #2...\n\n\n");
		sleep(1);

		printf("Thread #2 resumes its work and waits for access to Mutex #1...\n\n");
		pthread_mutex_lock(&MutexForDeadlock1);


		printf("Thread #2 finally accessed to Mutex #1\n");
		printf("Thread #2 finished its work...\n\n\n");
		pthread_mutex_unlock(&MutexForDeadlock1);
	}
	if (counterForDeadlock == 2)					//Thread #3 will enter this if statement
	{
		counterForDeadlock++;						//counterForDeadlock now will be three, so by repeat call of this method it won't enter any of 3 'if' statements

		printf("Thread #3 starts to work\n");

		printf("Thread #3 works for 7 seconds\n\n\n");
		sleep(7);

		printf("Thread #3 finished its work and it unlocks locked Mutex #1 and Mutex #2\n\n");
		pthread_mutex_unlock(&MutexForDeadlock1);
		pthread_mutex_unlock(&MutexForDeadlock2);
	}
}

/// Method Name: Deadlock
/// Purpose: To demonstrate Deadlock
void Deadlock()
{
	counterForDeadlock = 0;

	printf("\n\n");

	pthread_t thread1;
	pthread_t thread2;


	pthread_create(&thread1, NULL, deadlockProcess, NULL);
	pthread_create(&thread2, NULL, deadlockProcess, NULL);

	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
}

/// Method Name: Starvation
/// Purpose: To demonstrate Starvation
void Starvation()
{
	counterForDeadlock = 0;

	printf("\n\n");

	pthread_t thread1;
	pthread_t thread2;
	pthread_t thread3;


	pthread_create(&thread1, NULL, starvationProcess, NULL);
	pthread_create(&thread2, NULL, starvationProcess, NULL);
	pthread_create(&thread3, NULL, starvationProcess, NULL);

	pthread_join(thread1, NULL);
	pthread_join(thread2, NULL);
	pthread_join(thread3, NULL);
}

/// Method Name: Main
/// Purpose: Main method with all Interactive Menu
int main()
{
	bool menu = true;
	int option = 0;

	while (menu) {					//Starting of User Interface for Main Menu

		printf("\n\n");
		printf("_________________________________________________________\n");
		printf("|\t\t\t\t\t\t\t|\n");
		printf("|\tChoose Task Number\t\t\t\t|\n");
		printf("|\t\t\t\t\t\t\t|\n");
		printf("|\t1. Race Condition | Critical Section Problem\t|\n");
		printf("|\t2. Critical Section Solution | Mutex Lock\t|\n");
		printf("|\t3. Deadlock Example\t\t\t\t|\n");
		printf("|\t4. Starvation Example\t\t\t\t|\n");
		printf("|\t\t\t\t\t\t\t|\n");
		printf("|\t! Enter other digit to exit program !\t\t|\n");
		printf("_________________________________________________________\n\n");

		scanf("%d", &option);		//Choose option from menu

		switch (option)
		{
		default: 					// case which executes when "option" value is not 1 to 4
			menu = false;
			printf("Program Exiting...\n");
			break;

		case 1:
			Race();
			break;

		case 2:
			Mutex();
			break;

		case 3:
			Deadlock();
			break;
			
		case 4:
			Starvation();
			break;
		}
	}
}