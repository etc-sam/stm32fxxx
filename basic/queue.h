/**
 * @brief queue.h
 *
 * @param student: Sameer Almaldein
 * @param ID: 679699
 * @param University TU-Chemnitz
 * @param Master : ASE(Automotive Software Engineering )
 */ 


#ifndef _QUEUE_H_
#define _QUEUE_H_

//********************************************************************************************
//
//  geniric structs
//
//********************************************************************************************
/**
 * @brief a queue struct for a ring buffer 
 *  
 * @details the ring queue buffer consist of a pointer to fixed array usually with a total
 *          capacity and a length defines shows how data are in the queue, while index shows the position 
 *          of the read data
 * 
 * @param  buf          a pointer to a memory block of bytes to be read/ written
 * @param capacity      it defines the phsical total size or capacity of that block of memory  
 * @param pWR           a pointer to the write position "the tail" within the queue     
 * @param pRD           a pointer to the read  position "the head" within the queue
 * @param pTR           a uart  pointer to the "head" in the queue , just to print on the uart
 */ 

typedef struct _queue_t
{
    uint8_t  * buf;       //! a pointer to a memory block of bytes to be read/ written
    uint16_t capacity;    //! it defines the phsical total size or capacity of that block of memory  
    
    uint16_t pWR;         //! a write pointer to the "tail" in the queue     
    uint16_t pRD;         //! a read  pointer to the "head" in the queue
    uint16_t pTR;         //! a uart  pointer to the "head" in the queue , just to print on the uart

//    void (* init )(uint8_t * buf, uint16_t size);  //! a pointer function  to initialize the queue   
} queue_t;

//********************************************************************************************
//
//  queue buffer Prototype function
//
//********************************************************************************************
//! used to initialize the queue buffer
extern void queue_init(queue_t * q, uint8_t * buf,uint16_t len);
//! used to initialize the queue buffer
extern void queue_reset(queue_t * q);


//! returns the total capacity of the buffer
extern uint16_t  queue_get_capacity(queue_t * q); 
//! returns the relative length of data in the buffer
extern uint16_t queue_get_length(queue_t * q);
//! checks if the buffer is full and no space to add data
extern uint8_t  queue_is_full(queue_t * q);
//! checks if the buffer is empty 
extern uint8_t  queue_is_empty(queue_t * q);

/*!
   read & write methods affects both read/write pointers
   by means read a value free its space and writing a value 
   allocate a data space
*/

//! write a byte value to the queue 
extern uint8_t  queue_write(queue_t * q,uint8_t val); 
//! read a byte value of the queue
extern uint8_t  queue_read(queue_t * q,uint8_t * val); 

/*!
*/

//! returns a pointer to the whole buffer as if it a linear buffer
extern uint8_t * queue_Array(queue_t * q);	
//! returns a character pointer as if it is a linear buffer
extern char * queue_toCharArray(queue_t * q);

/*!
  printable methods deals with printable portion of the queue
  helps to indeicate a task to print on uart or screen without
  affecting data processing of the queue
*/

//! returns the relative printable length of data in the buffer
extern uint16_t queue_get_length_printable(queue_t * q);
//! checks if the buffer is empty from data to print 
extern uint8_t  queue_is_empty_printable(queue_t * q);
//! read a value from the queue the next to print to print
extern uint8_t  queue_getch_printable(queue_t * q,uint8_t * byte); 


#endif /* _QUEUE_H_ */