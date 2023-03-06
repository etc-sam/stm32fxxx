/**
 * @brief queue.c
 *
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

//********************************************************************************************
//
//  static function ProtoType
//
//********************************************************************************************

//********************************************************************************************
//
//  static  functions' definitions
//
//*******************************************************************************************

//********************************************************************************************
//
//  printable methods of the queue
//
//********************************************************************************************
/**
 * @brief  checks if the queue is empty from printable data
 * 
 * @details checks if the queue is empty from printable data, 
 * 			it is used before reading from the queue a printable data
 *  notice : this method has no effect on the writing/reading data within the ring buffer
 * 			 it just helps to implement an asynchrouns retriavl method for received data 
 * 			 to allow printing it outside the receive interrupt
 *
 * @param q 	a pointer to the queue
 * @return uint8_t 
 * @retval 0: the queue is not empty, contains printable data
 * @retval 1: the queue is empty
 */
 uint8_t  queue_is_empty_printable(queue_t * q)
 {
  if(q->pWR==q->pTR)
	 return 1;
	return 0;
 }
//--------------------------------------------------------------------------------------------
/**
 * @brief returns the length of printable data to read 
 * 
 * @details returns the actual printable data after 
 * 			considering the overlap condition, this method is used to read a block of data 
 * 			instead of reading  data block sequentially(i.e. bytes by byte per read operation)
 
 *  notice : this method has no effect on the writing/reading data within the ring buffer
 * 			 it just helps to implement an asynchrouns retriavl method for received data 
 * 			 to allow printing it outside the receive interrupt
 *   
 * @param q a pointer to the queue
 * @return uint16_t 
 * 
 */
uint16_t queue_get_length_printable(queue_t * q)
{
   uint16_t len=0;
	len=(q->pWR >= q->pTR )? (q->pWR - q->pTR): q->capacity - q->pTR + q->pWR;
   return len;
}
//--------------------------------------------------------------------------------------------
/**
 * @brief reads a byte value of the queue
 *
 * @details  reads byte data from the queue and after reading this byte
 *			 it proceeds the terminal pointer "index of the printing" does not free any space
 *			 in the queue buffer 
 *  notice : this method has no effect on the writing/reading data within the ring buffer
 * 			 it just helps to implement an asynchrouns retriavl method for received data 
 * 			 to allow printing it outside the receive interrupt
 *
 * @param q  			a pointer to a queue to add data to
 * @param val 		    the data to be read		
 * @return uint8_t 
 * @retval 0 failed 	to read data from the queue, it is empty
 * @retval 1 succeeded  to read data from the queue 
 */
uint8_t  queue_getch_printable(queue_t * q,uint8_t * val)
{
  // no data available just exit 	
  if(queue_is_empty_printable(q))
	 	return 0;
  else 
  {
	// read data from the current terminal pointer position "terminal"
	 *val=q->buf[q->pTR];
	// increase the terminal pointer but also considers overlapping condition 
	 q->pTR=((q->pTR+1)==q->capacity)?0:q->pTR+1;
  } 
  return 1;
}
//--------------------------------------------------------------------------------------------

//********************************************************************************************
//
//  extern  functions' definitions
//
//********************************************************************************************
/**
 * @brief initialize the queue buffer
 * 
 * @param q 	a pointer to the queue
 * @param buf 	a physical static array of bytes perfoms as the queue data container
 * @param len 	the actual size of the array
 */
void queue_init(queue_t * q, uint8_t * buf,uint16_t len)
{
	q->buf=buf;
	q->capacity=len;
	queue_reset(q);
}
//-------------------------------------------------------------------------------------------
/**
 * @brief    resets the queue  and its intrnal pointers
 * @details  set zero value to all internal array elements and 
 * 			  resets the read/write/ terminal pointers	
 *
 * @param q a pointer to the queue
 */
