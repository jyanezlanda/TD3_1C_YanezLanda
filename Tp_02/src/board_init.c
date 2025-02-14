#include "../inc/gic.h"
#include "../inc/timer.h"
#include "../inc/scheduler.h"
#include "../inc/mmu.h"
#include "../inc/tareas.h"
__attribute__((section(".kernel_text"))) void board_init()
    {
        
        __gic_init();
        __task_ctx_init(); 
        __timer_init();
        __mmu_init();
        asm("cpsie i");
        tarea_idle();
    }