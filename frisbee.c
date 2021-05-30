#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char *argv[]){
    if(argc > 3 || argc < 2)
        return 1;
    int threads = atoi(argv[1]);
    int passes = atoi(argv[2]);
    int i;
    int pid[threads];
    void* stack = malloc(1000 * sizeof(char));
    for(i = 0; i < threads; i++){
    
        pid[i] = clone(stack, 1000);
        printf(1, "%d\n", pid[i]);
    }
    for(i = 0; i < threads; i++){
        if(pid[i] != 0)
            wait();
    }
    passes++;
    exit();
}