/**
 * @brief i2c-std.c
 *
 * @param student: Sameer Almaldein* @param ID: 679699
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
// Wait event internal methods
static uint8_t i2c_ready_std(I2C_TypeDef* I2CX);                         //! wait until I2C bus is Idle BUSY=0
static uint8_t i2c_wait_start_event_std(I2C_TypeDef* I2CX);		           //! wait start condition is complete SB=1 
static uint8_t i2c_wait_stop_event_std(I2C_TypeDef* I2CX);	             //! wait stop condition  is complete STOPF=1
static uint8_t i2c_wait_7bit_slave_address_wr_std(I2C_TypeDef* I2CX);    //! wait the slave address acknowledge Master_Write
static uint8_t i2c_wait_7bit_slave_address_rd_std(I2C_TypeDef* I2CX);    //! wait the slave address acknowledge Master_Read
static uint8_t i2c_wait_write_byte_txe_std(I2C_TypeDef* I2CX);		           //! wait the complete of current byte transmition (MASTER-write)
static uint8_t i2c_wait_write_byte_btf_std(I2C_TypeDef* I2CX);		           //! wait the complete of current byte transmition (MASTER-write)
static uint8_t i2c_wait_read_byte_rxne_std(I2C_TypeDef* I2CX);		       //! wait the complete of current byte receiption (MASTER-read) using RXNE
static uint8_t i2c_wait_read_byte_btf_std(I2C_TypeDef* I2CX);            //! wait the complete of current byte receiption (MASTER-read) using BTF

// trigger event internal methods
static uint8_t i2c_start_std(I2C_TypeDef* I2CX);						              //!initiate start condition
static uint8_t i2c_stop_std(I2C_TypeDef* I2CX);						                //! initiate stop condition
static uint8_t i2c_send_7bit_slave_address_wr_std(I2C_TypeDef* I2CX,uint8_t slave_address);	//! send a slave with write operation via I2C bus
static uint8_t i2c_send_7bit_slave_address_rd_std(I2C_TypeDef* I2CX,uint8_t slave_address);	//! send a slave with read operation via I2C bus


static uint8_t i2c_write_byte_std(I2C_TypeDef* I2CX,uint8_t data);		         //! send a byte via I2C bus
static uint8_t i2c_write_nbyte_std(I2C_TypeDef* I2CX, uint8_t *buf, size_t n); //! send a n bytes via I2C bus

static uint8_t i2c_read_lastbyte_std(I2C_TypeDef* I2CX,uint8_t *buf);	        // read only the last byte or only one byte read
static uint8_t i2c_read_last2byte_std(I2C_TypeDef* I2CX,uint8_t *buf);	      // read only the last 2 bytes or only two bytes
static uint8_t i2c_read_last3byte_std(I2C_TypeDef* I2CX,uint8_t *buf);
static uint8_t i2c_read_nbyte_std(I2C_TypeDef* I2CX,uint8_t *data, uint16_t n);	 

//********************************************************************************************
//
//  extern variables
//
//********************************************************************************************
volatile uint32_t I2Cx_Timeout =I2C_MAX_BUSY_TIME;

//********************************************************************************************
//
//  static methods definitions
//  Wait event methods
//
//********************************************************************************************
/**
 * @brief    checks that I2C bus & the module is in Idle state
 * @details  when the I2C module is in the idle state that means BUSY Flag is reset (BUSY=0)
 *          BUSY: Bus busy
                0: No communication on the bus
                1: Communication ongoing on the bus
                – Set by hardware on detection of SDA or SCL low
                – cleared by hardware on detection of a Stop condition.
               It indicates a communication in progress on the bus. This information is still updated when
               the interface is disabled (PE=0). 
 *           
             I2C_BUSY_CONDITION_ERROR:
              if a timeout is passed without detecting a BUSY=0 then set an error condition 
 *           to handle this error after 3 times try then reset the I2C and reconfigure it
 *           it could be the system is halt and need reset.  
 * @param I2CX 
 * @return uint8_t 
 */
