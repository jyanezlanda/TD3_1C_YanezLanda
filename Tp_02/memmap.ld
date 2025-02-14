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


/* ---------------- SIZES ---------------- */
SYS_STACK_SIZE = 128;
IRQ_STACK_SIZE = 128;
FIQ_STACK_SIZE = 128;
SVC_STACK_SIZE = 128;
ABT_STACK_SIZE = 128;
UND_STACK_SIZE = 128;
C_STACK_SIZE   = 4K;

TAREA_1_IRQ_STACK_SIZE = IRQ_STACK_SIZE;
TAREA_2_IRQ_STACK_SIZE = IRQ_STACK_SIZE;

TAREA_1_SVC_STACK_SIZE = SVC_STACK_SIZE;
TAREA_2_SVC_STACK_SIZE = SVC_STACK_SIZE;

TOTAL_IRQ_STACK_SIZE = TAREA_1_IRQ_STACK_SIZE + TAREA_2_IRQ_STACK_SIZE;
TOTAL_SVC_STACK_SIZE = TAREA_1_SVC_STACK_SIZE + TAREA_2_SVC_STACK_SIZE;

/* ------------------ PHYSICAL ------------------ */
__RESET_PHYSICAL  = _PUBLIC_RAM_INIT;
__PUBLIC_STACK_PHYSICAL = _PUBLIC_STACK_INIT;

__KERNEL_TXT_PHY       = 0x70030000;
__KERNEL_BSS_PHY       = 0x70022000;
__KERNEL_DATA_PHY      = 0x70032000;
__KERNEL_RODATA_PHY    = 0x70023000;

__SYSTABLES_PHYSICAL    = 0x70050000;
__SYSTABLES_TAREA_0_PHY = 0x70060000;
__SYSTABLES_TAREA_1_PHY = 0x70070000;
__SYSTABLES_TAREA_2_PHY = 0x70080000;

__TAREA_IDLE_TXT_PHY    = 0x70033000;

__TAREA_1_TXT_PHY       = 0x80750000;
__TAREA_1_BSS_PHY       = 0x80757000;
__TAREA_1_DATA_PHY      = 0x80756000;
__TAREA_1_RODATA_PHY    = 0x80758000;
__TAREA_1_READ_AREA_PHY = 0X80000000;

__TAREA_2_TXT_PHY       = 0x80740000;
__TAREA_2_BSS_PHY       = 0x80743000;
__TAREA_2_DATA_PHY      = 0x80741000;
__TAREA_2_RODATA_PHY    = 0x80754000;
__TAREA_2_READ_AREA_PHY = 0X80010000;

__KERNEL_PILA_IRQ_PHY      =  0x70020000;
__KERNEL_PILA_SYS_PHY      =  (__KERNEL_PILA_IRQ_PHY + IRQ_STACK_SIZE);
__KERNEL_PILA_SVC_PHY      =  (__KERNEL_PILA_SYS_PHY + SYS_STACK_SIZE);
__KERNEL_PILA_UND_PHY      =  (__KERNEL_PILA_SVC_PHY + SVC_STACK_SIZE);
__KERNEL_PILA_ABT_PHY      =  (__KERNEL_PILA_UND_PHY + UND_STACK_SIZE);

__TAREA_1_PILA_TOP_PHY     =   0x80752000;
__TAREA_1_PILA_IRQ_TOP_PHY =  (__TAREA_1_PILA_TOP_PHY + IRQ_STACK_SIZE);
__TAREA_1_PILA_SVC_TOP_PHY =  (__TAREA_1_PILA_IRQ_TOP_PHY + SVC_STACK_SIZE);

__TAREA_2_PILA_TOP_PHY     =  0x80742000;
__TAREA_2_PILA_IRQ_TOP_PHY =  (__TAREA_2_PILA_TOP_PHY + IRQ_STACK_SIZE);
__TAREA_2_PILA_SVC_TOP_PHY =  (__TAREA_2_PILA_IRQ_TOP_PHY + SVC_STACK_SIZE);

/* ----------------- TABLES ---------------- */
__TTBR0_KERNEL_  = 0x70080000;
__TTBR0_TAREA_1_ = 0x70480000;
__TTBR0_TAREA_2_ = 0x70880000;

/* ------------------ VMA ------------------ */
__RESET_VMA           = _PUBLIC_RAM_INIT;
__PUBLIC_STACK_VMA    = _PUBLIC_STACK_INIT;

__KERNEL_TXT_VMA        = 0x70030000;
__KERNEL_BSS_VMA        = 0x70022000;
__KERNEL_DATA_VMA       = 0x70032000;
__KERNEL_RODATA_VMA     = 0x70023000;

__TAREA_IDLE_TXT_VMA    = 0x70033000;

