/**
 * @brief uart.h
 *
 * @param student: Sameer Almaldein
 * @param ID: 679699
 * @param University TU-Chemnitz
 * @param Master : ASE(Automotive Software Engineering )
 */ 
#ifndef _UART_H
#define _UART_H

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

// UART buffer size
#define UART_DELIMITER_SIZE  	4  
#define UART_HEADER_SIZE  		4  
#define UART_BUFFER_SIZE 		64 
#define UART_BUFFER_MASK (UART_BUFFER_SIZE - 1)

//********************************************************************************************
//
//    constants
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
//  enum 
//
//********************************************************************************************

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
#define UART_WAIT_TIMEOUT 20000

enum UART_STATE {
 UART_WAIT,    //!< wait until data is available on the uart receive buffer
 UART_READ     //!< read the available data in the received 
};
extern volatile uint8_t  uart_state;
extern volatile uint32_t uart_ticks;

extern volatile uint16_t rx_index;
extern  uint8_t  rx_buffer[UART_BUFFER_SIZE];
extern volatile uint8_t  rx_buffer_length;
extern volatile uint8_t  buffer_overflow;

extern gpio_t uart_tx;
extern gpio_t uart_rx;

//********************************************************************************************
//
//  Commomd Method protoypes for USARTx Module peripherals
//
//********************************************************************************************
extern void USART1_init(void);
extern void USART2_init(void);
extern void USART3_init(void);

// not intterrupt 




//********************************************************************************************
//
// Method protoypes
//
//********************************************************************************************

//********************************************************************************************
//
// Prototype function
//
//********************************************************************************************
//! initialiaze the usart module
extern void uart_init(USART_TypeDef * usartx);
//! uart reset 
extern void uart_reset_buffer(void);
//! performs areceive operation of one byte on uart
extern uint8_t uart_receive(USART_TypeDef * usartx);
//! initializes the uart to operate in the receive mode
extern void uart_receive_start(USART_TypeDef * usartx);
//!checks if the uart in the receive mode and listens
extern uint8_t  uart_islistening(USART_TypeDef * usartx);
//********************************************************************************************
//
//  uart data manipulation Prototype function
//
//********************************************************************************************


//!checks if the data on the uart is available
extern uint8_t  uart_data_is_available();
extern uint8_t uart_rx_buffer_add(uint8_t val);
//extern uint8_t startswith_header(uint8_t * buffer,uint8_t Buffer_length,uint8_t * header);
//extern uint8_t endswith_delimiter(volatile uint8_t * buffer,uint8_t Buffer_length,uint8_t * delimiter);
//********************************************************************************************
//
//  uart data read/write Prototype function
//
//********************************************************************************************

extern  uint8_t uart_read_byte(USART_TypeDef * usartx);
//! write a byte to the uart data register
extern void uart_write_byte(USART_TypeDef * usartx,uint8_t val);
//! write an array of data to the uart transmit buffer
extern void uart_write_buffer(USART_TypeDef * usartx,uint8_t * buff,uint16_t length);
//! sends one byte on the  uart
extern uint8_t uart_send_byte(USART_TypeDef * usartx ,uint8_t byte);
//! sends an array of bytes on the uart
extern void uart_send_buffer(USART_TypeDef * usartx ,uint8_t * buf,uint16_t buf_size); 
//! sends a message on the uart 
extern void uart_send_message(USART_TypeDef * usartx ,uint8_t * buff,uint16_t length);



//********************************************************************************************
//
//  uart print Prototype function
//
//********************************************************************************************

//! a generic println  message on the uart
extern void uart_println(USART_TypeDef * usartx ,char * str);
//! a generic print  message on the uart
extern void uart_print(USART_TypeDef * usartx ,char * str);
//! a generic print  message as integer format on the uart
extern void uart_print_integer(USART_TypeDef * usartx ,uint32_t dword,uint8_t base);
//! a generic print  message as float format on the uart
extern void uart_print_float(USART_TypeDef * usartx ,float val,uint8_t digits);
//! a generic print  message as hexadecimal format on the uart
extern void uart_print_Array(USART_TypeDef * usartx ,uint8_t * data,uint8_t len);
//! a generic println  message as hexadecimal format on the uart
extern void uart_println_Array(USART_TypeDef * usartx ,uint8_t * data,uint8_t len);













#endif /* End of _UART_H*/
