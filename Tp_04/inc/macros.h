#ifndef __MACRO_LIB_H__
#define __MACRO_LIB_H__

#define reserved_bits(x,y,z) uint8_t reserved##x[z - y + 1];

#endif //__MACRO_LIB_H__