/**
 * @brief crc.h
 *  this header declare crc algorithems to be implmented the Frame checksum
 * 
 * @param student: Sameer Almaldein
 * @param ID:679699
 * @param University TU-Chemnitz
 * @param Master : ASE(Automotive Software Engineering )
 */ 


#ifndef CRC_H_
#define CRC_H_


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
// macros Definitions
//
//********************************************************************************************

//********************************************************************************************
//
//  data structures
//
//********************************************************************************************
/**
 * @brief crc32 structs 
 * @details a 32-bit data typed define as a union which
 * have multiple parts as words, or bytes 
 */
typedef union _CRC32_t
{
  uint32_t dword;
  struct
  {	 
	  uint16_t low;
	  uint16_t high;
  }word; 
  struct
  {	 
	  uint8_t low;
	  uint8_t high;
	  uint8_t upper; 
	  uint8_t most;
  }byte;  	

}crc32_t;
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
//! calculate the crc32 for an array of bytes the normal
extern uint32_t crc32_calc(uint8_t * msg,size_t len);

//! calculate the crc32 for an array of bytes the normal or reversed
extern uint32_t crc32_calc_as(uint8_t * msg,size_t len,uint8_t type);

//! calculate the crc32 for an array of bytes 
extern uint32_t crc32a_calc(uint8_t * msg,size_t len);

//! calculate the reversed crc32 for an array of bytes 
extern uint32_t crc32b_calc(uint8_t * msg,size_t len);


#endif /* CRC_H_ */