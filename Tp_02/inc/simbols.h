#ifndef SIMBOLS
#define SIMBOLS
#include "stddef.h"
#include "stdint.h"
  
extern uint32_t  (_PUBLIC_RAM_INIT);
extern uint32_t  (_PUBLIC_STACK_INIT); 
extern uint32_t  (_PUBLIC_TABLE_INIT);    

extern uint32_t  (IRQ_STACK_SIZE); 
extern uint32_t  (FIQ_STACK_SIZE); 
extern uint32_t  (SVC_STACK_SIZE); 
extern uint32_t  (ABT_STACK_SIZE); 
extern uint32_t  (UND_STACK_SIZE); 
extern uint32_t  (SYS_STACK_SIZE); 

extern uint32_t  (TAREA_1_IRQ_STACK_SIZE); 
extern uint32_t  (TAREA_2_IRQ_STACK_SIZE); 
extern uint32_t  (C_STACK_SIZE);   

/* ------------------ PHYSICAL ------------------ */

/* Vector de reset y código de inicialización */
extern uint32_t  (__RESET_PHYSICAL);       
/* Public stack */
extern uint32_t  (__PUBLIC_STACK_PHYSICAL);
/* ISR Table */

/* Kernel */
extern uint32_t  (__KERNEL_TXT_PHY);  
extern uint32_t  (__KERNEL_BSS_PHY);  
extern uint32_t  (__KERNEL_DATA_PHY); 
extern uint32_t  (__KERNEL_RODATA_PHY);

/* Tablas de paginación*/
extern uint32_t  (__SYSTABLES_PHYSICAL);
extern uint32_t  (__SYSTABLES_TAREA_0_PHY);   
extern uint32_t  (__SYSTABLES_TAREA_1_PHY);
extern uint32_t  (__SYSTABLES_TAREA_2_PHY);

/* Tabla de interrupciones*/
extern uint32_t  (_PUBLIC_TABLE_INIT);

extern uint32_t  (__KERNEL_PILA_PHY);     

/* Tareas */ 
extern uint32_t  (__TAREA_IDLE_TXT_PHY);

extern uint32_t  (__TAREA_1_TXT_PHY);      
extern uint32_t  (__TAREA_1_BSS_PHY);      
extern uint32_t  (__TAREA_1_DATA_PHY);    
extern uint32_t  (__TAREA_1_RODATA_PHY); 
extern uint32_t  (__TAREA_1_READ_AREA_PHY); 

extern uint32_t  (__TAREA_2_TXT_PHY);      
extern uint32_t  (__TAREA_2_BSS_PHY);      
extern uint32_t  (__TAREA_2_DATA_PHY);     
extern uint32_t  (__TAREA_2_RODATA_PHY);   
extern uint32_t  (__TAREA_2_READ_AREA_PHY);

extern uint32_t  (__TAREA_1_PILA_TOP_PHY);     
extern uint32_t  (__TAREA_2_PILA_TOP_PHY);     

/* Stacks */

extern uint32_t  (__KERNEL_PILA_IRQ_PHY);  
extern uint32_t  (__KERNEL_PILA_SYS_PHY);  
extern uint32_t  (__KERNEL_PILA_SVC_PHY);  
extern uint32_t  (__KERNEL_PILA_UND_PHY);  
extern uint32_t  (__KERNEL_PILA_ABT_PHY); 

extern uint32_t  (__TAREA_1_PILA_TOP_VMA); 
extern uint32_t  (__TAREA_2_PILA_TOP_VMA); 


/* ------------------ LMA ------------------ */
extern uint32_t (__KERNEL_TXT_LMA);
extern uint32_t  (__KERNEL_BSS_LMA);
extern uint32_t  (__KERNEL_DATA_LMA);
extern uint32_t  (__KERNEL_RODATA_LMA);

extern uint32_t  (__TAREA_IDLE_TXT_LMA);

extern uint32_t  (__TAREA_1_TXT_LMA);
extern uint32_t  (__TAREA_1_BSS_LMA);
extern uint32_t  (__TAREA_1_DATA_LMA);
extern uint32_t  (__TAREA_1_RODATA_LMA);

extern uint32_t  (__TAREA_2_TXT_LMA);
extern uint32_t  (__TAREA_2_BSS_LMA);
extern uint32_t  (__TAREA_2_DATA_LMA);
extern uint32_t  (__TAREA_2_RODATA_LMA);
/* ------------------ VMA ------------------ */

/* Vector de reset y código de inicialización */
extern uint32_t  (__RESET_VMA);            

/* Public stack */
extern uint32_t  (__PUBLIC_STACK_VMA);     
     

/* Kernel */

extern uint32_t  (__KERNEL_TXT_VMA);       
extern uint32_t  (__KERNEL_BSS_VMA);       
extern uint32_t  (__KERNEL_DATA_VMA);      
extern uint32_t  (__KERNEL_RODATA_VMA);    

/* Tareas */
extern uint32_t  (__TAREA_IDLE_TXT_VMA);

extern uint32_t  (__TAREA_1_TXT_VMA);      
extern uint32_t  (__TAREA_1_BSS_VMA);      
extern uint32_t  (__TAREA_1_DATA_VMA);     
extern uint32_t  (__TAREA_1_RODATA_VMA);
extern uint32_t  (__TAREA_1_READ_AREA_VMA);

extern uint32_t  (__TAREA_2_TXT_VMA);      
extern uint32_t  (__TAREA_2_BSS_VMA);      
extern uint32_t  (__TAREA_2_DATA_VMA);     
extern uint32_t  (__TAREA_2_RODATA_VMA);
extern uint32_t  (__TAREA_2_READ_AREA_VMA);   
  

/* Stacks */
extern uint32_t  (__KERNEL_PILA_IRQ_VMA);  
extern uint32_t  (__KERNEL_PILA_SYS_VMA);  
extern uint32_t  (__KERNEL_PILA_SVC_VMA);  
extern uint32_t  (__KERNEL_PILA_UND_VMA);  
extern uint32_t  (__KERNEL_PILA_ABT_VMA);  

extern uint32_t  (__TAREA_1_PILA_IRQ_VMA); 
extern uint32_t  (__TAREA_1_PILA_SYS_VMA); 
extern uint32_t  (__TAREA_1_PILA_SVC_VMA); 
 

extern uint32_t  (__TAREA_2_PILA_IRQ_VMA); 
extern uint32_t  (__TAREA_2_PILA_SYS_VMA); 
extern uint32_t  (__TAREA_2_PILA_SVC_VMA); 

extern uint32_t    __kernel_size__;
extern uint32_t    __kernel_bss_size__;
extern uint32_t    __kernel_data_size__;
extern uint32_t    __kernel_rodata_size__;

extern uint32_t    __txt_tarea_idle_size__;

extern uint32_t    __txt_tarea_1_size__;
extern uint32_t    __bss_tarea_1_size__;
extern uint32_t    __data_tarea_1_size__;
extern uint32_t    __rodata_tarea_1_size__;

extern uint32_t    __txt_tarea_2_size__;
extern uint32_t    __bss_tarea_2_size__;
extern uint32_t    __data_tarea_2_size__;
extern uint32_t    __rodata_tarea_2_size__;

#endif