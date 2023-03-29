/**
 * @brief i2c-com.c
 *
 * @param student: Sameer Almaldein
 * @param ID: 679699
 * @param University TU-Chemnitz
 * @param Master : ASE(Automotive Software Engineering )
 * 
 * 
 */
/**
* @brief Devices can have up to three I2C peripherals. The peripherals support SMBus and
          PMBus variants.
        A peripheral begins after reset in Slave mode. To become a Master a start
        condition must be generated. The peripheral will remain in Master mode unless
        a multimaster contention is lost or a stop condition is generated.

* @todo all sorts of lovely stuff like DMA, Interrupts, SMBus variant, Status
register access, Error conditions
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


//********************************************************************************************
//
//  Methods defnitions
//
//********************************************************************************************

//********************************************************************************************
//
//  I2C Controller Generic methods  
//
//********************************************************************************************
/** 
 * @brief I2C Peripheral Enable.
 * @param[in] i2c a pointer to the  I2C register base address @ref i2c_reg_base.
*/
void i2c_peripheral_enable(I2C_TypeDef_t * i2c)
{
  i2c->CR1.PE=1;          
  //sbits(i2c->CR1.val,I2C_CR1_PE);
  //i2c->CR1.val|= I2C_CR1_PE;  
} 
//---------------------------------------------------------------------------- 
/** 
 * @brief I2C Peripheral Disable.
 * @details This must not be reset while in Master mode until a communication has finished.
            In Slave mode, the peripheral is disabled only after communication has ended.
 * @param[in] i2c a pointer to the  I2C register base address @ref i2c_reg_base.
*/
void i2c_peripheral_disable(I2C_TypeDef_t * i2c)
{
    i2c->CR1.PE=0; 
    //cbits(i2c->CR1.val,I2C_CR1_PE);
    //i2c->CR1.val&=~(I2C_CR1_PE);
}
//---------------------------------------------------------------------------- 
//********************************************************************************************
//
//  Transmitter  Master Mode methods  
//
//********************************************************************************************
/** 
* @brief I2C Send Start Condition.

* @details If in Master mode this will cause a restart condition to occur at the end of the
            current transmission. If in Slave mode, this will initiate a start condition
            when the current bus activity is completed.
 
 * @param[in] i2c a pointer to the  I2C register base address @ref i2c_reg_base.
*/
void i2c_send_start(I2C_TypeDef_t * i2c)
{
    i2c->CR1.START=1; 
    //sbits(i2c->CR1.val,I2C_CR1_START);
    //i2c->CR1.val|= I2C_CR1_START;
}
//---------------------------------------------------------------------------- 
/** 
 * @brief I2C Send Stop Condition.
 * @details After the current byte transfer this will initiate a stop condition if in Master
            mode, or simply release the bus if in Slave mode.
* @param[in] i2c a pointer to the  I2C register base address @ref i2c_reg_base.
*/
void i2c_send_stop(I2C_TypeDef_t * i2c)
{
  i2c->CR1.STOP=1; 
  //sbits(i2c->CR1.val,I2C_CR1_STOP);
  //i2c->CR1.val|=I2C_CR1_STOP;  
}
//---------------------------------------------------------------------------- 
/** 
* @brief I2C Clear Stop Flag.
* @details Clear the "Send Stop" flag in the I2C config register
 * @param[in] i2c a pointer to the  I2C register base address @ref i2c_reg_base.
*/
void i2c_clear_stop(I2C_TypeDef_t* i2c)
{
  i2c->CR1.STOP=0; 
  //cbits(i2c->CR1.val,I2C_CR1_STOP);
  //i2c->CR1.val&=I2C_CR1_STOP;
}
//----------------------------------------------------------------------------

