/**
 * @brief i2c.c
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
//  extern variables
//
//********************************************************************************************
I2C_TypeDef_t * i2cx= (I2C_TypeDef_t *) I2C1_BASE; 

//gpio_t i2c_scl={GPIOB,6};
//gpio_t i2c_sda={GPIOB,7};

i2c_t myi2c={
 ((I2C_TypeDef_t *) I2C1_BASE),
{GPIOB,6},
{GPIOB,7},

//  Enable clock related to the alternative function & GPIO
{(__IO uint32_t *)&RCC->APB2ENR, RCC_APB2ENR_AFIOEN},

{(__IO uint32_t *)&RCC->APB2ENR,RCC_APB2ENR_IOPBEN},
{(__IO uint32_t *)& AFIO->MAPR,AFIO_MAPR_I2C1_REMAP},
// Enable clock related to i2c peripheral
{(__IO uint32_t *)& RCC->APB1ENR,RCC_APB1ENR_I2C1EN}, 

 // reset i2c peripheral
{(__IO uint32_t *)& RCC->APB1RSTR,RCC_APB1RSTR_I2C1RST},
 
  i2c_speed_fm_400k,//400000,
 0x3fff// reset i2c peripheral
 
};


//********************************************************************************************
//
//  i2c Methods defnitions 
//
//********************************************************************************************
void i2c_init()//(I2C_TypeDef_t *i2c,gpio_t sdl,gpio_t scl, uint32_t clock_speed)
{
  /* 1. Enable the Clock for the peripheral module AFIO/GPIO modules using */
  /* 2. Configure the pins required by the Module (AFIO_OUT or INPUT, ANALOG...) & remap incase of requirement */
  /* 3. Configure the peripheral hardware interrupt @ level of  NVIC  link to IRQ and set priority */
  /* 4.  the peripheral hardware  of the I2C */
  /* 5. Configure the peripheral interrupt @ level of the peripheral or DMA */
  /* 6. Enable the peripheral Module */

  /* 1. Enable the Clock for AFIO/GPIO modules then the peripheral module using  either
      registers :  RCC_APB1ENR |RCC_APB2ENR | RCC_AHBENR  or 
      methods periphstdlib  :  RCC_APBxPeriphClockCmd or using
  */

  // disable the i2c 
  myi2c.ptr->CR1.PE=0;

/* 1. Enable the Clock for the  AFIO/GPIO modules and the I2c peripheral module */
  
  //RCC->APB2ENR|=RCC_APB2ENR_AFIOEN;
   reg_sbits(myi2c.RCC_APBxENR_AFIO.reg,myi2c.RCC_APBxENR_AFIO.bits);

 //*(myi2c.RCC_APBxENR_AFIO_reg)|=myi2c.RCC_APBxENR_AFIOEN_val;
 // sbits(*myi2c.RCC_APBxENR_AFIO_reg,myi2c.RCC_APBxENR_AFIOEN_val);
 //RCC->APB2ENR|=RCC_APB2ENR_IOPBEN;
  reg_sbits(myi2c.RCC_APBxENR_IOP.reg,myi2c.RCC_APBxENR_IOP.bits);
  
  reg_cbits(myi2c.AFIO_MAPR_I2C.reg,myi2c.AFIO_MAPR_I2C.bits);
//*(myi2c.RCC_APBxENR_IOP_reg)|=myi2c.RCC_APBxENR_IOPEN_val;
//  sbits(*myi2c.RCC_APBxENR_IOP_reg,myi2c.RCC_APBxENR_IOPEN_val);
 //RCC->APB1ENR|=RCC_APB1ENR_I2C1EN;
 reg_sbits(myi2c.RCC_APBxENR_I2C.reg,myi2c.RCC_APBxENR_I2C.bits);
  //*(myi2c.RCC_APBxENR_I2C_reg)|=myi2c.RCC_APBxENR_I2CEN_reg;
  //  sbits(*myi2c.RCC_APBxENR_I2C_reg,myi2c.RCC_APBxENR_I2CEN_val);
