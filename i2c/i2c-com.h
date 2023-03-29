/**
 * @brief i2c.h
 *
 * @param student: Sameer Almaldein
 * @param ID: 679699
 * @param University TU-Chemnitz
 * @param Master : ASE(Automotive Software Engineering )
 */ 
#ifndef _I2C_COM_H
#define _I2C_COM_H

//********************************************************************************************
//
// including header  files
//
//********************************************************************************************

/******************************************************************************/
/*                                                                            */
/*                      Inter-integrated Circuit Interface                    */
/*                                                                            */
/******************************************************************************/
//********************************************************************************************
//
// constants
//
//********************************************************************************************

/* --- I2Cx_OAR1 values ---------------------------------------------------- */
#define I2C_OAR1_ADDMODE_7BIT           0
#define I2C_OAR1_ADDMODE_10BIT          1

/* --- I2Cx_CCR values ----------------------------------------------------- */

#define I2C_CCR_MASTER_STANDARD_MODE    0                      
#define I2C_CCR_MASTER_Fast_MODE        1                      

#define I2C_CCR_DUTY_DIV2               0
#define I2C_CCR_DUTY_16_DIV_9           1

/* --- i2c_rw I2C Read/Write bit ----------------------------------------------------- */
#define I2C_WRITE                       0
#define I2C_READ                        1

/** 
 * @defgroup i2c_rw I2C Read/Write bit
@{*/
  #define I2C_WRITE                       0
  #define I2C_READ                        1  
/* @} 
*/

//********************************************************************************************
//
// enum
//
//********************************************************************************************
enum i2c_cr2_freq_values  {
        I2C_CR2_FREQ_2MHZ __attribute__ ((deprecated("Replace with 2 directly"))) = 2,
        I2C_CR2_FREQ_3MHZ __attribute__ ((deprecated("Replace with 3 directly"))),
        I2C_CR2_FREQ_4MHZ __attribute__ ((deprecated("Replace with 4 directly"))),
        I2C_CR2_FREQ_5MHZ __attribute__ ((deprecated("Replace with 5 directly"))),
        I2C_CR2_FREQ_6MHZ __attribute__ ((deprecated("Replace with 6 directly"))),
        I2C_CR2_FREQ_7MHZ __attribute__ ((deprecated("Replace with 7 directly"))),
        I2C_CR2_FREQ_8MHZ __attribute__ ((deprecated("Replace with 8 directly"))),
        I2C_CR2_FREQ_9MHZ __attribute__ ((deprecated("Replace with 9 directly"))),
        I2C_CR2_FREQ_10MHZ __attribute__ ((deprecated("Replace with 10 directly"))),
        I2C_CR2_FREQ_11MHZ __attribute__ ((deprecated("Replace with 11 directly"))),
        I2C_CR2_FREQ_12MHZ __attribute__ ((deprecated("Replace with 12 directly"))),
        I2C_CR2_FREQ_13MHZ __attribute__ ((deprecated("Replace with 13 directly"))),
        I2C_CR2_FREQ_14MHZ __attribute__ ((deprecated("Replace with 14 directly"))),
        I2C_CR2_FREQ_15MHZ __attribute__ ((deprecated("Replace with 15 directly"))),
        I2C_CR2_FREQ_16MHZ __attribute__ ((deprecated("Replace with 16 directly"))),
        I2C_CR2_FREQ_17MHZ __attribute__ ((deprecated("Replace with 17 directly"))),
        I2C_CR2_FREQ_18MHZ __attribute__ ((deprecated("Replace with 18 directly"))),
        I2C_CR2_FREQ_19MHZ __attribute__ ((deprecated("Replace with 19 directly"))),
        I2C_CR2_FREQ_20MHZ __attribute__ ((deprecated("Replace with 20 directly"))),
        I2C_CR2_FREQ_21MHZ __attribute__ ((deprecated("Replace with 21 directly"))),
        I2C_CR2_FREQ_22MHZ __attribute__ ((deprecated("Replace with 22 directly"))),
        I2C_CR2_FREQ_23MHZ __attribute__ ((deprecated("Replace with 23 directly"))),
        I2C_CR2_FREQ_24MHZ __attribute__ ((deprecated("Replace with 24 directly"))),
        I2C_CR2_FREQ_25MHZ __attribute__ ((deprecated("Replace with 25 directly"))),
        I2C_CR2_FREQ_26MHZ __attribute__ ((deprecated("Replace with 26 directly"))),
        I2C_CR2_FREQ_27MHZ __attribute__ ((deprecated("Replace with 27 directly"))),
        I2C_CR2_FREQ_28MHZ __attribute__ ((deprecated("Replace with 28 directly"))),
        I2C_CR2_FREQ_29MHZ __attribute__ ((deprecated("Replace with 29 directly"))),
        I2C_CR2_FREQ_30MHZ __attribute__ ((deprecated("Replace with 30 directly"))),
        I2C_CR2_FREQ_31MHZ __attribute__ ((deprecated("Replace with 31 directly"))),
        I2C_CR2_FREQ_32MHZ __attribute__ ((deprecated("Replace with 32 directly"))),
        I2C_CR2_FREQ_33MHZ __attribute__ ((deprecated("Replace with 33 directly"))),
        I2C_CR2_FREQ_34MHZ __attribute__ ((deprecated("Replace with 34 directly"))),
        I2C_CR2_FREQ_35MHZ __attribute__ ((deprecated("Replace with 35 directly"))),
        I2C_CR2_FREQ_36MHZ __attribute__ ((deprecated("Replace with 36 directly"))),
        I2C_CR2_FREQ_37MHZ __attribute__ ((deprecated("Replace with 37 directly"))),
        I2C_CR2_FREQ_38MHZ __attribute__ ((deprecated("Replace with 38 directly"))),
        I2C_CR2_FREQ_39MHZ __attribute__ ((deprecated("Replace with 39 directly"))),
        I2C_CR2_FREQ_40MHZ __attribute__ ((deprecated("Replace with 40 directly"))),
        I2C_CR2_FREQ_41MHZ __attribute__ ((deprecated("Replace with 41 directly"))),
        I2C_CR2_FREQ_42MHZ __attribute__ ((deprecated("Replace with 42 directly"))),
} __attribute__ ((deprecated("Replace _nMHZ with n directly")));
 