__TAREA_1_TXT_VMA       = 0x70F50000;
__TAREA_1_BSS_VMA       = 0x70F53000;
__TAREA_1_DATA_VMA      = 0x70F51000;
__TAREA_1_RODATA_VMA    = 0x70F54000;
__TAREA_1_READ_AREA_VMA = 0X70A00000;

__TAREA_2_TXT_VMA       = 0x70F40000;
__TAREA_2_BSS_VMA       = 0x70F43000;
__TAREA_2_DATA_VMA      = 0x70F41000;
__TAREA_2_RODATA_VMA    = 0x82512000;
__TAREA_2_READ_AREA_VMA = 0X70A10000;

__KERNEL_PILA_IRQ_VMA      = 0x70020000;
__KERNEL_PILA_SYS_VMA      = (__KERNEL_PILA_IRQ_VMA + IRQ_STACK_SIZE);
__KERNEL_PILA_SVC_VMA      = (__KERNEL_PILA_SYS_VMA + SYS_STACK_SIZE);
__KERNEL_PILA_UND_VMA      = (__KERNEL_PILA_SVC_VMA + SVC_STACK_SIZE);
__KERNEL_PILA_ABT_VMA      = (__KERNEL_PILA_UND_VMA + UND_STACK_SIZE);

__TAREA_IDLE_PILA_TOP_VMA     =   0x70F32000;
__TAREA_IDLE_PILA_IRQ_TOP_VMA =  (__TAREA_IDLE_PILA_TOP_VMA + IRQ_STACK_SIZE);
__TAREA_IDLE_PILA_SVC_TOP_VMA =  (__TAREA_IDLE_PILA_IRQ_TOP_VMA + SVC_STACK_SIZE);

__TAREA_1_PILA_TOP_VMA     =   0x70F52000;
__TAREA_1_PILA_IRQ_TOP_VMA =  (__TAREA_1_PILA_TOP_VMA + IRQ_STACK_SIZE);
__TAREA_1_PILA_SVC_TOP_VMA =  (__TAREA_1_PILA_IRQ_TOP_VMA + SVC_STACK_SIZE);

