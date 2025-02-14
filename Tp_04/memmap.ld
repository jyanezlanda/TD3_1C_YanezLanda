/*
 * 	Definiciones necesarias: formato de salida, arquitectura
 * 	Todo lo de aca abajo son directivas para el linker, el entry define el punto de entrada del programa
 * 	indico 32 bit little endian y arm 
 */
OUTPUT_FORMAT("elf32-littlearm")
OUTPUT_ARCH(arm)
ENTRY(_reset_vector)

/*
 * 	Definiciones de simbolos necesarias
 *  
 *	Defino mis posiciones de inicio en un SIMBOLO
 */

_PUBLIC_RAM_INIT = 0x70010000;
_PUBLIC_STACK_INIT = 0X70020000;
_PUBLIC_TABLE_INIT = 0X00000000;

SYS_STACK_SIZE = 4K;
IRQ_STACK_SIZE = 2048;
FIQ_STACK_SIZE = 128;
SVC_STACK_SIZE = 2048;
ABT_STACK_SIZE = 128;
UND_STACK_SIZE = 128;
TASK_1_IRQ_STACK_SIZE = 128;
TASK_2_IRQ_STACK_SIZE = 128;
TASK_3_IRQ_STACK_SIZE = 128;
TASK_IDLE_IRQ_STACK_SIZE = 128;
TASK_1_SVC_STACK_SIZE = 128;
TASK_2_SVC_STACK_SIZE = 128;
TASK_3_SVC_STACK_SIZE = 128;
TASK_IDLE_SVC_STACK_SIZE = 128;

TOTAL_IRQ_STACK_SIZE = TASK_1_IRQ_STACK_SIZE + TASK_2_IRQ_STACK_SIZE + TASK_3_IRQ_STACK_SIZE + TASK_IDLE_IRQ_STACK_SIZE;
TOTAL_SVC_STACK_SIZE = TASK_1_SVC_STACK_SIZE + TASK_2_SVC_STACK_SIZE + TASK_3_SVC_STACK_SIZE + TASK_IDLE_SVC_STACK_SIZE;

/*
 *	Definicion del mapa de memoria
 *	Defino dos regiones de memoria y les doy el origen con los simbolos anteriores y el tamaño de cada una
 *	En este caso cada seccion tiene 4096 bytes = 0x1000
 */

MEMORY
{
	public_ram : org = _PUBLIC_RAM_INIT, len = 1M
	public_stack : org = _PUBLIC_STACK_INIT, len = 1M
}

/*
 * 	Definicion de las secciones
 *
 */
SECTIONS
{
	. = _PUBLIC_RAM_INIT; /* Defino el location counter y lo inicializo en mi public ram init*/
	.text : {
        *(.reset_vector*)
		*(.text*)
		*(.handlers*)
		*(.table_start*) 
		*(.startup*)
	} > public_ram

	/*Datos y variables globales inicializadas*/
	.data : {*(.data*) } > public_ram  /* Defino la seccion de memoria donde quiero que se asocie */

	.bss : {
		. = ALIGN(4); 
		__bss_start__ = .; 
		*(.bss*)
		__bss_end__ = .;
	} > public_ram

    . = _PUBLIC_STACK_INIT;

    .stack :
    {
        __stack_start__ = .;    /* Guardo en Location Counter donde empieza el stack*/

        . += TASK_IDLE_IRQ_STACK_SIZE;
        . = ALIGN(4);
        __task_idle_irq_top__ = .;

        . += TASK_1_IRQ_STACK_SIZE;
        . = ALIGN(4);
        __task_1_irq_top__ = .;

        . += TASK_2_IRQ_STACK_SIZE;
        . = ALIGN(4);
        __task_2_irq_top__ = .;

        . += TASK_3_IRQ_STACK_SIZE;
        . = ALIGN(4);
        __task_3_irq_top__ = .;

        . += (IRQ_STACK_SIZE - TOTAL_IRQ_STACK_SIZE);    /* Le sumo el valor del stack de IRQ */
        . = ALIGN(4);           /* Lo alineo a 4 bytes */
        __irq_stack_top__ = .;   /* Asigno donde empieza el stack de irq, recordar que es full descending (\uparrow)*/

        . += FIQ_STACK_SIZE;
        . = ALIGN(4);
        __fiq_stack_top__ = .;

        . += TASK_IDLE_SVC_STACK_SIZE;
        . = ALIGN(4);
        __task_idle_svc_top__ = .;

        . += TASK_1_SVC_STACK_SIZE;
        . = ALIGN(4);
        __task_1_svc_top__ = .;

        . += TASK_2_SVC_STACK_SIZE;
        . = ALIGN(4);
        __task_2_svc_top__ = .;

        . += TASK_3_SVC_STACK_SIZE;
        . = ALIGN(4);
        __task_3_svc_top__ = .;

        . += (SVC_STACK_SIZE - TOTAL_SVC_STACK_SIZE);    /* Le sumo el valor del stack de IRQ */
        . = ALIGN(4);           /* Lo alineo a 4 bytes */
        __svc_stack_top__ = .;   /* Asigno donde empieza el stack de irq, recordar que es full descending (\uparrow)*/

        . += ABT_STACK_SIZE;
        . = ALIGN(4);
        __abt_stack_top__ = .;

        . += UND_STACK_SIZE;
        . = ALIGN(4);
        __und_stack_top__ = .;

        . += SYS_STACK_SIZE;
        . = ALIGN(4);
        __sys_stack_top__ = .;

        __stack_end__ = .;
    } > public_stack
} 
