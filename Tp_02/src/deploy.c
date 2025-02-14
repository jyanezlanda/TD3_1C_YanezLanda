#include "../inc/deploy.h"
#include "../inc/simbols.h"


__attribute__((section(".text"))) void memcopy(uint32_t * DIR_LMA, uint32_t * DIR_VMA, uint32_t size)
{
    int i = 0;

    for(i = 0; i < size; i++)
        *(DIR_VMA + i) = *(DIR_LMA + i);
    
    return;
}

__attribute__((section(".text"))) void memdploy(void)
{
    memcopy((uint32_t*) &__KERNEL_TXT_LMA,(uint32_t *) &__KERNEL_TXT_PHY,(uint32_t) &__kernel_size__);
    memcopy((uint32_t*) &__KERNEL_BSS_LMA,(uint32_t *) &__KERNEL_BSS_PHY,(uint32_t) &__kernel_bss_size__);
    memcopy((uint32_t*) &__KERNEL_DATA_LMA,(uint32_t *) &__KERNEL_DATA_PHY,(uint32_t) &__kernel_data_size__);
    memcopy((uint32_t*) &__KERNEL_RODATA_LMA,(uint32_t *) &__KERNEL_RODATA_PHY,(uint32_t) &__kernel_rodata_size__);

    memcopy((uint32_t*) &__TAREA_IDLE_TXT_LMA,(uint32_t *) &__TAREA_IDLE_TXT_PHY,(uint32_t) &__txt_tarea_idle_size__);

   /* memcopy((uint32_t*) &__TAREA_0_TXT_LMA,(uint32_t *) &__TAREA_0_TXT_PHY,(uint32_t) &__txt_tarea_0_size__);
    memcopy((uint32_t*) &__TAREA_0_BSS_LMA,(uint32_t *) &__TAREA_0_BSS_PHY,(uint32_t) &__bss_tarea_0_size__);
    memcopy((uint32_t*) &__TAREA_0_DATA_LMA,(uint32_t *) &__TAREA_0_DATA_PHY,(uint32_t) &__data_tarea_0_size__);
    memcopy((uint32_t*) &__TAREA_0_RODATA_LMA,(uint32_t *) &__TAREA_0_RODATA_PHY,(uint32_t) &__rodata_tarea_0_size__);*/

    memcopy((uint32_t*) &__TAREA_1_TXT_LMA,(uint32_t *) &__TAREA_1_TXT_PHY,(uint32_t) &__txt_tarea_1_size__);
    memcopy((uint32_t*) &__TAREA_1_BSS_LMA,(uint32_t *) &__TAREA_1_BSS_PHY,(uint32_t) &__bss_tarea_1_size__);
    memcopy((uint32_t*) &__TAREA_1_DATA_LMA,(uint32_t *) &__TAREA_1_DATA_PHY,(uint32_t) &__data_tarea_1_size__);
    memcopy((uint32_t*) &__TAREA_1_RODATA_LMA,(uint32_t *) &__TAREA_1_RODATA_PHY,(uint32_t) &__rodata_tarea_1_size__);

    memcopy((uint32_t*) &__TAREA_2_TXT_LMA,(uint32_t *) &__TAREA_2_TXT_PHY,(uint32_t) &__txt_tarea_2_size__);
    memcopy((uint32_t*) &__TAREA_2_BSS_LMA,(uint32_t *) &__TAREA_2_BSS_PHY,(uint32_t) &__bss_tarea_2_size__);
    memcopy((uint32_t*) &__TAREA_2_DATA_LMA,(uint32_t *) &__TAREA_2_DATA_PHY,(uint32_t) &__data_tarea_2_size__);
    memcopy((uint32_t*) &__TAREA_2_RODATA_LMA,(uint32_t *) &__TAREA_2_RODATA_PHY,(uint32_t) &__rodata_tarea_2_size__);
}