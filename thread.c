#include "types.h"
#include "stat.h"
#include "fcntl.h"
#include "user.h"
#include "x86.h"
#include "mmu.h"
#include "thread.h"

//initialize lock to 0(open). Reference from spinlock.c
void
lock_init(struct lock_t *lt)
{
    lt->locked = 0;
}

int
thread_create(void *(*start_routine)(void*), void *arg)
{
    // uses clone to create threads, allocate size of stack* using
    // malloc. Get thread id from clone call passing in stack* and
    // PGSIZE as the size. If tid == 0 then return passed in arguments.
    void *stack = malloc(PGSIZE);
    int tid = clone(stack, PGSIZE);
    if(!tid){
        (*start_routine)(arg);
        free(stack);
        exit();
    }
    return tid;
}

void
lock_acquire(struct lock_t *lt)
{
    //The xchg is atomic. Reference from spinlock.c
    while(xchg(&lt->locked, 1) != 0)
        ;    
}

void
lock_release(struct lock_t *lt)
{  
    //Releases lock using xchg, Reference from spinlock.c and x86.h def.
    xchg(&lt->locked, 0);
}

void
thread_join()
{
    //reap children
    wait();
}
