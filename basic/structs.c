/**
 * @brief structs.c
 *
 * @param student: Sameer Almaldein
 * @param ID: 679699
 * @param University TU-Chemnitz
 * @param Master : ASE(Automotive Software Engineering )
 */ 
 
 //********************************************************************************************
//
//   header files
//
//********************************************************************************************
#include "init.h"

//********************************************************************************************
//
//   global variables
//
//********************************************************************************************

//********************************************************************************************
//
//  average Methods' definitions
//
//********************************************************************************************
/**
 * @brief calculates the sum of array of 16bit 
 * @details this method the sum of an array of words 
 *           which it is used in handling aquired data from adc
 * @param ptmp pointer to the array of words
 * @param len  length of the array
 * @return uint16_t 
 */
uint16_t clc_sum_16bit(uint16_t * ptmp,uint8_t len)
{
	uint16_t sum=0;
	uint8_t i=0;
	for(i=0;i<len;i++)
	sum+=ptmp[i];
	return sum;
}
//--------------------------------------------------------------------------------------------
/**
 * @brief   calculates the average  of an array of words
 * @details this method returns the average of an array of words 
 *           which is very useful in get the average result for 
 * 			 a set of aquired data from adc
 * @param ptmp pointer to the array of words
 * @param len  length of the array
 * @return uint16_t 
 */
uint16_t clc_avg_16bit(uint16_t * ptmp,uint8_t len)
{
	uint32_t sum=0;
	uint8_t i=0;
	for(i=0;i<len;i++)
	sum+=ptmp[i];	
	return sum/len;
}
//---------------------------------------------------------------------------------------------
/**
 * @brief   calculates the average  of an array of double words
 * @details this method returns the average of an array of words 
 * @param ptmp pointer to the array of words
 * @param len  length of the array
 * @return uint32_t 
 */
uint32_t clc_avg_32bit(uint32_t * ptmp,uint8_t len)
{
	uint32_t sum=0;
	uint8_t i=0;
	for(i=0;i<len;i++)
	sum+=ptmp[i];	
	return sum/len;
}
//-------------------------------------------------------------------------------------------------------------------------
//********************************************************************************************
//
//  real Methods' definitions
//  this special methods allow to deal directly with real_t instead of using float
//  suitable solution for low-performance old avr microcontrollers
//
//********************************************************************************************
/**
 * @brief    calculates the average of two real numbers
 * @details  this method allow to get the average of two real_t numbers instead of using float type
 * 			 more convenient solution for low-performance old avr microcontrollers
 * @param a  first real number
 * @param b  second real number 
 * @return real_t 
 */
real_t avg_real(real_t a,real_t b)
{	
	real_t c;
	int16_t d1=0,d2=0,d3=0;
	c.val=0;
	d1=a.integer*10+a.decimal;
	d2=b.integer*10+b.decimal;
	d1=(a.sig==1)?-d1:d1;
	d2=(b.sig==1)?-d2:d2;
	d3=d1+d2;
	c.sig=0;
	if(d3<0)
	{
	 c.sig=1;
	 d3*=-1;
	}
	c.integer=d3/20;
	c.decimal=(d3-c.integer*20)/2;
   return c;
}
//-------------------------------------------------------------------------------------------------------------------------
/**
 * @brief  compares between two real numbers
 * @details this method allow to compare two real_t numbers instead of using float type
 * 			 more convenient solution for low-performance old avr microcontrollers  			 
 * @param  a  first real number
 * @param  b  second real number
 * @retval 0  a == b 
 * @retval 1  a >  b 
 * @retval 2  a < b 
 * @return real_t 
 */
uint8_t cmp_real(real_t a,real_t b)
{
int16_t d1=0,d2=0;
d1=a.integer*10+a.decimal;
d2=b.integer*10+b.decimal;
d1=(a.sig==1)?-d1:d1;
d2=(b.sig==1)?-d2:d2;
 if(d1>d2)
  return 1;
 if(d1<d2)
  return 2;
 
 return 0;
 
}
//--------------------------------------------------------------------------------------------
/**
 * @brief    calculates the addition of two real numbers
 * @details  this method allow to add two real_t numbers instead of using float type
 * 			 more convenient solution for low-performance old avr microcontrollers
 * @param a  first real number
 * @param b  second real number 
 * @return real_t 
 */
