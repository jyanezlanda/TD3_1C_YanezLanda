#include "../inc/mmu.h"
#include <stdint.h>
#include "../inc/mmu_tools_.h"

__attribute__((section(".kernel_text"))) void __mmu_init(void)
{ 
    int i = 0;
    TTBR0 ttbr0 = (TTBR0)((uint32_t) TABLA_PRIMER_NIVEL);
    *((uint32_t *) DIR_FISICA_2) = 0x12345678;

    for(i = 0; i < LONG_TABLES; i++)
        *((uint32_t *)TABLA_PRIMER_NIVEL + i) = 0; // Asi voy hacia direcciones de memoria mas altas

    __lvl1_page_init(0x700 , TABLA_SEGUNDO_NIVEL_A);
    __lvl1_page_init(0x800 , TABLA_SEGUNDO_NIVEL_B);
    __lvl1_page_init(0x1E0 , TABLA_SEGUNDO_NIVEL_GIC);
    __lvl1_page_init(0x000 , TABLA_SEGUNDO_NIVEL_INT);

    __lvl2_page_init(TABLA_SEGUNDO_NIVEL_A, 0x10, DIR_FISICA_1);
    __lvl2_page_init(TABLA_SEGUNDO_NIVEL_A, 0x20, STACK_INIT + 0x0000);
    __lvl2_page_init(TABLA_SEGUNDO_NIVEL_A, 0x21, STACK_INIT + 0x1000);
    __lvl2_page_init(TABLA_SEGUNDO_NIVEL_A, 0x22, STACK_INIT + 0x2000);
    
    __lvl2_page_init(TABLA_SEGUNDO_NIVEL_B, 0x00, DIR_FISICA_2);


   __lvl2_page_init(TABLA_SEGUNDO_NIVEL_GIC, 0x00, DIR_FISICA_GICC);
   __lvl2_page_init(TABLA_SEGUNDO_NIVEL_GIC, 0x01, DIR_FISICA_GICD);

   __lvl2_page_init(TABLA_SEGUNDO_NIVEL_INT, 0x00, DIR_FISICA_INT);
   
    MMU_Set_TTBR0(ttbr0);

    asm("MCR p15, 0, %0 , c3, c0, 0" : : "r"((uint32_t)0x55555555));

    MMU_Enable(MMUENABLE_YES);

}

__attribute__((section(".kernel_text"))) void __lvl1_page_init(uint32_t slot, uint32_t addr)
{
    *( (uint32_t *) (TABLA_PRIMER_NIVEL + slot * 4) ) = addr + LVL1_CTRL_BITS;

    return;
}

__attribute__((section(".kernel_text"))) void __lvl2_page_init(uint32_t addr, uint32_t  slot, uint32_t dir)
{
    *( (uint32_t *) (addr + slot * 4) ) = dir + LVL2_CTRL_BITS;

    return;
}