uint8_t i2c_ready_std(I2C_TypeDef* I2CX)
{
   I2Cx_Timeout=I2C_MAX_BUSY_TIME;    
    //_delay_ms(25);
  //wait check that the I2c module is not busy
  
    while(bits_is_set(I2CX->SR2,I2C_SR2_BUSY))//I2C_GetFlagStatus(I2CX,I2C_FLAG_BUSY))
      if(I2Cx_Timeout==0)  
        return I2C_BUSY_ERROR;         // set the error then exit:: I2C_BUSY_ERROR

   return I2C_OK;   
}    
//-----------------------------------------------------------------------------------------------------------------------
/**
 * @brief wait the until the start condidtion is completed
 * @details  check that the start condition is finished  by checking the following flags 
 *            BUSY, MSL and SB flag are all set  
 *           EV5: at the  SB=1, cleared by reading SR1 register followed by writing the DR register.
 *           SB= 1 indicates Start condition generated and finished 
 *           BUSY=1 indicates the I2C is busy (no arbitration lost or peripheral) 
 *           MSL=1  indicates Master mode 
 * I2C_SR1 : I2C Status register 1
 *            SB: Start bit (Master mode)
              0: No Start condition
              1: Start condition generated.
              – Set when a Start condition generated.
              – Cleared by software by reading the SR1 register followed by writing the DR register, or by hardware when PE=0   
   I2C_SR2 : I2C Status register 2          
            TRA: Transmitter/receiver
              0: Data bytes received
              1: Data bytes transmitted
            This bit is set depending on the R/W bit of the address byte, at the end of total address phase.
            It is also cleared by hardware after detection of Stop condition (STOPF=1), repeated Start condition, 
            loss of bus arbitration (ARLO=1), or when PE=0.
            BUSY: Bus busy
             0: No communication on the bus
             1: Communication ongoing on the bus
             – Set by hardware on detection of SDA or SCL low
             – cleared by hardware on detection of a Stop condition.
             It indicates a communication in progress on the bus. This information is still updated when the interface is disabled (PE=0).
            MSL: Master/slave
              0: Slave Mode
              1: Master Mode
              – Set by hardware as soon as the interface is in Master mode (SB=1).
              – Cleared by hardware after detecting a Stop condition on the bus or a loss of arbitration (ARLO=1), or by hardware when PE=0
 *           I2C_START_ERROR :
 *           if a timeout is passed without detecting a SB=1 then set an error condition 
 *           to handle this error then reset the I2C and reconfigure it
 *           it could be the system is halt and need reset.  
 * @param I2CX 
 * @return uint8_t   
*/
uint8_t i2c_wait_start_event_std(I2C_TypeDef* I2CX)
{
   I2Cx_Timeout=I2C_MAX_WAIT_TIME;
    //wait the event I2C_EVENT_MASTER_MODE_SELECT where BUSY, MSL and SB flag are set  (At EV5)
    //EV5: at the  SB=1, cleared by reading SR1 register followed by writing the DR register.
    //!I2C_CheckEvent(I2CX,I2C_EVENT_MASTER_MODE_SELECT))
   while(bits_is_clear(I2CX->SR1,I2C_SR1_SB)|| 
         bits_is_clear(I2CX->SR2,(uint16_t)(I2C_SR2_BUSY | I2C_SR2_MSL)) ) 
    {     
        //   while(_I2C_GET_FLAG(I2CX,I2C_SR1_SB)==RESET   ||
        //         _I2C_GET_FLAG(I2CX,I2C_SR2_BUSY)==RESET ||
        //         _I2C_GET_FLAG(I2CX,I2C_SR2_MSL)==RESET  )
      if(I2Cx_Timeout==0)  
      {
        if (READ_BIT(I2CX->CR1, I2C_CR1_START) == I2C_CR1_START)
        {
          return  I2C_START_ERROR ; // set the error then exit :: I2C_START_CONDITION_ERROR :
        }
        return I2C_TIMEOUT ;        
      }   
    }
  return I2C_OK;  
}
//-----------------------------------------------------------------------------------------------------------------------
/**
 * @brief wait the until the stop condidtion is completed
 * @details  check that the stop condition is finished  by checking the flag STOPF=1 
 *           Master-Transmitter Mode:
 *              EV8_2: TxE=1, BTF = 1, Program Stop request. TxE and BTF are cleared by hardware by the Stop condition
 *           Master-receiver Mode:
 *            -N> 2
 *              EV7: RxNE=1, cleared by reading DR register
                EV7_2: BTF = 1, DataN-2 in DR and DataN-1 in shift register, program ACK = 0, Read DataN-2 in DR.Program STOP = 1, read DataN-1. 
 *           After the Stop condition generation, the interface goes automatically back to slave mode (MSL bit cleared).
            -N=2 
                EV7_3: BTF = 1, program STOP = 1, read DR twice (Read Data1 and Data2) just after programming the STOP.              
 *          STOPF:
 *            – Set by hardware when a Stop condition is detected on the bus by the slave after an acknowledge (if ACK=1).
 *            – Cleared by software reading the SR1 register followed by a write in the CR1 register, or by hardware when PE=0
            Note 1: The STOPF bit is not set after a NACK reception.
            Note 2:
                It is recommended to perform the complete clearing sequence (READ SR1 then WRITE CR1) after the STOPF is set. 
            Note 3:
                at the end of any I2C bus transaction checking the STOPF --> SR1 is read
                as each new start I2C bus transaction will always start (after checking BUSY) by generating start condition --> CR1 is written
                therefore actually after each startcondition generation the STOPF will be reset by the software implicitly  

 *           I2C_STOP_ERROR:
 *           if a timeout is passed without detecting a STOPF=1 then set an error condition 
 *           to handle this error then reset the I2C and reconfigure it
 *           it could be the system is halt and need reset.  
 * @param I2CX 
 * @return uint8_t   
*/
uint8_t i2c_wait_stop_event_std(I2C_TypeDef* I2CX)
{
  I2Cx_Timeout=I2C_MAX_WAIT_TIME;  
  // wait until stop condition is complete STOPF is set
  while(bits_is_set(I2CX->SR2,I2C_SR2_MSL))//I2Cx_Timeout>0)//bit_is_clear(I2CX->SR1,I2C_SR1_STOPF) && )//I2C_GetFlagStatus(I2CX,I2C_FLAG_STOPF))
   {   
        /* Generate Stop */
        //SET_BIT(I2CX->CR1, I2C_CR1_STOP);

      /* Check if a STOPF is detected */

      if (bits_is_set(I2CX->SR1,I2C_SR1_STOPF) )
      {
          /* Clear STOP Flag */
          _I2C_CLEAR_STOPFLAG(I2CX);      
          return 0x40;//I2C_OK;
      }
      if(I2Cx_Timeout==0)  
        return I2C_STOP_ERROR;

   }  
   //if(I2Cx_Timeout==0)  
    //return I2C_STOP_ERROR;
    // CLEAR_BIT(I2CX->CR1,I2C_CR1_PE);   //cbits(I2CX->CR1,I2C_CR1_PE);
    // asm("nop");
    // asm("nop");
    // asm("nop");
    // SET_BIT(I2CX->CR1,I2C_CR1_PE);

      //return I2C_STOP_ERROR;

    //sbits(I2CX->CR1,I2C_CR1_PE);
  return I2C_OK;
}
//-----------------------------------------------------------------------------------------------------------------------
/**
 * @brief    Waits until the slave acknowledges back to the reception of its address in write mode  
 * @details  check that the slave aknowledges back as it receives its address  the flags
 *           BUSY, MSL, ADDR, TXE and TRA which all set during EV6
 *            EV6: ADDR=1, cleared by reading SR1 register followed by reading SR2.
 *           TXE= 1 indicates that Data register empty that means th address is sent to shift-register 
 *                 and transmission is either on process or even done 
 *           ADDR=1 indicates End of address transmission which is defined by the slave acknowledgment (ACK)
 *           TRA=1  indicates Transmitter mode set depending on the R/W bit of the address byte
 *           BUSY=1 indicates the I2C is busy (no arbitration lost or peripheral) 
 *           MSL=1  indicates Master mode 
    I2C_SR1 : I2C Status register 1
            TXE: Data register empty (transmitters)
                0: Data register not empty
                1: Data register empty
              – Set when DR is empty in transmission. TxE is not set during address phase.
              – Cleared by software writing to the DR register or by hardware after a start or a stop condition or when PE=0.
              TxE is not set if either a NACK is received, or if next byte to be transmitted is PEC (PEC=1)
              Note: TxE is not cleared by writing the first data being transmitted, or by writing data when
              BTF is set, as in both cases the data register is still empty.
 *         ADDR: 
 *          This bit is cleared by software reading SR1 register followed reading SR2, or by hardware when PE=0.
 *           1.Slave :: Address matched (Slave)
              0: Address mismatched or not received.
              1: Received address matched
 *          
            2. Master : Address sent (Master)
              0: No end of address transmission
              1: End of address transmission
            – For 10-bit addressing, the bit is set after the ACK of the 2nd byte.
            – For 7-bit addressing, the bit is set after the ACK
 *          Note: 
               ADDR is not set after a NACK reception
 
   I2C_SR2 : I2C Status register 2          
            TRA: Transmitter/receiver
              0: Data bytes received
              1: Data bytes transmitted
            This bit is set depending on the R/W bit of the address byte, at the end of total address phase.
            It is also cleared by hardware after detection of Stop condition (STOPF=1), repeated Start condition, 
            loss of bus arbitration (ARLO=1), or when PE=0.
            BUSY: Bus busy
             0: No communication on the bus
             1: Communication ongoing on the bus
             – Set by hardware on detection of SDA or SCL low
             – cleared by hardware on detection of a Stop condition.
             It indicates a communication in progress on the bus. This information is still updated when the interface is disabled (PE=0).
            MSL: Master/slave
              0: Slave Mode
              1: Master Mode
              – Set by hardware as soon as the interface is in Master mode (SB=1).
              – Cleared by hardware after detecting a Stop condition on the bus or a loss of arbitration (ARLO=1), or by hardware when PE=0.

            I2C_SLAVE_ADDRESS_NACK_ERROR:
 *           if a timeout is passed without detecting a ADDR=1 then set an error condition  
 *           which indicates that no slave has acknowledged on the I2C bus either no one has
 *           this address or that slave has an issue to check 
 * @param I2CX 
 * @return uint8_t   
*/
uint8_t i2c_wait_7bit_slave_address_wr_std(I2C_TypeDef* I2CX)
{
  //! wait the slave address acknowledge Master_Write
    I2Cx_Timeout=I2C_MAX_WAIT_TIME;  
  // wait until the slave acknowledge  BUSY, MSL, ADDR, TXE and TRA flags are all set during Ev6
  //  EV6: ADDR=1, cleared by reading SR1 register followed by reading SR2. 
    while(bits_is_clear(I2CX->SR1,I2C_SR1_ADDR))
          //bits_is_clear(I2CX->SR2,(uint16_t)(I2C_SR2_BUSY|I2C_SR2_MSL|I2C_SR2_TRA)))   //!I2C_CheckEvent(I2CX,I2C_EVENT_MASTER_TRANSMITTER_MODE_SELECTED))
    {
      if(bits_is_set(I2CX->SR1,I2C_SR1_AF))  
      {
        /* Generate Stop */
        SET_BIT(I2CX->CR1, I2C_CR1_STOP);
        /* Clear AF Flag */
        CLEAR_BIT(I2CX->SR1,I2C_FLAG_AF);  //_I2C_CLEAR_FLAG(hi2c, I2C_FLAG_AF);
        
      // I2C_NACK Acknowledge no slave with this address at the bus
        return I2C_NACK_ERROR;
     }
     if(I2Cx_Timeout==0)
        return I2C_TIMEOUT; //I2C_ERROR
    }
   return I2C_OK; 
}
//-----------------------------------------------------------------------------------------------------------------------
/**
 * @brief    Waits the until the slave acknowledges back to the reception of its address in read mode 
 * @details  check that the slave aknowledges back as it receives its address  the flags
 *            BUSY, MSL and ADDR flags which all set  TRA=0
 *           TXE= 1 no need to check it as the master will go to receiver mode after 
 *           ADDR=1 indicates End of address transmission which is defined by the slave acknowledgment (ACK)
 *           TRA=0  indicates Receiver mode set depending on the R/W bit of the address byte
 *           BUSY=1 indicates the I2C is busy (no arbitration lost or peripheral) 
 *           MSL=1  indicates Master mode 
    I2C_SR1 : I2C Status register 1
 *         ADDR: 
 *          This bit is cleared by software reading SR1 register followed reading SR2, or by hardware when PE=0.
 *           1.Slave :: Address matched (Slave)
              0: Address mismatched or not received.
              1: Received address matched
 *          
            2. Master : Address sent (Master)
              0: No end of address transmission
              1: End of address transmission
            – For 10-bit addressing, the bit is set after the ACK of the 2nd byte.
            – For 7-bit addressing, the bit is set after the ACK
 *          Note: 
               ADDR is not set after a NACK reception
 
   I2C_SR2 : I2C Status register 2          
            TRA: Transmitter/receiver
              0: Data bytes received
              1: Data bytes transmitted
            This bit is set depending on the R/W bit of the address byte, at the end of total address phase.
            It is also cleared by hardware after detection of Stop condition (STOPF=1), repeated Start condition, 
            loss of bus arbitration (ARLO=1), or when PE=0.
            BUSY: Bus busy
             0: No communication on the bus
             1: Communication ongoing on the bus
             – Set by hardware on detection of SDA or SCL low
             – cleared by hardware on detection of a Stop condition.
             It indicates a communication in progress on the bus. This information is still updated when the interface is disabled (PE=0).
            MSL: Master/slave
              0: Slave Mode
              1: Master Mode
              – Set by hardware as soon as the interface is in Master mode (SB=1).
              – Cleared by hardware after detecting a Stop condition on the bus or a loss of arbitration (ARLO=1), or by hardware when PE=0.
               
            I2C_SLAVE_ADDRESS_NACK_ERROR:
 *           if a timeout is passed without detecting a ADDR=1 then set an error condition  
 *           which indicates that no slave has acknowledged on the I2C bus either no one has
 *           this address or that slave has an issue to check 
 * @param I2CX 
 * @return uint8_t   
*/
uint8_t i2c_wait_7bit_slave_address_rd_std(I2C_TypeDef* I2CX)
{
  //! wait the slave address acknowledge Master_Read
     I2Cx_Timeout=I2C_MAX_WAIT_TIME;  
    // wait until the slave acknowledge  BUSY, MSL, ADDR flags are all set 
    while(bits_is_clear(I2CX->SR1,I2C_SR1_ADDR) || bits_is_clear(I2CX->SR2,(uint16_t)(I2C_SR2_BUSY|I2C_SR2_MSL)))//!I2C_CheckEvent(I2CX,I2C_EVENT_MASTER_RECEIVER_MODE_SELECTED)) // while(I2C_GetFlagStatus(I2CX , I2C_FLAG_ADDR)) 
     {
      if(bits_is_set(I2CX->SR1,I2C_SR1_AF))  
      {
        /* Generate Stop */
        SET_BIT(I2CX->CR1, I2C_CR1_STOP);
        /* Clear AF Flag */
        CLEAR_BIT(I2CX->SR1,I2C_FLAG_AF);  //_I2C_CLEAR_FLAG(hi2c, I2C_FLAG_AF);
        
      // I2C_SLAVE_ADDRESS_NACK Acknowledge no slave with this address at the bus
        return I2C_NACK_ERROR;
      }        
     if(I2Cx_Timeout==0)
      return I2C_TIMEOUT; //I2C_ERROR
    }

  return I2C_OK; 
}
//-----------------------------------------------------------------------------------------------------------------------
/**
 * @brief    Waits the until the complete transmistion of the current data byte 
 * @details  check that  the complete transmistion of the current data byte has completed 
 *            by checking the flag BTF 
 *           EV8_1: TxE=1,BTF=1, shift register empty, data register empty, write Data1 in DR.
             EV8 :  TxE=1,BTF=0, shift register not empty, .data register empty, cleared by writing DR register
 *           BTF: Byte transfer finished
                0: Data byte transfer not done
                1: Data byte transfer succeeded
              – Set by hardware when NOSTRETCH=0 and:
              – In reception when a new byte is received (including ACK pulse) and DR has not been read yet (RxNE=1).
              – In transmission when a new byte should be sent and DR has not been written yet (TxE=1).
              – Cleared by software reading SR1 followed by either a read or write in the DR register or by
              - Cleared by hardware after a start or a stop condition in transmission or when PE=0.
              Note: The BTF bit is not set after a NACK reception

            I2C_TX_BYTE_ERROR:
 *           if a timeout is passed without detecting a BTF=1 then set an error condition  
 * @param I2CX 
 * @return uint8_t   
*/
uint8_t i2c_wait_write_byte_btf_std(I2C_TypeDef* I2CX)		           
{
    //! wait the complete of current byte transmition (MASTER-write)
    I2Cx_Timeout=I2C_MAX_WAIT_TIME; 
    //volatile uint32_t Timeout=0xffff;
    //Wait until BTF is set
    // each time just repeat Ev8_1 & Ev8 : shift register empty, data register empty, and need to write to DR register
    while(bits_is_clear(I2CX->SR1,I2C_SR1_BTF)) //!I2C_GetFlagStatus(I2CX,I2C_FLAG_TXE))
    {
        if(bits_is_set(I2CX->SR1,I2C_SR1_AF))  
        {
         /* Generate Stop */
         SET_BIT(I2CX->CR1, I2C_CR1_STOP);
        /* Clear AF Flag */
         CLEAR_BIT(I2CX->SR1,I2C_FLAG_AF);  //_I2C_CLEAR_FLAG(hi2c, I2C_FLAG_AF);
        
        // I2C_SLAVE_ADDRESS_NACK Acknowledge no slave with this address at the bus
        return I2C_NACK_ERROR;
       }
      if(I2Cx_Timeout==0)
        return  I2C_TX_BTF_ERROR;// set the error then exit ::I2C_TX_BTF_ERROR
   }
    return I2C_OK;
}
//-----------------------------------------------------------------------------------------------------------------------
/**
 * @brief    Waits the until the complete transmistion of the current data byte 
 * @details  check that  the complete transmistion of the current data byte has completed 
 *            by checking the flag BTF 
 *           EV8_1: TxE=1,BTF=1, shift register empty, data register empty, write Data1 in DR.
             EV8 :  TxE=1,BTF=0, shift register not empty, .data register empty, cleared by writing DR register
 *           BTF: Byte transfer finished
                0: Data byte transfer not done
                1: Data byte transfer succeeded
              – Set by hardware when NOSTRETCH=0 and:
              – In reception when a new byte is received (including ACK pulse) and DR has not been read yet (RxNE=1).
              – In transmission when a new byte should be sent and DR has not been written yet (TxE=1).
              – Cleared by software reading SR1 followed by either a read or write in the DR register or by
              - Cleared by hardware after a start or a stop condition in transmission or when PE=0.
              Note: The BTF bit is not set after a NACK reception

            I2C_TX_BYTE_ERROR:
 *           if a timeout is passed without detecting a BTF=1 then set an error condition  
 * @param I2CX 
 * @return uint8_t   
*/
uint8_t i2c_wait_write_byte_txe_std(I2C_TypeDef* I2CX)		           
{
    //! wait the complete of current byte transmition (MASTER-write)
    I2Cx_Timeout=I2C_MAX_WAIT_TIME; 
    //volatile uint32_t Timeout=0xffff;
    //Wait until BTF is set
    // each time just repeat Ev8_1 & Ev8 : shift register empty, data register empty, and need to write to DR register
    while(bits_is_clear(I2CX->SR1,I2C_SR1_TXE)) //!I2C_GetFlagStatus(I2CX,I2C_FLAG_TXE))
    {
        if(bits_is_set(I2CX->SR1,I2C_SR1_AF))  
        {
           /* Generate Stop */
            SET_BIT(I2CX->CR1, I2C_CR1_STOP);
          /* Clear AF Flag */
            CLEAR_BIT(I2CX->SR1,I2C_FLAG_AF);  //_I2C_CLEAR_FLAG(hi2c, I2C_FLAG_AF);
          // I2C_SLAVE_ADDRESS_NACK Acknowledge no slave with this address at the bus
            return I2C_NACK_ERROR;
        }
        if(I2Cx_Timeout==0)
          return  I2C_TX_TXE_ERROR; // set the error then exit ::I2C_TX_BTF_ERROR
    }
    return I2C_OK;
}
//-----------------------------------------------------------------------------------------------------------------------
/**
 * @brief    Waits the until the complete receiption of the current data byte 
 * @details  check that  the complete receiption  of the current data byte has completed 
 *            by checking the flag I2C_FLAG_RXNE
 * 
 *      RXNE: Data register not empty (receivers)
 *            0: Data register empty
              1: Data register not empty
              – Set when data register is not empty in receiver mode. RxNE is not set during address phase.
              – Cleared by software reading or writing the DR register or by hardware when PE=0.
            RxNE is not set in case of ARLO event.
            RxNE is not cleared by reading data when BTF is set, as the data register is still full. 

 *           BTF: Byte transfer finished
                0: Data byte transfer not done
                1: Data byte transfer succeeded
              – Set by hardware when NOSTRETCH=0 and:
              – In reception when a new byte is received (including ACK pulse) and DR has not been read yet (RxNE=1).
              – In transmission when a new byte should be sent and DR has not been written yet (TxE=1).
              – Cleared by software reading SR1 followed by either a read or write in the DR register or by
              - Cleared by hardware after a start or a stop condition in transmission or when PE=0.
          Note: The BTF bit is not set after a NACK reception

            I2C_RX_RXNE_ERROR:
 *           if a timeout is passed without detecting a RNXE=1 then set an error condition  
 * @param I2CX 
 * @return uint8_t   
*/
//#define  I2C_EVENT_MASTER_BYTE_RECEIVED                    ((uint32_t)0x00030040)  /* BUSY, MSL and RXNE flags */
uint8_t i2c_wait_read_byte_rxne_std(I2C_TypeDef* I2CX)		             
{
 //! wait the complete of current byte receiption (MASTER-read)
     //Wait until RXNE is set
    I2Cx_Timeout=I2C_MAX_WAIT_TIME; 
    while(bits_is_clear(I2CX->SR1,I2C_SR1_RXNE))//I2C_GetFlagStatus(I2CX,I2C_FLAG_RXNE))
    {
      /* Check if a STOPF is detected */
      if (bits_is_set(I2CX->SR1,I2C_SR1_STOPF) )
      {
          /* Clear STOP Flag */
           _I2C_CLEAR_STOPFLAG(I2CX);      
         return I2C_ERROR;
      }
      if(I2Cx_Timeout==0)  
           return I2C_RX_RXNE_ERROR;// set the error then exit ::I2C_RX_RXNE_ERROR
     }
    return I2C_OK;
}
//-----------------------------------------------------------------------------------------------------------------------
/**
 * @brief    Waits the until the complete receiption of the current data byte 
 * @details  check that  the complete receiption  of the current data byte has completed 
 *            by checking the flag I2C_FLAG_BTF
 
 *           BTF: Byte transfer finished
                0: Data byte transfer not done
                1: Data byte transfer succeeded
              – Set by hardware when NOSTRETCH=0 and:
              – In reception when a new byte is received (including ACK pulse) and DR has not been read yet (RxNE=1).
              – In transmission when a new byte should be sent and DR has not been written yet (TxE=1).
              – Cleared by software reading SR1 followed by either a read or write in the DR register or by
              - Cleared by hardware after a start or a stop condition in transmission or when PE=0.
          Note: The BTF bit is not set after a NACK reception

            I2C_RX_BTF_ERROR:
 *           if a timeout is passed without detecting a RNXE=1 then set an error condition  
 * @param I2CX 
 * @return uint8_t   
*/ 
uint8_t i2c_wait_read_byte_btf_std(I2C_TypeDef* I2CX)          
{
  //! wait the complete of current byte receiption (MASTER-read) using BTF
  // EV7_3 -- Wait for BTF , program stop , read data twice
    I2Cx_Timeout=I2C_MAX_WAIT_TIME; 
    while(bits_is_clear(I2CX->SR1,I2C_SR1_BTF)) //I2C_GetFlagStatus(I2CX,I2C_FLAG_BTF))
    {
      if(I2Cx_Timeout==0)  
          return I2C_RX_BTF_ERROR;// set the error then exit ::I2C_RX_RXNE_ERROR
     }

    return I2C_OK;
}
//-----------------------------------------------------------------------------------------------------------------------

