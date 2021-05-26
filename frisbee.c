#include "types.h"
#include "stat.h"
#include "user.h"

int main(int argc, char *argv[]){
    if(argc > 3 || argc < 2)
        return 1;
    //int threads = atoi(argv[1]);
    int passes = atoi(argv[2]);
    int i;
    for(i = 0; i < passes; i++){
        printf(1, "%d\n", clone( (void*)0, i));
    }
    exit();
}