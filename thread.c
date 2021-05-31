#include "thread.h"
#include "fcntl.h"
#include "x86.h"
#include "mmu.h"
#include "types.h"
#include "stat.h"
#include "user.h"

struct lock_t lock;

//initialize lock to 0(open). Reference from spinlock.c
int
lock_init(struct lock_t *lt)
{
    lt->locked = 0;
}

int
thread_create(void *(*start_routine)(void*), void *arg)
{
    // uses clone to create threads, allocate size of stack* using
    // malloc. Get thread id from clone call passing in stack* and
    // 1024 as the size. If tid == 0 then return passed in arguments.
    void *stack = malloc(1024);
    int tid = clone(stack, 1024);
    if(!tid)
        (*start_routine)(arg);
    return tid;
}

int
lock_acquire(lock_t *lt)
{
    //The xchg is atomic. Reference from spinlock.c
    while(xchg(&lt->locked, 1) != 0)
        ;    
}

int
lock_release(lock_t *lt)
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