//********************************************************************************************
//
//  static methods definitions
//  trigger event methods
//
//********************************************************************************************
/**
 * @brief initiate start condition
 * 
 * @param I2CX 
 * @return uint8_t 
 */
uint8_t i2c_start_std(I2C_TypeDef* I2CX)
{ 
   // activate PE
    //CLEAR_BIT(I2CX->CR1,I2C_CR1_PE);
    SET_BIT(I2CX->CR1,I2C_CR1_PE);
   // clear all error flags
    CLEAR_BIT(I2CX->SR1,I2C_SR1_BERR|I2C_SR1_ARLO|I2C_SR1_AF|I2C_SR1_OVR);
   // Disable Pos
   CLEAR_BIT(I2CX->CR1, I2C_CR1_POS);
   // Enable acknowledgment
   SET_BIT(I2CX->CR1,I2C_CR1_ACK);
   // send the start condition 
   SET_BIT(I2CX->CR1,I2C_CR1_START); //I2C_GenerateSTART(I2CX,ENABLE);
  //wait the event I2C_EVENT_MASTER_MODE_SELECT where BUSY, MSL and SB flag are set  
  return i2c_wait_start_event_std(I2CX);
}					        
//-----------------------------------------------------------------------------------------------------------------------
/**
 * @brief  initiate stop condition
 * 
 * @param I2CX 
 * @return uint8_t 
 */