/** 
* @brief I2C Send the 7-bit Slave Address.
* @param[in] i2c a pointer to the  I2C register base address @ref i2c_reg_base.
* @param[in] slave Unsigned int16. Slave address 0...1023.
* @param[in] readwrite Unsigned int8. Single bit to instruct slave to receive or send @ref i2c_rw.
*/ 
void i2c_send_7bit_address(I2C_TypeDef_t* i2c, uint8_t slave, uint8_t readwrite)
{
//  I2C_DR(i2c) = (uint8_t)((slave << 1) | readwrite);
    i2c->DR.byte = (uint8_t)((slave << 1) | readwrite);
}
//---------------------------------------------------------------------------- 
/** 
* @brief I2C Send Data.
* @param[in] i2c a pointer to the  I2C register base address @ref i2c_reg_base.
* @param[in] data Unsigned int8. Byte to send.
*/
void i2c_send_data(I2C_TypeDef_t* i2c, uint8_t data)
{
    i2c->DR.byte = data;
    i2c->DR.val &=0x00ff;
}
//----------------------------------------------------------------------------
/** 
* @brief I2C Get Data. 
* @param[in] i2c a pointer to the  I2C register base address @ref i2c_reg_base.
*/
uint8_t i2c_get_data(I2C_TypeDef_t * i2c)
{
    //return I2C_DR(i2c) & 0xff;
    return i2c->DR.byte & 0xff;
}
//----------------------------------------------------------------------------
//********************************************************************************************
//
//   slave Mode methods  
//
//********************************************************************************************
/** 
* @brief I2C Set the 7 bit Slave Address for the Peripheral.
 
* @details This sets an address for Slave mode operation, in 7 bit form.
* @param[in] i2c a pointer to the  I2C register base address @ref i2c_reg_base.
* @param[in] slave Unsigned int8. Slave address 0...127.
*/
void i2c_set_own_7bit_slave_address(I2C_TypeDef_t * i2c, uint8_t slave)
{
  uint16_t val = (uint16_t)(slave << 1);
  /* Datasheet: always keep 1 by software. */
   val |= (1 << 14);
   i2c->OAR1.val=val;//I2C_OAR1(i2c) = val;
  /*  
  i2c->OAR1.ADD0_9=(uint8_t)(slave<<1);
  i2c->OAR1.ADD0=0;
  i2c->OAR1.ADD8_9=0;
  i2c->OAR1.AD_MODE=0;
  i2c->OAR1.b10_13=0;
  i2c->OAR1.b14=1;
  */
}
//---------------------------------------------------------------------------- 
/** 
* @brief I2C Set the 10 bit Slave Address for the Peripheral.
* @details This sets an address for Slave mode operation, in 10 bit form.
 
* @todo add "I2C_OAR1(i2c) |= (1 << 14);" as above
* @param[in] i2c a pointer to the  I2C register base address @ref i2c_reg_base.
* @param[in] slave Unsigned int16. Slave address 0...1023.
*/
void i2c_set_own_10bit_slave_address(I2C_TypeDef_t * i2c, uint16_t slave)
{
 /*
 I2C_OAR1_t AR;
  AR.ADD0_9=slave;
  AR.b10_13=0;
  AR.b14=1;
  AR.AD_MODE=1;
  i2c->OAR1.val= AR.val;
*/
  uint16_t val =slave &0x03ff;
  val |=I2C_OAR1_ADDMODE;
  val |= (1 << 14);
  i2c->OAR1.val=val;
  //i2c->OAR1.val = (uint16_t)(I2C_OAR1_ADDMODE |(1<<14) | slave);
}
 //---------------------------------------------------------------------------- 
 /** 
* @brief I2C Set the secondary 7 bit Slave Address for the Peripheral.
 
* @details This sets a secondary address for Slave mode operation, in 7 bit form.

* @param[in] i2c a pointer to the  I2C register base address @ref i2c_reg_base.
* @param[in] slave Unsigned int8. Slave address 0...127.
*/
 void i2c_set_own_7bit_slave_address_two(I2C_TypeDef_t * i2c, uint8_t slave)
{
  uint16_t val = (uint16_t)(slave << 1);
  i2c->OAR2.val=val;

  /*  
   i2c->OAR2.ADD2=(uint8_t)(slave << 1);
  i2c->OAR2.ENDUAL=0; // enable dual mode in a different method
  */      
}
//---------------------------------------------------------------------------- 
 /** 
 * @brief I2C Enable dual addressing mode for the Peripheral.
 * @details Both OAR1 and OAR2 are recognised in 7-bit addressing mode.
 * @param[in] i2c a pointer to the  I2C register base address @ref i2c_reg_base.
*/
void i2c_enable_dual_addressing_mode(I2C_TypeDef_t * i2c)
{
  i2c->OAR2.ENDUAL=1;  
  //sbits(i2c->OAR2.val,I2C_OAR2_ENDUAL);
  //i2c->OAR2.val|=I2C_OAR2_ENDUAL; 
}
//---------------------------------------------------------------------------- 
/** 
* @brief I2C Disable dual addressing mode for the Peripheral.
* @details Only OAR1 is recognised in 7-bit addressing mode.
* @param[in] i2c a pointer to the  I2C register base address @ref i2c_reg_base.
*/
void i2c_disable_dual_addressing_mode(I2C_TypeDef_t * i2c)
{
  i2c->OAR2.ENDUAL=0;  
  //cbits(i2c->OAR2.val,I2C_OAR2_ENDUAL);
  //i2c->OAR2.val&=~I2C_OAR2_ENDUAL; 
}
//----------------------------------------------------------------------------
//********************************************************************************************
//
//  set I2C Controller clock frequency methods : Master Mode 
//
//********************************************************************************************
/** 
* @brief I2C Set Peripheral Clock Frequency.

* @details Set the peripheral clock frequency: 2MHz to 36MHz (the APB frequency). 
          Note:
          that this is <b> not </b> the I2C bus clock. This is set in conjunction with
          the Clock Control register to generate the Master bus clock, see @ref i2c_set_ccr
 
* @param[in] i2c a pointer to the  I2C register base address @ref i2c_reg_base.
* @param[in] freq Clock Frequency Setting in MHz, valid range depends on part,+
  normally 2Mhz->Max APB speed.
*/
void i2c_set_clock_frequency(I2C_TypeDef_t* i2c, uint8_t freq)
{
        uint16_t reg16;
        reg16 = i2c->CR2.val &0xffc0;  /* Clear bits [5:0]. */
        reg16 |= freq;
        i2c->CR2.val = reg16;
        
       // i2c->CR2.FREQ=freq;
}
//---------------------------------------------------------------------------- 
/** 
* @brief I2C Set Fast Mode. 
* @details Set the clock frequency to the high clock rate mode (up to 400kHz). 
            The actual clock frequency must be set with @ref i2c_set_clock_frequency
* @param[in] i2c a pointer to the  I2C register base address @ref i2c_reg_base.
*/
void i2c_set_fast_mode(I2C_TypeDef_t* i2c)
{
  i2c->CCR.FS=1;     
  //sbits(i2c->CCR.val,I2C_CCR_FS);
  //i2c->CCR.val|=I2C_CCR_FS;
}
//----------------------------------------------------------------------------
/** 
* @brief I2C Set Standard Mode.
 
* @details Set the clock frequency to the standard clock rate mode (up to 100kHz). 
  The actual clock frequency must be set with @ref i2c_set_clock_frequency
* @param[in] i2c a pointer to the  I2C register base address @ref i2c_reg_base.
*/
void i2c_set_standard_mode(I2C_TypeDef_t* i2c)
{
  i2c->CCR.FS=0;
  //cbits(i2c->CCR.val,I2C_CCR_FS);
  // i2c->CCR.val&=~I2C_CCR_FS;
}
//----------------------------------------------------------------------------
/** 
* @brief I2C Set Bus Clock Frequency.
 
* @details Set the bus clock frequency. This is a 12 bit number (0...4095) calculated
          from the formulae given in the STM32F1 reference manual in the description
          of the CCR field. It is a divisor of the peripheral clock frequency
          @ref i2c_set_clock_frequency modified by the fast mode setting
          @ref i2c_set_fast_mode
 
  @todo provide additional API assitance to set the clock, eg macros
 
  @param[in] i2c a pointer to the  I2C register base address @ref i2c_reg_base.
  @param[in] freq Unsigned int16. Bus Clock Frequency Setting 0...4095.
*/
 void i2c_set_ccr(I2C_TypeDef_t * i2c, uint16_t freq)
{
  uint16_t reg16;
  reg16 = i2c->CCR.val & 0xf000; /* Clear bits [11:0]. */
  reg16 |= freq;
  i2c->CCR.val = reg16;

  //i2c->CCR.CCR=freq ; 
}
//----------------------------------------------------------------------------
/** 
 * @brief I2C Set the Rise Time.
 
 * @details Set the maximum rise time on the bus according to the I2C specification, 
            as 1 more than the specified rise time in peripheral clock cycles. 
            This is a 6 bit number.
 @todo provide additional APIP assistance.
 @param[in] i2c a pointer to the  I2C register base address @ref i2c_reg_base.
 @param[in] trise Unsigned int16. Rise Time Setting 0...63.
*/
 void i2c_set_trise(I2C_TypeDef_t * i2c, uint16_t trise)
{
    //I2C_TRISE(i2c) = trise;
    i2c->TRISE.val=trise;
}
//----------------------------------------------------------------------------
/** 
* @brief I2C Set clock duty cycle 
* @param[in] i2c a pointer to the  I2C register base address @ref i2c_reg_base.
* @param[in] dutycycle Unsigned int32. I2C duty cycle @ref i2c_duty_cycle.
*/
void i2c_set_dutycycle(I2C_TypeDef_t* i2c, uint32_t dutycycle)
{

    i2c->CCR.DUTY=0;
    //cbits( i2c->CCR.val,I2C_CCR_DUTY);
    //i2c->CCR.val&=~I2C_CCR_DUTY;
  if (dutycycle == I2C_CCR_DUTY_16_DIV_9) 
  {
    i2c->CCR.DUTY=1;
    //sbits(i2c->CCR.val,I2C_CCR_DUTY);
    //i2c->CCR.val|=I2C_CCR_DUTY;
  }   
 // else 
 // {
 //   i2c->CCR.DUTY=0;
 //   //cbits( i2c->CCR.val,I2C_CCR_DUTY);
 //   //i2c->CCR.val&=~I2C_CCR_DUTY;
 // }
}
//---------------------------------------------------------------------------
/**
 * @brief set  the i2c communication speed.
 * @param[in] i2c a pointer to the  I2C register base address @ref i2c_reg_base.
 * @param speed one of the listed speed modes @ref i2c_speeds
 * @param clock_megahz i2c peripheral clock speed in MHz. Usually, rcc_apb1_frequency / 1e6
 */
