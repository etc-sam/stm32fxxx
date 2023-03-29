/**
 * @brief uart-common.c
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
//  USART initialization methods
//
//********************************************************************************************
    /**
    * @brief in stm32f1038ct6 USART2 is shared with ADC define in the following pins
    * @param PA9 ---   TX1   /SCL1/T4C2
    * @param PA10 ---  RX1   /SDA1/T4C1
    * @param PA11 ---  CTS1  /USB-/CANRX
    * @param PA12 ---  RTS1  /USB+/CANTX
    * 
    */ 

void USART1_init(void)
{

  //1. Enable the Clock of peripheral USART1/AFIO/GPIOA Modules using RCC_APB2PeriphClockCmd
    //RCC_APB2PeriphClockCmd(RCC_APB2Periph_USART1,ENABLE);
    //RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO|
    //                       RCC_APB2Periph_GPIOA,ENABLE);
   RCC->APB2ENR|=RCC_APB2ENR_AFIOEN|RCC_APB2ENR_IOPAEN|RCC_APB2ENR_USART1EN;
   

  /* 2. Configure the pins required by the Module (AFIO_OUT or INPUT, ANALOG...) 
      & remap incase of requirement */
      gpio_pin_mode(uart_tx,GPIO_MODE_AF_PP_50MHZ);
      /*GPIO_InitTypeDef _gpio_init_struct;
      GPIO_StructInit((GPIO_InitTypeDef*)& _gpio_init_struct);
      // init TX1=PA9
      _gpio_init_struct.GPIO_Pin=GPIO_Pin_9;
      _gpio_init_struct.GPIO_Speed=GPIO_Speed_50MHz;
      _gpio_init_struct.GPIO_Mode=GPIO_Mode_AF_PP;
      GPIO_Init(GPIOA,&_gpio_init_struct);
      */
    // PA9 as a AFIO_PP_50MHZ MODE2[1:0]=11,CNF2[1:0]=10
    // GPIOA->CRH& =~(GPIO_CRH_MODE9|GPIO_CRH_CNF9); // at register level
    // GPIOA->CRH|=GPIO_CRH_MODE9 | GPIO_CRH_CNF9_1;
   
      // init RX1=PA10
      gpio_pin_mode(uart_rx,GPIO_MODE_IN_FLOATING);
    /*  
      _gpio_init_struct.GPIO_Pin=GPIO_Pin_10;
      _gpio_init_struct.GPIO_Speed=GPIO_Speed_50MHz;
      _gpio_init_struct.GPIO_Mode=GPIO_Mode_IN_FLOATING;
      GPIO_Init(GPIOA,&_gpio_init_struct);
      //GPIOA->ODR|=GPIO_ODR_ODR10;
    */
    // PA10 as a floating input MODE10[1:0]=00,CNF10[1:0]=01
    // GPIOA->CRH & =~(GPIO_CRH_MODE10|GPIO_CRH_CNF10);
    // GPIOA->CRH | =  GPIO_CRH_CNF10_0;


  /* 3. Configure the peripheral hardware interrupt @ level of  NVIC  link to IRQ and set priority */
     NVIC_InitTypeDef NVIC_InitStruct;
     NVIC_InitStruct.NVIC_IRQChannel=USART1_IRQn;
     NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=0;
     NVIC_InitStruct.NVIC_IRQChannelSubPriority=8;
     NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
     NVIC_Init((NVIC_InitTypeDef*) &NVIC_InitStruct);

  /* 4. Configure the peripheral hardware  of the USART3 */
    USART_InitTypeDef _usart_init_struct;
    USART_StructInit((USART_InitTypeDef *)& _usart_init_struct);
    _usart_init_struct.USART_BaudRate=115200;
    _usart_init_struct.USART_Mode=USART_Mode_Rx | USART_Mode_Tx ;
    _usart_init_struct.USART_Parity=USART_Parity_No;
    _usart_init_struct.USART_StopBits=USART_StopBits_1;
    _usart_init_struct.USART_WordLength=USART_WordLength_8b;
    _usart_init_struct.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
    USART_Init((USART_TypeDef*)USART1,(USART_InitTypeDef *)& _usart_init_struct);

/* 5. Configure the peripheral interrupt @ level of the peripheral or DMA */
  USART_ITConfig(USART1,USART_IT_RXNE,ENABLE);

/* 6. Enable the peripheral Module */
  USART_Cmd(USART1,ENABLE);
   
}
//--------------------------------------------------------------------------------------------
void USART2_init(void)
{
    /**
    * @brief in stm32f1038ct6 USART2 is shared with ADC define in the following pins
    * @param PA3 ---  RX2  /ADC3
    * @param PA2 ---  TX2  /ADC2
    * @param PA1 ---  RTS2 /ADC1
    * @param PA0 ---  CTS2 /ADC0
    * 
    */ 
  // 1. Enable the Clock of peripheral USART2 Module using RCC_APB1PeriphClockCmd
    RCC->APB1ENR |=RCC_APB1Periph_USART2;  //RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2,ENABLE);
    RCC->APB2ENR |=RCC_APB2Periph_AFIO | RCC_APB2Periph_GPIOA;

  /* 2. Configure the pins required by the Module (AFIO_OUT or INPUT, ANALOG...) 
      & remap incase of requirement */
      GPIO_InitTypeDef _gpio_init_struct;
      GPIO_StructInit((GPIO_InitTypeDef*)& _gpio_init_struct);
      // init TX2=PA2
      _gpio_init_struct.GPIO_Pin=GPIO_Pin_2;
      _gpio_init_struct.GPIO_Speed=GPIO_Speed_50MHz;
      _gpio_init_struct.GPIO_Mode=GPIO_Mode_AF_PP;
      GPIO_Init(GPIOA,&_gpio_init_struct);
   
   // PA2 as a AFIO_PP_50MHZ MODE2[1:0]=11,CNF2[1:0]=10
    // GPIOA->CRL& =~(GPIO_CRL_MODE2|GPIO_CRL_CNF2); // at register level
    // GPIOA->CRL|=GPIO_CRL_MODE2 | GPIO_CRL_CNF2_1;

      // init RX2=PA3
      _gpio_init_struct.GPIO_Pin=GPIO_Pin_3;
      _gpio_init_struct.GPIO_Speed=GPIO_Speed_50MHz;
      _gpio_init_struct.GPIO_Mode=GPIO_Mode_IN_FLOATING;
      GPIO_Init(GPIOA,&_gpio_init_struct);

  // PA3 as a floating input MODE3[1:0]=00,CNF3[1:0]=01
    // GPIOA->CRL& =~(GPIO_CRL_MODE3|GPIO_CRL_CNF3);
    // GPIOA->CRL| =  GPIO_CRL_CNF3_0;


  /* 3. Configure the peripheral hardware interrupt @ level of  NVIC  link to IRQ and set priority */
     NVIC_InitTypeDef NVIC_InitStruct;
     NVIC_InitStruct.NVIC_IRQChannel=USART2_IRQn;
     NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=0;
     NVIC_InitStruct.NVIC_IRQChannelSubPriority=8;
     NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
     NVIC_Init((NVIC_InitTypeDef*) &NVIC_InitStruct);

/* 4. Configure the peripheral hardware  of the USART2 */
    USART_InitTypeDef _usart_init_struct;
    USART_StructInit((USART_InitTypeDef*)& _usart_init_struct);
    _usart_init_struct.USART_BaudRate=115200;
    _usart_init_struct.USART_Mode=USART_Mode_Rx | USART_Mode_Tx ;
    _usart_init_struct.USART_Parity=USART_Parity_No;
    _usart_init_struct.USART_StopBits=USART_StopBits_1;
    _usart_init_struct.USART_WordLength=USART_WordLength_8b;
    _usart_init_struct.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
    USART_Init(USART2,&_usart_init_struct);

/* 5. Configure the peripheral interrupt @ level of the peripheral or DMA */
    USART_ITConfig(USART2,USART_IT_RXNE | USART_IT_TXE,ENABLE);

/* 6. Enable the peripheral Module */
    USART_Cmd(USART2,ENABLE);
  

}
//--------------------------------------------------------------------------------------------
void USART3_init(void)
{
   /**
    * @brief in stm32f1038ct6 USART3 is shared with I2c2 define in the following pins
    * @param PB11 --- RX3/SDA2
    * @param PB10 --- TX3/SCL2
    * 
    */
  //1. Enable the Clock of peripheral USART3 Module using RCC_APB1PeriphClockCmd
    RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3,ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO|
                           RCC_APB2Periph_GPIOB,ENABLE);
   
  /* 2. Configure the pins required by the Module (AFIO_OUT or INPUT, ANALOG...) 
      & remap incase of requirement */
      GPIO_InitTypeDef _gpio_init_struct;
      GPIO_StructInit((GPIO_InitTypeDef*)& _gpio_init_struct);
      // init TX3=PB10
      _gpio_init_struct.GPIO_Pin=GPIO_Pin_10;
      _gpio_init_struct.GPIO_Speed=GPIO_Speed_50MHz;
      _gpio_init_struct.GPIO_Mode=GPIO_Mode_AF_PP;
      GPIO_Init(GPIOB,&_gpio_init_struct);

      // init RX3=PB11
      _gpio_init_struct.GPIO_Pin=GPIO_Pin_11;
      _gpio_init_struct.GPIO_Speed=GPIO_Speed_50MHz;
      _gpio_init_struct.GPIO_Mode=GPIO_Mode_IN_FLOATING;
      GPIO_Init(GPIOB,&_gpio_init_struct);


  /* 3. Configure the peripheral hardware interrupt @ level of  NVIC  link to IRQ and set priority */
     NVIC_InitTypeDef NVIC_InitStruct;
     NVIC_InitStruct.NVIC_IRQChannel=USART3_IRQn;
     NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=0;
     NVIC_InitStruct.NVIC_IRQChannelSubPriority=8;
     NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
     NVIC_Init((NVIC_InitTypeDef*) &NVIC_InitStruct);

  /* 4. Configure the peripheral hardware  of the USART3 */
    USART_InitTypeDef _usart_init_struct;
    USART_StructInit((USART_InitTypeDef *)& _usart_init_struct);
    _usart_init_struct.USART_BaudRate=115200;
    _usart_init_struct.USART_Mode=USART_Mode_Rx | USART_Mode_Tx ;
    _usart_init_struct.USART_Parity=USART_Parity_No;
    _usart_init_struct.USART_StopBits=USART_StopBits_1;
    _usart_init_struct.USART_WordLength=USART_WordLength_8b;
    _usart_init_struct.USART_HardwareFlowControl=USART_HardwareFlowControl_None;
    USART_Init((USART_TypeDef*)USART3,(USART_InitTypeDef *)& _usart_init_struct);