uint8_t i2c_stop_std(I2C_TypeDef* I2CX)
{
    // generate the stop condition 
      SET_BIT(I2CX->CR1,I2C_CR1_STOP); //I2C_GenerateSTOP(I2CX,ENABLE);
    // wait until stop condition is complete STOPF is set
     return i2c_wait_stop_event_std(I2CX);
}				
//-----------------------------------------------------------------------------------------------------------------------
/**
 * @brief send a slave with write operation via I2C bus
 * 
 * @param I2CX 
 * @param  slave_address
 * @return * uint8_t 
 */
uint8_t i2c_send_7bit_slave_address_wr_std(I2C_TypeDef* I2CX,uint8_t slave_address)
{
      //(void)I2CX->SR1;
    uint8_t error=0;
    
    /* Send slave address */
     //I2CX->DR = slave_address & 0xfe;
     I2CX->DR = I2C_7BIT_ADD_WRITE(slave_address); //I2C_Send7bitAddress(I2CX,slave_address,I2C_Direction_Transmitter);
   
    // wait until the slave acknowledge  BUSY, MSL, ADDR, TXE and TRA flags are all set 
    error=i2c_wait_7bit_slave_address_wr_std(I2CX);
    
    if(error==I2C_OK)
    {
      /* Clear ADDR flag */
       _I2C_CLEAR_ADDRFLAG(I2CX);

        /* Wait until TXE flag is set */
      error=i2c_wait_write_byte_txe_std(I2CX);
 
    }

    return error;    
}
//-----------------------------------------------------------------------------------------------------------------------
/**
 * @brief send a slave with read operation via I2C bus
 * 
 * @param I2CX 
 * @param  slave_address
 * @return uint8_t 
 */
