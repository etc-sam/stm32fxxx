/**
 * @brief TIM.h
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
// Method definitions
//
//********************************************************************************************

/**
   * @brief To Configure any Pripheral Module you have to follow the following:
   * 1. Enable the Clock of peripheral Module (RCC_APBXPeriphClockCmd or RCC_AHBPeriphClockCmd)
   * 2. Configure the pins required by the Module (AFIO_OUT or INPUT, ANALOG ...) & remap incase of requirement
   * 3. Configure the peripheral hardware interrupt @ level of  NVIC  link to IRQ and set priority
   * 4. Configure the peripheral hardware 
   * 5. Configure the peripheral interrupt @ level of the peripheral or DMA
   * 6. Enable the peripheral Module 
   * 7. Implement the the IRQ_handler a function 
   * 
   */


//********************************************************************************************
//
//  definition of Timer & interrupts
//
//********************************************************************************************
void TIM2_init(void)
{
  //1. Enable the Clock of peripheral TIM2 Module using RCC_APB1PeriphClockCmd
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);
    //RCC->APB1ENR|=RCC_APB1ENR_TIM2EN;
   
  /* 2. Configure the pins required by the Module (AFIO_OUT or INPUT, ANALOG...) & remap incase of requirement */
   // no need to implement an pin Configuration Just event update @ overflow 

  /* 3. Configure the peripheral hardware interrupt @ level of  NVIC  link to IRQ and set priority */
     NVIC_InitTypeDef NVIC_InitStruct;
     NVIC_InitStruct.NVIC_IRQChannel=TIM2_IRQn;
     NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=0;
     NVIC_InitStruct.NVIC_IRQChannelSubPriority=10;
     NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
     NVIC_Init((NVIC_InitTypeDef*) &NVIC_InitStruct);
     

  /* 4. Configure the peripheral hardware  of the TIM2 */
    
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseInitStruct;
  TIM_TimeBaseInitStruct.TIM_Prescaler=SystemCoreClock/100000 -1;
  TIM_TimeBaseInitStruct.TIM_Period=50000;
  TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM2, (TIM_TimeBaseInitTypeDef*) &TIM_TimeBaseInitStruct);

/* 5. Configure the peripheral interrupt @ level of the peripheral or DMA */
  TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);

/* 6. Enable the peripheral Module */
  TIM_Cmd(TIM2,ENABLE);
   
}
//--------------------------------------------------------------------------------------------
void TIM3_init(void)
{
  // Enable the Clock of peripheral TIM2 Module using RCC_APB1PeriphClockCmd
      RCC->APB1ENR |=RCC_APB1Periph_TIM3;  //RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2,ENABLE);

  /* 3. Configure the peripheral hardware interrupt @ level of  NVIC  link to IRQ and set priority */
     NVIC_InitTypeDef NVIC_InitStruct;
     NVIC_InitStruct.NVIC_IRQChannel=TIM3_IRQn;
     NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=0;
     NVIC_InitStruct.NVIC_IRQChannelSubPriority=11;
     NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
     NVIC_Init((NVIC_InitTypeDef*) &NVIC_InitStruct);

/* 4. Configure the peripheral hardware  of the TIM6 */
    
  TIM_TimeBaseInitTypeDef  TIM_TimeBaseInitStruct;
  TIM_TimeBaseInitStruct.TIM_Prescaler=SystemCoreClock/10000 -1;
  TIM_TimeBaseInitStruct.TIM_Period=10000;
  TIM_TimeBaseInitStruct.TIM_CounterMode=TIM_CounterMode_Up;
  TIM_TimeBaseInit(TIM3, (TIM_TimeBaseInitTypeDef*) &TIM_TimeBaseInitStruct);

/* 5. Configure the peripheral interrupt @ level of the peripheral or DMA */
    TIM3->DIER |= TIM_IT_Update;//TIM_ITConfig(TIM2,TIM_IT_Update,ENABLE);

/* 6. Enable the peripheral Module */
    TIM3->CR1 |= TIM_CR1_CEN;//TIM_Cmd(TIM3,ENABLE);
  

}
//--------------------------------------------------------------------------------------------
void TIM4_init(void)
{

}
//--------------------------------------------------------------------------------------------

//********************************************************************************************
//
// Interrupt Handler Method definitions
//
//********************************************************************************************
void TIM2_IRQHandler(void)
{
    // clear the Interrupt 
   TIM_ClearITPendingBit(TIM2,TIM_IT_Update);

    //pilots.pilot_0=~pilots.pilot_0;
    //pilot_write(pilots.val);  
}
//--------------------------------------------------------------------------------------------
void TIM3_IRQHandler(void)
{
  uint16_t t=0;
    // clear the Interrupt 
   TIM_ClearITPendingBit(TIM3,TIM_IT_Update);

    relays.val=(relays.val<0x3f)?relays.val+1:0;
    rly_write(relays.val); 
    lcd_update=1;
}
//--------------------------------------------------------------------------------------------
