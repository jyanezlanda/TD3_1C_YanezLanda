#ifndef TAREAS_H
#define TAREAS_H
void tarea_idle(void);
void tarea_1(void);
void tarea_2(void);

extern void _TASK1_TTBR0_VMA;

#define END_OF_READ_AREA  0x10000/4

#endif