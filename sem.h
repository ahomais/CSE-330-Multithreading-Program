#include <stdlib.h>
#include <stdio.h>
#include "threads.h"

semaphore full;
semaphore empty;
semaphore R_Sem;
semaphore W_Sem;

void InitSem(semaphore* sem, int value) {
    InitQueue(&(sem->semQ));
    sem->val = value;
}

void P(semaphore* sem) {
    while (sem->val == 0) {
        TCB_t* storedTCB = DelQueue(&runQ);
        AddQueue(&(sem->semQ), storedTCB);
        int tid = sem->semQ->prev->tid;
        // if (tid > 0) {
        //     printf("\n Producer %d is waiting \n", tid);
        // }
        // else {
        //     printf("\n Consumer %d is waiting \n", abs(tid));
        // }
        if (runQ == NULL) {
            exit(0);
        }
        else {
            swapcontext(&(sem->semQ->prev->context), &(runQ->context));
        }
    }
    sem->val = sem->val - 1;
}

void V(semaphore* sem) {
    if (sem->semQ != NULL) {
        TCB_t* storedTCB = DelQueue(&(sem->semQ));
        AddQueue(&runQ, storedTCB);
    }
    sem->val = sem->val + 1;
}