/**
 * I2C speed modes.
 */
enum i2c_speeds {
        i2c_speed_sm_100k,
        i2c_speed_fm_400k,
        i2c_speed_fmp_1m,
        i2c_speed_unknown
};

/*******************  Bit definition for I2C_CR1 register  ********************/
/**
 * @brief data structure Bit definition for I2C_CR1 register
 * 
 * @details this structure allows access at bit or byte level for the 
 *          I2C Control register 2
 * @param  val          16-bit value that represent the half word I2C_CR1 register
 * @param   PE        1-bit Peripheral Enable {0:Disable,1:Enable}
 * @param SMBUS       1-bit SMBus Mode {0: I2C mode, 1:SMBus:mode}
 * @param res1        1-bit reserved not used bit
 * @param SMBTYPE     1-bit SMBus Type {0:SMBus Device,1: SMBus Host} 
 * @param SMBTYPE     1-bit SMBus Type {0:SMBus Device,1: SMBus Host} 
 * @param ENARP       1-bit ARP Enable
 * @param ENPEC       1-bit PEC Enable
 * @param ENGC        1-bit General Call Enable
 * @param NOSTRETCH   1-bit Clock Stretching Disable (Slave mode)
 * @param START       1-bit Start Generation
 * @param STOP        1-bit Stop Generation
 * @param ACK         1-bit Acknowledge Enable
 * @param POS         1-bit Acknowledge/PEC Position (for data reception)
 * @param PEC         1-bit Packet Error Checking
 * @param ALERT       1-bit SMBus Alert {0: release SMBA to High( alert response address header followed by NACK ,1: drive SMBA low}
 * @param res2        1-bit reserved not used bit
 * @param SWRST       1-bit Software Reset{0:I2C not under reset,1:I2C under reset state }
 */
