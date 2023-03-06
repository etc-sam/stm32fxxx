/**
 * @brief uart.c
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
//! uart state variable it defines thes state in the FSM (Finite state machine)
volatile uint8_t uart_state=UART_WAIT;
volatile uint32_t uart_ticks=0;

volatile uint16_t rx_index=0;
uint8_t  rx_buffer[UART_BUFFER_SIZE]={0};
volatile uint8_t  rx_buffer_length=0;
volatile uint8_t  buffer_overflow=0;
//********************************************************************************************
//
// static variables' declarations 
//
//********************************************************************************************
static uint8_t uart_delimiter[UART_DELIMITER_SIZE]={0x55,0xaa,0x55,0xaa};

// Atmega328p gertboard CPU_F 12MHz
//static uart_options_t uart_options={
//	F_CPU,		// frequency of CPU
//	9600, 		// baud rate
//	8,      	// char size
//	1,      	//stop bit
//	0,      	//no parity
//	0,      	// asynchronous mode
//	0,      	// no dual speed mode
//	0	    	// UBRD
//};



//********************************************************************************************
//
//  static function ProtoType
//
//********************************************************************************************
//! read a byte to the uart data register
extern uint8_t uart_reg_read_byte(USART_TypeDef * usartx);
//! write a byte to the uart data register
extern void uart_reg_write_byte(USART_TypeDef * usartx,uint8_t val);
//! write an array of data to the uart transmit buffer
extern void uart_reg_write_buffer(USART_TypeDef * usartx,uint8_t * buff,uint16_t length);

//! configures the uart module
//static void uart_configure();
//! initialize the receive mask interrupt
//static void uart_set_rx_Int_mask(uint8_t enable);
//! uart reset 
static void uart_reset();

//static uint8_t startswith_header(uint8_t * buffer,uint8_t Buffer_length,uint8_t * delimiter);
static uint8_t endswith_delimiter(volatile uint8_t * buffer,uint8_t Buffer_length,uint8_t * delimiter);

//********************************************************************************************
//
//
//********************************************************************************************
/**
 * @brief configures the uart module
 * @details configures the uart module using the options 
 * 			defined by static  uart_options variable
 * 			
 * @return void
 * 
 */
//void uart_configure()
//{
 /*   
	uart_mode_reg.reg_select=0;
	// mode operation
	if(uart_options.synch==1)
	 uart_mode_reg.mode=_UART_SYNC;
	else
	 uart_mode_reg.mode=_UART_ASYNC;
	
	// define options of USART mode
	if(uart_options.stop_bit==2)
		uart_mode_reg.stop_bit=_UART_TWO_STOPBIT;
	else
		uart_mode_reg.stop_bit=_UART_ONE_STOPBIT;

	switch(uart_options.parity)
	{
		case 1:  uart_mode_reg.parity=_UART_ODD_PARITY;  break;
		case 2:  uart_mode_reg.parity=_UART_EVEN_PARITY; break;
		default: uart_mode_reg.parity=_UART_NO_PARITY;   break;
	}

	// clear 8th bit of uart
	uart_control_reg.char_size_9bit=0;
	
	switch(uart_options.char_size)
	{
		case 5: uart_mode_reg.char_size=_UART_FRAME_5_BITS; break;
		case 6: uart_mode_reg.char_size=_UART_FRAME_6_BITS; break;
		case 7: uart_mode_reg.char_size=_UART_FRAME_7_BITS; break;
		case 8: uart_mode_reg.char_size=_UART_FRAME_8_BITS; break;
		case 9:
				uart_mode_reg.char_size=_UART_FRAME_8_BITS;
				uart_control_reg.char_size_9bit=1;
		break;
		default:
		      uart_mode_reg.char_size=_UART_FRAME_8_BITS; break;
	}

	//uart_regs.p_mode_reg->val=my_mode.val;

	// set baud rate
	WORD_BYTES baud_rate;
	baud_rate.word=uart_options.UBRD;
	uart_status_reg.double_speed=uart_options.dual_speed;
	
	if(uart_options.UBRD==0)
	{		
	// define dual speed U2X bit
	 if(uart_options.dual_speed==1)
	 {
		baud_rate.word=UART_BAUD_ASYNC_double(uart_options.buad_rate,uart_options.xtal_cpu);
	 }
	 else
	 {
		if(!uart_options.synch)
		 baud_rate.word=UART_BAUD_ASYNC(uart_options.buad_rate,uart_options.xtal_cpu);
		else
		  baud_rate.word=UART_BAUD_SYNC(uart_options.buad_rate,uart_options.xtal_cpu);
	 }
	}

	// set baud rate registers
	uart_mode_reg.reg_select=0;
	uart_baud_rate_low_reg.val=baud_rate.byte.low;
	uart_baud_rate_high_reg.val=baud_rate.byte.high;
 */
