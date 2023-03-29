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
#include "i2c-com.h"
#include "i2c-std.h"
//********************************************************************************************
//
// constants
//
//********************************************************************************************
#define I2C_WAIT_TIMEOUT 20000

enum I2C_STATE {
 _I2C_WAIT,    		//!< wait until data is available on the i2c receive buffer
 _I2C_READ_BYTE,     //!< read only one byte from the I2c slave device  
 _I2C_READ_2BYTE,    //!< read only two bytes from the I2c slave device  
 _I2C_READ_NBYTE,    //!< read n bytes from the I2c slave device
 _I2C_WRITE_BYTE,    //!< write only one byte to  I2c slave device the 
 _I2C_WRIE_NBYTE,    //!< read n bytes to I2c slave device 
 _I2C_FAULT
};

enum I2C_WR_BYTE_STATE {
 _I2C_WR_BYTE_WAIT_BUSY,   	 //!< wait until the i2c Module is not busy any more
 _I2C_WR_BYTE_START_SEND,  	 //!< send start condition  
 _I2C_WR_BYTE_START_WAIT,  	 //!< wait start condition to complete
 _I2C_WR_BYTE_SLAVE_WR,    	 //!< send slave address with write operation condition  
 _I2C_WR_BYTE_SlAVE_WR_WAIT,  //!< wait slave to AK/NAK condition to complete
 _I2C_WR_BYTE_MASTER,    	 //!< master writes one byte to the slave   
 _I2C_WR_BYTE_MASTER_WAIT,    //!< master waits to AK/NAK to complete in AK case just go to stop 
 _I2C_WR_BYTE_STOP_SEND,		//!< send stop condition  
 _I2C_WR_BYTE_STOP_WAIT,		//!< wait stop condition to complete
 _I2C_WR_BYTE_FAULT
};
enum I2C_WRITE_BYTE_STATE {
 _I2C_WRITE_BYTE_WAIT_BUSY,   	 //!< wait until the i2c Module is not busy any more
 _I2C_WRITE_BYTE_START_SEND,  	 //!< send start condition  
 _I2C_WRITE_BYTE_START_WAIT,  	 //!< wait start condition to complete
 _I2C_WRITE_BYTE_SLAVE_WR,    	 //!< send slave address with write operation condition  
 _I2C_WRITE_BYTE_SlAVE_WR_WAIT,  //!< wait slave to AK/NAK condition to complete
 _I2C_WRITE_BYTE_REG_AR,    	 //!< send base register address to slave define   
 _I2C_WRITE_BYTE_REG_AR_WAIT, 	 //!< wait slave to AK/NAK condition to complete
 _I2C_WRITE_BYTE_MASTER,    	 //!< master write one byte from the slave with NAK condition  
 _I2C_WRITE_BYTE_MASTER_WAIT,    //!< wait master  read operation finish NAK condition to complete
 _I2C_WRITE_BYTE_STOP_SEND,		//!< send stop condition  
 _I2C_WRITE_BYTE_STOP_WAIT,		//!< wait stop condition to complete
 _I2C_WRITE_BYTE_FAULT
};

enum I2C_WRITE_NBYTE_STATE {
 _I2C_WRITE_NBYTE_WAIT_BUSY,   	 	//!< wait until the i2c Module is not busy any more
 _I2C_WRITE_NBYTE_START_SEND,  	 	//!< send start condition  
 _I2C_WRITE_NBYTE_START_WAIT,  	 	//!< wait start condition to complete
 _I2C_WRITE_NBYTE_SLAVE_WR,    	 	//!< send slave address with write operation condition  
 _I2C_WRITE_NBYTE_SlAVE_WR_WAIT,  	//!< wait slave to AK/NAK condition to complete
 _I2C_WRITE_NBYTE_REG_AR,    	 	//!< send base register address to slave define   
 _I2C_WRITE_NBYTE_REG_AR_WAIT, 		//!< wait slave to AK/NAK condition to complete
 _I2C_WRITE_NBYTE_MASTER,    	    //!< master writes n bytes to the slave and wait after each byte AK   
 _I2C_WRITE_NBYTE_MASTER_WAIT,      //!< master waits  slave to AK/NAK condition to complete
 _I2C_WRITE_NBYTE_STOP_SEND,		//!< send stop condition  
 _I2C_WRITE_NBYTE_STOP_WAIT,		//!< wait stop condition to complete
 _I2C_WRITE_NBYTE_FAULT
};