typedef union _I2C_CR1_t
{
    uint16_t val;
    struct
    {
        uint8_t PE          :1 ; //! Peripheral Enable {0:Disable,1:Enable}
        uint8_t SMBUS       :1 ; //! SMBus Mode {0: I2C mode, 1:SMBUS:mode}
        uint8_t res1        :1 ; //! reserved not used bit
        uint8_t SMBTYPE     :1 ; //! SMBus Type {0:SMBus Device,1: SMBus Host} 
        uint8_t ENARP       :1 ; //! ARP Enable
        uint8_t ENPEC       :1 ; //! PEC Enable
        uint8_t ENGC        :1 ; //! General Call Enable
        uint8_t NOSTRETCH   :1 ; //! Clock Stretching Disable (Slave mode)
        uint8_t START       :1 ; //! Start Generation
        uint8_t STOP        :1 ; //! Stop Generation
        uint8_t ACK         :1 ; //! Acknowledge Enable
        uint8_t POS         :1 ; //! Acknowledge/PEC Position (for data reception)
        uint8_t PEC         :1 ; //! Packet Error Checking
        uint8_t ALERT       :1 ; //! SMBus Alert {0: release SMBA to High( alert response address header followed by NACK ,1: drive SMBA low}
        uint8_t res2        :1 ; //! reserved not used bit
        uint8_t SWRST       :1 ; //! Software Reset{0:I2C not under reset,1:I2C under reset state }
    };    
}I2C_CR1_t;

/*******************  Bit definition for I2C_CR2 register  ********************/

/**
 * @brief data structure Bit definition for I2C_CR2 register
 * 
 * @details this structure allows access at bit or byte level for the 
 *          I2C Control register 2
 * @param  val        16-bit value that represent the half word I2C_CR1 register
  * @param  FREQ      6-bit FREQ[5:0] bits (Peripheral Clock Frequency)
  * @param  res1      2-bit reserved not used bit
  * @param  ITERREN   1-bit Error Interrupt Enable 
  * @param  ITEVTEN   1-bit Event Interrupt Enable
  * @param  ITBUFEN   1-bit Buffer Interrupt Enable
  * @param  DMAEN     1-bit DMA Requests Enable
  * @param  LAST      1-bit DMA Last Transfer
  * @param  res2      3-bit reserved not used bit

 */
typedef union _I2C_CR2_t
{
    uint16_t val;
    struct
    {
        uint8_t FREQ      :6 ; //! FREQ[5:0] bits (Peripheral Clock Frequency)
        uint8_t res1      :2 ; //! reserved not used bit
        uint8_t ITERREN   :1 ; //! Error Interrupt Enable 
        uint8_t ITEVTEN   :1 ; //! Event Interrupt Enable
        uint8_t ITBUFEN   :1 ; //! Buffer Interrupt Enable
        uint8_t DMAEN     :1 ; //! DMA Requests Enable
        uint8_t LAST      :1 ; //! DMA Last Transfer
        uint8_t res2      :3 ; //! reserved not used bit
    };    
}I2C_CR2_t;

/*******************  Bit definition for I2C_OAR1 register  *******************/

/**
 * @brief data structure Bit definition for I2C_OAR1 register
 * 
 * @details this structure allows access at bit or byte level for the 
 *          I2C own address register 1
 * @param  val        16-bit value that represent the half word I2C_CR1 register
 * @param  ADD0      1-bit Bit 0 of  10 bit Interface Address
 * @param  ADD1_7    7-bit Bit[1..7] 7-bit Interface Address/10 bit Interface Address
 * @param  ADD8_9    2-bit Bit[8..9] 10-bit Interface Address 
   @param  b10_13    4-bit reserved not used bits should always be kept at reset
   @param  b14       1-bit reserved not used bits should always be kept at 1 by software 
 * @param  ADDMODE   1-bit Addressing Mode (Slave mode)
 */
