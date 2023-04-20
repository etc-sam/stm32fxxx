/**
 * @brief structs.c
 *
 * @param student: Sameer Almaldein
 * @param ID: 679699
 * @param University TU-Chemnitz
 * @param Master : ASE(Automotive Software Engineering )
 */ 


#ifndef STRUCTS_H_
#define STRUCTS_H_

#define BYTE		0
#define WORD		1
#define DWORD		2
#define REAL		3
#define UREAL		4
#define SECOND		5
#define MINUTE		6
#define HOUR		7
#define PERIOD		8
#define TIME		9
#define DATE		10
#define PASSWORD	11
#define ID			12
#define INDP		13


//********************************************************************************************
//
//  Common integers Structure(Little and big endian order)
//
//********************************************************************************************

/**
 * @brief Little-endian format for one byte (8bits)
 * @details Little -Endian format for one byte 
 * 			with some extra bit access simplify 
 * 			reversing with Big endian 
 */
typedef union _BYTE_BITS
{
    uint8_t  byte;
    struct
    {
        uint8_t bit0:1;
        uint8_t bit1:1;
        uint8_t bit2:1;
        uint8_t bit3:1;
        uint8_t bit4:1;
        uint8_t bit5:1;
        uint8_t bit6:1;
        uint8_t bit7:1;
    };
} BYTE_BITS;
/**
 * @brief Little-endian format for one word (16bits)
 * @details Little -Endian format for one word 
 * 			with some extra bit access simplify 
 * 			reversing with Big endian format
 */
typedef union _WORD_BYTES
{
	uint16_t word;
	uint8_t bytes[2];
    struct
    {
		uint8_t low;
		uint8_t high;
    }byte;
    struct
    {
    	uint8_t bit0:1;
    	uint8_t bit1:1;
    	uint8_t bit2:1;
    	uint8_t bit3:1;
    	uint8_t bit4:1;
    	uint8_t bit5:1;
    	uint8_t bit6:1;
    	uint8_t bit7:1;
    	uint8_t bit8:1;
    	uint8_t bit9:1;
    	uint8_t bit10:1;
    	uint8_t bit11:1;
    	uint8_t bit12:1;
    	uint8_t bit13:1;
    	uint8_t bit14:1;
    	uint8_t bit15:1;
    }bits;
} WORD_BYTES;

/**
 * @brief Little-endian format for one double word (32-bits)
 * @details Little -Endian format for double word 
 * 			with some extra bit access simplify 
 * 			reversing with Big endian format
 */

typedef union _DWORD_BYTE
{
	uint32_t dword;
	uint16_t words[2];
	uint8_t bytes[4];
    struct
    {
		uint16_t low;
		uint16_t high;
    } word;
	struct
	{
		uint8_t byte0;
		uint8_t byte1;
		uint8_t byte2;
		uint8_t byte3;
	} byte;

    struct
    {
    	uint8_t bit0:1;
    	uint8_t bit1:1;
    	uint8_t bit2:1;
    	uint8_t bit3:1;
    	uint8_t bit4:1;
    	uint8_t bit5:1;
    	uint8_t bit6:1;
    	uint8_t bit7:1;
    	uint8_t bit8:1;
    	uint8_t bit9:1;
    	uint8_t bit10:1;
    	uint8_t bit11:1;
    	uint8_t bit12:1;
    	uint8_t bit13:1;
    	uint8_t bit14:1;
    	uint8_t bit15:1;
    	uint8_t bit16:1;
    	uint8_t bit17:1;
    	uint8_t bit18:1;
    	uint8_t bit19:1;
    	uint8_t bit20:1;
    	uint8_t bit21:1;
    	uint8_t bit22:1;
    	uint8_t bit23:1;
    	uint8_t bit24:1;
    	uint8_t bit25:1;
    	uint8_t bit26:1;
    	uint8_t bit27:1;
    	uint8_t bit28:1;
    	uint8_t bit29:1;
    	uint8_t bit30:1;
    	uint8_t bit31:1;
    } bits;
} DWORD_BYTES;

/**
 * @brief Little-endian format for one quadrable word (64-bits)
 * @details Little -Endian format for quadrable word 
 * 			with some extra bit access simplify 
 * 			reversing with Big endian format
 */

