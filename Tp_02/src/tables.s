.code 32

.global _table_start
.global _table_size

.extern _reset_vector
.extern _undefined_handler
.extern _swi_handler
.extern _prefetch_handler
.extern _dabort_handler
.extern _irq_handler
.extern _fiq_handler

.section .table_start
_table_start:
    ldr pc, addr_reset_vector
    ldr pc, addr_undefined_handler
    ldr pc, addr_swi_handler
    ldr pc, addr_prefetch_handler
    ldr pc, addr_dabort_handler
    ldr pc, addr_reset_vector
    ldr pc, addr_irq_handler
    ldr pc, addr_fiq_handler

addr_reset_vector          :.word _reset_vector  // Asi se define el literal pool
addr_undefined_handler     :.word _undefined_handler
addr_swi_handler           :.word _swi_handler
addr_prefetch_handler      :.word _prefetch_handler
addr_dabort_handler        :.word _dabort_handler
addr_irq_handler           :.word _irq_handler
addr_fiq_handler           :.word _fiq_handler

.equ _table_size, (.-_table_start) 
.end