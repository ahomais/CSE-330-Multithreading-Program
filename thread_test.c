#include "threads.h"
#include <stdlib.h>
#include <stdio.h>

int global;
void foo(int TiD, int runNum){
    int local = 0;
    int i = 1;
    while (i<=runNum){
        local++;
        global += TiD;
        printf("\n This is %d th execution of thread %d with global var value %d \n", local, TiD, global);
        i++;
        yield();
    }
};

int main(){
    int threadNum, runNum;
    scanf("%d,%d", &threadNum, &runNum);
    if (threadNum == 0){
        printf("No Threads\n");
        return 0;
    }

    for (int id=1; id<=threadNum; id++){
        start_thread(foo, id, runNum);
    }
    run();
}