uint8_t i2c_send_7bit_slave_address_rd_std(I2C_TypeDef* I2CX,uint8_t slave_address)	
{ 
    uint8_t error=I2C_OK;
    //(void)I2CX->SR1;
       //I2CX->DR = slave_address | 0x01;
     I2CX->DR = I2C_7BIT_ADD_READ(slave_address); //I2C_Send7bitAddress(I2CX,slave_address,I2C_Direction_Receiver);
     
     // wait until the slave acknowledge  BUSY, MSL, ADDR flags are all set 
     error=i2c_wait_7bit_slave_address_rd_std(I2CX);
     return error;
}
//-----------------------------------------------------------------------------------------------------------------------
/**
 * @brief write a byte via TWI/I2C bus to the slave
 * 
 * @param I2CX 
 * @param data 
 * @return uint8_t 
 */
uint8_t i2c_write_byte_std(I2C_TypeDef* I2CX,uint8_t data)		        
{
    uint8_t error=0;
    //Ev6: send the byte
      I2CX->DR=data;///I2C_SendData(I2CX,data);    
    //Wait until txe is set
    error=i2c_wait_write_byte_txe_std(I2CX);
    return error;
}
//-----------------------------------------------------------------------------------------------------------------------
/**
 * @brief write an array of n byte via TWI/I2C bus to the slave
 * 
 * @param I2CX 
 * @param data 
 * @return uint8_t 
 */
uint8_t i2c_write_nbyte_std(I2C_TypeDef* I2CX, uint8_t *buf, size_t n)		        
{
    uint16_t i=0;
    uint8_t error=0;
    //Ev6: send the byte
    for(i=0;i<n;i++)
    {
        error=i2c_write_byte_std(I2CX,buf[i]);
        if(error) 
          return error;
    }
    // no error detected just return 0
    return I2C_OK;
}
//-----------------------------------------------------------------------------------------------------------------------
/**
 * @brief 
 *      EV7_3: BTF = 1, program STOP = 1, read DR twice (Read Data1 and Data2) just after programming the STOP.
 * @param I2CX 
 * @param data 
 * @param ack 
 * @return uint8_t 
 */
uint8_t i2c_read_lastbyte_std(I2C_TypeDef* I2CX,uint8_t *data)
{
   uint8_t error=I2C_OK;
   // clear POS flag
     CLEAR_BIT(I2CX->CR1,I2C_CR1_POS); //I2C_NACKPositionConfig(I2CX , I2C_NACKPosition_Current);

    /* Disable Acknowledge */
     CLEAR_BIT(I2CX->CR1,I2C_CR1_ACK); //I2C_AcknowledgeConfig(I2CX , DISABLE);

// EV6_3 -- must be atomic -- Clear ADDR (by reading SR1 then SR2), generate STOP  
  /* Disable all active IRQs around ADDR clearing and STOP programming because the EV6_3
    software sequence must complete before the current byte end of transfer */
  __disable_irq ();
    _I2C_CLEAR_ADDRFLAG(I2CX);                /* Clear ADDR flag */ // (void) I2CX->SR1; (void) I2CX->SR2;
     SET_BIT(I2CX->CR1,I2C_CR1_STOP);        /* Generate Stop */  //I2C_GenerateSTOP(I2CX ,ENABLE);
 __enable_irq ();

  // Receive data EV7
  error=i2c_wait_read_byte_rxne_std(I2CX);
  if(error!=I2C_OK)
    return error;

   *data = I2CX->DR;
   //uart_print(USART1,"I2C_DR:");
   //uart_print_integer(USART1,*data,16);
   //uart_print(USART1,"\r\n");

  return I2C_OK;
}
//-----------------------------------------------------------------------------------------------------------------------
/**
 * @brief 
 * 
 * @param I2CX 
 * @param data 
 * @param ack 
 * @return uint8_t 
 */
uint8_t i2c_read_last2byte_std(I2C_TypeDef* I2CX,uint8_t * buf)
{
  uint8_t error=I2C_OK;
  /* Enable Pos */
  SET_BIT(I2CX->CR1, I2C_CR1_POS); //I2CX->CR1|=I2C_CR1_POS;   //I2C_NACKPositionConfig(I2CX , I2C_NACKPosition_Next);

  /* Disable all active IRQs around ADDR clearing and STOP programming because the EV6_3
      software sequence must complete before the current byte end of transfer */
__disable_irq ();
// Clear ADDR flag
  _I2C_CLEAR_ADDRFLAG(I2CX);    //(void) I2CX->SR1;(void) I2CX->SR2; 
  /* Disable Acknowledge */
  CLEAR_BIT(I2CX->CR1,I2C_CR1_ACK); //I2CX->CR1&=~I2C_CR1_ACK;//I2C_AcknowledgeConfig(I2CX , DISABLE); // Clear Ack bit
__enable_irq ();

// EV7_3 -- Wait for BTF , program stop , read data twice
  error=i2c_wait_read_byte_btf_std(I2CX);
  if(error!=I2C_OK)
  return error;

__disable_irq ();
  /* Generate Stop */
  SET_BIT(I2CX->CR1,I2C_CR1_STOP); //I2C_GenerateSTOP(I2CX ,ENABLE);
  //*buf++ = I2CX->DR;  
  /* Read data from DR */
  *buf = I2CX->DR;
  /* Increment Buffer pointer */
  buf++;
 __enable_irq ();
 /* Read data from DR */
  *buf= I2CX->DR;

 return I2C_OK;
}
//-----------------------------------------------------------------------------------------------------------------------
 uint8_t i2c_read_last3byte_std(I2C_TypeDef* I2CX,uint8_t *buf)
 {
  uint8_t error=0;
  volatile uint32_t Timeout=0xfffff;
  // Clear ADDR flag
  // _I2C_CLEAR_ADDRFLAG(I2CX);//(void) I2CX ->SR1;(void) I2CX ->SR2; 
   error=i2c_wait_read_byte_btf_std(I2CX);
   if(error!=I2C_OK)
      return error;
// EV7_2 -- Figure 1 has an error , doesn 't read N-2 !
    /* Disable Acknowledge */
    CLEAR_BIT(I2CX->CR1,I2C_CR1_ACK);  //I2C_AcknowledgeConfig(I2CX , DISABLE); // clear ack bit

/*
__disable_irq ();
  *buf++=I2CX->DR; // receive byte N-2
 // Generate Stop 
  SET_BIT(I2CX->CR1,I2C_CR1_STOP); //I2C_GenerateSTOP(I2CX ,ENABLE); // program stop
__enable_irq ();

*buf++ = I2CX->DR;  // receive byte N-1
// wait for byte N
// Receive data EV7
error=i2c_wait_read_byte_rxne_std(I2CX);
  if(error)  // I2C_EVENT_MASTER_BYTE_RECEIVED:: BUSY, MSL and RXNE flags 
    return error;
 *buf++ = I2CX->DR;
 return I2C_OK; 
 */

/* Disable all active IRQs around ADDR clearing and STOP programming because the EV6_3
             software sequence must complete before the current byte end of transfer */
__disable_irq ();
  *buf=I2CX->DR; // receive byte N-2
   buf++;
   Timeout=I2C_MAX_WAIT_TIME *(SystemCoreClock / 25U / 1000U);
    while(bits_is_clear(I2CX->SR1,I2C_SR1_BTF))//bits_is_clear(I2CX->SR1,I2C_SR1_BTF)) //I2C_GetFlagStatus(I2CX,I2C_FLAG_BTF))
    if(Timeout--==0)  
    {
      __enable_irq();
      // set the error then exit ::I2C_RX_RXNE_ERROR
        return I2C_RX_BTF_ERROR;
    }
 // Generate Stop 
  SET_BIT(I2CX->CR1,I2C_CR1_STOP); 
  *buf=I2CX->DR; // receive byte N-1
   buf++;
  /* Re-enable IRQs */        
  __enable_irq();

  *buf=I2CX->DR; // receive byte N-1
   buf++;
   return I2C_OK;
}
//-----------------------------------------------------------------------------------------------------------------------
/**
 * @brief 
 * 
 * @param I2CX 
 * @param data 
 * @param ack 
 * @return uint8_t 
 */
