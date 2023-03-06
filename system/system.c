/**
 * @brief system.c
 *
 * @param student: Sameer Almaldein
 * @param ID: 679699
 * @param University TU-Chemnitz
 * @param Master : ASE(Automotive Software Engineering )
 */ 

//********************************************************************************************
//
// including header  files
//
//********************************************************************************************
 #include "init.h"
//********************************************************************************************
//
// Global variables 
//
//********************************************************************************************
uint32_t systemticks=0;
uint8_t  is_tick=0;
minute_t logout_timeout;

uint8_t me_address=1; 
uint8_t src_address=0 ;
uint8_t dst_address=0; 
//********************************************************************************************
//
// Method definitions
//
//********************************************************************************************
void system_init(void)
{

//********************************************************************************************
//
//  NVIC Global Interrupts Priority Group
//
//********************************************************************************************
  NVIC_PriorityGroupConfig(NVIC_PriorityGroup_0); 
//********************************************************************************************
//
//  Configure SysTick  and  other clock module
//
//
//********************************************************************************************
    //Configure SysTick Timer interrupt for 10 uS micro second
    if(SysTick_Config(SystemCoreClock/100000)) while(1);	 

    systemticks=0;
    is_tick=0;
    logout_timeout.sec=5;
    logout_timeout.min=0;
//********************************************************************************************
//
//  Configure RCC clock  for other peripherals module
//  mainly for GPIOx and AFIO
//
//********************************************************************************************

	// Enable peripheral clocks
   	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC,ENABLE);
	  RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD,ENABLE);
	 //RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);

	 TimingDelay=0; 
 
//********************************************************************************************
//
//  the GPIO Module Initialize
//
//********************************************************************************************    

   blink_init();
   pilot_init();
   rly_init();
   pilots.val=0xff;
   relays.val=0;
   pilot_write(pilots.val); 
   rly_write(relays.val);

   blink_update=0;
//********************************************************************************************
//
//  Keypad Module Initialize
//
//********************************************************************************************
    keypad_init(0xfc);
//********************************************************************************************
//
//  character lcd module
//
//********************************************************************************************
    lcd_init();
	  lcd_refresh();
    lcd_print_xy(0,0,"stm32f10x  ");
    lcd_update=0;
//********************************************************************************************
//
//  Configure Timer module
//
//********************************************************************************************
    //TIM2_init();
    TIM3_init();

//********************************************************************************************
//
//  Configure USART module
//
//********************************************************************************************
    //USART1_init();
    uart_init();
   
//********************************************************************************************
//
//  Configure  module
//
//********************************************************************************************
  keypad_state=0;
  keypad_ticks=0;
  keypad_debounce_cnt=0;
 
  lcd_state=0;
  lcd_ticks=0;
 
  pilot_state=0;
  pilot_ticks=0;
  
  rtc_state=0;
  rtc_ticks=0;
}
//--------------------------------------------------------------------------------------------
void system_run(void)
{
 
 // Task1 to read  external analog voltage
  //adc_task();	

  // Task2 to scan keypad
  keypad_task();	

// Task3 to read input buffer
  //inbuf_task();	

 // Task4 to read usb buffer
  //uart_task();	
  lcd_task();

// Task5 to real time clock to refresh the whole system
   rtc_task();    

}
//--------------------------------------------------------------------------------------------
void system_ticks(void)
{
// keypad task tick
  if(keypad_state==KEYPAD_WAIT)
     keypad_ticks++;

// keypad debounce tick
  if(keypad_state==KEYPAD_DEBOUNCE)
      keypad_debounce_cnt++;

// rtc task tick
  if(rtc_state==RTC_WAIT)
     rtc_ticks++;

}
//--------------------------------------------------------------------------------------------
void system_rtc(void)
{
    pilot_write(pilots.val);
	//lcd_refresh();
	
	//lcd_print_double_xy_str(0,0,"t1:",t1,2);
    //lcd_print_double_xy_str(0,1,"t2:",t2,2);

	//lcd_print_uint32_xy(10,0,systemticks,10);
	//lcd.print(0,1,SystemCoreClock);

}
//--------------------------------------------------------------------------------------------