real_t add_real(real_t a ,real_t b)
{
	real_t c;
	c.val=0;
	int16_t d1=0,d2=0,d3=0;
	d1=a.integer*10+a.decimal;
	d2=b.integer*10+b.decimal;
	d1=(a.sig==1)?-d1:d1;
	d2=(b.sig==1)?-d2:d2;
	d3=d1+d2;
	c.sig=0;
	if(d3<0)
	{
	 c.sig=1;
	 d3*=-1;
	}
	c.integer=d3/10;
	c.decimal=d3%10;
	return c;
}
//--------------------------------------------------------------------------------------------
/**
 * @brief    calculates the subtraction of two real numbers
 * @details  this method allows to substract two real_t numbers instead of using float type
 * 			 more convenient solution for low-performance old avr microcontrollers
 * @param a  first real number
 * @param b  second real number 
 * @return real_t 
 */
real_t sub_real(real_t a ,real_t b)
{
	//b.integer=0-b.integer;
	b.sig=1;
	return add_real(a,b);
}
//--------------------------------------------------------------------------------------------
/**
 * @brief      increments a real number
 * @details    this method allows to increment an real_t number instead of using float type
 * 			   more convenient solution for low-performance old avr microcontrollers
 * @param ptr  a pointer to  real number (pass by reference)
 * @return real_t 
 */
void inc_real(real_t * ptr)
{
	real_t a;
	a.val=0;	
	a.decimal=1;
	*ptr=add_real((real_t)*ptr,a);

}
//--------------------------------------------------------------------------------------------
/**
 * @brief    decrements a real number
 * @details  this method allows to decrement an real_t number instead of using float type
 * 			 more convenient solution for low-performance old avr microcontrollers
 * @param ptr  a pointer to  real number (pass by reference)
 
 * @return real_t 
 */
void dec_real(real_t * ptr)
{
real_t a;
a.val=0;
a.decimal=1;
*ptr=sub_real((real_t)*ptr,a);
}
//--------------------------------------------------------------------------------------------
//********************************************************************************************
//
//  conversion Methods' definitions
//
//********************************************************************************************
/**
 * @brief 	  reverses a data of byte-size length
 * @details   reverses a data of byte size length from big  endigan to little endigan or vice versa
 * @param val the byte data to be reversed
 * @return uint8_t 
 */
uint8_t reverse_byte(uint8_t val)
{
	BYTE_BITS byt;
	Big_BYTE_BITS rv_byt;
	byt.byte=val;
	rv_byt.bit0=byt.bit0;
	rv_byt.bit1=byt.bit1;
	rv_byt.bit2=byt.bit2;
	rv_byt.bit3=byt.bit3;
	rv_byt.bit4=byt.bit4;
	rv_byt.bit5=byt.bit5;
	rv_byt.bit6=byt.bit6;
	rv_byt.bit7=byt.bit7;
	return rv_byt.byte;
}
//--------------------------------------------------------------------------------------------
/**
 * @brief 	  reverses a data of word-size length
 * @details   reverses a data of word size length from big  endigan to little endigan or vice versa
 * @param val the byte data to be reversed
 * @return uint8_t 
 */
uint16_t reverse_word(uint16_t val)
{
	WORD_BYTES byt;
	Big_WORD_BYTES rv_byt;
	byt.word=val;
	rv_byt.bits.bit0=byt.bits.bit0;
	rv_byt.bits.bit1=byt.bits.bit1;
	rv_byt.bits.bit2=byt.bits.bit2;
	rv_byt.bits.bit3=byt.bits.bit3;
	rv_byt.bits.bit4=byt.bits.bit4;
	rv_byt.bits.bit5=byt.bits.bit5;
	rv_byt.bits.bit6=byt.bits.bit6;
	rv_byt.bits.bit7=byt.bits.bit7;
	rv_byt.bits.bit8=byt.bits.bit8;
	rv_byt.bits.bit9=byt.bits.bit9;
	rv_byt.bits.bit10=byt.bits.bit10;
	rv_byt.bits.bit11=byt.bits.bit11;
	rv_byt.bits.bit12=byt.bits.bit12;
	rv_byt.bits.bit13=byt.bits.bit13;
	rv_byt.bits.bit14=byt.bits.bit14;
	rv_byt.bits.bit15=byt.bits.bit15;

	return rv_byt.word;
}
//--------------------------------------------------------------------------------------------
/**
 * @brief 	  reverses a data of double word-size length
 * @details   reverses a data of double word-size length from big  endigan to little endigan or vice versa
 * @param val the byte data to be reversed
 * @return uint8_t 
 */