uint8_t i2c_read_nbyte_std(I2C_TypeDef* I2CX,uint8_t *buf,uint16_t n)
{
    uint8_t error=0;    
    if(n==0) 
    {      
      /* Clear ADDR flag */
      _I2C_CLEAR_ADDRFLAG(I2CX);

      /* Generate Stop */
      SET_BIT(I2CX->CR1, I2C_CR1_STOP);
      return I2C_OK;
    }

    if(n==1) return i2c_read_lastbyte_std(I2CX,buf);
    if(n==2) return i2c_read_last2byte_std(I2CX,buf);
     
    // clear POS flag
     CLEAR_BIT(I2CX->CR1,I2C_CR1_POS); 
     /* Enable Acknowledge */
      SET_BIT(I2CX->CR1,I2C_CR1_ACK);
      /* Clear ADDR flag */
      _I2C_CLEAR_ADDRFLAG(I2CX);

    if(n>3)
    {
      for (uint16_t i = 0; i < n-3; i++) 
       {
            // EV7 -- cannot guarantee 1 transfer completion time ,
            // wait for BTF instead of RXNE
            error=i2c_wait_read_byte_rxne_std(I2CX);
            if(error!=I2C_OK)
                return error;
              buf[i] = I2CX->DR;
           if(bits_is_set(I2CX->SR1,I2C_SR1_BTF))//__HAL_I2C_GET_FLAG(hi2c, I2C_FLAG_BTF) == SET)
            {
              /* Read data from DR */
              i++;
              buf[i] = I2CX->DR;
            }

       }
    }
  
    return i2c_read_last3byte_std(I2CX,(uint8_t *) &buf[n-3]);
}
//-----------------------------------------------------------------------------------------------------------------------

//********************************************************************************************
//
//  extern i2c Methods defnitions using standard peripheral library
//
//********************************************************************************************
void i2c_init_std(I2C_TypeDef* I2CX, uint32_t clock_speed,uint16_t ownaddress)
{
    GPIO_InitTypeDef _gpio_init_struct;
    I2C_InitTypeDef _i2c_init_struct;
  
 /*1. Enable the Clock  the AFIO/GPIO Modules using RCC_APB2PeriphClockCmd*/
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO| RCC_APB2Periph_GPIOB,ENABLE);
    

 /* 1.,2. Enable the Clock  the I2Cx Modules  and its GPIO pins mode */
    if(I2CX==I2C1)  
    {
    /*Enable the Clock  the AFIO/GPIO Modules using RCC_APB2PeriphClockCmd*/
     RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C1,ENABLE);
    /* Configure the pins required by the Module (AFIO_OUT or INPUT, ANALOG...) & remap incase of requirement */
      GPIO_StructInit((GPIO_InitTypeDef*)& _gpio_init_struct);      
      // I2C1_SCL=PB6,I2C1_SDA=PB7
     _gpio_init_struct.GPIO_Pin=GPIO_Pin_6 | GPIO_Pin_7;
     _gpio_init_struct.GPIO_Speed=GPIO_Speed_50MHz;
     _gpio_init_struct.GPIO_Mode=GPIO_Mode_AF_OD;
      GPIO_Init(GPIOB,&_gpio_init_struct);

    /* I2C1 Hardware reset/set of the module */
     RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C1,ENABLE);
     RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C1,DISABLE);
    }
    else
    { //I2C2
            /*Enable the Clock  the AFIO/GPIO Modules using RCC_APB2PeriphClockCmd*/
     RCC_APB1PeriphClockCmd(RCC_APB1Periph_I2C2,ENABLE);
    /* Configure the pins required by the Module (AFIO_OUT or INPUT, ANALOG...) & remap incase of requirement */
      GPIO_StructInit((GPIO_InitTypeDef*)& _gpio_init_struct);      
      // I2C2_SCL=PB10,I2C2_SDA=PB11
     _gpio_init_struct.GPIO_Pin=GPIO_Pin_10 | GPIO_Pin_11;
     _gpio_init_struct.GPIO_Speed=GPIO_Speed_50MHz;
     _gpio_init_struct.GPIO_Mode=GPIO_Mode_AF_OD;
      GPIO_Init(GPIOB,&_gpio_init_struct);

    /* I2C2 Hardware reset/set of the module */
     RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C2,ENABLE);
     RCC_APB1PeriphResetCmd(RCC_APB1Periph_I2C2,DISABLE);
    }
  /* 3. Configure the peripheral hardware interrupt @ level of  NVIC  link to IRQ and set priority */
  /*   NVIC_InitTypeDef NVIC_InitStruct;
     NVIC_InitStruct.NVIC_IRQChannel=I2C1_EV_IRQn;
     NVIC_InitStruct.NVIC_IRQChannelPreemptionPriority=0;
     NVIC_InitStruct.NVIC_IRQChannelSubPriority=9;
     NVIC_InitStruct.NVIC_IRQChannelCmd=ENABLE;
     NVIC_Init((NVIC_InitTypeDef*) &NVIC_InitStruct);
  */
/* 4.  the peripheral hardware  of the I2C */
    I2C_StructInit((I2C_InitTypeDef *)& _i2c_init_struct);
    _i2c_init_struct.I2C_Mode=I2C_Mode_I2C ;
    _i2c_init_struct.I2C_DutyCycle=I2C_DutyCycle_2;
    _i2c_init_struct.I2C_Ack=I2C_Ack_Enable;
    _i2c_init_struct.I2C_AcknowledgedAddress=I2C_AcknowledgedAddress_7bit ;
    _i2c_init_struct. I2C_OwnAddress1=ownaddress;
    _i2c_init_struct.I2C_ClockSpeed=clock_speed;
    // reset the I2C Module
    I2CX->CR1|=I2C_CR1_SWRST;
    I2CX->CR1&=~I2C_CR1_SWRST;

    I2C_Init((I2C_TypeDef*)I2CX,(I2C_InitTypeDef *)& _i2c_init_struct);
    //I2CX->TRISE=37;
  /* 5. Configure the peripheral interrupt @ level of the peripheral or DMA */
    //I2C_ITConfig(I2C1, I2C_IT_EVT| I2C_IT_EVT,ENABLE);

  /* 6. Enable the peripheral Module */
    //I2C_Cmd((I2C_TypeDef*)I2CX,ENABLE);
    I2CX->CR1|=I2C_CR1_PE;

}
//-----------------------------------------------------------------------------------------------------------------------

