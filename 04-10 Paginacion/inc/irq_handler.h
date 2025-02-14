#ifndef _IRQ_HANDLER
#define _IRQ_HANDLER

#include <stdint.h>

typedef struct _context_t
{
    uint32_t sp, spsr, gpr[13], lr;
}_context_t;

uint32_t kernel_handler_irq(_context_t*);

#endif