//}
//--------------------------------------------------------------------------------------------------------------------
/**
 * @brief initializes the receive mask interrupt
 * 
 *  sets or resets the receive complete interrupt mask bit
 *  based on the passed value
 * @param enable sets/resets the receive complete interrupt mask bit
 * @return   void
 */
//void uart_set_rx_Int_mask(uint8_t enable)
//{
/*UCSR0A=0x00;
	//UCSRxB=(1<<RXEN)|(1<<RXCIE);
if(enable)
 {	
	uart_control_reg.rx_enable=1;	 		 //sbit(UCSR0B,RXEN0);
	uart_control_reg.receive_complete_ie=1;	 //sbit(UCSR0B,RXCIE0);
 }
 else
 {
	uart_control_reg.rx_enable=0;			 //sbit(UCSR0B,RXEN0);
	uart_control_reg.receive_complete_ie=0;	 //cbit(UCSR0B,RXCIE0);	 
 }
 */
//}
//-----------------------------------------------------------------------------------------------------
/**
 * @brief read a byte to the uart data register
 * @details reseved for future use
 * @return uint8_t
 * 
 */
uint8_t uart_reg_read_byte(USART_TypeDef * usartx)
{
   while(USART_GetFlagStatus(usartx,USART_FLAG_RXNE)==RESET);
     return usartx->DR & (uint16_t) 0x00ff;  
    
}
//------------------------------------------------------------------------------
/**
 * @brief  writes a byte to the uart data register
 * 
 * @details writes a byte to the uart data register
 * 			which be later sent on the uart TX output pin 
 * 
 * @param val the passed value to be sent on the uart TX line
 */
void uart_reg_write_byte(USART_TypeDef * usartx ,uint8_t val)
{
 /*
  uint32_t i=0;	
   while(!uart_status_reg.data_register_empty);
	uart_data_reg.val=val;
*/
while(USART_GetFlagStatus(usartx,USART_FLAG_TXE)==RESET);
  usartx->DR=(val & (uint16_t) 0x00ff);

 }
//------------------------------------------------------------------------------------------------------------
/**
 * @brief write an array of data to the uart transmit buffer
 * 
 * @details  writes this array of bytes to the uart data rgister 
 * 			 in sequnce to be transmisted on the TX output pin
 * 
 * @param buff a pointer to the data array
 * @param size  the length of this data array buffer
 * @returns void
 */
void uart_reg_write_buffer(USART_TypeDef * usartx ,uint8_t * buff,uint16_t size)
{
	uint16_t i=0;
	for(i=0;i<size;i++)
	 uart_reg_write_byte((USART_TypeDef *) usartx ,buff[i]);
}
//------------------------------------------------------------------------------------------------------------
/**
 * @brief resets the received buffer 
 * @details resets the received buffer by 
 * 			setting each member a zero value
 * @return void  
 */
void uart_reset(void)
{
	rx_buffer_length=0;
	for(uint8_t i=0;i<UART_BUFFER_SIZE;i++)
	  rx_buffer[i]=0;
}
//------------------------------------------------------------------------------------------------------------
/**
 * @brief append the new received byte to the receive buffer
 * 
 * @param val  the byte value intended to be appended to the end of the received buffer
 * @return uint8_t 
 * @retval  0 failed to add this byte no enough space 
 * @retval  1 succeeded to add this byte to the end of the buffer
 */
