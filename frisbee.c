#include "types.h"
#include "stat.h"
#include "user.h"
#include "thread.h"

// struct args_struct
// {
//     int *numPasses;
//     int player;
//     struct lock_t *lt;
// };

// void* pass(void* args){
//     struct args_struct *arg = (struct args_struct*)args;
//     int i;
//     printf(0,"inside pass func before loop\n");
//     for(i = 0; i < *arg->numPasses; i++)
//     {
//         lock_acquire(arg->lt);
//         printf(1,"Pass number no: %d, Thread %d passing the token to thread\n", i+1, arg->player);
//         lock_release(arg->lt);
//     }
//     return 0;
// };

// int main(int argc, char *argv[]){

//     if(argc > 3 || argc < 2)
//         return 1;
//     int threads = atoi(argv[1]);
//     int passes = atoi(argv[2]);

//     struct lock_t lock;
//     lock_init(&lock);

//     int i;
//     struct args_struct args;
//     args.numPasses = &passes;
//     args.lt = &lock;
//     void* arguments = (void*)&args;
//     // int pid[threads];
//     // void* stack = malloc(1000 * sizeof(char));
//     for(i = 0; i < threads; i++){
//         args.player = i;
//         printf(0,"threadCreate\n");
//         thread_create(pass, arguments);
//         // pid[i] = clone(stack, 1000);
//         // printf(1, "%d\n", pid[i]);
//     }
//     for(i = 0; i < threads; i++){
//         printf(0,"thread join\n");
//         thread_join();
//     }
//     passes++;
//     printf(0,"exiting");
//     exit();
//     printf(0,"finihed!");
// }


int numPasses;
int numThreads;
int currPass = 1;
int holder = 0;
struct lock_t lock;

void passFrisbee(void* arg)
{
	int threadnumber = *(int*)arg;
	for(;;)
	{	
		lock_acquire(&lock);
		if(numPasses <= 0)
		{
			lock_release(&lock);
			break;
		}
		if(holder != threadnumber)
		{
			lock_release(&lock);
			continue;
		}
		
		holder++;
		if(holder == numThreads)
		{
			holder = 0;
		}
		printf(0, "Pass number no. %d, Thread %d is passing the token to %d\n", currPass, threadnumber, holder);
		numPasses--;
		currPass++;
		lock_release(&lock);
	}
	return;
}

int main(int argc, char *argv[])
{
	if(argc != 3)
	{
		printf(0,"Usage: frisbee numThreads numPasses\n");
		exit();
	}
	numThreads = atoi(argv[1]);
	numPasses = atoi(argv[2]);
	printf(0,"Num Threads: %d, Num Passes: %d\n", numThreads, numPasses);

	lock_init(&lock);
	int i;
    // int rc;
	for(i = 0; i < numThreads; i++)
	{
		int * t = malloc(sizeof(*t));
		*t = i; 
		// printf(0,"t = %d\n", *t);
		thread_create((void*)passFrisbee,(void*)t);
		// printf(0,"rc = %d\n", rc);
	}
	for(i = 0; i < numThreads; i++)
	{
        thread_join();
	}
	printf(0,"Frisbee complete: %d rounds were played.\n", currPass-1);
	exit();	
}