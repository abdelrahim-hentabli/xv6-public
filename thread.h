int thread_create(void *(*start_routine)(void*), void *arg);

struct lock_t {
    uint locked;
}

int lock_init(lock_t *)
int lock_acquire(lock_t *)
int lock_release(lock_t*)
void thread_join(lock_t*)