uint32_t reverse_dword(uint32_t val)
{
	DWORD_BYTES byt;
	Big_DWORD_BYTES rv_byt;
	byt.dword=val;
	rv_byt.bits.bit0=byt.bits.bit0;
	rv_byt.bits.bit1=byt.bits.bit1;
	rv_byt.bits.bit2=byt.bits.bit2;
	rv_byt.bits.bit3=byt.bits.bit3;
	rv_byt.bits.bit4=byt.bits.bit4;
	rv_byt.bits.bit5=byt.bits.bit5;
	rv_byt.bits.bit6=byt.bits.bit6;
	rv_byt.bits.bit7=byt.bits.bit7;
	rv_byt.bits.bit8=byt.bits.bit8;
	rv_byt.bits.bit9=byt.bits.bit9;
	rv_byt.bits.bit10=byt.bits.bit10;
	rv_byt.bits.bit11=byt.bits.bit11;
	rv_byt.bits.bit12=byt.bits.bit12;
	rv_byt.bits.bit13=byt.bits.bit13;
	rv_byt.bits.bit14=byt.bits.bit14;
	rv_byt.bits.bit15=byt.bits.bit15;	
	rv_byt.bits.bit16=byt.bits.bit16;
	rv_byt.bits.bit17=byt.bits.bit17;
	rv_byt.bits.bit18=byt.bits.bit18;
	rv_byt.bits.bit19=byt.bits.bit19;
	rv_byt.bits.bit20=byt.bits.bit20;
	rv_byt.bits.bit21=byt.bits.bit21;
	rv_byt.bits.bit22=byt.bits.bit22;
	rv_byt.bits.bit23=byt.bits.bit23;
	rv_byt.bits.bit24=byt.bits.bit24;
	rv_byt.bits.bit25=byt.bits.bit25;
	rv_byt.bits.bit26=byt.bits.bit26;
	rv_byt.bits.bit27=byt.bits.bit27;
	rv_byt.bits.bit28=byt.bits.bit28;
	rv_byt.bits.bit29=byt.bits.bit29;
	rv_byt.bits.bit30=byt.bits.bit30;
	rv_byt.bits.bit31=byt.bits.bit31;
	
	return rv_byt.dword;
}
//--------------------------------------------------------------------------------------------
/**
 * @brief 	  converts a bcd number to a binary number
 * @details   converts a bcd number to a binary number very powerful method
 * 			  for displaying data on BCD
 * @param bcd the byte data to be reversed
 * @return uint16_t 
 */
uint16_t bcd_to_bin(uint8_t bcd)
{
	bcd_t bcd_val;
	uint16_t bin_val=0;
	bcd_val.byte=bcd;
	
	bin_val=bcd_val.high_nibble*10;
	bin_val+=bcd_val.low_nibble;
	return bin_val;	
}
//--------------------------------------------------------------------------------------------
/**
 * @brief 	  converts a binary number to a bcd number
 * @details   converts a binary number to a bcd number very powerful method
 * 			  for displaying data on BCD
 * @param bcd the byte data to be reversed
 * @return uint16_t 
 */
uint8_t bin_to_bcd(uint16_t bin_val)
{
	bcd_t bcd_val;
	bcd_val.high_nibble=bin_val/10;
	bcd_val.low_nibble=bin_val%10;
	return bcd_val.byte;
	
}
//--------------------------------------------------------------------------------------------
/**
 * @brief  converts a float number to real_t number
 * @details this methods help to converts a float number to real_t number
 * 		    which is very uesfull for display on LCD Display or to send/receive on a bus network
 * @param number  a float number
 * @param digits  number of decimal digits (resolution)
 * @return real_t 
 */
real_t float_to_real(float number,uint8_t digits)
{
	real_t r;
    r.val=0;	
	if(number<0)
	 {
		 r.sig=1;
		 number=-number;
	 }

	// Round correctly so that print(1.999, 2) prints as "2.00"
	double rounding = 0.5;
	for (uint8_t i=0; i<digits; ++i)
	rounding /= 10.0;

	number += rounding;//number += 0.05f;

	// Extract the integer part of the number and print it
	unsigned long int_part = (unsigned long)number;
    float reminder = number - (double)int_part;
	
	// Extract digits from the remainder one at a time
	while (digits-- > 0)
	   reminder *=10.0f;
		
	r.integer=int_part;		
	r.decimal=(uint8_t) reminder;	 
		
	return r;	
}
//--------------------------------------------------------------------------------------------
/**
 * @brief  converts an real_t number to a float number 
 * @details this methods help to converts a received reat_l numbers to float number
 * 		    which is very uesfull for display on LCD Display or to send/receive on a bus network
 * @param number  a float number
 * @param digits  number of decimal digits (resolution)
 * @return real_t 
 */
float real_to_float(real_t r,uint8_t digits)
{
	float number=0,reminder=0;
	number=r.integer;
	reminder = (float)r.decimal;

	for (uint8_t i=0; i<digits; ++i)
		reminder /= 10.0;
 
    number+=reminder;
	
	if(r.sig==1)
	number=-number;
	return number;
}
//--------------------------------------------------------------------------------------------