typedef union _QWORD_BYTE
{
	uint64_t Qword;
	uint32_t Dwords[2];
	uint16_t words[4];
	uint8_t bytes[8];
	struct
	{
		uint32_t low;
		uint32_t high;
	}dword;
   struct
	{
		uint16_t word0;
		uint16_t word1;
		uint16_t word2;
		uint16_t word3;
	}word;
	struct
	{
		uint8_t byte0;
		uint8_t byte1;
		uint8_t byte2;
		uint8_t byte4;
		uint8_t byte5;
		uint8_t byte6;
		uint8_t byte7;		
	} byte;
	struct
	{
		uint8_t bit0:1;
		uint8_t bit1:1;
		uint8_t bit2:1;
		uint8_t bit3:1;
		uint8_t bit4:1;
		uint8_t bit5:1;
		uint8_t bit6:1;
		uint8_t bit7:1;
		uint8_t bit8:1;
		uint8_t bit9:1;
		uint8_t bit10:1;
		uint8_t bit11:1;
		uint8_t bit12:1;
		uint8_t bit13:1;
		uint8_t bit14:1;
		uint8_t bit15:1;
		uint8_t bit16:1;
		uint8_t bit17:1;
		uint8_t bit18:1;
		uint8_t bit19:1;
		uint8_t bit20:1;
		uint8_t bit21:1;
		uint8_t bit22:1;
		uint8_t bit23:1;
		uint8_t bit24:1;
		uint8_t bit25:1;
		uint8_t bit26:1;
		uint8_t bit27:1;
		uint8_t bit28:1;
		uint8_t bit29:1;
		uint8_t bit30:1;
		uint8_t bit31:1;
		
		uint8_t bit32:1;
		uint8_t bit33:1;
		uint8_t bit34:1;
		uint8_t bit35:1;
		uint8_t bit36:1;
		uint8_t bit37:1;
		uint8_t bit38:1;
		uint8_t bit39:1;
		uint8_t bit40:1;
		uint8_t bit41:1;
		uint8_t bit42:1;
		uint8_t bit43:1;
		uint8_t bit44:1;
		uint8_t bit45:1;
		uint8_t bit46:1;
		uint8_t bit47:1;
		uint8_t bit48:1;
		uint8_t bit49:1;
		uint8_t bit50:1;
		uint8_t bit51:1;
		uint8_t bit52:1;
		uint8_t bit53:1;
		uint8_t bit54:1;
		uint8_t bit55:1;
		uint8_t bit56:1;
		uint8_t bit57:1;
		uint8_t bit58:1;
		uint8_t bit59:1;
		uint8_t bit60:1;
		uint8_t bit61:1;
		uint8_t bit62:1;
		uint8_t bit63:1;
	} bits;
} QWORD_BYTES;
//---------------------------------------------------
//Big -Endian format
/**
 * @brief Big-Endian format for one byte (8-bits)
 * @details Big -Endian format for one byte 
 * 			with some extra bit access simplify 
 * 			reversing with little endian format
 */
typedef union _Big_BYTE_BITS
{
    uint8_t  byte;
    struct
    {
        uint8_t bit7:1;
        uint8_t bit6:1;
        uint8_t bit5:1;
        uint8_t bit4:1;
        uint8_t bit3:1;
        uint8_t bit2:1;
        uint8_t bit1:1;
        uint8_t bit0:1;
    };
} Big_BYTE_BITS;

/**
 * @brief Big-Endian format for one word (16-bits)
 * @details Big -Endian format for one word
 * 			with some extra bit access simplify 
 * 			reversing with little endian format
 */
typedef union _Big_WORD_BYTES
{
	uint16_t word;
	uint8_t bytes[2];
    struct
    {
		uint8_t high;
		uint8_t low;
    }byte;
    struct
    {
    	uint8_t bit15:1;
    	uint8_t bit14:1;
    	uint8_t bit13:1;
    	uint8_t bit12:1;
    	uint8_t bit11:1;
    	uint8_t bit10:1;
    	uint8_t bit9:1;
    	uint8_t bit8:1;
    	uint8_t bit7:1;
    	uint8_t bit6:1;
    	uint8_t bit5:1;
    	uint8_t bit4:1;
    	uint8_t bit3:1;
    	uint8_t bit2:1;
    	uint8_t bit1:1;
    	uint8_t bit0:1;
    }bits;
} Big_WORD_BYTES;

/**
 * @brief Big-Endian format for double word (32-bits)
 * @details Big -Endian format for one byte 
 * 			with some extra bit access simplify 
 * 			reversing with little endian format
 */