uint8_t uart_rx_buffer_add(uint8_t val)
{
if(rx_buffer_length<=UART_BUFFER_SIZE)  
 {
  rx_buffer_length++;
  rx_buffer[rx_buffer_length-1]=val;
  return 1;
 }
 return 0; 
}
//------------------------------------------------------------------------------------------------------------
/**
 * @brief checks how the received message on the uart begins with
 * 	
 * @details checks if the header of received message on the uart
 * 			is greater than the minimum command legth
 * 			then it compare the first part with a predefined header	
 * 		
 * @param buffer 			array of bytes i.e. data message received on the 
 * @param Buffer_length 	the length of the message array of bytes
 * @param header 			a pointer to predefined header for the command message
 * @return uint8_t 
 */
uint8_t startswith_header(uint8_t * buffer,uint8_t Buffer_length,uint8_t * header)
{
	if(Buffer_length<UART_HEADER_SIZE)
	 return 0;
	for(uint8_t i=1;i<=UART_HEADER_SIZE;i++)
	 if(buffer[i]!=header[i])
	  return 0;	  
 return 1;	
}
//------------------------------------------------------------------------------------------------------------
/**
 * @brief checks how the received message on the uart ends with
 * 	
 * @details checks if the delimiter of received message on the uart
 * 			has received and matches with predefined delimiter
 * 		
 * @param buffer 			array of bytes i.e. data message received on the 
 * @param Buffer_length 	the length of the message array of bytes
 * @param delimiter 		a pointer to predefined delimiter for the command message
 * @return uint8_t 
 * @retval 0: neither delimiter  has received yet nor a correct delimiter received 
 * @retval 1: a correct delimiter has received 
 */
uint8_t endswith_delimiter(volatile uint8_t * buffer,uint8_t Buffer_length,uint8_t * delimiter)
{
	if(Buffer_length<UART_DELIMITER_SIZE)
	 return 0;
	for(uint8_t i=1;i<=UART_DELIMITER_SIZE;i++)
	 if(buffer[Buffer_length-i]!=delimiter[UART_DELIMITER_SIZE-i])
	  return 0;	  
 return 1;	
}
//------------------------------------------------------------------------------------------------------------

//*********************************************************************************************************
//
//  global functions' definitions
//
//**********************************************************************************************************
/**
 * @brief puts the uart in the receive mode
 * @details initializes the uart to operate in the receive mode
 * 			and resets the receive buffer
 * @return void 
 */
void uart_receive_start(void)
{
 // define the data direction of tx,rx pins
 /*  uart_CNTA_DIR.tx=1;   // set as output pin        //sbit(DDRD,PD1) DDRD |=(1<<PD1)
   uart_CNTA_DIR.rx=0;   // set as an input pin      //sbit(DDRD,PD0) DDRD &=~(1<<PD1)
   uart_CNTA_PORT.tx=1;  // set to High State        //sbit(PORT,PD1) PORTD|=(1<<PD1)
   uart_CNTA_PORT.rx=1;  // Enable Weak up resistor  //sbit(PORT,PD0) PORTD|=(1<<PD1)

   //UCSR0A=0x00;
   uart_status_reg.val=0;

  //UCSR0B=(1<<RXEN0)|(1<<RXCIE0);
   uart_control_reg.val=0;
   uart_control_reg.rx_enable=1;
   uart_control_reg.receive_complete_ie=1;
   */
   //reset the uart buffer
    uart_reset();	  
}
//-------------------------------------------------------------------------------------------------
/**
 * @brief stop the current receiving message  
 * @details stop the current receive operation and resets the 
 * 			the receive module of the uart
 */
void uart_receive_stop(void)
{
// Stop listening. 
  //uart_status_reg.val=0;  //UCSR0A=0x00;
  //uart_control_reg.val=0; //UCSR0B=0x00;

   //reset the uart buffer
   uart_reset();	 
}
//-------------------------------------------------------------------------------------------------
/**
 * @brief  checks if the uart in the receive mode and listens
 * 
 * @details checks if the uart in the receive mode and the 
 * 			receive complete interrupt mask bit has been activated
 * @return uint8_t 
 */
