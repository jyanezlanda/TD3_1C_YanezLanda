.code 32

.global _start

.extern board_init

.extern _table_size
.extern _table_start
.extern _reset_vector

.extern _undefined_handler
.extern _swi_handler
.extern _prefetch_handler
.extern _dabort_handler
.extern _irq_handler
.extern _fiq_handler

.extern __abt_stack_top__
.extern __fiq_stack_top__
.extern __irq_stack_top__
.extern __svc_stack_top__
.extern __sys_stack_top__
.extern __und_stack_top__

.equ USR_MODE,  0X10 /* USER  según B1.3.1 del Architectural Reference Manager se ve el encoding para cada uno */
.equ FIQ_MODE,  0X11 /* FIQ mode encoding*/
.equ IRQ_MODE,  0X12 /* IRQ mode encoding*/
.equ SVC_MODE,  0X13 /* Supervisor mode encoding */
.equ ABT_MODE,  0X17 /* Abort mode encoding */
.equ UND_MODE,  0X1B /* Undefined mode encoding */
.equ SYS_MODE,  0X1F /* System mode encoding  */
.equ I_BIT,     0X80 /* Desactivar las IRQ (Se desactivan con un '1') */
.equ F_BIT,     0X40 /* Desactivar las FIQ (Se desactivan con un '1') */

.section .startup
_start:
    _TABLE_COPY:
        LDR R0,=#_PUBLIC_TABLE_INIT
        LDR R1,=_table_start
        LDR R2,=#_table_size
    _TABLE_LOOP:
        LDR R3, [R1], #4
        STR R3, [R0], #4

        SUBS R2, #4
        CMP R2, #0
        BNE _TABLE_LOOP
    
    _STACK_INIT:
        MSR cpsr_c,#(IRQ_MODE | I_BIT | F_BIT)  /*Se carga en los bits de modo el modo que se va a cargar y tambien se desactivan las interrupciones */
        LDR SP,=__irq_stack_top__               /* Se le carga al SP el fondo de la memoria para el modo determinado */

        MSR cpsr_c,#(FIQ_MODE | I_BIT | F_BIT)
        LDR SP,=__fiq_stack_top__
        
        MSR cpsr_c,#(ABT_MODE | I_BIT | F_BIT)
        LDR SP,=__abt_stack_top__

        MSR cpsr_c,#(UND_MODE | I_BIT | F_BIT)
        LDR SP,=__und_stack_top__

        MSR cpsr_c,#(SYS_MODE | I_BIT | F_BIT)
        LDR SP,=__sys_stack_top__

        MSR cpsr_c,#(SVC_MODE | I_BIT | F_BIT)
        LDR SP,=__svc_stack_top__

        /* Pasamos a una funcion en c donde vamos a inicializar el resto de las cosas y nos olvidamos del assembler */
    _BOARD_START:
        LDR R10,= board_init /* Funcion en C que tiene que llamar a gic_init() y a timer_init() */
        MOV LR, PC  /* Se tiene que hacer en este orden xq sino el PC apunta mal y tendriamos que corregirlo */
        BX R10

        /* ACA TENES QUE ACTIVAR LAS INTERRUPCIONES SON 3 LINEAS DE ASSEMBLER */
        /*MRS R0, cpsr   Carga en R0 el valor del CPSR 
        BIC R1, R0, #0x80
        MSR cpsr,R0*/

        cpsie i
        
    idle:
        WFI         /*Mandas a dormir al procesador hasta que llegue una interrupción */
        B idle      /*Vuelve a idle, el consumo es mínimo */
.end
