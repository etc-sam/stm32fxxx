/**
 * @brief i2c-std.h
 *
 * @param student: Sameer Almaldein
 * @param ID: 679699
 * @param University TU-Chemnitz
 * @param Master : ASE(Automotive Software Engineering )
 */ 
#ifndef _I2C_STD_H
#define _I2C_STD_H
/* C++ detection */
#ifdef __cplusplus
extern "C" {
#endif
//********************************************************************************************
//
// including header  files
//
//********************************************************************************************

//********************************************************************************************
//
// constants
//
//********************************************************************************************
#define I2C_MAX_BUSY_TIME   3500
#define I2C_MAX_WAIT_TIME   3500

#define I2C_TIMEOUT_FLAG          3500U         /*!< Timeout 35 ms  */
#define I2C_TIMEOUT_BUSY_FLAG     2500U         /*!< Timeout 25 ms  */
#define I2C_TIMEOUT_STOP_FLAG     50U          /*!< Timeout 5 ms   */
//********************************************************************************************
//
// enum
//
//********************************************************************************************
#define I2C_AR_ADD                          0x01 
#define I2C_7BIT_ADD_WRITE(ADDRESS)     ((uint8_t) ((ADDRESS) & (uint8_t) (~I2C_AR_ADD)))
#define I2C_7BIT_ADD_READ(ADDRESS)     ((uint8_t) ((ADDRESS) | (uint8_t) ( I2C_AR_ADD)))
/*
typedef enum
{
  I2C_OK       = 0x00U,
  I2C_ERROR    = 0x01U,
  I2C_BUSY     = 0x02U,
  I2C_TIMEOUT  = 0x03U
} HAL_StatusTypeDef;
*/
#define I2C_ERROR_BERR              0x00000001U    /*!< BERR error            */
#define I2C_ERROR_ARLO              0x00000002U    /*!< ARLO error            */
#define I2C_ERROR_AF                0x00000004U    /*!< AF error              */
#define HAL_I2C_ERROR_OVR               0x00000008U    /*!< OVR error             */
#define HAL_I2C_ERROR_DMA               0x00000010U    /*!< DMA transfer error    */
#define HAL_I2C_ERROR_TIMEOUT           0x00000020U    /*!< Timeout Error         */
#define HAL_I2C_ERROR_SIZE              0x00000040U    /*!< Size Management error */
#define HAL_I2C_ERROR_DMA_PARAM         0x00000080U    /*!< DMA Parameter Error   */
#define HAL_I2C_WRONG_START             0x00000200U    /*!< Wrong start Error     */

typedef enum _I2C_ERROR_TYPE{
I2C_OK                =0x00U,
I2C_TIMEOUT           = 0x0A,
//I2C_ERROR           =0x01U,
//I2C_BUSY             =0x02U,

I2C_BUSY_ERROR         =0x01,
I2C_START_ERROR        =0x02,
I2C_STOP_ERROR         =0x03, 
I2C_NACK_ERROR         =0x04,

I2C_TX_BTF_ERROR        =0x05,
I2C_TX_TXE_ERROR        =0x06,

I2C_RX_RXNE_ERROR       =0x07,
I2C_RX_BTF_ERROR        =0x08,

I2C_ERROR               =0x09U,


}I2C_ERROR_TYPE;

//********************************************************************************************
//
// global variables
//
//********************************************************************************************
#define  UNUSED(tmpreg)    (void)(tmpreg)
#define  I2C_FLAG_MASK       0x0000FFFFU

#define _I2C_GET_FLAG(I2Cx, __FLAG__) ((((uint8_t)((__FLAG__) >> 16U)) == 0x01U) ? \
                                      (((((I2Cx)->SR1) & ((__FLAG__) & I2C_FLAG_MASK)) == ((__FLAG__) & I2C_FLAG_MASK)) ? SET : RESET) : \
                                      (((((I2Cx)->SR2) & ((__FLAG__) & I2C_FLAG_MASK)) == ((__FLAG__) & I2C_FLAG_MASK)) ? SET : RESET))

/** @brief  Clears the I2C pending flags which are cleared by writing 0 in a specific bit.
  * @param  I2Cx specifies the I2C Handle.
  * @param  __FLAG__ specifies the flag to clear.
  *         This parameter can be any combination of the following values:
  *            @arg I2C_FLAG_OVR: Overrun/Underrun flag (Slave mode)
  *            @arg I2C_FLAG_AF: Acknowledge failure flag
  *            @arg I2C_FLAG_ARLO: Arbitration lost flag (Master mode)
  *            @arg I2C_FLAG_BERR: Bus error flag
  * @retval None
  */