uint8_t uart_islistening()
{ 	
 //if(bit_is_set(UCSR0B,RXEN0) && bit_is_set(UCSR0B,RXCIE0))	
// if (uart_control_reg.rx_enable && uart_control_reg.receive_complete_ie)
//	 return 1;
 return 0;
}
//-------------------------------------------------------------------------------------------------
/**
 * @brief sends one byte on the  uart
 * 
 * @details it first change the uart mode to work in the transmist mode 
 * 			then sends the byte by first configure the TX IO pin , then write to the 
 * 			uart data register. finally returns the module to the receive mode to avoid 
 * 			losing any received data on the  RX Input pin
 * @param byte 
 * @return uint8_t 
 */
uint8_t uart_send_byte(USART_TypeDef * usartx, uint8_t byte)
{
	// send payload
	uart_reg_write_byte(usartx,byte);		
	return 1;
}
//-----------------------------------------------------------------------------------------------------------
/**
 * @brief sends an array of bytes on the uart
 * 
 * @details it is an extension to uart_send_byte, hence it sends an array of data bytes 
 * 			on the uart
 * 
 * @param buf 			a pointer to array of bytes 
 * @param buf_size 		the length of data array/buffer
 */
void uart_send_buffer(USART_TypeDef * usartx ,uint8_t * buf,uint16_t buf_size)
{
	
	// send payload
	uart_reg_write_buffer(usartx,buf,buf_size);
	
}
//-----------------------------------------------------------------------------------------------------------
/**
 * @brief sends a message on the uart
 * 
 * @details it is an extension to uart_send_buffer, 
 * 			hence, it may builds a header or a delimiter to the information data portion  
 * 			on the uart
 * 
 * @param buf 			a pointer to data array of bytes 
 * @param buf_size 		the length of data array/buffer
 */
void uart_send_message(USART_TypeDef * usartx ,uint8_t * buff,uint16_t length)
{
// Send header - a start of the message : 
 
 // send payload
 uart_send_buffer(usartx,buff,length);
 
 // Send delimiter- a end of the message :
   
}
//------------------------------------------------------------------------------------------------------------
/**
 * @brief a generic print  message on the uart
 * 
 * @details similar to uart_send_buffer, except it handles characters as an ASCII data
 * 
 * @param str 	a pointer to character string 
 */
void uart_print(USART_TypeDef * usartx ,char * str)
{
 	uart_send_buffer(usartx ,(uint8_t*)str,strlen(str));
}
//------------------------------------------------------------------------------------------------------------
/**
 * @brief a generic println  message on the uart
 * 
 * @details similar to uart_send_buffer, except it handles characters as an ASCII
 * 			data with \newline \r
 * 
 * @param str 	a pointer to character string 
 */
void uart_println(USART_TypeDef * usartx ,char * str)
{
 	uart_send_buffer(usartx ,(uint8_t*)str,strlen(str));
	uart_send_byte(usartx,'\r');
	uart_send_byte(usartx,'\n');
}
//------------------------------------------------------------------------------------------------------------
/**
 * @brief a generic print message on the uart in hexadecimal format
 
 * @details similar to uart_send_buffer, except it converrs ASCII data to hexadecimal format
 * 
 * @param data 	a pointer to start of message buffer
 * @param len 	the length of the buffer message
 */
void uart_print_Array(USART_TypeDef * usartx ,uint8_t * data,uint8_t len)
{
 	char buf[16]="";
	uint8_t val=0;
   for(uint8_t i=0;i<len;i++)
   {
      val=data[i];
       uart_print(usartx ," 0x");
       itoa(val,buf,16);
       uart_print(usartx ,buf);	   
	   if (i%5==0)
	    uart_println(usartx," ");
  }
}
//------------------------------------------------------------------------------------------------------------
/**
 * @brief a generic println message on the uart in hexadecimal format
 
 * @details similar to uart_send_buffer, except it converrs ASCII data to hexadecimal format
 * 
 * @param data 	a pointer to start of message buffer
 * @param len 	the length of the buffer message
 */
void uart_println_Array(USART_TypeDef * usartx ,uint8_t * data,uint8_t len)
{
 	char buf[16]="";
	uint8_t val=0;
   for(uint8_t i=0;i<len;i++)
   {
      val=data[i];
       uart_print(usartx,"0x");
       itoa(val,buf,16);
       uart_println(usartx,buf);	   
  }
}
//------------------------------------------------------------------------------------------------------------
/**
 * @brief 	initializes the uart module
 * @details initializes the uart module and configure the buad rate 
 * 			and the message format such as start bit, parity , stop bit
 * 			and the charactersize , it also resets the receive buffer size 
 * 			of the uart 
 * @return void
 */
