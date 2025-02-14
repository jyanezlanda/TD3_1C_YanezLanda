#include "../inc/gic.h"
#include "../inc/timer.h"
#include "../inc/scheduler.h"
#include "../inc/irq_handler.h"

extern uint32_t* SP_act;

__attribute__((section(".text"))) uint32_t kernel_handler_irq(_context_t* ctx) //El argumento es el puntero a la pila
    {
        _gicc_t* const GIC = (_gicc_t*) GICC0_ADDR;
        _timer_t* const TIMER01 =  (_timer_t*) TIMER01_ADDR;
        uint32_t id = 0;
        uint32_t new_sp;
        id = GIC->IAR & 0x000001FF; // XQ TIENEN EL MISMO 

        SP_act = (uint32_t *) ctx; //Cargo la dirección del SP para usarla en el scheduler
        switch (id)
        {
        case (GIC_SOURCE_TIMER0): 
            if ((TIMER01->Timer1RIS & 0x01)== 0x01)
            {
                TIMER01->Timer1IntClr |= 0x01;
                new_sp = scheduler_c();
            }
            else if ((TIMER01->Timer2RIS & 0x01)== 0x01)
                TIMER01->Timer1IntClr |= 0x01;           
        break;
        
        default:
            break;
        }

        GIC->EOIR = id; //Al terminar el handler se escribe en End Of Interrupt el id del timer.
        return new_sp;
    }
