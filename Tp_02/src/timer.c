
#include "../inc/timer.h"

__attribute__((section(".kernel_text"))) void __timer_init()
    {
        _timer_t* const TIMER0 = ( _timer_t* )TIMER01_ADDR;

        TIMER0->Timer1Load     = 0x00010000; // Período = 2^18 ticks ~= 0.25 segundos
        TIMER0->Timer1Ctrl     = 0x00000002; // Seleccionamos timer de 32-bit 
        TIMER0->Timer1Ctrl    |= 0x00000040; // Seleccionamos timer periodico
        TIMER0->Timer1Ctrl    |= 0x00000020; // Habilitamos interrupción del timer
        TIMER0->Timer1Ctrl    |= 0x00000080; // Habilitamos el timer

    }