/* 2. Configure the pins required by the Module (AFIO_OUT or INPUT, ANALOG...) & remap incase of requirement */
  
  gpio_pin_mode(myi2c.scl,GPIO_MODE_AF_OD_50MHZ);
  gpio_pin_mode(myi2c.sda,GPIO_MODE_AF_OD_50MHZ);



  /* 3. Configure the peripheral hardware interrupt @ level of  NVIC  link to IRQ and set priority */
  /* 4.  the peripheral hardware  of the I2C */
  /* 5. Configure the peripheral interrupt @ level of the peripheral or DMA */
  /* 6. Enable the peripheral Module */
myi2c.ptr->CR1.PE=1; //AFIO_MAPR_I2C1_REMAP;
/*  if(i2c==(I2C_TypeDef_t *) I2C1_BASE)
  {
   RCC->APB1ENR|=RCC_APB1ENR_I2C1EN;
   RCC->APB1RSTR|=RCC_APB1RSTR_I2C1RST;
   RCC->APB1RSTR&=~RCC_APB1RSTR_I2C1RST;    
  }
  else
  {

  }
  */
}
//-------------------------------------------------------------------------





void i2c_uart_print(USART_TypeDef *uart)
{
  WORD_BYTES t;	 
   RCC_ClocksTypeDef  rcc_clocks; 
   uint32_t pclk1 =0;
    RCC_GetClocksFreq(&rcc_clocks);
    pclk1 = rcc_clocks.PCLK1_Frequency;

	uart_print(uart,"\t pclk1:");  
  uart_print_integer(uart,pclk1,10);
  t.word= i2cx->CR2.FREQ;//I2C1->CR2 & 0x003f;// i2cx->CR2.FREQ
	uart_print(uart,"\t frq:");  
  uart_print_integer(uart,t.word,10); 
  
  t.word=I2C1->CCR & 0x0FFF ;//i2cx->CCR.CCR;
  uart_print(uart,"\t CCR:");
  uart_print_integer(uart,t.word,10);
  uart_print(uart,"\t");
 // t.word=i2cx->CCR.CCR & 0x0FFF ;
 // uart_print(uart,"\t CCRx:");
 // uart_print_integer(uart,t.word,10);
 // uart_print(uart,"\t");

  t.word=I2C1->TRISE& 0x003f;
  uart_print(uart,"\t tris:");
  uart_print_integer(uart,t.word,10);
  uart_print(uart,"\t\r\n");

  //t.word=i2cx->TRISE.val & 0x003f;//I2C1->TRISE& 0x003f;//i2cx->TRISE.val;
  //uart_print(uart,"\t trisx:");
  //uart_print_integer(uart,t.word,10);
  //uart_print(uart,"\r\n");


//I2C1
//  I2C1->CR1=0x3456;
  t.word=I2C1->CR1;
  uart_print(uart,"\t I2C1_CR1:");
  uart_print_integer(uart,t.word,16);
  uart_print(uart,"\t");
 
 // I2C1->CR2=0x1239;  
  t.word=I2C1->CR2;
  uart_print(uart,"\t I2C1_CR2:");
  uart_print_integer(uart,t.word,16);
  uart_print(uart,"\t");
 
 // I2C1->OAR1;
  t.word=I2C1->OAR1;
  uart_print(uart,"\t I2C1_OAR1:");
  uart_print_integer(uart,t.word,16);
  uart_print(uart,"\t");
  
 // I2C1->OAR2=0x342e;
  t.word=I2C1->OAR2;
  uart_print(uart,"\t I2C1_OAR2:");
  uart_print_integer(uart,t.word,16);
  uart_print(uart,"\r\n");

  //I2C1->SR1=0x4444;
  t.word=I2C1->SR1;
  uart_print(uart,"\t I2C1_SR1:");
  uart_print_integer(uart,t.word,16);
  uart_print(uart,"\t");
  
  //I2C1->SR2=0x8888;
  t.word=I2C1->SR2;
  uart_print(uart,"\t I2C1_SR2:");
  uart_print_integer(uart,t.word,16);
  uart_print(uart,"\t");
  
 // I2C1->CCR=0x3024;
  t.word=I2C1->CCR;
  uart_print(uart,"\t I2C1_CCR:");
  uart_print_integer(uart,t.word,16);
  uart_print(uart,"\t");

 // I2C1->TRISE=0x0040;
  t.word=I2C1->TRISE;
  uart_print(uart,"\t I2C1_TRISE:");
  uart_print_integer(uart,t.word,16);
  uart_print(uart,"\t");
  //I2C1->DR=0x6734;
  t.word=I2C1->DR;
  uart_print(uart,"\t I2C1_DR:");
  uart_print_integer(uart,t.word,16);
  uart_print(uart,"\r\n");

//I2Cx
/*
  t.word=i2cx->CR1.val;
  uart_print(uart,"\t I2Cx_CR1:");
  uart_print_integer(uart,t.word,16);
  uart_print(uart,"\t");

  t.word=i2cx->CR2.val;
  uart_print(uart,"\t I2Cx_CR2:");
  uart_print_integer(uart,t.word,16);
  uart_print(uart,"\t");
  
  t.word=i2cx->OAR1.val;
  uart_print(uart,"\t I2Cx_OAR1:");
  uart_print_integer(uart,t.word,16);
  uart_print(uart,"\t");

  t.word=i2cx->OAR2.val;
  uart_print(uart,"\t I2Cx_OAR2:");
  uart_print_integer(uart,t.word,16);
  uart_print(uart,"\r\n");

  t.word=i2cx->SR1.val;
  uart_print(uart,"\t I2Cx_SR1:");
  uart_print_integer(uart,t.word,16);
  uart_print(uart,"\t");

  t.word=i2cx->SR2.val;
  uart_print(uart,"\t I2Cx_SR2:");
  uart_print_integer(uart,t.word,16);
  uart_print(uart,"\t");

  t.word=i2cx->CCR.val;
  uart_print(uart,"\t I2Cx_CCR:");
  uart_print_integer(uart,t.word,16);
  uart_print(uart,"\t");

  t.word=i2cx->TRISE.val;
  uart_print(uart,"\t I2Cx_TRISE:");
  uart_print_integer(uart,t.word,16);
  uart_print(uart,"\t");

  t.word=i2cx->DR.val;
  uart_print(uart,"\t I2Cx_DR:");
  uart_print_integer(uart,t.word,16);
  uart_print(uart,"\r\n");
 */

}
//---------------------------------------------------------------------------------------------







