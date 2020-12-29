#include <stdio.h>
#include <stdlib.h>
#include "TCB.h"


TCB_t* NewItem() {
    TCB_t * newItem;
    newItem = (TCB_t *) malloc(sizeof(TCB_t));
    return newItem;
}

void InitQueue(TCB_t** phead) {
    *phead = NULL;
}

void AddQueue(TCB_t** phead, TCB_t* item) {
    TCB_t* head = *phead;
    if (head == NULL){
        item->next = item;
        item->prev = item;
        (*phead) = item;
    }

    else if (head->prev == head) {
        head->next = item;
        head->prev = item;  
        item->next = head;
        item->prev = head;
    }

    else{
        TCB_t* back = head->prev;
        head->prev = item;
        back->next = item;
        item->next = head;
        item->prev = back;
    }
    return;
}

TCB_t* DelQueue(TCB_t** phead) {

    TCB_t* deleted = (*phead);
    
    if (deleted != NULL) {

        if (deleted->next == deleted){
            (*phead) = NULL;
        }

        else if (deleted->next == deleted->prev) {
            TCB_t* back = deleted->prev;
            back->next = back;
            back->prev = back;
            (*phead) = back;
        }
        else {
            TCB_t* front = deleted->next;
            TCB_t* back = deleted->prev;
            front->prev = back;
            back->next = front;
            (*phead) = front;
        }
        deleted->next = NULL;
        deleted->prev = NULL;
        return deleted;
    }
    return NULL;
}

void RotateQ(TCB_t** phead) {
    TCB_t* head = (*phead);
    if (head != NULL) {
        (*phead) = head->next;
    }
}


