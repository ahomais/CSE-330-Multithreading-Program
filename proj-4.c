#include <stdlib.h>
#include <stdio.h>
#include "sem.h"

int rc, wc, rwc, wwc, i = 0;

void read(int readerID) {
    if (wwc > 0 || wc > 0) {
        rwc++;
        P(&R_Sem);
        rwc--;
    }
    rc++;
    printf("\n This is the %d th reader reading value i = %d for the first time \n", readerID, i);
    yield();
    printf("\n This is the %d th reader reading value i = %d for the second time \n", readerID, i);
    rc--;
    if (rc == 0 && wwc > 0) {
        V(&W_Sem);
    }
    TCB_t* temp = DelQueue(&runQ);
    swapcontext(&(temp->context), &(runQ->context));
}
void write(int writerID) {
    if (rc > 0 || wc > 0 || rwc > 0|| wwc > 0) {
        wwc++;
        P(&W_Sem);
        wwc--;
    }
    wc++;
    i++;
    printf("\n This is the %d th writer writing value i = %d \n", writerID, i);
    yield();
    printf("\n This is the %d th writer verifying value i = %d \n", writerID, i);
    wc--;
    if (rwc > 0) {
        for (int j=0; j<rwc; j++) {
            V(&R_Sem);
        }
    }
    else if (wwc > 0) { 
        V(&W_Sem);
    }
    TCB_t* temp = DelQueue(&runQ);
    swapcontext(&(temp->context), &(runQ->context));
}

int main(){
    int readNum, writeNum, id;
    scanf("%d,%d\n", &readNum, &writeNum);
    InitSem(&R_Sem, 0);
    InitSem(&W_Sem, 0);
    for (int j = 1; j <= readNum+writeNum; j++){
        scanf("%d\n", &id);
        if (id > 0){
            int readerID = id;
            start_thread(read, readerID);
        }
        else {
            int writerID = abs(id);
            start_thread(write, writerID);
        }
    }
    run();
}