//********************************************************************************************
// GROUP A
//  extern i2c Methods defnitions using standard peripheral library
// read and write directly without definition of a base register address in the slave
//
//********************************************************************************************

uint8_t i2c_write_7bit_byte_std(I2C_TypeDef* I2CX, uint8_t  slave_address,uint8_t data)
{
 // get the result of any sub operation where a non-zero value indicates an error condition
    uint8_t error=0; 

  //wait check that the I2c module is not busy
    if((error=i2c_ready_std(I2CX)))
        return error;

  // send the start condition 
    if((error=i2c_start_std(I2CX)))
        return error;

    //EV5: send the slave address with write operation master transmit 
    if((error=i2c_send_7bit_slave_address_wr_std(I2CX,slave_address)))
        return error;

    //Ev6: send the byte
    if((error=i2c_write_byte_std(I2CX,data)))
        return error;

    // generate the stop condition 
    if((error=i2c_stop_std(I2CX)))
        return error;

    return I2C_OK;
}
//-----------------------------------------------------------------------------------------------------------------------
uint8_t i2c_write_7bit_nbyte_std(I2C_TypeDef* I2CX, uint8_t  slave_address, uint8_t *buf, size_t n)
{
 // get the error of the any sub operation where a non-zero value indicate an error 
  uint8_t error=0; 

  //wait check that the I2c module is not busy
    if((error=i2c_ready_std(I2CX)))
        return error;
  // send the start condition 
    if((error=i2c_start_std(I2CX)))
        return error;

    //EV5: send the slave address with write operation master transmit 
    if((error=i2c_send_7bit_slave_address_wr_std(I2CX,slave_address)))
        return error;

    //Ev6: send the byte
    if((error=i2c_write_nbyte_std(I2CX,buf,n)))
        return error;

    // generate the stop condition 
    if((error=i2c_stop_std(I2CX)))
        return error;

    // all operation has succeeded no error to return 
    return 0;
}
//-----------------------------------------------------------------------------------------------------------------------
uint8_t i2c_read_7bit_byte_std(I2C_TypeDef* I2CX, uint8_t  slave_address, uint8_t *data)
{
  uint8_t error=0;

  if((error=i2c_read_7bit_nbyte_std(I2CX,slave_address, (uint8_t *)data, 1)))
   return error;

  return I2C_OK;
}
//-----------------------------------------------------------------------------------------------------------------------
uint8_t i2c_read_7bit_word_std(I2C_TypeDef* I2CX, uint8_t  slave_address, uint16_t *data)
{
  uint8_t error=0;
  WORD_BYTES t;
  t.word=0;
  if((error=i2c_read_7bit_nbyte_std(I2CX,slave_address, (uint8_t *)t.bytes, 2)))
   return error;
  *data=t.word;
  return I2C_OK;
}
//-----------------------------------------------------------------------------------------------------------------------
uint8_t i2c_read_7bit_nbyte_std(I2C_TypeDef* I2CX, uint8_t  slave_address, uint8_t *buf, size_t n)
{

  // get the error of the any sub operation where a non-zero value indicate an error 
  uint8_t error=0; 
 //wait check that the I2c module is not busy
    if((error=i2c_ready_std(I2CX)))
        return error;

  // send the repeat start condition 
    if((error=i2c_start_std(I2CX)))
        return error;
 // Enable Acknowledgment , clear POS flag
     I2C_AcknowledgeConfig(I2CX , ENABLE);
     I2C_NACKPositionConfig(I2CX , I2C_NACKPosition_Current);

//EV5: send the slave address with a read operation master transmit 
    if((error=i2c_send_7bit_slave_address_rd_std(I2CX,slave_address)))
        return error;
//EV7:     
   if((error=i2c_read_nbyte_std(I2CX,buf,n)))
    return error;

// generate the stop condition : note stop generation is done implicitly by the  
   if((error=i2c_wait_stop_event_std(I2CX)))
      return error;

    // all operation has succeeded no error to return 
    return I2C_OK;
}
//-----------------------------------------------------------------------------------------------------------------------


