#include "../inc/gic.h"
#include "../inc/timer.h"
#include "../inc/scheduler.h"
#include "../inc/mmu.h"

__attribute__((section(".text"))) void board_init()
    {
        __mmu_init();
        __gic_init();
        /*__task_ctx_init(); 
        __timer_init();*/
        
    /* Esta última funcion me carga la pila de las tareas con los 13 registros + el puntero al inicio + el SP + el SPSR de cada tarea.
    El SP TIENE que apuntar al puntero a la tarea para simular que estas haciendo el salvado de contexto que se hace en el handler de IRQ.
    Es basicamente simular que el contexto ya estaba para que cuando lo agarre el ASM sea lo mismo pero en otro stack. */
    }