typedef union _I2C_OAR1_t
{
    uint16_t val;
  /*   struct
    {
        uint16_t ADD0_9   :10 ; //! Bit 0 of  10 bit Interface Address
        uint8_t           :6 ; //! reserved Bit[10..13] should always be kept zero, Bit[14] should always be kept one by software
       
    };    
        struct
    {
        uint8_t ADD0_7   :8 ; //! Bit 0 of  10 bit Interface Address
        uint8_t          :8 ; //! reserved Bit[10..13] should always be kept zero, Bit[14] should always be kept one by software
    };    
    struct
    {
        uint8_t ADD0      :1 ; //! Bit 0 of  10 bit Interface Address
        uint8_t ADD1_7    :7 ; //! Bit[1..7] 7-bit Interface Address/10 bit Interface Address
        uint8_t ADD8_9    :2 ; //! Bit[8..9] 10-bit Interface Address 
        uint8_t           :5 ; //! reserved Bit[10..13] should always be kept zero, Bit[14] should always be kept one by software
        uint8_t ADDMODE   :1 ; //! Addressing Mode (Slave mode)
    };    */
    struct
    {
        uint8_t AD0      :1 ; //! Bit 0 of Interface Address
        uint8_t AD1      :1 ; //! Bit 1 of Interface Address
        uint8_t AD2      :1 ; //! Bit 2 of Interface Address
        uint8_t AD3      :1 ; //! Bit 3 of Interface Address
        uint8_t AD4      :1 ; //! Bit 4 of Interface Address
        uint8_t AD5      :1 ; //! Bit 5 of Interface Address
        uint8_t AD6      :1 ; //! Bit 6 of Interface Address
        uint8_t AD7      :1 ; //! Bit 7 of Interface Address
        uint8_t AD8      :1 ; //! Bit 8 of Interface Address
        uint8_t AD9      :1 ; //! Bit 9 of Interface Address
        uint8_t b10_13   :4 ; //! reserved not used bits should always be kept at reset
        uint8_t b14      :1 ; //! reserved not used bits should always be kept at 1 by software 
        uint8_t AD_MODE  :1 ; //! Addressing Mode (Slave mode)
    };
}I2C_OAR1_t;

/*******************  Bit definition for I2C_OAR2 register  *******************/

/**
 * @brief data structure Bit definition for I2C_OAR2 register
 * 
 * @details this structure allows access at bit or byte level for the 
 *          I2C own address register 2
 * @param  val      16-bit value that represent the half word I2C_CR1 register
 * @param ENDUAL    1-bit Dual addressing mode enable {0: only recognize OAR1 in 7bit addressing mode,1:both OAR1 & OAR2 recogniingzed in 7bit addressing mode }
 * @param ADD2      7-bit Bit[1..7] 7-bit Interface Address only
 * @param res       8-bit reserved not used bits
 */
typedef union _I2C_OAR2_t  {
    uint16_t val;
    struct
    {
        uint8_t ENDUAL    :1 ; //! Dual addressing mode enable {0: only recognize OAR1 in 7bit addressing mode,1:both OAR1 & OAR2 recogniingzed in 7bit addressing mode }
        uint8_t ADD2      :7 ; //! Bit[1..7] 7-bit Interface Address only
        uint8_t res       :8 ; //! reserved not used bits
    };    

}I2C_OAR2_t;

/********************  Bit definition for I2C_DR register  ********************/
/**
 * @brief data structure Bit definition for I2C_DR register
 * 
 * @details this structure allows access at bit or byte level for the 
*          I2C data register 
 * @param  val      16-bit value that represent the half word I2C_CR1 register
 * @param ENDUAL    1-bit Dual addressing mode enable {0: only recognize OAR1 in 7bit addressing mode,1:both OAR1 & OAR2 recogniingzed in 7bit addressing mode }
 * @param ADD2      7-bit Bit[1..7] 7-bit Interface Address only
 * @param res       8-bit reserved not used bits
 */