typedef union _Big_DWORD_BYTE
{
	uint32_t dword;
	uint16_t words[2];
	uint8_t bytes[4];
    
	struct
    {
		uint16_t high;
		uint16_t low;
    } word;

    struct
    {
	    uint8_t byte3;
	    uint8_t byte2;
	    uint8_t byte1;
	    uint8_t byte0;
    } byte;

    struct
    {
    	uint8_t bit31:1;
    	uint8_t bit30:1;
    	uint8_t bit29:1;
    	uint8_t bit28:1;
    	uint8_t bit27:1;
    	uint8_t bit26:1;
    	uint8_t bit25:1;
    	uint8_t bit24:1;
    	uint8_t bit23:1;
    	uint8_t bit22:1;
    	uint8_t bit21:1;
    	uint8_t bit20:1;
    	uint8_t bit19:1;
    	uint8_t bit18:1;
    	uint8_t bit17:1;
    	uint8_t bit16:1;
    	uint8_t bit15:1;
    	uint8_t bit14:1;
    	uint8_t bit13:1;
    	uint8_t bit12:1;
    	uint8_t bit11:1;
    	uint8_t bit10:1;
    	uint8_t bit9:1;
    	uint8_t bit8:1;
    	uint8_t bit7:1;
    	uint8_t bit6:1;
    	uint8_t bit5:1;
    	uint8_t bit4:1;
    	uint8_t bit3:1;
    	uint8_t bit2:1;
    	uint8_t bit1:1;
    	uint8_t bit0:1;
    } bits;

} Big_DWORD_BYTES;

/**
 * @brief 	Big-Endian format for quadrable word (64-bits)
 * @details Big -Endian format for quadrable word 
 * 			with some extra bit access simplify 
 * 			reversing with little endian format
 */

typedef union _Big_QWORD_BYTE
{
	uint64_t Qword;
	uint32_t Dwords[2];
	uint16_t words[4];
	uint8_t bytes[8];
	struct
	{
		uint32_t high;
		uint32_t low;
	}dword;
	struct
	{
		uint16_t word3;
		uint16_t word2;
		uint16_t word1;
		uint16_t word0;
	}word;
	struct
	{
		uint8_t byte7;
		uint8_t byte6;	
		uint8_t byte5;
		uint8_t byte4;
		uint8_t byte2;
		uint8_t byte1;
		uint8_t byte0;
	} byte;
	struct
	{		
		uint8_t bit63:1;
		uint8_t bit62:1;
		uint8_t bit61:1;
		uint8_t bit60:1;
		uint8_t bit59:1;
		uint8_t bit58:1;
		uint8_t bit57:1;
		uint8_t bit56:1;
		uint8_t bit55:1;
		uint8_t bit54:1;
		uint8_t bit53:1;
		uint8_t bit52:1;
		uint8_t bit51:1;
		uint8_t bit50:1;
		uint8_t bit49:1;
		uint8_t bit48:1;
		uint8_t bit47:1;
		uint8_t bit46:1;
		uint8_t bit45:1;
		uint8_t bit44:1;
		uint8_t bit43:1;
		uint8_t bit42:1;
		uint8_t bit41:1;
		uint8_t bit40:1;
		uint8_t bit39:1;
		uint8_t bit38:1;
		uint8_t bit37:1;
		uint8_t bit36:1;
		uint8_t bit35:1;
		uint8_t bit34:1;
		uint8_t bit33:1;
        uint8_t bit32:1;
		uint8_t bit31:1;
		uint8_t bit30:1;
		uint8_t bit29:1;
		uint8_t bit28:1;
		uint8_t bit27:1;
		uint8_t bit26:1;
		uint8_t bit25:1;
		uint8_t bit24:1;
		uint8_t bit23:1;
		uint8_t bit22:1;
		uint8_t bit21:1;
		uint8_t bit20:1;
		uint8_t bit19:1;
		uint8_t bit18:1;
		uint8_t bit17:1;
		uint8_t bit16:1;
		uint8_t bit15:1;
		uint8_t bit14:1;
		uint8_t bit13:1;
		uint8_t bit12:1;
		uint8_t bit11:1;
		uint8_t bit10:1;
		uint8_t bit9:1;
		uint8_t bit8:1;
		uint8_t bit7:1;
		uint8_t bit6:1;
		uint8_t bit5:1;
		uint8_t bit4:1;
		uint8_t bit3:1;
		uint8_t bit2:1;
		uint8_t bit1:1;
		uint8_t bit0:1;		
	} bits;
} Big_QWORD_BYTES;


