#include "../inc/mmu.h"
#include <stdint.h>
#include "../inc/mmu_tools_.h"
#include "../inc/timer.h"

__attribute__((section(".kernel_data"))) uint32_t lvl2PageInit = 0;

__attribute__((section(".kernel_text"))) void __lvl1_page_init(uint32_t* ttbr, uint32_t slot)
{
    uint32_t addr = (uint32_t) ttbr + ENTRIES_LVL_1 * 4  + lvl2PageInit * ENTRIES_LVL_2 * 4;

    if(  *( (ttbr + slot ) ) == 0)
    {
        *( (uint32_t *) (ttbr + slot) ) = addr + LVL1_CTRL_BITS;
        lvl2PageInit++;
    }
    return;
}

__attribute__((section(".kernel_text"))) void __lvl2_page_init(uint32_t* addr, uint32_t  slot, uint32_t dir)
{
    if( addr[slot] == 0)
        addr[slot] = dir + LVL2_CTRL_BITS;

    return;
}

__attribute__((section(".kernel_text"))) void __CicloLimpiezaTablas(uint32_t* TTBR0, uint32_t size)
{
    uint32_t i = 0;

    for(i = 0; i < size; i++)
        *(TTBR0 + i) = 0;
    
    return;
}

__attribute__((section(".kernel_text"))) void __PageInit(uint32_t *TTBR0, uint32_t dirLogica, uint32_t dirFisica)
{
    uint32_t slotLvl1 = (dirLogica & SLOTLVL1_MASK) >> 20;
    __lvl1_page_init( TTBR0, slotLvl1);

    uint32_t* addrLvl2 = (uint32_t *) (( *(TTBR0 + slotLvl1) ) & 0xFFFFFF00);

    uint32_t slotLvl2 = (dirLogica & SLOTLVL2_MASK) >> 12;

    __lvl2_page_init( addrLvl2, slotLvl2, dirFisica);
}