typedef union _I2C_DR_t  {
    uint16_t val;
    struct
    {
        uint8_t byte     :8 ; //! 8-bit Data Register
        uint8_t reserved :8 ; //! reserved not used bits
    };    
    struct
    {
        uint8_t D0      :1 ; //! Bit 0 of 8-bit Data Register
        uint8_t D1      :1 ; //! Bit 1 of 8-bit Data Register
        uint8_t D2      :1 ; //! Bit 2 of 8-bit Data Register
        uint8_t D3      :1 ; //! Bit 3 of 8-bit Data Register
        uint8_t D4      :1 ; //! Bit 4 of 8-bit Data Register
        uint8_t D5      :1 ; //! Bit 5 of 8-bit Data Register
        uint8_t D6      :1 ; //! Bit 6 of 8-bit Data Register
        uint8_t D7      :1 ; //! Bit 7 of 8-bit Data Register
        uint8_t res     :8 ; //! reserved not used bits
    };    
}I2C_DR_t;

/*******************  Bit definition for I2C_SR1 register  ********************/

/**
 * @brief data structure Bit definition for I2C_SR1 register
 * 
 * @details this structure allows access at bit or byte level for the 
 *          I2C status register 1
 * @param  val        16-bit value that represent the half word I2C_CR1 register
 * @param SB       1-bit Start Bit (Master mode) 
 * @param ADDR     1-bit Address sent (master mode)/matched (slave mode) 
 * @param BTF      1-bit Byte Transfer Finished 
 * @param ADD10    1-bit 10-bit header sent (Master mode) 
 * @param STOPF    1-bit Stop detection (Slave mode) 
 * @param res1     1-bit Reserved not used bits 
 * @param RXNE     1-bit Data Register not Emp (receivers) 
 * @param TXE      1-bit Data Register Empty (transmitters
 * @param BERR     1-bit Bus Error 
 * @param ARLO     1-bit Arbitration Lost (master mode) 
 * @param AF       1-bit Acknowledge Failure 
 * @param OVR      1-bit Overrun/Underrun 
 * @param PECERR   1-bit PEC Error in reption 
 * @param res2     1-bit Reserved not used bit
 * @param TIMEOUT  1-bit Timeout or Tlow Erro
 * @param SMBALERT 1-bit SMBus Alert 
 */
typedef union _I2C_SR1_t
{
    uint16_t val;
    struct
    {
        uint8_t SB       :1;  /*!< Start Bit (Master mode) */
        uint8_t ADDR     :1;  /*!< Address sent (master mode)/matched (slave mode) */
        uint8_t BTF      :1;  /*!< Byte Transfer Finished */
        uint8_t ADD10    :1;  /*!< 10-bit header sent (Master mode) */
        uint8_t STOPF    :1;  /*!< Stop detection (Slave mode) */
        uint8_t res1     :1;  /*!< Reserved not used bits */
        uint8_t RXNE     :1;  /*!< Data Register not Empty (receivers) */
        uint8_t TXE      :1;  /*!< Data Register Empty (transmitters) */
        uint8_t BERR     :1;  /*!< Bus Error */
        uint8_t ARLO     :1;  /*!< Arbitration Lost (master mode) */
        uint8_t AF       :1;  /*!< Acknowledge Failure */
        uint8_t OVR      :1;  /*!< Overrun/Underrun */
        uint8_t PECERR   :1;  /*!< PEC Error in reception */
        uint8_t res2     :1;  /*!< Reserved not used bits */
        uint8_t TIMEOUT  :1;  /*!< Timeout or Tlow Error */
        uint8_t SMBALERT :1;  /*!< SMBus Alert */        
    };
}I2C_SR1_t;

/*******************  Bit definition for I2C_SR2 register  ********************/