void uart_init()
{
  
  USART1_init();
// pins initialization
//	uart_CNTA_DIR.tx=1;   // set as output pin
//	uart_CNTA_DIR.rx=0;   // set as an input pin
//	uart_CNTA_PORT.tx=1;  // set to High State
//	uart_CNTA_PORT.rx=1;  // Enable Weak up resistor
  
//to change uart configuration such buad rate,data frame length ,stop bits,  parity
// based on the static options provided at the top of this file 
 //    uart_configure();

 // Reset USART buffer
    uart_reset();

 }
//-------------------------------------------------------------------------------------------

/**
 * @brief  performs areceive operation of one byte on uart
 * 
 * @details receives one byte on uart at the trigger of the receive complete interrupt 
 * 			and appends this received byte to the receive buffer
 * 			this method is called in the uart receive complete interrupt service routine
 
 * @returns the received byte on the uart rx module
 * @return uint8_t 
 */
uint8_t uart_receive(USART_TypeDef * usartx)
{


  //uint8_t data=0;
  //uart_status_t status;
 // read data byte received from the rx buffer as soon as possible
   //data= uart_data_reg.val;
  // get the status of the uart
   //status.val=uart_status_reg.val;
   //uart_status_reg.val=0;
  // check no error in the received byte 
   //if(!status.data_over_run && 
//	   !status.frame_error   && 
//	   !status.parity_error)

    // clear the Interrupt 
     //USART_ClearITPendingBit(USART1,USART_IT_RXNE);

      volatile uint8_t data=0;
      volatile uint16_t status=0;
      status=usartx->SR;
      // read the received data from the usart receive buffer
      data=usartx->DR & 0x00ff;    // onlu 8_bit
    
     // reset the receive interrupt flag by software optional, reading data  reset IT_RXNE by hardware
     //RXNE flag can be also cleared by a read to the USART_DR register (USART_ReceiveData()).
     //USART_GetFlagStatus(USART1,USART_IT_TXE);
     //USART_ClearITPendingBit(USART1,USART_IT_RXNE);
        
     // push it to the receive queue
    uart_put_char(USART1,data);
    if(data==';')
        relays.val=0;

    if(USART_GetFlagStatus(USART1,USART_FLAG_PE | USART_FLAG_FE | 
                           USART_FLAG_NE | USART_FLAG_ORE)==RESET)
    {
      /** 
       * @arg USART_FLAG_ORE:  OverRun Error flag
       * @arg USART_FLAG_NE:   Noise Error flag
       * @arg USART_FLAG_FE:   Framing Error flag
       * @arg USART_FLAG_PE:   Parity Error flag
       * 
       *  PE  (Parity error) , FE (Framing error), NE (Noise error),  
       *  ORE (OverRun error) and IDLE (Idle line detected) flags are cleared by software 
       *     sequence: 
       *       1. a read operation to USART_SR register (USART_GetFlagStatus()) 
       *       2. followed by a read operation to USART_DR register (USART_ReceiveData()).
       * 
       *     RXNE flag can be also cleared by a read to the USART_DR register (USART_ReceiveData()).
       */
       //

	  // here try to append the data to the received buffer
		if(!uart_rx_buffer_add(data))
		{
		  // it is failed to add a new data as buffer is full
			uart_reset();
			buffer_overflow=1;	      
		}
	}
     
  return data;	

}
//-----------------------------------------------------------------------------
/**
 * @brief checks if data is available 
 * @details it checks if a complete command message has received
 * 			note that each command message should ends witha space and ; == " ;"
 * @return uint8_t 
 */
uint8_t uart_data_is_available(void)
{
 char * delim=" ;";
 if(rx_buffer_length!=0)
 {	 
    const uint8_t * tmp=0;//(uint8_t *) memmem((uint8_t *)rx_buffer,rx_buffer_length,(uint8_t *)delim,sizeof(delim));
   if(tmp!=NULL)
     return 1;
 }
  
 return 0;
}
//-----------------------------------------------------------------------------
//********************************************************************************************
//
// uart task definition
//
//********************************************************************************************