/**
 * @brief initiate start condition
 * 
 * @return uint8_t 
 */
 uint8_t i2c_start()
 {

    return 0;
 }
//----------------------------------------------------------------------------------
/**
 * @brief initiate stop condition
 * 
 * @return uint8_t 
 */
uint8_t i2_stop()
{
    return 0;
}
//----------------------------------------------------------------------------------
/**
 * @brief send a byte via TWI bus
 * 
 * @param data 
 * @return uint8_t 
 */
uint8_t i2c_send_byte(uint8_t data)
{
    return 0;
}
//----------------------------------------------------------------------------------
/**
 * @brief send a slave with write operation via TWI bus
 * 
 * @param SLA_W 
 * @return uint8_t 
 */
uint8_t i2c_send_sla_wr(uint8_t SLA_W)
{
  return 0;
}
//----------------------------------------------------------------------------------
/**
 * @brief send a slave with read operation via TWI bus
 * 
 * @param SLA_R 
 * @return uint8_t 
 */
uint8_t i2c_send_sla_rd(uint8_t SLA_R)
{
 return 0;
}
//----------------------------------------------------------------------------------
/**
 * @brief write data
 * 
 * @param data 
 * @return uint8_t 
 */
uint8_t i2c_write_data(uint8_t data)
{
 return 0;
}
//----------------------------------------------------------------------------------
uint8_t i2c_read_data(uint8_t *data,uint8_t ack)
{
 return 0;
}
//----------------------------------------------------------------------------------