#define _I2C_CLEAR_FLAG(I2Cx, __FLAG__) (I2Cx->SR1 = ~((__FLAG__) & I2C_FLAG_MASK))

/** @brief  Clears the I2C ADDR pending flag.
  * @param  __HANDLE__ specifies the I2C Handle.
  *         This parameter can be I2C where x: 1, 2, or 3 to select the I2C peripheral.
  * @retval None
  */
#define _I2C_CLEAR_ADDRFLAG(I2Cx)    \
do{                                  \
    __IO uint32_t tmpreg = 0x00U;    \
    tmpreg = I2Cx->SR1;              \
    tmpreg = I2Cx->SR2;              \
    UNUSED(tmpreg);                  \
  } while(0)

/** @brief  Clears the I2C STOPF pending flag.
  * @param  I2Cx specifies the I2C Handle.
  * @retval None
  */
#define _I2C_CLEAR_STOPFLAG(I2Cx)           \
do{                                     \
    __IO uint32_t tmpreg = 0x00U;       \
    tmpreg = I2Cx->SR1;                 \
    SET_BIT(I2Cx->CR1, I2C_CR1_PE);     \
    UNUSED(tmpreg);                      \
  } while(0)

/** @brief  Enable the specified I2C peripheral.
  * @param  I2Cx specifies the I2C Handle.
  * @retval None
  */
#define _I2C_ENABLE(I2Cx)                  SET_BIT(I2Cx->CR1, I2C_CR1_PE)

/** @brief  Disable the specified I2C peripheral.
  * @param  I2Cx specifies the I2C Handle.
  * @retval None
  */
#define _I2C_DISABLE(I2Cx)                 CLEAR_BIT(I2Cx->CR1, I2C_CR1_PE)

/**
  * @}
  */

//********************************************************************************************
//
// global variables
//
//********************************************************************************************
extern volatile uint32_t I2Cx_Timeout;

//********************************************************************************************
//
// Method protoypes using standard peripheral library
//
//********************************************************************************************
//********************************************************************************************
//
// I2c using standard peripheral library Method protoypes
//
//********************************************************************************************
extern void i2c_init_std(I2C_TypeDef* I2CX, uint32_t clock_speed,uint16_t ownaddress);

// Group A without the base address (register address to start from)

extern uint8_t i2c_write_7bit_byte_std(I2C_TypeDef* I2CX, uint8_t  slave_address,uint8_t data);
extern uint8_t i2c_write_7bit_nbyte_std(I2C_TypeDef* I2CX, uint8_t  slave_address, uint8_t *buf, size_t n);

extern uint8_t i2c_read_7bit_byte_std(I2C_TypeDef* I2CX, uint8_t  slave_address, uint8_t *data);
extern uint8_t i2c_read_7bit_word_std(I2C_TypeDef* I2CX, uint8_t  slave_address, uint16_t *data);
extern uint8_t i2c_read_7bit_nbyte_std(I2C_TypeDef* I2CX, uint8_t  slave_address, uint8_t *buf, size_t n);

// Group A with the base address (register address to start from)
extern uint8_t i2c_write_7bit_base_byte_std(I2C_TypeDef* I2CX, uint8_t  slave_address,uint8_t base_address,uint8_t data);
extern uint8_t i2c_write_7bit_base_nbyte_std(I2C_TypeDef* I2CX, uint8_t  slave_address,uint8_t base_address, uint8_t *buf, size_t n);
extern uint8_t i2c_read_7bit_base_byte_std(I2C_TypeDef* I2CX, uint8_t  slave_address,uint8_t base_address, uint8_t *data);
extern uint8_t i2c_read_7bit_base_word_std(I2C_TypeDef* I2CX, uint8_t  slave_address,uint8_t base_address, uint16_t *data);
extern uint8_t i2c_read_7bit_base_nbyte_std(I2C_TypeDef* I2CX, uint8_t  slave_address,uint8_t base_address, uint8_t *buf, size_t n);


/* C++ detection */
#ifdef __cplusplus
}
#endif
#endif /* End of _I2C_STD_H*/