/**
 * @brief data structure Bit definition for I2C_SR2 register
 * 
 * @details this structure allows access at bit or byte level for the 
 *          I2C status register 2
 * @param  val     16-bit value that represent the half word I2C_CR1 register
 * @param SB       1-bit Start Bit (Master mode) 
 * @param ADDR     1-bit Address sent (master mode)/matched (slave mode) 
 * @param BTF      1-bit Byte Transfer Finished 
 * @param ADD10    1-bit 10-bit header sent (Master mode) 
 * @param STOPF    1-bit Stop detection (Slave mode) 
 * @param res1     1-bit Reserved not used bits 
 * @param RXNE     1-bit Data Register not Emp (receivers) 
 * @param TXE      1-bit Data Register Empty (transmitters
 * @param BERR     1-bit Bus Error 
 * @param ARLO     1-bit Arbitration Lost (master mode) 
 * @param AF       1-bit Acknowledge Failure 
 * @param OVR      1-bit Overrun/Underrun 
 * @param PECERR   1-bit PEC Error in reption 
 * @param res2     1-bit Reserved not used bit
 * @param TIMEOUT  1-bit Timeout or Tlow Erro
 * @param SMBALERT 1-bit SMBus Alert 
 */
typedef union _I2C_SR2_t
{
    uint16_t val;
    struct
    {
        uint8_t  MSL        :1 ; /*!< Master/Slave */
        uint8_t  BUSY       :1 ; /*!< Bus Busy */
        uint8_t  TRA        :1 ; /*!< Transmitter/Receiver */
        uint8_t  res        :1 ; /*!< Reserved not used bits */
        uint8_t  GENCALL    :1 ; /*!< General Call Address (Slave mode) */
        uint8_t  SMBDEFAULT :1 ; /*!< SMBus Device Default Address (Slave mode) */
        uint8_t  SMBHOST    :1 ; /*!< SMBus Host Header (Slave mode) */
        uint8_t  DUALF      :1 ; /*!< Dual Flag (Slave mode) */
        uint8_t  PEC        :8 ; /*!< Packet Error Checking Register */
    };
}I2C_SR2_t;

/*******************  Bit definition for I2C_CCR register  ********************/

/**
 * @brief data structure Bit definition for I2C_CCR register
 * 
 * @details this structure allows access at bit or byte level for the 
 *          I2C clock control register 
 * @param val  16-bit value that represent the half word I2C_CR1 register
 * @param CCR  12-bit Clock Control Register in Fast/Standard mode (Master mode) 
 * @param res  1 -bit Reserved not used bits 
 * @param DUTY 1 -bit Fast Mode Duty Cycle 
 * @param FS   1 -bit I2C Master Mode Selection 
 */
typedef union _I2C_CCR_t
{
    uint16_t val;
    struct
    {
    uint16_t CCR : 12 ; /*!< Clock Control Register in Fast/Standard mode (Master mode) */
    uint8_t res  : 2  ; /*!< Reserved not used bits */
    uint8_t DUTY : 1  ; /*!< Fast Mode Duty Cycle */
    uint8_t FS   : 1  ; /*!< I2C Master Mode Selection */
    };
}I2C_CCR_t;

/******************  Bit definition for I2C_TRISE register  *******************/

/**
 * @brief data structure Bit definition for I2C_TRISE register
 * 
 * @details this structure allows access at bit or byte level for the 
 *          I2C TRISE register 
 * @param val   16-bit value that represent the half word I2C_CR1 register
 * @param TRISE 6-bit Maximum Rise Time in Fast/Standard mode (Master mode) 
 * @param res   10-bit Reserved not used bits 
 */
typedef union _I2C_TRISE_t
{
    uint16_t val;
    struct
    {
     uint8_t TRISE    : 6  ; /*!< Maximum Rise Time in Fast/Standard mode (Master mode) */
     uint16_t reserve : 10 ; /*!< Reserved not used bits */
    };
}I2C_TRISE_t;

/** 
  * @brief Inter Integrated Circuit Interface
  */