enum I2C_READ_BYTE_STATE {
 _I2C_READ_BYTE_WAIT_BUSY,   	//!< wait until the i2c Module is not busy any more
 _I2C_READ_BYTE_START_SEND,  	//!< send start condition  
 _I2C_READ_BYTE_START_WAIT,  	//!< wait start condition to complete
 _I2C_READ_BYTE_SLAVE_WR,    	//!< send slave address with write operation condition  
 _I2C_READ_BYTE_SlAVE_WR_WAIT,  //!< wait slave to AK/NAK condition to complete
 _I2C_READ_BYTE_REG_AR,    	 	//!< send base register address to slave define   
 _I2C_READ_BYTE_REG_AR_WAIT, 	//!< wait slave to AK/NAK condition to complete
 _I2C_READ_BYTE_RESTART_SEND,   //!< send a repeat start condition  
 _I2C_READ_BYTE_RESTART_WAIT,   //!< wait start condition to complete
 _I2C_READ_BYTE_SLAVE_RD,    	//!< send slave address with READ operation condition  
 _I2C_READ_BYTE_SlAVE_RD_WAIT,  //!< wait slave to AK/NAK condition to complete
 _I2C_READ_BYTE_MASTER_RD,    	//!< master reads one byte from the slave with NAK condition  
 _I2C_READ_BYTE_MASTER_RD_WAIT, //!< wait master  read operation finish NAK condition to complete
 _I2C_READ_BYTE_STOP_SEND,		//!< send stop condition  
 _I2C_READ_BYTE_STOP_WAIT,		//!< wait stop condition to complete
 _I2C_READ_BYTE_FAULT
};


enum I2C_READ_2BYTE_STATE {
 _I2C_READ_2BYTE_WAIT_BUSY,   	//!< wait until the i2c Module is not busy any more
 _I2C_READ_2BYTE_START_SEND,  	//!< send start condition  
 _I2C_READ_2BYTE_START_WAIT,  	//!< wait start condition to complete
 _I2C_READ_2BYTE_SLAVE_WR,    	//!< send slave address with write operation condition  
 _I2C_READ_2BYTE_SlAVE_WR_WAIT,  //!< wait slave to AK/NAK condition to complete
 _I2C_READ_2BYTE_REG_AR,    	 	//!< send base register address to slave define   
 _I2C_READ_2BYTE_REG_AR_WAIT, 	//!< wait slave to AK/NAK condition to complete
 _I2C_READ_2BYTE_RESTART_SEND,   //!< send a repeat start condition  
 _I2C_READ_2BYTE_RESTART_WAIT,   //!< wait start condition to complete
 _I2C_READ_2BYTE_SLAVE_RD,    	//!< send slave address with READ operation condition  
 _I2C_READ_2BYTE_SlAVE_RD_WAIT,  //!< wait slave to AK/NAK condition to complete
 _I2C_READ_2BYTE_MASTER_RD,    	//!< master read one byte from the slave with NAK condition  
 _I2C_READ_2BYTE_MASTER_RD_WAIT, //!< wait master  read operation finish NAK condition to complete
 _I2C_READ_2BYTE_STOP_SEND,		//!< send stop condition  
 _I2C_READ_2BYTE_STOP_WAIT,		//!< wait stop condition to complete
 _I2C_READ_2BYTE_FAULT
};

enum I2C_READ_NBYTE_STATE {
 _I2C_READ_NBYTE_WAIT_BUSY,   	//!< wait until the i2c Module is not busy any more
 _I2C_READ_NBYTE_START_SEND,  	//!< send start condition  
 _I2C_READ_NBYTE_START_WAIT,  	//!< wait start condition to complete
 _I2C_READ_NBYTE_SLAVE_WR,    	//!< send slave address with write operation condition  
 _I2C_READ_NBYTE_SlAVE_WR_WAIT,  //!< wait slave to AK/NAK condition to complete
 _I2C_READ_NBYTE_REG_AR,    	 	//!< send base register address to slave define   
 _I2C_READ_NBYTE_REG_AR_WAIT, 	//!< wait slave to AK/NAK condition to complete
 _I2C_READ_NBYTE_RESTART_SEND,   //!< send a repeat start condition  
 _I2C_READ_NBYTE_RESTART_WAIT,   //!< wait start condition to complete
 _I2C_READ_NBYTE_SLAVE_RD,    	//!< send slave address with READ operation condition  
 _I2C_READ_NBYTE_SlAVE_RD_WAIT,  //!< wait slave to AK/NAK condition to complete
 
_I2C_READ_NBYTE_MASTER_RD,    	//!< master read one byte from the slave with AK condition  
_I2C_READ_NBYTE_MASTER_RD_WAIT, //!< wait master  read operation finish AK condition to complete

_I2C_READ_NBYTE_MASTER_RD_N1,    	//!< master read one byte from the slave with NAK condition  
_I2C_READ_NBYTE_MASTER_RD_N1_WAIT, //!< wait master  read operation finish NAK condition to complete
 