/* 5. Configure the peripheral interrupt @ level of the peripheral or DMA */
    USART_ITConfig(USART3,USART_IT_RXNE|USART_IT_TXE,ENABLE);

/* 6. Enable the peripheral Module */
    USART_Cmd(USART3,ENABLE);

}
//--------------------------------------------------------------------------------------------

//********************************************************************************************
//
// Interrupt Handler Method definitions
//
//********************************************************************************************
/**
 * @brief USART1_IRQHandler Interrupt request for USART3 peripheral
 * @details 1. it checks: 
 *             a. the receive  data interrupt 
 *             b. the transmit data complete interrupt 
 *          2. it pushs in the received data to the received Queue to be later handled
 *          3. it pop up the data from the transmit Queue to be send through USART transmit buffer
 * @param  void
 * @returns void 
 */
void USART1_IRQHandler(void)
{
    // clear the Interrupt 
     //USART_ClearITPendingBit(USART1,USART_IT_RXNE);
     volatile uint8_t data=0;
     volatile uint16_t t=0;
    
    if(USART_GetITStatus(USART1,USART_IT_RXNE)!=RESET)
      uart_receive(USART1);

    //  TX : check if data is sent
    /*if(USART_GetITStatus(USART1,USART_IT_TXE)!=RESET)
    {
     
      // pop data  from the transmit queue to send 
        
      // reset the transmit interrupt flag by software optional,
        //USART_ClearITPendingBit(USART1,USART_IT_TXE);

       //data=0x37;//relays.val;       
      // send data to USART1 transmit buffer
        USART_SendData(USART1,data);
    }
    */
}
//--------------------------------------------------------------------------------------------
/**
 * @brief USART2_IRQHandler Interrupt request for USART3 peripheral
 * @details 1. it checks: 
 *             a. the receive  data interrupt 
 *             b. the transmit data complete interrupt 
 *          2. it pushs in the received data to the received Queue to be later handled
 *          3. it pop up the data from the transmit Queue to be send through USART transmit buffer
 * @param  void
 * @returns void 
 */
