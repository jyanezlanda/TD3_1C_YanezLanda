#ifndef _SCHEDULER_H_
#define _SCHEDULER_H_

#define MAX_TASK 3
#define TCBSPSR0 0x113 //Valor inicial del SPSR con la interrupciones prendidas.

typedef struct TaskControlBlock
{
    uint32_t ticks;
    uint32_t id;
    uint32_t *PC;
    uint32_t *SP_IRQ_PHY;
    uint32_t *SP_IRQ_VMA;
    uint32_t *SP_SVC;
    uint32_t SPSR;
    uint32_t TTBR0;
}TCB;

uint32_t scheduler_c(void);
void __task_ctx_init(void);

extern uint32_t  __TAREA_1_PILA_IRQ_TOP_PHY, __TAREA_2_PILA_IRQ_TOP_PHY, __irq_stack_top__;
extern uint32_t  __TAREA_1_PILA_SVC_TOP_PHY, __TAREA_2_PILA_SVC_TOP_PHY, __svc_stack_top__;
extern uint32_t  __TAREA_1_PILA_SVC_TOP_VMA,__TAREA_2_PILA_SVC_TOP_VMA;
extern uint32_t  __TAREA_1_PILA_IRQ_TOP_VMA,__TAREA_2_PILA_IRQ_TOP_VMA;

#endif
