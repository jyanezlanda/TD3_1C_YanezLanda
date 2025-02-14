.code 32

.global _undefined_handler
.global _swi_handler
.global _prefetch_handler
.global _dabort_handler
.global _RESERVED_
.global _irq_handler
.global _fiq_handler
.extern kernel_handler_irq

.section .handlers
_undefined_handler:
    b .
_swi_handler:
    b .
_prefetch_handler:
    b .
_dabort_handler:
    WFI
_RESERVED_:
    b .
_irq_handler:
    sub lr, lr, #4 /* Se corrige la direccion de retorno de la interrupcion */
    
    stmfd sp!, { r0-r12, lr} /* guardo los registros que puedo modificar */
    mov r7,SP /* antes no lo podia guardar al SP xq lo tenia que ir aumentando para guardar los otros registros */
    mrs r8, spsr /* Guardo el contexto al que tengo que retornar por si en algun momento tengo reentrancia o si lo modifico en la funcion */
    push {r7,r8}

    mov r0,sp
    bl  kernel_handler_irq /*el BL es lo mismo que el BX pero sin cambio de contexto */    
    mov sp,r0 //ACA ACTUALIZO EL SP


    pop {r7, r8}
    mov sp, r7
    msr spsr, r8
    ldmfd sp!, {r0-r12, pc}^ /* con el '^' le indicas que estas volviendo de una función y que cargue el cpsr con el spsr */
_fiq_handler:
    b .
.end
