/**
 * @brief system-task.c
 *
 * @param student: Sameer Almaldein
 * @param ID: 679699
 * @param University TU-Chemnitz
 * @param Master : ASE(Automotive Software Engineering )
 */ 

//********************************************************************************************
//
//  header  files
//
//********************************************************************************************
#include "init.h"
//********************************************************************************************
//
//  static Methods
//
//********************************************************************************************

//********************************************************************************************
//
//  global variables
//
//********************************************************************************************
uint8_t keypad_state=0;
uint32_t keypad_ticks=0;
uint32_t keypad_debounce_cnt=0;
 
uint8_t lcd_state=0;
uint32_t lcd_ticks=0;

uint8_t pilot_state=0;
uint32_t pilot_ticks=0;
  
uint8_t rtc_state=0;
uint32_t rtc_ticks=0;

uint8_t mpu_state=0;
uint32_t mpu_ticks=0;

//********************************************************************************************
//
//  static Methods prototype
//
//********************************************************************************************
//********************************************************************************************
//
//  extern Methods definition
//
//********************************************************************************************
void adc_task(void)
{

}
//----------------------------------------------------------
/**
 * @brief a generic task to handle uart task 
 * 
 * @details this a uart task in which the system handle all send and receive
 * 			data on this module it sleeps most of the time when a data is available 
 * 			it simply wakes up and handles the received message (i.e a message command)
 * 			it may send a response on the uart, perfom some reactions like changing the speed delay
 * 			or just pass the message to raspnet stack
 */
void uart_task(void)
{
	char buf[16]="";
	switch(uart_state)
	{
		case UART_WAIT:
			//my_gnc.usb_ticks++;
			//if(uart_ticks> UART_WAIT_TIMEOUT)// || uart_data_is_available())
			if(uart_data_is_available())
				uart_state=UART_READ;
		 break;
		case UART_READ:
			 uart_print(USART1,"\nrx_buf-len:");			 
			 utoa(rx_buffer_length,buf,10);
			 uart_println(USART1,buf);			 
			 uart_print(USART1,"rx_buf:");			 
			 uart_println(USART1,(char*) rx_buffer);

			 uart_handle_frame(USART1);
			 uart_reset_buffer();
			uart_ticks=0;
			uart_state=UART_WAIT;
		break;
	}
}
//--------------------------------------------------------------------------------------------------------------------------
void mpu6050_task(void)
{

	switch(mpu_state)
	{
		case MPU_WAIT:	mpu_wait_handle();	break;
		case MPU_INIT:	mpu_init_handle(USART1,(MPU6050_t *)&myMPU6050); break;
		case MPU_READ:
		  			switch(mpu_settings.acq_mode){
			 			case MPU_ACQ_MODE_SAMPLE: mpu_acq_handle(USART1,(MPU6050_t *)&myMPU6050); break; 			//! collecting data samples 
						case MPU_ACQ_MODE_NORM: 	mpu_read_handle(USART1,(MPU6050_t *)&myMPU6050);  break; 		//! normal collect to detect vibraion using normal threshold
					//case MPU_ACQ_MODE_AI: 		mpu6050_AI_read_task(USART1,(MPU6050_t *)&myMPU6050); break;// to be accomplish later
					}
			break;
		case MPU_PROC :mpu_proc_handle(USART1,(MPU6050_t *)&myMPU6050);   break;
		case MPU_ERROR: mpu_error_handle(USART1,(MPU6050_t *)&myMPU6050); break;
                     			
	}
}
//----------------------------------------------------------
void keypad_task()
{
 //uint8_t scan_val=0;
   switch(keypad_state)
   {

		case KEYPAD_WAIT:
				if(keypad_ticks>=KEYPAD_WAIT_TIMEOUT)
					keypad_state=KEYPAD_DEBOUNCE;
				break;
		case KEYPAD_DEBOUNCE:
				if(keypad_debounce_cnt>=KEYPAD_DEBOUNCE_TIMEOUT)
				{
					keypad_debounce_cnt=0;
					keypad_state=KEYPAD_SCAN;
				}
		        break;
		case KEYPAD_SCAN:
				// read the keys pin status
			    keypad_scan(); 
			    //scan_val=keypad_scan(); 
                //lcd_print_uint8_xy(12,0,scan_val,10);
				keypad_state=KEYPAD_PROCESS;
				break;

		case KEYPAD_PROCESS:
			    keypad_process();
				keypad_ticks=0;
				keypad_state=KEYPAD_WAIT;
				break;
	}
}
//-------------------------------------------------------------------------------------------------
void lcd_task(void)
{
  if(lcd_update)
  {
    lcd_update=0;
    //lcd_clear();
    lcd_print_xy(0,0,"UAV IMU stm32 ");
    lcd_print_xy(0,1,"VIB ");
    lcd_print_uint8(relays.val,10);
	  lcd_print("       ");	
  }
}
//----------------------------------------------------------
void X_input_task(void)
{

}
//----------------------------------------------------------
void X_output_task(void)
{

}
//----------------------------------------------------------
void rtc_task()
{

	switch(rtc_state)
	{
		case RTC_WAIT:

			if(rtc_ticks> RTC_WAIT_TIMEOUT)
			{
			 rtc_state=RTC_RUN;
			 rtc_ticks=0;
			}
		break;
		case RTC_RUN:
					system_rtc();
          gpio_toggle(blink_led);
				systemticks++;
			rtc_ticks=0;
			rtc_state=RTC_WAIT;
		break;

	}

}
//--------------------------------------------------------------------------------------------------------------------------



/*    if(blink_update)
    {
      if(GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13))
          GPIO_WriteBit(GPIOC,GPIO_Pin_13, Bit_RESET);
      else     
          GPIO_WriteBit(GPIOC,GPIO_Pin_13, Bit_SET);

      blink_update=0;
      BlinkTimingDelay= SystemCoreClock/1000;
    }
*/
