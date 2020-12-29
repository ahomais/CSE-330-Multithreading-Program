#include <ucontext.h>
#include <string.h>

typedef struct TCB_t {
    struct TCB_t	*next;
    struct TCB_t	*prev;
    ucontext_t	context;
    int tid;
} TCB_t;	

typedef struct semaphore {
    int val;
    TCB_t * semQ;
}semaphore;

TCB_t * runQ;

void init_TCB (TCB_t *tcb, void *function, void *stackP, int stack_size, int threadNum) {
 
    memset(tcb, '\0', sizeof(TCB_t)); // wash, rinse
    getcontext(&tcb->context); // have to get parent context, else snow forms on hell 
    
    tcb->context.uc_stack.ss_sp = stackP;

    tcb->context.uc_stack.ss_size = (size_t) stack_size; 
    makecontext(&tcb->context, function, 1, threadNum); // context is now cooked
}

