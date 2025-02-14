#include"../inc/tareas.h"
#include <stdint.h>
#include "../inc/simbols.h"

__attribute__((section(".tarea_data"))) int g_i = 0, g_d = 0;

__attribute__((section(".txt_tarea_idle"))) void tarea_idle (void)
{
    while(1)
        asm("WFI");
}

__attribute__((section(".tarea_1_txt"))) void tarea_1 (void)
{
    uint32_t data_read1 = 0;
    uint32_t data_read2 = 0;

    uint32_t i = 0;
    while(1){
        data_read1 = ((uint32_t *) &__TAREA_1_READ_AREA_VMA) [i];

        ((uint32_t *) &__TAREA_1_READ_AREA_VMA) [i] = 0xAA55AA55; 
        
        data_read2 = ((uint32_t *) &__TAREA_1_READ_AREA_VMA) [i];

        if(data_read2 == 0xAA55AA55)
            ((uint32_t *) &__TAREA_1_READ_AREA_VMA) [i] = data_read1;
        i++;

        i %= END_OF_READ_AREA;

    }
}

__attribute__((section(".tarea_2_txt"))) void tarea_2 (void)
{
    uint32_t i = 0;
    while(1){
        ((uint32_t *) &__TAREA_2_READ_AREA_VMA) [i] = ~((uint32_t *) &__TAREA_2_READ_AREA_VMA) [i]; 
        
        i++;

        i %= END_OF_READ_AREA;

    }
}
