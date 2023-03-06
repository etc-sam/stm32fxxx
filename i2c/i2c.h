/**
 * @brief i2c.h
 *
 * @param student: Sameer Almaldein
 * @param ID: 679699
 * @param University TU-Chemnitz
 * @param Master : ASE(Automotive Software Engineering )
 */ 
#ifndef _I2C_H
#define _I2C_H

//********************************************************************************************
//
// including header  files
//
//********************************************************************************************

//********************************************************************************************
//
// constants
//
//********************************************************************************************
#define I2C_WAIT_TIMEOUT 20000

enum I2C_STATE {
 I2C_WAIT,    //!< wait until data is available on the i2c receive buffer
 I2C_READ     //!< read the available data in the received 
};

// UART buffer size
#define I2C_DELIMITER_SIZE  	4  
#define I2C_HEADER_SIZE  		4  
#define I2C_BUFFER_SIZE 		64 
#define I2C_BUFFER_MASK (I2C_BUFFER_SIZE - 1)

//********************************************************************************************
//
//    constants
//
//********************************************************************************************
#define  I2C_MAX_RX_QUEUE_LEN      120
#define  I2C_MAX_TX_QUEUE_LEN      120

#define  I2C_MAX_FRAME_LEN   		40
#define  I2C_MAX_PAYLOAD_LEN        (I2C_MAX_FRAME_LEN-I2C_LINK_HEADER_LEN)

#define  I2C_PACKET_P        		0x06
#define  I2C_PAYLOAD_P        		0x08

//********************************************************************************************
//
//  enum 
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
//! a gloabl variale define the I2C receive  Ring Queue
extern queue_t i2c_rx_queue;

//! a gloabl variale define the I2C transmit  Ring Queue
extern queue_t i2c_tx_queue;

//! a gloabl variale define the I2C transmit buffer for the (Ring Queue)
extern  uint8_t  i2c_tx_buffer[I2C_MAX_TX_QUEUE_LEN];

//! a gloabl variale define the I2C receive buffer for the ring (Ring Queue)
extern  uint8_t  i2c_rx_buffer[I2C_MAX_RX_QUEUE_LEN];

//********************************************************************************************
//
// Data Structure
//
//********************************************************************************************

//********************************************************************************************
//
//  Global  variables' declarations 
//
//********************************************************************************************

extern volatile uint8_t  i2c_state;
extern volatile uint32_t i2c_ticks;

extern volatile uint16_t i2c_index;

extern volatile uint8_t  i2c_buffer_length;
extern volatile uint8_t  i2c_overflow;

//********************************************************************************************
//
// Method protoypes
//
//********************************************************************************************
extern void I2C1_init(void);

//********************************************************************************************
//
// Prototype function
//
//********************************************************************************************




#endif /* End of _I2C_H*/
