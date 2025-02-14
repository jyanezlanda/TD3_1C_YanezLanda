#include"../inc/tareas.h"
#include <stdint.h>
//#include <stddef.h>

void tarea_idle(void);
void tarea_1(void);
void tarea_2(void);
void tarea_3(void);

__attribute__((section(".tarea_data"))) int g_i = 0, g_d = 0;

__attribute__((section(".tarea_idle_text"))) void tarea_idle (void)
{
    while(1)
        asm("WFI");
}

__attribute__((section(".tarea_1_text"))) void tarea_1 (void)
{
    int num = 0;
    while(1){
        num++;
        g_i++;
    }
}

__attribute__((section(".tarea_2_text"))) void tarea_2 (void)
{
    int num = 0;
    while(1){
        num--;
        g_d--;
    }
}

__attribute__((section(".tarea_3_text"))) void tarea_3 (void)
{
    while(1){
        g_i--;
        g_d++;
    }
}