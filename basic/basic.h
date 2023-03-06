/**
 * @brief basic.h
 *
 * @param student: Sameer Almaldein
 * @param ID: 679699
 * @param University TU-Chemnitz
 * @param Master : ASE(Automotive Software Engineering )
 */ 

#ifndef _BASIC_H_
#define _BASIC_H_

//********************************************************************************************
//
// including header  files
//
//********************************************************************************************
#include "stm32f10x_conf.h"

#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>
#include <ctype.h>
#include <inttypes.h>
#include <alloca.h>
#include <stdarg.h>
#include <stdalign.h>
#include <limits.h>
#include <syslimits.h>
#include <math.h>
#include <string.h>
//#include <cstring>

//********************************************************************************************
//
// Macros
//
//********************************************************************************************
#define cbit(reg,b)	                        reg&=~((uint32_t)1<<b)
#define sbit(reg,b)	                        reg|=((uint32_t)1<<b)
#define tbit(reg,b)	                        reg^=((uint32_t)1<<b)

#define bit_is_set(data,b)	                ((data)&((uint32_t)1<<b))
#define bit_is_clear(data,b)                !((data)&((uint32_t)1<<b))

#define c_bits(reg,bits)	                reg&=~((uint32_t)bits)
#define s_bits(reg,bits)	                reg|= ((uint32_t)bits)
#define t_bits(reg,bits)	                reg^= ((uint32_t)bits)

#define check_bits_is_set(data,bits)        ((data)&((uint32_t)bits)
#define check_bits_is_clear(data,bits)      !((data)&((uint32_t)bits)

//********************************************************************************************
//
// include header files
//
//********************************************************************************************
#include "structs.h"
#include "time.h"
#include "gpio.h"
 
//#include "pins.h"
//#include "ports.h"
//#include "reg.h"
#include "array.h"
#include "queue.h"

//#include "uart_basic.h"
//#include "twi.h"
//#include "pt100rtd.h"
//#include "NTC.h"
//#include "LM335.h"
//#include "serial_uart.h"
//#include "advanced.h"
//********************************************************************************************
//
// Constants
//
//********************************************************************************************



#endif /* BASIC_BASIC_H_ */
