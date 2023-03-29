/**
 * @brief gpio.c
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
//********************************************************************************************
//
// data struct register methods
//
//********************************************************************************************
void reg_sbits(__IO uint32_t * reg,uint32_t bits)
{
if(reg!=NULL)
 {
		*reg|=bits;
 }
}
//-------------------------------------------------------------------------------
void reg_cbits(__IO uint32_t * reg,uint32_t bits)
{
 if(reg!=NULL)
  {
	*reg&=~bits;
  }

}
//----------------------------------------------------------------------------
//********************************************************************************************
//
// Method definitions
//
//********************************************************************************************
void gpio_init(GPIO_TypeDef * port,uint16_t pin,GPIOMode_TypeDef mode,GPIOSpeed_TypeDef speed)
{
    GPIO_InitTypeDef gpioinit;
    GPIO_StructInit((GPIO_InitTypeDef *)&gpioinit);
    gpioinit.GPIO_Mode=mode;
    gpioinit.GPIO_Speed=speed;
    gpioinit.GPIO_Pin=(uint32_t)(1<<pin);
    GPIO_Init(port,(GPIO_InitTypeDef *)&gpioinit);
}
//--------------------------------------------------------------------------------------------
void gpio_pinmode(gpio_t io,GPIOMode_TypeDef mode,GPIOSpeed_TypeDef speed)
{
    GPIO_InitTypeDef gpioinit;
    GPIO_StructInit((GPIO_InitTypeDef *)&gpioinit);
    gpioinit.GPIO_Mode=mode;
    gpioinit.GPIO_Speed=speed;
    gpioinit.GPIO_Pin=(uint32_t)(1<<io.pin);
    GPIO_Init(io.port,(GPIO_InitTypeDef *)&gpioinit);
}
//--------------------------------------------------------------------------------------------
void gpio_pin_mode(gpio_t pio,uint8_t mode)
{
	uint32_t temp=0,a=0;
	uint16_t shift=0;

  shift=(pio.pin<8)?pio.pin:pio.pin-8;
  shift<<=2;
  temp= (uint32_t)(mode & 0x0f);     

  if(pio.pin<8)
  {
    a = pio.port->CRL & ~(0x0f<<shift);
    a|= temp<<shift;
    pio.port->CRL=a;
  }
  else
  {
    a =pio.port->CRH & ~(0x0f<<shift);
    a|=temp<<shift;
    pio.port->CRH=a;
  }
   
}
//--------------------------------------------------------------------------------------------
//********************************************************************************************
//
//  output operation Method definitions
//
//********************************************************************************************
void gpio_set(gpio_t pio)
{
    pio.port->BSRR|=(uint16_t)(1<<pio.pin);
    
    //sbit(pio.port->BSRR,pio.pin);
}
//--------------------------------------------------------------------------------------------
void gpio_clear(gpio_t pio)
{
  pio.port->BRR|=(uint16_t)(1<<pio.pin);
}
//--------------------------------------------------------------------------------------------
void gpio_toggle(gpio_t pio)
{
// uint8_t val=(pio.port->ODR)&((uint16_t)(1<<pio.pin));
 if(bit_is_set(pio.port->ODR,pio.pin))
  sbit(pio.port->BRR,pio.pin);
 else 
  sbit(pio.port->BSRR,pio.pin);
}
//--------------------------------------------------------------------------------------------
//********************************************************************************************
//
//  input operation Method definitions
//
//********************************************************************************************
void gpio_in_pullup(gpio_t pio)
{
  gpio_pin_mode(pio,GPIO_MODE_IN_PUPD);
  pio.port->BSRR|=((uint32_t)1<<pio.pin);
}
//--------------------------------------------------------------------------------------------
void gpio_in_pulldown(gpio_t pio)
{
  gpio_pin_mode(pio,GPIO_MODE_IN_PUPD);
  pio.port->BSRR &=~((uint32_t)1<<pio.pin);
}
//--------------------------------------------------------------------------------------------
void gpio_in_float(gpio_t pio)
{
  gpio_pin_mode(pio,GPIO_MODE_IN_FLOATING);
}
//--------------------------------------------------------------------------------------------
uint8_t gpio_get(gpio_t pio)
{
  //if((pio.port->IDR & (uint32_t)(1<<pio.pin)))
  if(bit_is_set(pio.port->IDR,pio.pin))
   return 1;
  return 0; 
}
//--------------------------------------------------------------------------------------------
uint8_t gpio_get_out(gpio_t pio)
{
 return (uint8_t) (pio.port->ODR & (uint32_t)(1<<pio.pin));
}
//--------------------------------------------------------------------------------------------
