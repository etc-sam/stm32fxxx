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

uint8_t mpu_state=0;
uint32_t mpu_ticks=0;
uint8_t mpu_init_sucess=0;

uint8_t pilot_state=0;
uint32_t pilot_ticks=0;
  
uint8_t rtc_state=0;
uint32_t rtc_ticks=0;
 
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

			 uart_handle_frame();
			 uart_reset();
			uart_ticks=0;
			uart_state=UART_WAIT;
		break;
	}
}
//--------------------------------------------------------------------------------------------------------------------------
void mpu6050_task(void)
{
	static uint8_t rst=0;
	char buf[16]="";
	uint8_t error=0,temp=0;

	switch(mpu_state)
	{
		case MPU_WAIT:
			if(mpu_ticks>=MPU_WAIT_TIMEOUT)
			 { 
				if(mpu_init_sucess) 
					mpu_state=MPU_READ_ALL;
				else
					mpu_state=MPU_INIT;	
			 }
		 break;
		case MPU_INIT:
					rst=I2C_OK;
					i2c_init_std(MPU6050_I2C,MPU6050_I2C_CLOCK,0x20);
					rst=mpu6050_init((MPU6050_t *)&myMPU6050,MPU6050_Accel_Range_2G,MPU6050_Gyro_Range_500s);
					i2c_uart_print(USART1);

					mpu_init_sucess=0;
					mpu_state=MPU_ERROR;
		
					if(rst==I2C_OK)
					 {
						mpu_init_sucess=1;
						mpu_state=MPU_READ_ALL;
					 }
		 		break;

		case MPU_READ_ALL:
					rst=I2C_OK;
					rst=mpu6050_read_All((MPU6050_t *)&myMPU6050);
					mpu_state=MPU_ERROR;
					if(rst==I2C_OK)
					{
						uart_print (USART1,"...............\r\n");
						uart_print (USART1,"MPU6050 integer Data ...\r\n");
				 	    mpu6050_uart_print(USART1,(MPU6050_t *)&myMPU6050);

						uart_print (USART1,"MPU6050 Hex Data ...\r\n");
				 	    mpu6050_uart_print_raw_Data(USART1,(MPU6050_t *)&myMPU6050);

						uart_print (USART1,"MPU6050 Raw Data ...\r\n");
				 	    mpu6050_uart_print_raw_Array(USART1,(MPU6050_t *)&myMPU6050);
						uart_print (USART1,"...............\r\n");
						uart_print(USART1,"Read MPU6050_WHO_AM_I  :");	
						error=i2c_read_7bit_base_byte_std(MPU6050_I2C, myMPU6050.Address, MPU6050_WHO_AM_I , &temp);
    					uart_print(USART1,"\nResponse MPU6050_WHO_AM_I  er:");
    					uart_print_integer(USART1,error,16);
    					uart_print(USART1,"\t rd:");
    					uart_print_integer(USART1,temp,16);
    					uart_print(USART1,"\r\n");
						mpu_ticks=0;
						mpu_state=MPU_WAIT;
						//uart_print(USART1,"\t MPU_READ\r\n");
					}
				break;

				case MPU_ERROR:
				uart_print(USART1,"\t MPU_ERROR_rst:");
    			uart_print_integer(USART1,rst,10);
    			uart_print(USART1,"\n");
			    i2c_uart_print(USART1);
				
				//I2C_GenerateSTOP(I2C1,ENABLE);	
				//I2C1->CR1&=~I2C_CR1_PE;
				//I2C1->CR1|=I2C_CR1_PE;

				mpu_init_sucess=0;
				mpu_ticks=0;
				mpu_state=MPU_WAIT;
				break;
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
    lcd_print_xy(0,0,"stm32f10x ");
    lcd_print_xy(0,1,"TIM2...  ");
    lcd_print_uint8(relays.val,10);
	  lcd_print("       ");
	
		//uart_print(USART1,"RLY:");
		//uart_print_integer(USART1, relays.val,10);//t.word);
		//uart_print(USART1,"\r\n");
  }
}
//----------------------------------------------------------
void input_task(void)
{

}
//----------------------------------------------------------
void pilot_task(void)
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
