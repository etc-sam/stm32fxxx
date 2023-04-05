/**
 * @brief mem.h
 *  this header declare mem algorithems to be implmented 
 * that support memory allocation and process manipulation
 * 
 * @param student: Sameer Almaldein
 * @param ID:679699
 * @param University TU-Chemnitz
 * @param Master : ASE(Automotive Software Engineering )
 */ 


#ifndef _MEM_H_
#define _MEM_H_

//********************************************************************************************
//
// including header  files
//
//********************************************************************************************
#include <stdlib.h>
#include <stdio.h>
#include <stddef.h>
#include <stdint.h>
#include <stdarg.h>
#include <stdalign.h>
#include <ctype.h>
#include <inttypes.h>
#include <math.h>

#include <alloca.h>
#include <limits.h>
#include <syslimits.h>
#include <string.h>

//********************************************************************************************
//
//    constants
//
//********************************************************************************************

//********************************************************************************************
//
// macros
//
//********************************************************************************************


//********************************************************************************************
//
//  data structures
//
//********************************************************************************************

//********************************************************************************************
//
// global variables
//
//********************************************************************************************


//********************************************************************************************
//
//  function prototypes
//
//********************************************************************************************
//! find the substring s in the long string l and return a pointer for it

extern void * memmem(const void *l, size_t l_len, const void *s, size_t s_len);

#endif /* _MEM_H_ */