//********************************************************************************************
//
// Other Formats
//
//********************************************************************************************
/**
 * @brief 	bcd format for one byte
 * @details BCD format for one byte  defines on two nibbles 
 * 			the lower nibble holds the lower  portion of the BCD data byte, while
 * 			the upper nibble holds the higher portion of the BCD data byte
 */
typedef union _bcd_t
{
	uint8_t byte;
	struct
	{
	 uint8_t low_nibble:4;
	 uint8_t high_nibble:4;	
	};
}bcd_t;

/** 
 * @brief 	signed real format 
 * @details  signed real format is used to store float data its three portions
 * 			 this structure very helpful to convert from float to real_t and vice versa
 * 			 before sending in a network bus or displaying on a LCD /GLCD display 	
 *           for example a float number -23.58
 *           decimal holds the decimal part 58 
 *           integer holds the integer part 23
 * 			 sig  holds the sign 0:positive,1: negative  
 */
typedef union _real_t
{
	uint8_t Array[4];
	uint32_t val;

	struct
	{
		uint8_t decimal;
		uint16_t integer;
		uint8_t sig;
	};
}real_t;


/*typedef union _lreal_t
{
	uint8_t Array[9];
	uint64_t val;
	struct
	{
		
		uint32_t decimal;
		uint32_t integer;
		uint8_t sig;
	};
}lreal_t;
*/
typedef struct _lreal_t
{
	unsigned long decimal;
	unsigned long integer;
	uint8_t sig;
	uint8_t zero;

}lreal_t;

/** 
 * @brief 	 unsigned real format (small size 8bit)
 * @details  unsigned real format is used to store float data its two portions
 * 			 this structure very helpful to convert from float to ureal_t and vice versa
 * 			 before sending in a network bus or displaying on a LCD /GLCD display 	
 *           for example a float number 137.76
 *           decimal holds the decimal part 76 
 *           integer holds the integer part 137
 */

typedef union _ureal_t
{
	uint32_t dword;
	uint8_t bytes[4];
	struct
	{
		uint8_t decimal;
		uint16_t integer;
		uint8_t :8;
	};
}ureal_t;

/** 
 * @brief 	 unsigned real format (small size 8bit)
 * @details  unsigned real format is used to store float data its two portions
 * 			 this structure very helpful to convert from float to ureal_t and vice versa
 * 			 before sending in a network bus or displaying on a LCD /GLCD display 	
 *           for example a float number 137.76
 *           decimal holds the decimal part 76 
 *           integer holds the integer part 137
 */
typedef union _usreal_t
{
	uint16_t word;
	uint8_t Array[2];
	struct
	{
		uint8_t decimal;
		uint8_t integer;
	};
}usreal_t;




//********************************************************************************************
//
// Prototype functions
//
//********************************************************************************************
//!< calculates the sum of array of 16bit 
extern uint16_t clc_sum_16bit(uint16_t * ptmp,uint8_t len);
//!< calculates the average method on 16bit result for array of 16bit
extern uint16_t clc_avg_16bit(uint16_t * ptmp,uint8_t len);
//!< calculates the average method on 32bit result for array of 32bit
extern uint32_t clc_avg_32bit(uint32_t * ptmp,uint8_t len);

// real methods 
//!< calclautes the avareage of two real methods
extern real_t avg_real(real_t a,real_t b);
//!< compares between two real numbers 
extern uint8_t cmp_real(real_t a,real_t b);
//!< adds two real numbers
extern real_t add_real(real_t a,real_t b);
//!< substracts two real numbers
extern real_t sub_real(real_t ,real_t);
//!< increments a real number
extern void inc_real(real_t * ptr);
//!< decrements a real number
extern void dec_real(real_t * ptr);

//!< converts float number to real 
extern lreal_t float_to_real(double val,uint8_t digits);
//extern real_t float_to_real(float val,uint8_t digits);
//!< converts real number to float 
extern float  real_to_float(real_t val,uint8_t digits);

// reverse methods 
//!< reverses byte data from big to little endigan or vice versa
extern uint8_t reverse_byte(uint8_t val);
//!< reverses  word data from big to little endigan or vice versa
extern uint16_t reverse_word(uint16_t val);
//!< reverses  double word data from big to little endigan or vice versa
extern uint32_t reverse_dword(uint32_t val);

//!< converts from bcd to binary
extern uint16_t bcd_to_bin(uint8_t bcd);
//!< converts from binary to bcd 
extern uint8_t bin_to_bcd(uint16_t bin_val);


#endif /* STRUCTS_H_ */