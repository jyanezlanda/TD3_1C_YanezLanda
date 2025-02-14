#ifndef _SCHEDULER_H_
#define _SCHEDULER_H_

#define MAX_TASK 4

typedef struct TaskControlBlock
{
    uint32_t ticks;
    uint32_t id;
    uint32_t *PC;
    uint32_t *SP_IRQ;
    uint32_t *SP_SVC;
    uint32_t SPSR;
}TCB;

uint32_t scheduler_c(void);
void __task_ctx_init(void);

#endif
