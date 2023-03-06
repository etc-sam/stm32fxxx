/**
 * @brief keypad.c
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
static uint8_t keypad_port_get_input_data(void);

static uint8_t keypad_read(void);
static void keypad_handle(void);
//********************************************************************************************
//
//  extern variables
//
//********************************************************************************************
Keypad_btn_t key_val;

uint8_t keypad_unpressed_mask=0;
//uint8_t keypad_Enter_cnt=0,keypad_Timeout_cnt=0;
//uint8_t keypad_Reset_cnt=0,keypad_Start_cnt=0;

gpio_t keypad_en={GPIOB,11};
gpio_t keypad_port[8]={
{GPIOA,0},   // keypad_DQ0=PA7
{GPIOA,1},   // keypad_DQ1=PA6
{GPIOA,2},   // keypad_DQ2=PA5
{GPIOA,3},   // keypad_DQ3=PA4
{GPIOA,4},   // keypad_DQ4=PA3
{GPIOA,5},   // keypad_DQ5=PA2   
{GPIOA,6},   // keypad_DQ5=PA2   
{GPIOA,7},   // keypad_DQ5=PA2   
};

//********************************************************************************************
//
//  static Methods defnitions
//
//********************************************************************************************
void keypad_port_input_pullup(void)
{
  for(uint8_t i=0;i<8;i++)
   gpio_in_pullup(keypad_port[i]);

}
//---------------------------------------------------------
uint8_t keypad_port_get_input_data(void)
{
  uint8_t val=0xff;
  for(uint8_t i=0;i<8;i++)
   if(!gpio_get(keypad_port[i]))
     cbit(val,i);  
  
  return val ;   
}
//---------------------------------------------------------
uint8_t keypad_read(void)
{
  uint8_t val=0xff;
// set keypad port as input with pull up resistor
   keypad_port_input_pullup();
 // set keypad enable pin as output with push-pull  
   gpio_pin_mode(keypad_en,GPIO_MODE_OUT_PP_2MHZ);
 // deactivate the keypad  
   gpio_set(keypad_en); 

  	// activate the keypad
	gpio_clear(keypad_en);

  _delay_us(10);
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");

	// read data from input port
	val=keypad_port_get_input_data();
  //lcd_print_uint8_xy(12,0,val,16);
	// deactivate the keypad
   gpio_set(keypad_en); 

return val; 
}
//---------------------------------------------------------
void keypad_handle(void)
{
//my_gnc.usb.printf("key_val:0x%02x",key_val.val);
  //my_gnc.usb.println();
  switch(key_val.val)
  {
	case 0x7c:keypad_up_key_handle();		  break;
	case 0xbc:keypad_down_key_handle();	  break;
	case 0xdc:keypad_set_key_handle();	  break;
	case 0xec:keypad_esc_key_handle();		break;
	case 0xf4:keypad_shft_key_handle();	  break;
  }
}
//---------------------------------------------------------
//********************************************************************************************
//
//  extern Methods
//
//********************************************************************************************
void keypad_init(uint8_t unpressed_mask)
{
 // set the unpressed value   
   keypad_unpressed_mask=unpressed_mask;
// set keypad port as input with pull up resistor
   keypad_port_input_pullup();
 // set keypad enable pin as output with push-pull  
   gpio_pin_mode(keypad_en,GPIO_MODE_OUT_PP_2MHZ);
 // deactivate the keypad  
   gpio_set(keypad_en); 
}
//---------------------------------------------------------
uint8_t keypad_scan(void)
{
  disable_buffer();
  key_val.val= keypad_read() & keypad_unpressed_mask;
 return key_val.val;
}
//---------------------------------------------------------
void keypad_process(void)
{
 if(key_val.val!=keypad_unpressed_mask)
 {
	 // the keypad is pressed therefore reset exit_timeout counter
		//App_t::menu.set_exit_cnt(0);
    logout_timeout.sec=5;
    logout_timeout.min=0;    
		keypad_handle();
 }

}
//---------------------------------------------------------
uint8_t keypad_is_pressed(void)
{
  if(key_val.val==keypad_unpressed_mask)
	  return 0;
  return 1;
}
//---------------------------------------------------------
void keypad_up_key_handle(void)
{
  lcd_print_xy(0,1,"up key pressed...");
  pilots.pilot_7=~pilots.pilot_7;
  TIM_Cmd(TIM2,DISABLE);
}
//---------------------------------------------------------
void keypad_down_key_handle(void)
{
   lcd_print_xy(0,1,"down key pressed...");
   pilots.pilot_6=~pilots.pilot_6;
  TIM_Cmd(TIM2,ENABLE);
}
//---------------------------------------------------------
void keypad_set_key_handle(void)
{
	lcd_print_xy(0,1,"set key pressed...");
	pilots.pilot_5=~pilots.pilot_5;
  TIM_Cmd(TIM3,DISABLE);
}
//---------------------------------------------------------
void keypad_esc_key_handle(void)
{
  lcd_print_xy(0,1,"esc key pressed...");
  pilots.pilot_4=~pilots.pilot_4;
  TIM_Cmd(TIM3,ENABLE);

}
//---------------------------------------------------------
void keypad_shft_key_handle(void)
{
	lcd_print_xy(0,1,"shft key pressed...");
	pilots.pilot_3=~pilots.pilot_3;
}
//---------------------------------------------------------
void keypad_info_key_handle(void)
{
   lcd_print_xy(0,1,"info key pressed...");
   pilots.pilot_2=~pilots.pilot_2;
}
//---------------------------------------------------------
