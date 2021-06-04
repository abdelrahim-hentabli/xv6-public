#include "types.h"
#include "stat.h"
#include "user.h"
#include "thread.h"

// argument variables
int passes;
int threads;
// start frisbee game variables
int numPass = 1;
int holder = 0;
// thread struct init
struct lock_t lock;

void frisbee(void* arg)
{
	int threadNumber = *(int*)arg;
	while(1)
	{	
		lock_acquire(&lock);
		if(passes <= 0)
		{
			lock_release(&lock);
			break;
		}
		if(holder != threadNumber)
		{
			lock_release(&lock);
			continue;
		}
	
		holder++;
		if(holder == threads)
		{
			holder = 0;
		}
		printf(0, "Pass number no. %d, Thread %d is passing the token to %d\n", numPass, threadNumber, holder);
		numPass++;
		passes--;
		lock_release(&lock);
	}
	return;
}

int main(int argc, char *argv[])
{

	if(argc != 3)
	{
		printf(0,"Too many/little arguments passed!\n");
		exit();
	}
	threads = atoi(argv[1]);
	passes = atoi(argv[2]);
	// printf(0,"Num Threads: %d, Num Passes: %d\n", threads, passes);
	
	//init thread lock
	lock_init(&lock);
	int i;
	for(i = 0; i < threads; i++)
	{
		//init pointer for int cast stack will point to #threads
		int *arg = malloc(sizeof(i));
		*arg = i; 
		thread_create((void*)frisbee,(void*)arg);
	}
	for(i = 0; i < threads; i++)
	{
        thread_join();
	}
	printf(0,"Simulation of Frisbee game has finished, %d rounds were played in total!.\n", numPass-1);
	exit();	
}