__attribute__((section(".kernel_text"))) void __mmu_init(void)
{ 
    TTBR0 ttbr0Kernel = (TTBR0)((uint32_t) &__SYSTABLES_PHYSICAL);
    uint32_t i = 0;

    __CicloLimpiezaTablas((uint32_t *)&__SYSTABLES_PHYSICAL, ENTRIES_LVL_1);
    __CicloLimpiezaTablas((uint32_t *)&__SYSTABLES_TAREA_1_PHY, ENTRIES_LVL_1);
    __CicloLimpiezaTablas((uint32_t *)&__SYSTABLES_TAREA_2_PHY, ENTRIES_LVL_1);
    

/*                                  PAGINACION DEL KERNEL                                                       */
    __PageInit((uint32_t *) &__SYSTABLES_PHYSICAL,(uint32_t) &__KERNEL_TXT_VMA, (uint32_t) &__KERNEL_TXT_PHY);
    __PageInit((uint32_t *) &__SYSTABLES_PHYSICAL,(uint32_t) ((uint32_t)&__KERNEL_TXT_VMA + 0x1000), (uint32_t) ((uint32_t)&__KERNEL_TXT_PHY + 0x1000));
    __PageInit((uint32_t *) &__SYSTABLES_PHYSICAL,(uint32_t) &__KERNEL_DATA_VMA, (uint32_t) &__KERNEL_DATA_PHY);
    __PageInit((uint32_t *) &__SYSTABLES_PHYSICAL,(uint32_t) &__KERNEL_RODATA_VMA, (uint32_t) &__KERNEL_RODATA_PHY);
    __PageInit((uint32_t *) &__SYSTABLES_PHYSICAL,(uint32_t) &__KERNEL_BSS_VMA, (uint32_t) &__KERNEL_BSS_PHY);
    __PageInit((uint32_t *) &__SYSTABLES_PHYSICAL,(uint32_t) &_PUBLIC_STACK_INIT, (uint32_t) &_PUBLIC_STACK_INIT);

    __PageInit((uint32_t *) &__SYSTABLES_PHYSICAL,(uint32_t) &__TAREA_IDLE_TXT_VMA, (uint32_t) &__TAREA_IDLE_TXT_PHY);

    __PageInit((uint32_t *) &__SYSTABLES_PHYSICAL, DIR_FISICA_GICC,  DIR_FISICA_GICC);
    __PageInit((uint32_t *) &__SYSTABLES_PHYSICAL, DIR_FISICA_GICD,  DIR_FISICA_GICD);
    __PageInit((uint32_t *) &__SYSTABLES_PHYSICAL, DIR_FISICA_INT,   DIR_FISICA_INT);

    __PageInit((uint32_t *) &__SYSTABLES_PHYSICAL,(uint32_t) &__RESET_VMA,(uint32_t) &__RESET_PHYSICAL);
    __PageInit((uint32_t *) &__SYSTABLES_PHYSICAL,(uint32_t) &_PUBLIC_TABLE_INIT,(uint32_t) &_PUBLIC_TABLE_INIT);

    __PageInit((uint32_t *) &__SYSTABLES_PHYSICAL,TIMER01_ADDR, TIMER01_ADDR);

/*                                  PAGINACION DE TAREA 1                                                       */

    __PageInit((uint32_t *) &__SYSTABLES_TAREA_1_PHY,(uint32_t) &__KERNEL_TXT_VMA, (uint32_t) &__KERNEL_TXT_PHY);
    __PageInit((uint32_t *) &__SYSTABLES_TAREA_1_PHY,((uint32_t)&__KERNEL_TXT_VMA + 0x1000), (uint32_t) ((uint32_t)&__KERNEL_TXT_PHY + 0x1000));
    __PageInit((uint32_t *) &__SYSTABLES_TAREA_1_PHY,(uint32_t) &__KERNEL_DATA_VMA, (uint32_t) &__KERNEL_DATA_PHY);
    __PageInit((uint32_t *) &__SYSTABLES_TAREA_1_PHY,(uint32_t) &__KERNEL_RODATA_VMA, (uint32_t) &__KERNEL_RODATA_PHY);
    __PageInit((uint32_t *) &__SYSTABLES_TAREA_1_PHY,(uint32_t) &__KERNEL_BSS_VMA, (uint32_t) &__KERNEL_BSS_PHY);
    //__PageInit((uint32_t *) &__SYSTABLES_TAREA_1_PHY,(uint32_t) &_PUBLIC_STACK_INIT, (uint32_t) &_PUBLIC_STACK_INIT);

    __PageInit((uint32_t *) &__SYSTABLES_TAREA_1_PHY, DIR_FISICA_GICC,  DIR_FISICA_GICC);
    __PageInit((uint32_t *) &__SYSTABLES_TAREA_1_PHY, DIR_FISICA_GICD,  DIR_FISICA_GICD);
    __PageInit((uint32_t *) &__SYSTABLES_TAREA_1_PHY, DIR_FISICA_INT,   DIR_FISICA_INT);

    __PageInit((uint32_t *) &__SYSTABLES_TAREA_1_PHY,(uint32_t) &__RESET_VMA,(uint32_t) &__RESET_PHYSICAL);
    __PageInit((uint32_t *) &__SYSTABLES_TAREA_1_PHY,(uint32_t) &_PUBLIC_TABLE_INIT,(uint32_t) &_PUBLIC_TABLE_INIT);

    __PageInit((uint32_t *) &__SYSTABLES_TAREA_1_PHY,TIMER01_ADDR, TIMER01_ADDR);

    __PageInit((uint32_t *) &__SYSTABLES_TAREA_1_PHY,(uint32_t) &__TAREA_1_TXT_VMA, (uint32_t) &__TAREA_1_TXT_PHY);
    __PageInit((uint32_t *) &__SYSTABLES_TAREA_1_PHY,(uint32_t) &__TAREA_1_DATA_VMA, (uint32_t) &__TAREA_1_DATA_PHY);
    __PageInit((uint32_t *) &__SYSTABLES_TAREA_1_PHY,(uint32_t) &__TAREA_1_RODATA_VMA, (uint32_t) &__TAREA_1_RODATA_PHY);
    __PageInit((uint32_t *) &__SYSTABLES_TAREA_1_PHY,(uint32_t) &__TAREA_1_BSS_VMA, (uint32_t) &__TAREA_1_BSS_PHY);
    for(i = 0; i < 16; i++)
        __PageInit((uint32_t *) &__SYSTABLES_TAREA_1_PHY,((uint32_t) &__TAREA_1_READ_AREA_VMA + 0x1000 * i), ((uint32_t) &__TAREA_1_READ_AREA_PHY + 0x1000 * i));

    __PageInit((uint32_t *) &__SYSTABLES_TAREA_1_PHY,(uint32_t) &__TAREA_1_PILA_TOP_VMA, (uint32_t) &__TAREA_1_PILA_TOP_PHY);
    

/*                                  PAGINACION DE TAREA 2                                                       */

    __PageInit((uint32_t *) &__SYSTABLES_TAREA_2_PHY,(uint32_t) &__KERNEL_TXT_VMA, (uint32_t) &__KERNEL_TXT_PHY);
    __PageInit((uint32_t *) &__SYSTABLES_TAREA_2_PHY,((uint32_t)&__KERNEL_TXT_VMA + 0x1000), (uint32_t) ((uint32_t)&__KERNEL_TXT_PHY + 0x1000));
    __PageInit((uint32_t *) &__SYSTABLES_TAREA_2_PHY,(uint32_t) &__KERNEL_DATA_VMA, (uint32_t) &__KERNEL_DATA_PHY);
    __PageInit((uint32_t *) &__SYSTABLES_TAREA_2_PHY,(uint32_t) &__KERNEL_RODATA_VMA, (uint32_t) &__KERNEL_RODATA_PHY);
    __PageInit((uint32_t *) &__SYSTABLES_TAREA_2_PHY,(uint32_t) &__KERNEL_BSS_VMA, (uint32_t) &__KERNEL_BSS_PHY);
    //__PageInit((uint32_t *) &__SYSTABLES_TAREA_2_PHY,(uint32_t) &_PUBLIC_STACK_INIT, (uint32_t) &_PUBLIC_STACK_INIT);

    __PageInit((uint32_t *) &__SYSTABLES_TAREA_2_PHY, DIR_FISICA_GICC,  DIR_FISICA_GICC);
    __PageInit((uint32_t *) &__SYSTABLES_TAREA_2_PHY, DIR_FISICA_GICD,  DIR_FISICA_GICD);
    __PageInit((uint32_t *) &__SYSTABLES_TAREA_2_PHY, DIR_FISICA_INT,   DIR_FISICA_INT);

    __PageInit((uint32_t *) &__SYSTABLES_TAREA_2_PHY,(uint32_t) &__RESET_VMA,(uint32_t) &__RESET_PHYSICAL);
    __PageInit((uint32_t *) &__SYSTABLES_TAREA_2_PHY,(uint32_t) &_PUBLIC_TABLE_INIT,(uint32_t) &_PUBLIC_TABLE_INIT);

    __PageInit((uint32_t *) &__SYSTABLES_TAREA_2_PHY,TIMER01_ADDR, TIMER01_ADDR);

    __PageInit((uint32_t *) &__SYSTABLES_TAREA_2_PHY,(uint32_t) &__TAREA_2_TXT_VMA, (uint32_t) &__TAREA_2_TXT_PHY);
    __PageInit((uint32_t *) &__SYSTABLES_TAREA_2_PHY,(uint32_t) &__TAREA_2_DATA_VMA, (uint32_t) &__TAREA_2_DATA_PHY);
    __PageInit((uint32_t *) &__SYSTABLES_TAREA_2_PHY,(uint32_t) &__TAREA_2_RODATA_VMA, (uint32_t) &__TAREA_2_RODATA_PHY);
    __PageInit((uint32_t *) &__SYSTABLES_TAREA_2_PHY,(uint32_t) &__TAREA_2_BSS_VMA, (uint32_t) &__TAREA_2_BSS_PHY);
    for(i = 0; i < 16; i++)
        __PageInit((uint32_t *) &__SYSTABLES_TAREA_2_PHY,((uint32_t) &__TAREA_2_READ_AREA_VMA + 0x1000 * i), ((uint32_t) &__TAREA_2_READ_AREA_PHY + 0x1000 * i));

    __PageInit((uint32_t *) &__SYSTABLES_TAREA_2_PHY,(uint32_t) &__TAREA_2_PILA_TOP_VMA, (uint32_t) &__TAREA_2_PILA_TOP_PHY);


    MMU_Set_TTBR0(ttbr0Kernel);

    asm("MCR p15, 0, %0 , c3, c0, 0" : : "r"((uint32_t)0x55555555));

    MMU_Enable(MMUENABLE_YES);
}