 _I2C_READ_NBYTE_STOP_SEND,		//!< send stop condition  
 _I2C_READ_NBYTE_STOP_WAIT,		//!< wait stop condition to complete
 _I2C_READ_NBYTE_FAULT
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
/**
 * @brief data structure Bit definition for I2C_OAR1 register
 * 
 * @details this structure allows access at bit or byte level for the 
 *          I2C own address register 1
 * @param  val        16-bit value that represent the half word I2C_CR1 register
 * @param  ADD0      1-bit Bit 0 of  10 bit Interface Address
 * @param  ADD1_7    7-bit Bit[1..7] 7-bit Interface Address/10 bit Interface Address
 * @param  ADD8_9    2-bit Bit[8..9] 10-bit Interface Address 
 * @param  res       5-bit reserved not used bits
 * @param  ADDMODE   1-bit Addressing Mode (Slave mode)
 */
typedef union _I2c_tx_byte_t
{
	uint8_t  Array[3];
	struct
	{
		uint8_t slave_address:8;
		uint8_t reg_address:8;
		uint8_t reg_data:8;
	};
}I2c_tx_byte_t;
//********************************************************************************************
//
// global variables
//
//********************************************************************************************
//! a gloabl variale define the I2C receive  Ring Queue
//extern queue_t i2c_rx_queue;

//! a gloabl variale define the I2C transmit  Ring Queue
//extern queue_t i2c_tx_queue;

//! a gloabl variale define the I2C transmit buffer for the (Ring Queue)
//extern  uint8_t  i2c_tx_buffer[I2C_MAX_TX_QUEUE_LEN];

//! a gloabl variale define the I2C receive buffer for the ring (Ring Queue)
//extern  uint8_t  i2c_rx_buffer[I2C_MAX_RX_QUEUE_LEN];

//********************************************************************************************
//
// Data Structure
//
//********************************************************************************************
typedef struct _i2c_t{
//pinter to i2c module
 I2C_TypeDef_t *ptr;

// sda & scl pins
gpio_t scl;
gpio_t sda;

//  Enable clock related to the alternative function & GPIO
reg_t RCC_APBxENR_AFIO;
//__IO uint32_t * RCC_APBxENR_AFIO_reg;
//uint32_t RCC_APBxENR_AFIOEN_val; 

reg_t RCC_APBxENR_IOP;
//__IO uint32_t * RCC_APBxENR_IOP_reg;
//uint32_t RCC_APBxENR_IOPEN_val;
// i2c Remap GPIO register peripheral
reg_t AFIO_MAPR_I2C;
 //__IO uint32_t * AFIO_MAPR_reg;
//uint32_t AFIO_MAPR_I2C_REMAP_val;


// Enable clock related to i2c peripheral
reg_t RCC_APBxENR_I2C;
//__IO uint32_t * RCC_APBxENR_I2C_reg;
// uint32_t RCC_APBxENR_I2CEN_val; 


 // reset i2c peripheral
 reg_t RCC_APBxRSTR_I2C;
 //__IO uint32_t * RCC_APBxRSTR_I2C_reg;
//uint32_t RCC_APBXRSTR_I2C_val;
 

 // i2c peripheral clock speed pclk
 uint32_t clock_speed;
 //i2c peripheral timeout for pollying
 uint32_t Timeout;

}i2c_t;

//********************************************************************************************
//
//  Global  variables' declarations 
//
//********************************************************************************************

//extern volatile uint8_t  i2c_state;
//extern volatile uint32_t i2c_ticks;

//extern volatile uint16_t i2c_index;

//extern volatile uint8_t  i2c_buffer_length;
//extern volatile uint8_t  i2c_overflow;
extern i2c_t myi2c;

extern I2C_TypeDef_t * i2cx;


//********************************************************************************************
//
// Prototype function
//
//********************************************************************************************
extern void i2c1_init(uint32_t clock_speed,uint16_t ownaddress);

extern void i2c_init();//(I2C_TypeDef_t *i2c,gpio_t sdl,gpio_t scl, uint32_t clock_speed);
// 
extern void i2c_uart_print(USART_TypeDef * uart);


// members function
extern uint8_t i2c_start();						   //!initiate start condition
extern uint8_t i2_stop();						   //! initiate stop condition
extern uint8_t i2c_send_byte(uint8_t data);		   //! send a byte via TWI bus
extern uint8_t i2c_send_sla_wr(uint8_t SLA_W);	   //! send a slave with write operation via TWI bus
extern uint8_t i2c_send_sla_rd(uint8_t SLA_R);	   //! send a slave with read operation via TWI bus

extern uint8_t i2c_write_data(uint8_t data);	   //! write data
extern uint8_t i2c_read_data(uint8_t *data,uint8_t ack);	 

#endif /* End of _I2C_H*/
