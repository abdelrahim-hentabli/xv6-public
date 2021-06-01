#include "types.h"
#include "stat.h"
#include "user.h"
#include "thread.h"

struct args_struct
{
    int *numPasses;
    struct lock_t *lt;
};

void* pass(void* args){
    struct args_struct *arg = (struct args_struct*)args;
    int i;
    printf(0,"inside pass func before loop\n");
    while(1)
        ;
    for(i = 0; i < *arg->numPasses; i++)
    {
        lock_acquire(arg->lt);
        printf(1,"Pass number no: %d, Thread is passing the token to thread\n", i);
        lock_release(arg->lt);
    }
    while(1)
        ;
    return 0;
};

int main(int argc, char *argv[]){

    if(argc > 3 || argc < 2)
        return 1;
    int threads = atoi(argv[1]);
    int passes = atoi(argv[2]);

    struct lock_t lock;
    lock_init(&lock);

    int i;
    struct args_struct args;
    args.numPasses = &passes;
    args.lt = &lock;
    void* arguments = (void*)&args;
    // int pid[threads];
    // void* stack = malloc(1000 * sizeof(char));
    for(i = 0; i < threads; i++){
        printf(0,"for loop threads\n");
        thread_create(pass, arguments);
        printf(0,"threadCreate\n");
        // pid[i] = clone(stack, 1000);
        // printf(1, "%d\n", pid[i]);
    }
    for(i = 0; i < threads; i++){
        thread_join();
    }
    passes++;
    exit();
}