typedef struct _I2C_TypeDef_t
{
  __IO I2C_CR1_t CR1;
  uint16_t  RESERVED0;

  __IO I2C_CR2_t CR2;
  uint16_t  RESERVED1;

  __IO I2C_OAR1_t OAR1;
  uint16_t  RESERVED2;

  __IO I2C_OAR2_t OAR2;
  uint16_t  RESERVED3;

  __IO I2C_DR_t DR;
  uint16_t  RESERVED4;

  __IO I2C_SR1_t SR1;
  uint16_t  RESERVED5;

  __IO I2C_SR2_t SR2;
  uint16_t  RESERVED6;

  __IO I2C_CCR_t CCR;
  uint16_t  RESERVED7;

  __IO I2C_TRISE_t TRISE;
  uint16_t  RESERVED8;

} I2C_TypeDef_t;
//********************************************************************************************
//
// global variables
//
//********************************************************************************************


//********************************************************************************************
//
// Method protoypes
//
//********************************************************************************************

extern void i2c_peripheral_enable(I2C_TypeDef_t * i2c);
extern void i2c_peripheral_disable(I2C_TypeDef_t * i2c);

// master mode methods : Transmitter
extern void i2c_send_start(I2C_TypeDef_t * i2c);
extern void i2c_send_stop(I2C_TypeDef_t * i2c);
extern void i2c_clear_stop(I2C_TypeDef_t* i2c);

extern void i2c_send_7bit_address(I2C_TypeDef_t* i2c, uint8_t slave, uint8_t readwrite);
extern void i2c_send_data(I2C_TypeDef_t* i2c, uint8_t data);
extern uint8_t i2c_get_data(I2C_TypeDef_t * i2c);

// slave mode methods
extern void i2c_set_own_7bit_slave_address(I2C_TypeDef_t * i2c, uint8_t slave);
extern void i2c_set_own_10bit_slave_address(I2C_TypeDef_t * i2c, uint16_t slave);
extern void i2c_set_own_7bit_slave_address_two(I2C_TypeDef_t * i2c, uint8_t slave);
extern void i2c_enable_dual_addressing_mode(I2C_TypeDef_t * i2c);
extern void i2c_disable_dual_addressing_mode(I2C_TypeDef_t * i2c);

// set I2C Controller clock frequency : Master Mode  
extern void i2c_set_clock_frequency(I2C_TypeDef_t* i2c, uint8_t freq);
extern void i2c_set_fast_mode(I2C_TypeDef_t* i2c);
extern void i2c_set_standard_mode(I2C_TypeDef_t* i2c);
extern void i2c_set_ccr(I2C_TypeDef_t * i2c, uint16_t freq);
extern void i2c_set_trise(I2C_TypeDef_t * i2c, uint16_t trise);
extern void i2c_set_dutycycle(I2C_TypeDef_t* i2c, uint32_t dutycycle);
extern void i2c_set_speed(I2C_TypeDef_t* i2c, enum i2c_speeds speed, uint32_t clock_megahz);

// receiver mode both master and slave 
extern void i2c_enable_ack(I2C_TypeDef_t* i2c);
extern  void i2c_disable_ack(I2C_TypeDef_t* i2c);
extern void i2c_nack_next(I2C_TypeDef_t* i2c);
extern void i2c_nack_current(I2C_TypeDef_t *i2c);

// interrupt & DMA 
extern void i2c_enable_interrupt(I2C_TypeDef_t * i2c, uint32_t interrupt);
extern void i2c_disable_interrupt(I2C_TypeDef_t* i2c, uint32_t interrupt);
extern void i2c_enable_dma(I2C_TypeDef_t * i2c);
extern void i2c_disable_dma(I2C_TypeDef_t * i2c);
extern void i2c_set_dma_last_transfer(I2C_TypeDef_t * i2c);
extern void i2c_clear_dma_last_transfer(I2C_TypeDef_t * i2c);

extern uint8_t i2c_write7_v1(I2C_TypeDef_t* i2c, int addr, const uint8_t *data, size_t n);
extern uint8_t i2c_read7_v1(I2C_TypeDef_t* i2c, int addr, uint8_t *res, size_t n);
extern void i2c_transfer7(I2C_TypeDef_t * i2c, uint8_t addr, const uint8_t *w, size_t wn, uint8_t *r, size_t rn);



//********************************************************************************************
//
// Prototype function
//
//********************************************************************************************




#endif /* End of _I2C_H*/
