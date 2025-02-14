#include <stddef.h>
#include <stdint.h>
#include "macros.h"


void __mmu_init(void);
void __lvl1_page_init(uint32_t slot, uint32_t addr);

void __lvl2_page_init(uint32_t addr, uint32_t  slot, uint32_t dir);

#define LARGO_TABLA_L1          0x1000*4 // en bytes
#define LARGO_TABLA_L2          0x400    // en bytes

#define LVL1_CTRL_BITS          0x1
#define LVL2_CTRL_BITS          0x32

#define TABLA_PRIMER_NIVEL      0x70080000

#define TABLA_SEGUNDO_NIVEL_A       0x70090000
#define TABLA_SEGUNDO_NIVEL_B       0X700A0000
#define TABLA_SEGUNDO_NIVEL_GIC     0x700A1000
#define TABLA_SEGUNDO_NIVEL_INT     0X700A2000

#define DIR_FISICA_1                0x70010000
#define DIR_FISICA_2                0x70020000

#define DIR_FISICA_GICC             0x1E000000
#define DIR_FISICA_GICD             0x1E001000
#define DIR_FISICA_INT              0x00000000

#define STACK_INIT                  0x70020000
#define LONG_TABLES                 (TABLA_SEGUNDO_NIVEL_B + LARGO_TABLA_L2 - TABLA_PRIMER_NIVEL)/4 // La cuenta da en bytes, se divide por 4 ya que se usa aritmetica de punteros
