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
#define  RASPNET_MAX_RX_QUEUE_LEN      120
#define  RASPNET_MAX_TX_QUEUE_LEN      120

#define  RASPNET_MAX_FRAME_LEN   		40
#define  RASPNET_MAX_PAYLOAD_LEN    (RASPNET_MAX_FRAME_LEN-RASPNET_LINK_HEADER_LEN)

#define  RASPNET_PACKET_P        		0x06
#define  RASPNET_PAYLOAD_P        		0x08

//********************************************************************************************
//
//  data structures
//
//********************************************************************************************
// RASPNET Frame structure
/**
 * @brief  defines the Raspnet Frame structure
 * 
 * @details this define the Raspnet Frame structure
 *  
 * it consists of the folowing parts
 * @param header    a 6-byte  length that defines the header part of the raspnet frame
 * @param data      an array of bytes that defines the payload of raspnet frame 
 */
/*typedef union _RASPNET_FRAME_t
{
	uint8_t Array[RASPNET_MAX_FRAME_LEN];		
	struct
	{
	  raspnet_lnk_header_t header;	    		//!< a 6-byte  length that defines the header part of the raspnet frame
	  uint8_t data [RASPNET_MAX_PAYLOAD_LEN];	//!< an array of bytes that defines the payload of raspnet frame  
	};
		
}raspnet_frame_t;
*/
//********************************************************************************************
//
// global variables
//
//********************************************************************************************
//! a gloabl variale define the transmit frame buffer
//extern raspnet_frame_t raspnet_tx_frame;
//! a gloabl variale define the receive frame buffer
//extern raspnet_frame_t raspnet_rx_frame;


//! a gloabl variale define the raspnet receive  Ring Queue
extern queue_t raspnet_rx_queue;

//! a gloabl variale define the raspnet transmit  Ring Queue
extern queue_t raspnet_tx_queue;

//! a gloabl variale define the raspnet receive buffer (Ring Queue)
extern  uint8_t  raspnet_tx_buffer[RASPNET_MAX_TX_QUEUE_LEN];

//! a gloabl variale define the raspnet receive buffer (Ring Queue)
extern  uint8_t  raspnet_rx_buffer[RASPNET_MAX_RX_QUEUE_LEN];

//********************************************************************************************
//
//  enum 
//
//********************************************************************************************
/**
 * @brief commands types theat can be send on the uart
 * 
 * @details list an enumerated numbers for some of supperted commands 
 *          to check/debug the functionality of the raspnet project @ Atmega
 * 
 * @param _SPD    =0 changes the speed of blinking leds
 * @param _INC    =1 increases the speed delay of the blinking leds
 * @param _DEC    =2 decreases the speed delay of the blinking leds
 * @param _INFO   =3 returns information about the value of speed delay  
 * @param _CRC    =4 returns the crc32 for a sequnce of bytes to debug crc32 function operation
 * @param _TX     =5 sends a message through uart from rasperpi to atmega to be sent as raspnet message
 * @param _RX     =6 reserved to receive a message for  future usage
 */
enum CMD_TYPES
{
  
  _SPD=0,   //!< changes the speed of blinking leds
  _INC=1,   //!< increases the speed delay of the blinking leds     
  _DEC=2,   //!< decreases the speed de,lay of the blinking leds     
  _INFO=3,  //!< returns information about the value of speed delay 
  _CRC=4,   //!< returns the crc32 for a sequnce of bytes to debug crc32 function operation     
  _TX=5,    //!< sends a message through uart from rasperpi to atmega to be sent as raspnet message    
  _RX=6     //!< reserved to receive a message for  future usage 
};
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

//********************************************************************************************
//
//  Commomd Method protoypes for USARTx Module peripherals
//
//********************************************************************************************
extern void USART1_init(void);
extern void USART2_init(void);
extern void USART3_init(void);

// not intterrupt 
extern uint8_t uart_put_char(USART_TypeDef * usartx,uint8_t data);
extern uint8_t uart_get_char(USART_TypeDef * usartx);

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
extern void uart_init(void);



//! performs areceive operation of one byte on uart
extern uint8_t uart_receive(USART_TypeDef * usartx);
//! initializes the uart to operate in the receive mode
extern void uart_receive_start(void);
//!checks if the uart in the receive mode and listens
extern uint8_t  uart_islistening(void);
//!checks if the data on the uart is available
extern uint8_t  uart_data_is_available(void);

//! handles the whole message as if it is a correct command structure
extern void     uart_handle_frame(void);

extern void uart_handle_cmd(uint8_t * cmd,size_t cmd_len, uint8_t * data, size_t data_len);

//! sends one byte on the  uart
extern uint8_t uart_send_byte(USART_TypeDef * usartx ,uint8_t byte);
//! sends an array of bytes on the uart
extern void uart_send_buffer(USART_TypeDef * usartx ,uint8_t * buf,uint16_t buf_size); 
//! sends a message on the uart 
extern void uart_send_message(USART_TypeDef * usartx ,uint8_t * buff,uint16_t length);
//! a generic println  message on the uart
extern void uart_println(USART_TypeDef * usartx ,char * str);
//! a generic print  message on the uart
extern void uart_print(USART_TypeDef * usartx ,char * str);

//! a generic print  message as hexadecimal format on the uart
extern void uart_print_Array(USART_TypeDef * usartx ,uint8_t * data,uint8_t len);
//! a generic println  message as hexadecimal format on the uart
extern void uart_println_Array(USART_TypeDef * usartx ,uint8_t * data,uint8_t len);



extern  void uart_handle_frame();

//! info command: returns the current speed delay time for the blinking led
extern void  uart_info_cmd_handle();
//! blink command: just activates blinking task
extern void  uart_blk_cmd_handle();
//! halt command: just deactivates blinking task
extern void  uart_hlt_cmd_handle();

//! reset command: reset  raspnet tx/rx buffers
extern void  uart_rst_cmd_handle();
extern void  uart_tx_queue_cmd_handle();
extern void  uart_rx_queue_cmd_handle();

//! speed command: changes the speed delay time for the blinking led
extern void  uart_spd_cmd_handle(uint8_t * data, size_t data_len);
//! increase command: increases the speed delay time for the blinking led
extern void  uart_inc_cmd_handle(uint8_t * data, size_t data_len);
//! decrease command: decreases the speed delay time for the blinking led
extern void  uart_dec_cmd_handle(uint8_t * data, size_t data_len);
//! increase command: increases the speed delay time for the blinking led

extern void  uart_crc_cmd_handle(uint8_t * data, size_t data_len);
extern void  uart_crc_cmd_handle_type(uint8_t * data, size_t data_len,uint8_t type);

extern void  uart_tx_cmd_handle(uint8_t * data, size_t data_len);
extern void  uart_rx_cmd_handle(uint8_t * data, size_t data_len);

extern void  uart_id_cmd_handle(uint8_t * data, size_t data_len);


//! a generic task to handle uart task 
extern void uart_task(void);




#endif /* End of _UART_H*/