void queue_reset(queue_t * q)
{
	
  q->pWR=0; // resets the write pointer "tail"
  q->pRD=0; // resets the read  pointer "head"
  q->pTR=0; // resets the print pointer "terminal"
  
  // clear the value of memory
  memset(q->buf,0,q->capacity);
}
//-------------------------------------------------------------------------------------------
/** 
 * @brief checks if the queue is full
 * @details checks if the queue is full		
 * 			by means no more space is available for new data
 * 			this method is very important in case
 * @param q 	a pointer to the queue
 * @return uint8_t 
 * @retval 0: the queue is not full
 * @retval 1: the queue is full
 */
uint8_t  queue_is_full(queue_t * q)
{
  if( ((q->pWR+1)%q->capacity)==q->pRD)
	 return 1;
	return 0; 	
}
//--------------------------------------------------------------------------------------------
/**
 * @brief  checks if the queue is empty
 * 
 * @details checks if the queue is empty, it is used before reading from the queue 
 *           
 * @param q 	a pointer to the queue
 * @return uint8_t 
 * @retval 0: the queue is not empty
 * @retval 1: the queue is empty
 */
 uint8_t  queue_is_empty(queue_t * q)
 {
  if(q->pWR==q->pRD)
	 return 1;
	return 0;
 }
//--------------------------------------------------------------------------------------------
/**
 * @brief returns the length of data to read 
 * 
 * @details returns the actual readable data after 
 * 			considering the overlap condition, this method to read a block of data 
 * 			instead of reading  data block sequentially(i.e. bytes by byte per read operation)
 * 
 * @param q a pointer to the queue
 * @return uint16_t 
 * 
 */
uint16_t queue_get_length(queue_t * q)
{
   uint16_t len=0;
	len=(q->pWR >= q->pRD )? (q->pWR - q->pRD): q->capacity-q->pRD+q->pWR;
   return len;
}
//--------------------------------------------------------------------------------------------
/**
 * @brief returns the capacity of the queue
 * 
 * @param q a pointer to the queue 
 * @return uint16_t 
 */
uint16_t queue_get_capacity(queue_t * q)
{
    return q->capacity;
}  
//--------------------------------------------------------------------------------------------
/**
 * @brief  add a byte value to the queue 
 * 
 * @details it tries to add a byte value to the queue 
 * 			first it checks if the queue is full then it returns 0
 * 			otherwise it is succeeded
 * @param q 		a pointer to the queue to add data to
 * @param val 		the data to be added
 * @return uint16_t 
 * @retval 0 failed 	to add/ append data to the queue
 * @retval 1 succeeded  to add/ append data to the queue
 */
uint8_t  queue_write(queue_t * q,uint8_t val)
{
	if(queue_is_full(q))
	 	return 0;
	else 
	{
		// add data to the current write pointer position "tail "
		q->buf[q->pWR]=val;
		// increase the tail but consider overlap condition 
		q->pWR=((q->pWR+1)==q->capacity)?0:q->pWR+1;
	} 
	return 1;
}
//--------------------------------------------------------------------------------------------
/**
 * @brief reads a byte value of the queue
 
 * @details  reads byte data from the queue and after reading this byte
			 it proceeds the read pointer "the head" this empty a one space
			 in the queue buffer 
 * @param q  			a pointer to a queue to add data to
 * @param data 		    the data to be read		
 * @return uint8_t 
 * @retval 0 failed 	to read data from the queue, it is empty
 * @retval 1 succeeded  to read data from the queue 
 */
uint8_t queue_read(queue_t * q,uint8_t * val)
{
  // no data available just exit 	
  if(queue_is_empty(q))
	return 0;
   // read data from the current read pointer position "head"
	*val=q->buf[q->pRD];
  // increase the head but consider overlap condition 
	 q->pRD=((q->pRD+1)==q->capacity)?0:q->pRD+1;
  return 1;
}
//--------------------------------------------------------------------------------------------
/**
 * @brief  returns an array for the internal queue buffer 
 * 
 * @param q 
 * @return uint8_t* 
 */
uint8_t * queue_Array(queue_t * q)
{
  return q->buf;
}	
//--------------------------------------------------------------------------------------------
/**
 * @brief 
 * 
 * @param q 
 * @return char* 
 */
char*  queue_toCharArray(queue_t * q)
{
  return (char*)q->buf;
}
//--------------------------------------------------------------------------------------------