void USART2_IRQHandler(void)
{
    // clear the Interrupt 
     //USART_ClearITPendingBit(USART1,USART_IT_RXNE);
   /* 
    // RX: check if a data is received 
    if(USART_GetITStatus(USART2,USART_IT_RXNE)!=RESET)
    {
        uint8_t data=0;
        // read the received data from the usart receive buffer
        data=USART_ReceiveData(USART2) & 0x00ff;    // onlu 8_bit
        // reset the receive interrupt flag by software optional, reading data  reset IT_RXNE by hardware
        USART_ClearITPendingBit(USART2,USART_IT_RXNE);
        // push it to the receive queue
          USART_SendData(USART2,data); // for test only
    }

    //  TX : check if data is sent
    if(USART_GetITStatus(USART2,USART_IT_TXE)!=RESET)
    {
      uint8_t data=0;
      // pop data  from the transmit queue to send 
        
      // reset the transmit interrupt flag by software optional,
        USART_ClearITPendingBit(USART2,USART_IT_TXE);
      // send data to USART1 transmit buffer
      USART_SendData(USART2,data);
    }
   */
}
//--------------------------------------------------------------------------------------------
/**
 * @brief USART3_IRQHandler Interrupt request for USART3 peripheral
 * @details 1. it checks: 
 *             a. the receive  data interrupt 
 *             b. the transmit data complete interrupt 
 *          2. it pushs in the received data to the received Queue to be later handled
 *          3. it pop up the data from the transmit Queue to be send through USART transmit buffer
 * @param  void
 * @returns void 
 */

