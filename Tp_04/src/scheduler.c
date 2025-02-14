#include"../inc/tareas.h"
#include <stdint.h>
#include "../inc/scheduler.h"

extern uint32_t  __task_idle_irq_top__, __task_1_irq_top__, __task_2_irq_top__, __task_3_irq_top__;
extern uint32_t  __task_idle_svc_top__, __task_1_svc_top__, __task_2_svc_top__, __task_3_svc_top__;

__attribute__((section(".kernel_data"))) uint32_t first_in = 0;

__attribute__((section(".kernel_data"))) uint32_t * SP_act = 0; //Puntero que va a contener el SP a la hora de entrar a la funcion

__attribute__((section(".kernel_data"))) int ticks = 0, current_task = 0, task_switch = 0; 

__attribute__((section(".kernel_data"))) TCB tareas[4]; 

__attribute__((section(".kernel_data"))) uint32_t task_tick [4] = {5, 8, 12, 5};

__attribute__((section(".kernel_data"))) uint32_t *task_stack_irq [4] = {&__task_idle_irq_top__, &__task_1_irq_top__, &__task_2_irq_top__, &__task_3_irq_top__};
__attribute__((section(".kernel_data"))) uint32_t *task_stack_svc [4] = {&__task_idle_svc_top__, &__task_1_svc_top__, &__task_2_svc_top__, &__task_3_svc_top__};

__attribute__((section(".kernel_data"))) void (*task_start[])(void)  = {tarea_idle, tarea_1, tarea_2, tarea_3};

__attribute__((section(".kernel_text"))) void __task_ctx_init(void)
{
    uint32_t i = 0, j = 0;

    for(i = 0; i < 4; i++)
    {
        tareas[i].SP_IRQ = task_stack_irq[i];
        tareas[i].SP_SVC = task_stack_svc[i];
       
        asm("cpsie i"); /// Estoy en modo svc pero todavía no active las interrupciones
        asm("mrs %0, cpsr" : "=r"(tareas[i].SPSR));
        asm("cpsid i"); //Si no las desactivo me pueden unterrummpir antes de que este todo configurado

        tareas[i].id = i;
        tareas[i].ticks =task_tick[i];
        
        *(tareas[i].SP_IRQ) =(uint32_t) task_start[i];
        tareas[i].SP_IRQ--;

        for(j = 0; j < 13; j++)
        {
            *(tareas[i].SP_IRQ) = j;
            tareas[i].SP_IRQ--;
        }

        *(tareas[i].SP_IRQ) = tareas[i].SPSR;
        tareas[i].SP_IRQ--;

        *(tareas[i].SP_IRQ) =(uint32_t) (tareas[i].SP_IRQ + 2); //Guardo el SP que apunta a R0 en este caso por lo que le tegp que sumar 2 posiciones      
    }  
}

__attribute__((section(".kernel_text"))) uint32_t scheduler_c(void)
{
    uint32_t new_task_id;
    ticks++;
    if(ticks == (tareas[current_task].ticks))
    {
        new_task_id =(current_task + 1) % MAX_TASK;
        task_switch = 1;
        ticks = 0;
    }
    else 
    {
        task_switch = 0;
        new_task_id = current_task;
    }
    
    if(task_switch)
    {
        // ACA TENGO QUE ACTUALIZAR MI TCB ANTES DE CAMBIAR LAS PILAS
        tareas[current_task].SP_IRQ = SP_act;
        
        asm("MOV SP, %0" :: "r"(tareas[new_task_id].SP_IRQ)); //CAMBIO EL SP AL DE LA TAREA NUEVA TODAVIA ESTOY EN MODO IRQ
        asm("CPS #0X13");  //CAMBIO A MODO SVC
        asm("MOV %0, SP" : "=r"(tareas[current_task].SP_SVC)); //Alamceno mi pila de SVC antes de cambiarla por la de la nueva tarea
        asm("MOV SP, %0" :: "r"(tareas[new_task_id].SP_SVC));
        asm("CPS #0X12");  //CAMBIO A MODO IRQ DE NUEVO.
        
        current_task = tareas[new_task_id].id;
    }

    if(first_in == 0) // La primera vez que entro a la función tengo los SP apuntando a "irq_stack_top" y "svc_stack_top" el primero se va a corregir cuando vuelva a handler.s el de SVC lo tengo que corregir a mano ahora, recién despues de esta entrada agarra el control la primer tarea 
    {
        asm("CPS #0X13");
        asm("MOV SP, %0" :: "r"(tareas[new_task_id].SP_SVC));
        asm("CPS #0X12");

        first_in = 1;
    }

    return (uint32_t) tareas[new_task_id].SP_IRQ;
}