/**
 * @brief init.c
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
uint32_t TimingDelay =0,BlinkTimingDelay=0;
uint8_t lcd_update=0,blink_update=0;

pilot_t pilots;
rly_t relays;

gpio_t blink_led={GPIOC,13};
gpio_t pilot_en={GPIOC,15};
gpio_t pilot_db[8]={
{GPIOA,7},   // pilot_db0=PA7
{GPIOA,6},   // pilot_db0=PA6
{GPIOA,5},   // pilot_db0=PA5
{GPIOA,4},   // pilot_db0=PA4
{GPIOA,3},   // pilot_db0=PA3
{GPIOA,2},   // pilot_db0=PA2   
{GPIOA,1},   // pilot_db0=PA1
{GPIOA,0},   // pilot_db0=PA0
};
gpio_t rly[6]={
{GPIOB, 12},     // rly0
{GPIOB, 13},     // rly1
{GPIOB, 14},     // rly2
{GPIOB, 15},     // rly3
{GPIOA, 8},     // rly4
{GPIOA, 11},     // rly5
};
//********************************************************************************************
//
// Method definitions
//
//********************************************************************************************
void pilot_init(void)
{
    for(uint8_t i=0;i<8;i++)
    gpio_pin_mode(pilot_db[i],GPIO_MODE_OUT_PP_2MHZ);

    gpio_pin_mode(pilot_en,GPIO_MODE_OUT_PP_2MHZ);
}
//--------------------------------------------------------------------------------------------
void rly_init(void)
{
  for(uint8_t i=0;i<6;i++)
   gpio_pin_mode(rly[i],GPIO_MODE_OUT_PP_2MHZ);
}
//--------------------------------------------------------------------------------------------
void pilot_write(uint8_t val)
{
	gpio_set(pilot_en);
    
   for(uint8_t i=0;i<8;i++)    
   if(bit_is_set(val,i))
     gpio_set(pilot_db[i]);
   else
     gpio_clear(pilot_db[i]);

    gpio_clear(pilot_en);
	    asm("nop");
	    asm("nop");
	    asm("nop");
	    asm("nop");
	gpio_set(pilot_en); 
}
//--------------------------------------------------------------------------------------------
void rly_write(uint8_t val)
{    
   for(uint8_t i=0;i<6;i++)    
   if(bit_is_set(val,i))
     gpio_set(rly[i]);
   else
     gpio_clear(rly[i]); 
}
//--------------------------------------------------------------------------------------------

void blink_init(void)
{
 /**
  * @brief Configure the blink led using the stander peripheral library
  * @details a full details steps is used to configure it 
  *          as a digital output with push-pull and low speed 2MHz
  */
    GPIO_InitTypeDef gpio;
    GPIO_StructInit((GPIO_InitTypeDef *)&gpio);
    gpio.GPIO_Speed=GPIO_Speed_2MHz;
    gpio.GPIO_Pin=GPIO_Pin_13;
    GPIO_Init(GPIOC,&gpio);    
 /**
  * @brief a number of methods to write data to gpio pin or pins or port
    
  *  void GPIO_SetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
  *  void GPIO_ResetBits(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
  *  void GPIO_WriteBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin, BitAction BitVal)
  *  void GPIO_Write(GPIO_TypeDef* GPIOx, uint16_t PortVal)
  */

     GPIO_SetBits(GPIOC,GPIO_Pin_13);
     //GPIO_ResetBits(GPIOC,GPIO_Pin_13);
     //GPIO_WriteBit(GPIOC,GPIO_Pin_13,Bit_RESET);
     //GPIO_WriteBit(GPIOC,GPIO_Pin_13,Bit_SET);
     //GPIO_Write(GPIOC,0b1110111111111111);

/**
  * @brief a number of methods to read data from 
  *             IDR (input data register)  as pins or port 
  *             ODR (output data register) as pins or port 
  *   uint8_t GPIO_ReadInputDataBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)  
  *   uint8_t GPIO_ReadOutputDataBit(GPIO_TypeDef* GPIOx, uint16_t GPIO_Pin)
  *     
  *   uint16_t GPIO_ReadInputData(GPIO_TypeDef* GPIOx)
  *   uint16_t GPIO_ReadOutputData(GPIO_TypeDef* GPIOx)
  *
  */
   uint8_t in_bit_val=0, out_bit_val=0;
   uint16_t in_port_val=0,out_port_val=0;
   
   in_bit_val=GPIO_ReadInputDataBit(GPIOC,GPIO_Pin_13);    // read IDR bit
   out_bit_val=GPIO_ReadOutputDataBit(GPIOC,GPIO_Pin_13); // read ODR  bit
   
   in_port_val=GPIO_ReadInputData(GPIOC);                // read IDR for port C
   out_port_val=GPIO_ReadOutputData(GPIOC);               // read IDR for port C