void USART3_IRQHandler(void)
{
    // clear the Interrupt 
     //USART_ClearITPendingBit(USART1,USART_IT_RXNE);
   /* 
    // RX: check if a data is received 
    if(USART_GetITStatus(USART3,USART_IT_RXNE)!=RESET)
    {
        uint8_t data=0;
        // read the received data from the usart receive buffer
        data=USART_ReceiveData(USART3) & 0x00ff;    // onlu 8_bit
        // reset the receive interrupt flag by software optional, reading data  reset IT_RXNE by hardware
        USART_ClearITPendingBit(USART3,USART_IT_RXNE);
        // push it to the receive queue
          USART_SendData(USART3,data); // for test only
    }

    //  TX : check if data is sent
    if(USART_GetITStatus(USART3,USART_IT_TXE)!=RESET)
    {
      uint8_t data=0;
      // pop data  from the transmit queue to send 
        
      // reset the transmit interrupt flag by software optional,
        USART_ClearITPendingBit(USART3,USART_IT_TXE);
      // send data to USART1 transmit buffer
        USART_SendData(USART3,data);
    }
 */
}
//--------------------------------------------------------------------------------------------

//********************************************************************************************
//
// uart Method definitions
//
//********************************************************************************************
uint8_t uart_put_char(USART_TypeDef * usartx,uint8_t data)
{
  while(USART_GetFlagStatus(usartx,USART_FLAG_TXE)==RESET);
  usartx->DR=(data & (uint16_t) 0x00ff);
  return 0;
}
//--------------------------------------------------------------------------------------------

uint8_t uart_get_char(USART_TypeDef * usartx)
{

  while(USART_GetFlagStatus(usartx,USART_FLAG_RXNE)==RESET);
  return usartx->DR & (uint16_t) 0x00ff;  
}
//--------------------------------------------------------------------------------------------
