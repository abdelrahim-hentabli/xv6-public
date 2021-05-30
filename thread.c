#include "thread.h"
#include "fcntl.h"
#include "x86.h"
#include "mmu.h"
#include "types.h"
#include "stat.h"
#include "user.h"

struct lock_t lock;

int
thread_create(void*(*start_routine)(void*), void *arg)
{
    // uses clone to create threads
    
    return
}

int
lock_init(lock_t *)
{
    
}

int
lock_acquire(lock_t *)
{
    
}

int
lock_release(lock_t*)
{
    
}

void
thread_join(lock_t*)
{

}