void i2c_set_speed(I2C_TypeDef_t* i2c, enum i2c_speeds speed, uint32_t clock_megahz)
{
    i2c_set_clock_frequency(i2c, clock_megahz);
  switch(speed) 
  {
      case i2c_speed_fm_400k:
          i2c_set_fast_mode(i2c);
          i2c_set_ccr(i2c, clock_megahz * 5 / 6);
          i2c_set_trise(i2c, clock_megahz + 1);
        break;      
      
      case i2c_speed_sm_100k:
      default:/* fall back to standard mode */                
          i2c_set_standard_mode(i2c);
          i2c_set_ccr(i2c, clock_megahz * 5); /* x Mhz / (100kHz * 2) */
          i2c_set_trise(i2c, clock_megahz + 1); /* Sm mode, (100kHz) freqMhz + 1 */
        break;
  }
}
//--------------------------------------------------------------------------- 
//********************************************************************************************
//
//  Receiver mode both master and slave 
//
//********************************************************************************************
/** 
* @brief I2C Enable ACK
* @details Enables acking of own 7/10 bit address
* @param[in] i2c a pointer to the  I2C register base address @ref i2c_reg_base.
*/
void i2c_enable_ack(I2C_TypeDef_t* i2c)
{
  i2c->CR1.ACK=1;
  //sbits(i2c->CR1.ACK,I2C_CR1_ACK);
  //i2c->CR1.val|=I2C_CR1_ACK;
}
//----------------------------------------------------------------------------
/** 
* @brief I2C Disable ACK
* @details  Disables acking of own 7/10 bit address
* @param[in] i2c a pointer to the  I2C register base address @ref i2c_reg_base.
*/
void i2c_disable_ack(I2C_TypeDef_t* i2c)
{
  i2c->CR1.ACK=0;
  //cbits(i2c->CR1.ACK,I2C_CR1_ACK);
  //i2c->CR1.val&=~I2C_CR1_ACK; 
}
//----------------------------------------------------------------------------
/** 
* @brief I2C NACK Next Byte
* @details Causes the I2C controller to NACK the reception of the next byte
* @param[in] i2c a pointer to the  I2C register base address @ref i2c_reg_base.
*/
void i2c_nack_next(I2C_TypeDef_t* i2c)
{
  i2c->CR1.POS=1;
  //sbits(i2c->CR1.val,I2C_CR1_POS);
  //i2c->CR1.val|=I2C_CR1_POS;

}
//----------------------------------------------------------------------------
/** 
* @brief I2C NACK Next Byte
* @details Causes the I2C controller to NACK the reception of the current byte
* @param[in] i2c a pointer to the  I2C register base address @ref i2c_reg_base.
*/
void i2c_nack_current(I2C_TypeDef_t* i2c)
{
  i2c->CR1.POS=0;
  //cbits(i2c->CR1.val,I2C_CR1_POS);
  //i2c->CR1.val&=~I2C_CR1_POS;
} 
//----------------------------------------------------------------------------
//********************************************************************************************
//
//  I2C interrupt & DMA Methods
//
//********************************************************************************************
/** 
* @brief I2C Enable Interrupt

* @param[in] i2c a pointer to the  I2C register base address @ref i2c_reg_base.
* @param[in] interrupt Unsigned int32. Interrupt to enable.
*/
void i2c_enable_interrupt(I2C_TypeDef_t * i2c, uint32_t interrupt)
{
    i2c->CR2.val |= interrupt;
  //sbits(i2c->CR2,interrupt);  
  //  i2c->CR2.ITEVTEN=1; // Enable Event Interrupt
  //  i2c->CR2.ITBUFEN=1; // Enable TXE,RXNE buffered events
  //  i2c->CR2.ITERREN=1; // Enable Error events 
}
//----------------------------------------------------------------------------
/** 
* @brief I2C Disable Interrupt
 
* @param[in] i2c a pointer to the  I2C register base address @ref i2c_reg_base.
* @param[in] interrupt Unsigned int32. Interrupt to disable.
*/
void i2c_disable_interrupt(I2C_TypeDef_t* i2c, uint32_t interrupt)
{
  i2c->CR2.val &= ~interrupt;
  //cbits(i2c->CR2.val,interrupt);
  //  i2c->CR2.ITEVTEN=0; // disable Event Interrupt
  //  i2c->CR2.ITBUFEN=0; // disable TXE,RXNE buffered events
  //  i2c->CR2.ITERREN=0; // disable Error events 
  
}
//----------------------------------------------------------------------------
/** 
* @brief I2C Enable DMA
* @param[in] i2c a pointer to the  I2C register base address @ref i2c_reg_base.
*/
void i2c_enable_dma(I2C_TypeDef_t * i2c)
{
  i2c->CR2.DMAEN=1;
  //sbits(i2c->CR2.val,I2C_CR2_DMAEN);
  //i2c->CR2.val|=I2C_CR2_DMAEN;
}
//----------------------------------------------------------------------------
 /** 
* @brief I2C Disable DMA 
* @param[in] i2c a pointer to the  I2C register base address @ref i2c_reg_base.
*/
void i2c_disable_dma(I2C_TypeDef_t * i2c)
{
  i2c->CR2.DMAEN=0;
  //cbits(i2c->CR2.val,I2C_CR2_DMAEN);
  //i2c->CR2.val&=~I2C_CR2_DMAEN;
}
//----------------------------------------------------------------------------
/** 
* @brief I2C Set DMA last transfer
* @param[in] i2c a pointer to the  I2C register base address @ref i2c_reg_base.
*/
void i2c_set_dma_last_transfer(I2C_TypeDef_t * i2c)
{
  i2c->CR2.LAST=1;
  //sbits(i2c->CR2.val,I2C_CR2_LAST);
  //i2c->CR2.val|=I2C_CR2_LAST;
}
//----------------------------------------------------------------------------
/**
* @brief I2C Clear DMA last transfer
* @param[in] i2c a pointer to the  I2C register base address @ref i2c_reg_base.
*/
void i2c_clear_dma_last_transfer(I2C_TypeDef_t * i2c)
{
  i2c->CR2.LAST=0;
  //cbits(i2c->CR2.val,I2C_CR2_LAST);
  //i2c->CR2.val&=~I2C_CR2_LAST;
}
//----------------------------------------------------------------------------