__TAREA_2_PILA_TOP_VMA     =  0x70F42000;
__TAREA_2_PILA_IRQ_TOP_VMA =  (__TAREA_2_PILA_TOP_VMA + IRQ_STACK_SIZE);
__TAREA_2_PILA_SVC_TOP_VMA =  (__TAREA_2_PILA_IRQ_TOP_VMA + SVC_STACK_SIZE);
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

    __text_size__ = SIZEOF(.text);

	/*Datos y variables globales inicializadas*/
	.data : {*(.data*) } > public_ram  /* Defino la seccion de memoria donde quiero que se asocie */

	.bss : {
		. = ALIGN(4); 
		__bss_start__ = .; 
		*(.bss*)
		__bss_end__ = .;
	} > public_ram

    /* ------------------------------ Kernel ------------------------------ */
    /* Código de kernel */    
    __KERNEL_TXT_LMA = .;
    .kernel __KERNEL_TXT_VMA : AT (__KERNEL_TXT_LMA)
    { 
        *(.kernel_text*) 
        *(.tarea_idle_text);
        . = ALIGN(4); 
        } > public_ram
    __kernel_size__ = SIZEOF(.kernel);

    /* BSS de kernel */ 
    __KERNEL_BSS_LMA = __kernel_size__ + LOADADDR(.kernel);
    .kernel_bss __KERNEL_BSS_VMA : AT(__KERNEL_BSS_LMA)
        {
            *(.kernel_bss*);
            . = ALIGN(4); 
        } > public_ram
    __kernel_bss_size__ = SIZEOF(.kernel_bss);

    /* Data de kernel */ 
    __KERNEL_DATA_LMA = __kernel_bss_size__ + LOADADDR(.kernel_bss);
    .kernel_data __KERNEL_DATA_VMA : AT(__KERNEL_DATA_LMA)
        {
            *(.kernel_data*);
            . = ALIGN(4);
        } > public_ram
    __kernel_data_size__ = SIZEOF(.kernel_data);

    /* RO_Data de kernel */
    __KERNEL_RODATA_LMA = __kernel_data_size__ + LOADADDR(.kernel_data);
    .kernel_rodata __KERNEL_RODATA_VMA : AT(__KERNEL_RODATA_LMA)
        {
            *(.kernel_rodata*);
            . = ALIGN(4);        
        } > public_ram
    __kernel_rodata_size__ = SIZEOF(.kernel_rodata);
    /* -------------------------- Tarea Idle ------------------------------ */
    /* Código de Tarea 1 */ 
    __TAREA_IDLE_TXT_LMA = __kernel_rodata_size__ + LOADADDR(.kernel_rodata);
    .txt_tarea_idle __TAREA_IDLE_TXT_VMA : AT(__TAREA_IDLE_TXT_LMA)
        {
            *(.tarea_idle_txt*);
            . = ALIGN(4);
        } 
    __txt_tarea_idle_size__ = SIZEOF(.txt_tarea_idle);    

   
    /* ------------------------------ Tarea 1 ------------------------------ */

    /* Código de Tarea 1 */ 
    __TAREA_1_TXT_LMA = __txt_tarea_idle_size__ + LOADADDR(.txt_tarea_idle);
    .txt_tarea_1 __TAREA_1_TXT_VMA : AT(__TAREA_1_TXT_LMA)
        {
            *(.tarea_1_txt*);
            . = ALIGN(4);
        } 
    __txt_tarea_1_size__ = SIZEOF(.txt_tarea_1);    

    /* BSS de Tarea 1 */ 
    __TAREA_1_BSS_LMA = __txt_tarea_1_size__ + LOADADDR(.txt_tarea_1);
    .bss_tarea_1 __TAREA_1_BSS_VMA : AT(__TAREA_1_BSS_LMA)
        {
            *(.tarea_1_bss*);
            . = ALIGN(4); 
        } > public_ram
    __bss_tarea_1_size__ = SIZEOF(.bss_tarea_1);

    /* Data de Tarea 1 */ 
    __TAREA_1_DATA_LMA = __bss_tarea_1_size__ + LOADADDR(.bss_tarea_1);
    .data_tarea_1 __TAREA_1_DATA_VMA : AT(__TAREA_1_DATA_LMA)
        {
            *(.tarea_1_data*);
            . = ALIGN(4);
        } > public_ram
    __data_tarea_1_size__ = SIZEOF(.data_tarea_1);

    /* RO_Data de Tarea 1 */
    __TAREA_1_RODATA_LMA = __data_tarea_1_size__ + LOADADDR(.data_tarea_1);
    .rodata_tarea_1 __TAREA_1_RODATA_VMA : AT(__TAREA_1_RODATA_LMA)
        {
            *(.tarea_1_rodata*);
            . = ALIGN(4);        
        } > public_ram
    __rodata_tarea_1_size__ = SIZEOF(.rodata_tarea_1);

    /* ------------------------------ Tarea 2 ------------------------------ */

    /* Código de Tarea 2 */ 
    __TAREA_2_TXT_LMA = __rodata_tarea_1_size__ + LOADADDR(.rodata_tarea_1);
    .txt_tarea_2 __TAREA_2_TXT_VMA : AT(__TAREA_2_TXT_LMA)
        {
            *(.tarea_2_txt*);
            . = ALIGN(4);
        } 
    __txt_tarea_2_size__ = SIZEOF(.txt_tarea_2);    

    /* BSS de Tarea 2 */ 
    __TAREA_2_BSS_LMA = __txt_tarea_2_size__ + LOADADDR(.txt_tarea_2);
    .bss_tarea_2 __TAREA_2_BSS_VMA : AT(__TAREA_2_BSS_LMA)
        {
            *(.tarea_2_bss*);
            . = ALIGN(4);
        } > public_ram
    __bss_tarea_2_size__ = SIZEOF(.bss_tarea_2);

    /* Data de Tarea 2 */ 
    __TAREA_2_DATA_LMA = __bss_tarea_2_size__ + LOADADDR(.bss_tarea_2);
    .data_tarea_2 __TAREA_2_DATA_VMA : AT(__TAREA_2_DATA_LMA)
        {
            *(.tarea_2_data*);
            . = ALIGN(4);
        } > public_ram
    __data_tarea_2_size__ = SIZEOF(.data_tarea_2);

    /* RO_Data de Tarea 2 */
    __TAREA_2_RODATA_LMA = __data_tarea_2_size__ + LOADADDR(.data_tarea_2);
    .rodata_tarea_2 __TAREA_2_RODATA_VMA : AT(__TAREA_2_RODATA_LMA)
        {
            *(.tarea_2_rodata*);
            . = ALIGN(4);        
        } > public_ram
    __rodata_tarea_2_size__ = SIZEOF(.rodata_tarea_2);
    
    . = _PUBLIC_STACK_INIT;

    .stack :
    {
        __stack_start__ = .;    /* Guardo en Location Counter donde empieza el stack*/

        . += (IRQ_STACK_SIZE);    /* Le sumo el valor del stack de IRQ */
        . = ALIGN(4);           /* Lo alineo a 4 bytes */
        __irq_stack_top__ = .;   /* Asigno donde empieza el stack de irq, recordar que es full descending (\uparrow)*/

        . += FIQ_STACK_SIZE;
        . = ALIGN(4);
        __fiq_stack_top__ = .;

        . += (SVC_STACK_SIZE);    /* Le sumo el valor del stack de IRQ */
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
