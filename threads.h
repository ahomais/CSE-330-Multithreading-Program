#include "q.h"

void start_thread(void (*func)(int), int threadNum){
    void * stackPtr = malloc(8192);
    TCB_t * itemPtr = NewItem();
    init_TCB(itemPtr, func, stackPtr, 8192, threadNum);
    itemPtr->tid = threadNum;
    AddQueue(&runQ, itemPtr);
}

void run(){
    ucontext_t parent;	// get a place to store the main context, for faking
    getcontext(&parent);	// magic sauce
    swapcontext(&parent, &(runQ->context));	// start the first thread
}

void yield(){
    RotateQ(&runQ);
    swapcontext(&((runQ->prev)->context), &(runQ->context));
}