//********************************************************************************************
//
//  I2C 
//
//********************************************************************************************

uint8_t i2c_write7_v1(I2C_TypeDef_t* i2c, int addr, const uint8_t *data, size_t n)
{
  I2Cx_Timeout=I2C_MAX_BUSY_TIME;
   // wait while busy
  while(i2c->SR2.BUSY) //((I2C_SR2(i2c) & I2C_SR2_BUSY)) 
   if(I2Cx_Timeout==0)
    return 1;
 
 // send start 
  i2c_send_start(i2c);
   I2Cx_Timeout=I2C_MAX_WAIT_TIME;
  /* Wait for the end of the start condition, master mode selected, and BUSY bit set */
  while(!i2c->SR1.SB && i2c->SR2.MSL && i2c->SR2.BUSY)   //while( !( (I2C_SR1(i2c) & I2C_SR1_SB)  && (I2C_SR2(i2c) & I2C_SR2_MSL) && (I2C_SR2(i2c) & I2C_SR2_BUSY) ));
    if( I2Cx_Timeout==0)
      return 0;
                                                        
  // send the slave address   
  i2c_send_7bit_address(i2c, addr, I2C_WRITE);
 
 /* Waiting for address is transferred. */
 //while (!(I2C_SR1(i2c) & I2C_SR1_ADDR));
   I2Cx_Timeout=I2C_MAX_WAIT_TIME;
  while(!i2c->SR1.ADDR)  
    if( I2Cx_Timeout==0)
      return 1;

  /* Clearing ADDR condition sequence. */
    (void)i2c->SR1.val;
    (void)i2c->SR2.val;    //(void)I2C_SR2(i2c);
 // send the array of data 
    for (size_t i = 0; i < n; i++) 
    {
      i2c_send_data(i2c, data[i]);
       I2Cx_Timeout=I2C_MAX_WAIT_TIME;
      while(!i2c->SR1.BTF)// while (!(I2C_SR1(i2c) & (I2C_SR1_BTF)));
        if( I2Cx_Timeout==0)
          return 1;        
    }
  // send stop condition
    i2c_send_stop(i2c);
    return 1;
}
//-------------------------------------------------------------------------------------------------------- 
uint8_t i2c_read7_v1(I2C_TypeDef_t* i2c, int addr, uint8_t *res, size_t n)
{
    I2Cx_Timeout=I2C_MAX_BUSY_TIME;
    
    i2c_send_start(i2c);
    i2c_enable_ack(i2c);
 
   /* Wait for the end of the start condition, master mode selected, and BUSY bit set */
    //while ( !( (I2C_SR1(i2c) & I2C_SR1_SB) && (I2C_SR2(i2c) & I2C_SR2_MSL) && (I2C_SR2(i2c) & I2C_SR2_BUSY) ));
    
    while(!i2c->SR1.SB && i2c->SR2.MSL && i2c->SR2.BUSY)   
    {
      if(I2Cx_Timeout==0)
        return 1;          
    }                
    i2c_send_7bit_address(i2c, addr, I2C_READ);
   /* Waiting for address is transferred. */
    //while (!(I2C_SR1(i2c) & I2C_SR1_ADDR));
    I2Cx_Timeout=I2C_MAX_WAIT_TIME;
    while(!i2c->SR1.ADDR)
    {
      if(I2Cx_Timeout==0)
      // set error and exit
        return 1;
    }
    /* Clearing ADDR condition sequence. */
    (void)i2c->SR1.val;
    (void)i2c->SR2.val;  // (void)I2C_SR2(i2c);
 
    for (size_t i = 0; i < n; ++i) 
    {
      if (i == n - 1) 
        {
          i2c_disable_ack(i2c);
        }
      //while (!(I2C_SR1(i2c) & I2C_SR1_RXNE));
      I2Cx_Timeout=I2C_MAX_WAIT_TIME;
      while(!i2c->SR1.RXNE)
      {
        if(I2Cx_Timeout==0)
          // set error and exit
        return 1;
      
      }
       res[i] = i2c_get_data(i2c);
    }
    // send stop condition
    i2c_send_stop(i2c);
 
  return 0;
}
//-----------------------------------------------------------------------------------------------------------------
/**
 * Run a write/read transaction to a given 7bit i2c address
 * If both write & read are provided, the read will use repeated start.
 * Both write and read are optional
 * There are likely still issues with repeated start/stop condtions!
 * @param i2c peripheral of choice, eg I2C1
 * @param addr 7 bit i2c device address
 * @param w buffer of data to write
 * @param wn length of w
 * @param r destination buffer to read into
 * @param rn number of bytes to read (r should be at least this long)
 */
void i2c_transfer7(I2C_TypeDef_t * i2c, uint8_t addr, const uint8_t *w, size_t wn, uint8_t *r, size_t rn) 
{
    if (wn) i2c_write7_v1(i2c, addr, w, wn);
      
    if (rn) i2c_read7_v1(i2c, addr, r, rn);
     else    i2c_send_stop(i2c);
        
}
 