/**
  * @brief Configure the blink led using the stander peripheral library
  * @details a full detailed steps in one function gpio_init in which it defines
  *         the mode and speed as parameters
  *          as a digital output with push-pull and low speed 2MHz
  */ 
  gpio_init(blink_led.port,blink_led.pin,GPIO_Mode_Out_PP,GPIO_Speed_2MHz);
  GPIO_SetBits(blink_led.port,(uint32_t)(1<<blink_led.pin));
  GPIO_WriteBit(blink_led.port,(uint32_t)(1<<blink_led.pin),Bit_RESET);

/**
  * @brief Configure the blink led using the stander peripheral library
  * @details short detailed steps in one function gpio_pinmode in which it defines
  *         the mode and speed as parameters and pass a gpio_t
  *          as a digital output with push-pull and low speed 2MHz
  */ 
   gpio_pinmode(blink_led,GPIO_Mode_Out_PP,GPIO_Speed_2MHz);
   GPIO_SetBits(blink_led.port,(uint32_t)(1<<blink_led.pin));
   GPIO_WriteBit(blink_led.port,(uint32_t)(1<<blink_led.pin),Bit_RESET);

// Configure the blink led using the    
/**
  * @brief Configure the blink led using the stander peripheral library
  * @details short detailed steps in one function gpio_pinmode in which it defines
  *         the mode and speed as parameters and pass a gpio_t
  *          as a digital output with push-pull and low speed 2MHz
  */ 
    gpio_pin_mode(blink_led,GPIO_MODE_OUT_PP_2MHZ);  
    gpio_clear(blink_led);
  
}
//--------------------------------------------------------------------------------------------
void blink(void)
{

    // write Hi to PC13
    GPIO_SetBits(GPIOC,GPIO_Pin_13);

    //GPIO_SetBits(blink_led.port,(uint32_t)(1<<blink_led.pin)); 
    //gpio_set(blink_led);
    _delay_ms(500);
    // write LOW to PC13
    GPIO_ResetBits(GPIOC,GPIO_Pin_13);
    //GPIO_ResetBits(blink_led.port,(uint32_t)(1<<blink_led.pin)); 
    //gpio_clear(blink_led);
    _delay_ms(500);
    
}
//--------------------------------------------------------------------------------------------
void disable_buffer()
{

    // set pin mode of output latch as an output
	  gpio_pin_mode(pilot_en,GPIO_MODE_OUT_PP_2MHZ);
    // disable output latch
    gpio_set(pilot_en); 

    // set pin mode of lcd_en as an output
	  gpio_pin_mode(lcd_en,GPIO_MODE_OUT_PP_2MHZ);
    // disable lcd
    gpio_set(lcd_en); 

    // set pin mode of keypad as an output
	  gpio_pin_mode(keypad_en,GPIO_MODE_OUT_PP_2MHZ);
    // disable keypad
    gpio_set(keypad_en); 


  //set pin mode of keypad port as an input
  // which is shared with lcd and output latch 
   keypad_port_input_pullup();

}
//--------------------------------------------------------------------------------------------


//********************************************************************************************
//
//  definition of delay methods
//
//********************************************************************************************
void _delay_us(uint32_t mTime)
{
    TimingDelay=mTime;
    while(TimingDelay!=0);

    //uint32_t time=mTime*SystemCoreClock/1000000;
    //for (uint32_t i=0;i<time;i++)
    //  asm("nop");
}
//--------------------------------------------------------------------------------------------
void _delay_ms(uint32_t mTime)
{
  //uint32_t time=mTime*SystemCoreClock/5000;
  //for (uint32_t i=0;i<time;i++)
  //    asm("nop");

	 TimingDelay=mTime*1000;
   while(TimingDelay!=0);
}
//--------------------------------------------------------------------------------------------

