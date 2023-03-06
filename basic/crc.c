/**
 * @brief crc.c
 *  this source code for crc implementation 
 * @param student: Sameer Almaldein
 * @param ID: 679699
 * @param University TU-Chemnitz
 * @param Master : ASE(Automotive Software Engineering )
 */ 
//********************************************************************************************
//
// include header files
//
//********************************************************************************************
#include "init.h"

//********************************************************************************************
//
// global variables' declarations 
//
//********************************************************************************************

//********************************************************************************************
//
// static variables' declarations 
//
//********************************************************************************************
static void crc32a_calc_byte(uint8_t val, uint32_t * crc);
static void crc32b_calc_byte(uint8_t val, uint32_t * crc);

//********************************************************************************************
//
//  function definitions
//
//********************************************************************************************
 /**
 * @brief  implements the polynom shifting and xor 
 * 
 * @details implements the polynom shifting and xor 
 *          due to one byte and for each bit of its bits
 *          it uses the reversed Generatorpolynom= 0xEDB88320
 *  
 * @param val  a byte value from the message
 * @param crc   a 32bit pointer to allow nested call for
 * @return nothing 
*/ 
void crc32b_calc_byte(uint8_t val, uint32_t * crc)
{
  uint8_t i=0;
  uint32_t polynom = 0xEDB88320;// Generatorpolynom
  for (i=0; i<8; i++)
  {      
    if ((*crc&1) != (val&1))
        *crc = (*crc>>1) ^polynom; 
    else 
        (*crc) = *crc >>1;
    val >>= 1;
  }

}
//----------------------------------------------------------------------------------------------
 /**
 * @brief  calculate the crc32 as a 32-bit for an array of bytes
 * 
 * @details it uses a reversed crc32 polynominal algorithm that allows to calculate
 *          the crc32 value starting form the least significant bit in the lowest byte in the 
 *          array 
 * @param msg  an array of bytes as the message to calculate the crc32
 * @param len  length of the message 
 * @return 32bit crc 
*/ 
uint32_t crc32b_calc(uint8_t * msg,size_t len)
{
  uint32_t crc=0xFFFFFFFF;
  uint8_t val=0;
  for(size_t i=0;i<len;i++) 
  {
	val=msg[i];
    crc32b_calc_byte(val,(uint32_t*)&crc);
  }	
	return ~crc;
}
//----------------------------------------------------------------------------------------------
 /**
 * @brief  implements the polynom shifting and xor 
 * 
 * @details implements the polynom shifting and xor 
 *          due to one byte and for each bit of its bits
 *          it uses the reversed Generatorpolynom= 0xEDB88320
 *  
 * @param val  a byte value from the message
 * @param crc   a 32bit pointer to allow nested call for
 * @return nothing 
*/ 
void crc32a_calc_byte(uint8_t val, uint32_t * crc)
{
  
  int8_t i=0;
  uint32_t polynom = 0x04C11DB7;// Generatorpolynom
  for (i=0; i<8; i++)
  {      
    if (((*crc>>31)&1) != (val&1))
        *crc = (*crc<<1) ^polynom; 
    else 
        (*crc) = *crc <<1;
    val >>= 1;
  }
}
//----------------------------------------------------------------------------------------------
 /**
 * @brief  calculate the crc32 as a 32-bit for an array of bytes
 * 
 * @details it uses a reversed crc32 polynominal algorithm that allows to calculate
 *          the crc32 value starting form the least significant bit in the lowest byte in the 
 *          array 
 * @param msg  an array of bytes as the message to calculate the crc32
 * @param len  length of the message 
 * @return 32bit crc 
*/ 
uint32_t crc32a_calc(uint8_t * msg,size_t len)
{
  uint32_t crc=0xffffffff;
  uint8_t val=0;
  for(size_t i=0;i<len;i++) 
  {
	  val=msg[i];
    crc32a_calc_byte(val,(uint32_t*)&crc);
  }	
  crc=reverse_dword(crc);
	return ~crc;
}
//----------------------------------------------------------------------------------------------
/**
 * @brief calculate the crc 32 as reversed or normal one for a given message based on a type given
 * 
 * @param msg       the message to calculate the crc32
 * @param len       the message length   
 * @param type      type of crc to calculate 
 * @return uint32_t 
 */
uint32_t crc32_calc_as(uint8_t * msg,size_t len,uint8_t type)
{
  switch (type)
  {
    case 0: return crc32a_calc(msg,len); // normal crc
    case 1: return crc32b_calc(msg,len); // reversed crc
  }
    return crc32b_calc(msg,len); 
}
//----------------------------------------------------------------------------------------------
uint32_t crc32_calc(uint8_t * msg,size_t len)
{
  return crc32b_calc(msg,len);
}
//----------------------------------------------------------------------------------------------