//********************************************************************************************
// GROUP B
//  extern i2c Methods defnitions using standard peripheral library
// read and write directly without definition of a base register address in the slave
//
//********************************************************************************************
uint8_t i2c_write_7bit_base_byte_std(I2C_TypeDef* I2CX, uint8_t  slave_address,uint8_t base_address,uint8_t data)
{

 // get the result of any sub operation where a non-zero value indicates an error condition
    uint8_t error=0; 
  //uart_print(USART1,"\nTX_BuSY ...\r\n");
  //wait check that the I2c module is not busy
    if((error=i2c_ready_std(I2CX)))
        return error;
    
  //uart_print(USART1,"TX_SB ...\r\n");
  // send the start condition 
    if((error=i2c_start_std(I2CX))) 
        return error;

   //uart_print(USART1,"TX_SLAVE_ADDR ...\r\n");
    //EV5: send the slave address with write operation master transmit 
    if((error=i2c_send_7bit_slave_address_wr_std(I2CX,slave_address)))
        return error;
//      (void) I2CX ->SR1;
//      (void) I2CX ->SR2; // Clear ADDR flag

   //uart_print(USART1,"TX_BASE_ADDR ...\r\n");
    //Ev6: send the byte :: the base address in the slave Memory/register map to start writing to 
    i2c_write_byte_std(I2CX,base_address);
    //if((error=i2c_write_byte_std(I2CX,base_address)))
    //    return error;

      //cbits(I2CX->SR1,I2C_SR1_AF);

   //uart_print(USART1,"TX_REG_DATA ...\r\n");
    //Ev6: send the byte
    i2c_write_byte_std(I2CX,data);
    //if((error=i2c_write_byte_std(I2CX,data))) 
    //    return error;
     // cbits(I2CX->SR1,I2C_SR1_AF);

   //uart_print(USART1,"TX_STOP ...\r\n");
    // generate the stop condition 
    i2c_stop_std(I2CX);
    if((error=i2c_stop_std(I2CX)))
        return error;

    return I2C_OK;
}
//-----------------------------------------------------------------------------------------------------------------------
uint8_t i2c_write_7bit_base_nbyte_std(I2C_TypeDef* I2CX, uint8_t  slave_address,uint8_t base_address, uint8_t *buf, size_t n)
{
 // get the error of the any sub operation where a non-zero value indicate an error 
  uint8_t error=0; 

  //wait check that the I2c module is not busy
    if((error=i2c_ready_std(I2CX))) 
        return error;
  // send the start condition 
    if((error=i2c_start_std(I2CX)))
        return error;

    //EV5: send the slave address with write operation master transmit 
    if((error=i2c_send_7bit_slave_address_wr_std(I2CX,slave_address)))
        return error;

    //Ev6: send the byte :: the base address in the slave Memory/register map to start writing to 
    if((error=i2c_write_byte_std(I2CX,base_address))) 
        return error;

    //Ev6: send the byte
    if((error=i2c_write_nbyte_std(I2CX,buf,n))) 
        return error;

    // generate the stop condition 
    if((error=i2c_stop_std(I2CX))) 
        return error;

    // all operation has succeeded no error to return 
    return 0;

}
//-----------------------------------------------------------------------------------------------------------------------
uint8_t i2c_read_7bit_base_byte_std(I2C_TypeDef* I2CX, uint8_t  slave_address,uint8_t base_address, uint8_t *data)
{
   
  uint8_t error=0;
   error=i2c_read_7bit_base_nbyte_std(I2CX,slave_address,base_address,(uint8_t *)data, 1);
   //uart_print(USART1,"RX DATA:");
   //uart_print_integer(USART1,*data,16);
   //uart_print(USART1,"\r\n");
  if(error!=I2C_OK)
   return error;
  return I2C_OK;
  
  /*
  // get the error of the any sub operation where a non-zero value indicate an error 
  uint8_t error=0; 
 //wait check that the I2c module is not busy
    uart_print(USART1,"\nRX_BuSY ...\r\n");
    error=i2c_ready_std(I2CX);
    if(error)//(error=i2c_ready_std(I2CX))) 
      return error;
 
  // send the start condition 
//    uart_print(USART1,"start condition:");
    uart_print(USART1,"RX_SB ...\r\n");
    error=i2c_start_std(I2CX);
    if(error)//(error=i2c_start_std(I2CX)))
        return error;

    uart_print(USART1,"RX_SLAVE_ADDR ...\r\n");
    //EV5: send the slave address with write operation master transmit 
    error=i2c_send_7bit_slave_address_wr_std(I2CX,slave_address);
    if(error)//(error=i2c_send_7bit_slave_address_wr_std(I2CX,slave_address)))
        return error;

//    uart_print(USART1,"REG:");
    uart_print(USART1,"RX_REG_DATA ...\r\n");
    //Ev6: send the base byte
    error=i2c_write_byte_std(I2CX,base_address);
    if(error)//(error=i2c_write_byte_std(I2CX,base_address))) 
      return error;

  // send the repeat start condition 
    uart_print(USART1,"repeat start....\r\n");
    error=i2c_start_std(I2CX);
    if(error)//(error=i2c_start_std(I2CX)))
        return error;

 // Enable Acknowledgment , clear POS flag
    I2C_AcknowledgeConfig(I2CX , ENABLE);
    I2C_NACKPositionConfig(I2CX , I2C_NACKPosition_Current);

 //EV5: send the slave address with read operation master transmit 
    uart_print(USART1,"RX_ Slave RD: \r\n");
    error=i2c_send_7bit_slave_address_rd_std(I2CX,slave_address);
    if(error)//(error=i2c_send_7bit_slave_address_rd_std(I2CX,slave_address)))
      return error;
     (void)I2CX->SR1;
     (void)I2CX->SR2;

    uart_print(USART1,"RX_DATA:");
    error=i2c_read_lastbyte_std(I2CX,data);
    uart_print_integer(USART1,*data,16);
    uart_print(USART1,"\r\n");

   if(error)//(error=i2c_read_lastbyte_std(I2CX,data)))
    return error;    

  // generate the stop condition : note stop generation is done implicitly by the  
    uart_print(USART1,"RX_STOP :\r\n");
    error=i2c_stop_std(I2CX);
    if(error)//(error=i2c_stop_std(I2CX)))// if((error=i2c_wait_stop_event_std(I2CX)))
      return error;

  // all operation has succeeded no error to return 
    return I2C_OK;
    */
}
//-----------------------------------------------------------------------------------------------------------------------
uint8_t i2c_read_7bit_base_word_std(I2C_TypeDef* I2CX, uint8_t  slave_address,uint8_t base_address, uint16_t * data)
{
  uint8_t error=0;
  WORD_BYTES t;
   t.word=0;
  if((error=i2c_read_7bit_base_nbyte_std(I2CX,slave_address,base_address,(uint8_t *)t.bytes, 2)))
    return error;
   *data=t.word;
  return I2C_OK;
  /*
  // get the error of the any sub operation where a non-zero value indicate an error 
  uint8_t error=0; 
  uint8_t buf[2]; 
  
 //wait check that the I2c module is not busy
    if((error=i2c_ready_std(I2CX))) 
        return error;

  // send the start condition  (wait for EV5) as the end of start condition
    if((error=i2c_start_std(I2CX))) 
        return error;

    //EV5: send the slave address with write operation master transmit 
    if((error=i2c_send_7bit_slave_address_wr_std(I2CX,slave_address)))
        return error;

    //Ev6: send the base byte
    if((error=i2c_write_byte_std(I2CX,base_address))) 
        return error;

  // send the repeat start condition 
    if((error=i2c_start_std(I2CX))) 
        return error;
 // Enable Acknowledgment , clear POS flag
     I2C_AcknowledgeConfig(I2CX , ENABLE);
     I2C_NACKPositionConfig(I2CX, I2C_NACKPosition_Current);

//EV5: send the slave address with read operation master transmit 
    if((error=i2c_send_7bit_slave_address_rd_std(I2CX,slave_address)))
        return error;
     
   if((error=i2c_read_last2byte_std(I2CX,buf)))
    return error;
    *data=(uint16_t)(buf[1]<<8 | buf[0]); 
    // generate the stop condition : note stop generation is done implicitly by the  
    if((error=i2c_wait_stop_event_std(I2CX)))
        return error;

    // all operation has succeeded no error to return 
    return I2C_OK;
    */
}
//-----------------------------------------------------------------------------------------------------------------------
uint8_t i2c_read_7bit_base_nbyte_std(I2C_TypeDef* I2CX, uint8_t  slave_address,uint8_t base_address, uint8_t *buf, size_t n)
{
  // get the error of the any sub operation where a non-zero value indicate an error 
  uint8_t error=0; 

 //wait check that the I2c module is not busy
  //wait check that the I2c module is not busy
    //uart_print(USART1,"\nRX_BuSY ...\r\n");
    if((error=i2c_ready_std(I2CX))) 
        return error;
    
   /* Enable I2C peripheral */
     //SET_BIT(I2CX->CR1, I2C_CR1_PE);               // done
   /* Disable Pos */
     //CLEAR_BIT(I2CX->CR1, I2C_CR1_POS);            // done
   /* Enable Acknowledge */
     //SET_BIT(I2CX->CR1, I2C_CR1_ACK);    // done
    /* Generate Start */
     //SET_BIT(I2CX->CR1, I2C_CR1_START);  // done


  // send the start condition 
    //uart_print(USART1,"RX_SB ...\r\n");
    error=i2c_start_std(I2CX);
    if(error) 
        return error;

    //EV5: send the slave address with write operation master transmit 
    //uart_print(USART1,"RX_SLAVE_ADDR_WR ...\r\n");
    error=i2c_send_7bit_slave_address_wr_std(I2CX,slave_address);
    if(error)
        return error;

    //Ev6: send the base byte
    //uart_print(USART1,"RX_REG_DATA ...\r\n");
    error=i2c_write_byte_std(I2CX,base_address);
    if(error)
        return error;
        
  // send the repeat start condition 
    //uart_print(USART1,"repeat start....\r\n");
    error=i2c_start_std(I2CX);
    if(error) 
        return error;
 // Enable Acknowledgment , clear POS flag
     //I2C_AcknowledgeConfig(I2CX , ENABLE);
     //I2C_NACKPositionConfig(I2CX , I2C_NACKPosition_Current);

//EV5: send the slave address with a read operation master transmit 
    //uart_print(USART1,"RX_ SLAVE_ADDR_RD... \r\n");
    error=i2c_send_7bit_slave_address_rd_std(I2CX,slave_address);
    if(error)
      return error;
//EV7:     
    //uart_print(USART1,"DATA RD .... \r\n");
    error=i2c_read_nbyte_std(I2CX,buf,n);
   if(error)
    return error;

// generate the stop condition : note stop generation is done implicitly by the  
    //uart_print(USART1,"Stop Condition: \r\n");
   if((error=i2c_wait_stop_event_std(I2CX)))
    return error;

    // all operation has succeeded no error to return 
    return I2C_OK;
}
//-----------------------------------------------------------------------------------------------------------------------