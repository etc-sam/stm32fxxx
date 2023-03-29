/**
 * @brief mpu6050.h
 *
 * @param student: Sameer Almaldein
 * @param ID: 679699
 * @param University TU-Chemnitz
 * @param Master : ASE(Automotive Software Engineering )
 */ 
#ifndef _MPU6050_H
#define _MPU6050_H

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
//    constants
//
//********************************************************************************************
/**
 * @defgroup TM_MPU6050_Macros
 * @brief    Library defines
 * @{
 */
/* Default I2C used */
#ifndef MPU6050_I2C
#define	MPU6050_I2C                    I2C1              /*!< Default I2C */
#define MPU6050_I2C_PINSPACK           TM_I2C_PinsPack_1 /*!< Default I2C pinspack. Check @ref TM_I2C for more information */
#endif

/* Default I2C clock */
#ifndef MPU6050_I2C_CLOCK
#define MPU6050_I2C_CLOCK              400000           /*!< Default I2C clock speed */
#endif

#define MPU6050_I2CADDR1        0xd0//0x68 ///< MPU6050 default i2c address w/ AD0 low
#define MPU6050_I2CADDR2        0xd2//0x69 ///< MPU6050 default i2c address w/ AD0 high
#define MPU6050_DEVICE_ID       0x68 ///< The correct MPU6050_WHO_AM_I value hard coded value

#define MPU6050_MOT_THR                 0x1F ///< Motion detection threshold bits [7:0]
#define MPU6050_MOT_DUR                 0x20 ///< Duration counter threshold for motion int. 1 kHz rate, LSB = 1 ms

/**
 * @brief  Data rates predefined constants for Sample rate divider
 * @{
 */
#define MPU6050_DataRate_8KHz       0   /*!< Sample rate set to 8 kHz */
#define MPU6050_DataRate_4KHz       1   /*!< Sample rate set to 4 kHz */
#define MPU6050_DataRate_2KHz       3   /*!< Sample rate set to 2 kHz */
#define MPU6050_DataRate_1KHz       7   /*!< Sample rate set to 1 kHz */
#define MPU6050_DataRate_500Hz      15  /*!< Sample rate set to 500 Hz */
#define MPU6050_DataRate_250Hz      31  /*!< Sample rate set to 250 Hz */
#define MPU6050_DataRate_125Hz      63  /*!< Sample rate set to 125 Hz */
#define MPU6050_DataRate_100Hz      79  /*!< Sample rate set to 100 Hz */
/**
 * @}
 */

/* Gyro sensitivities in degrees/s */
#define MPU6050_GYRO_SENS_250		  ((float) 131)
#define MPU6050_GYRO_SENS_500		  ((float) 65.5)
#define MPU6050_GYRO_SENS_1000		((float) 32.8)
#define MPU6050_GYRO_SENS_2000		((float) 16.4)

/* Acce sensitivities in g/s */
#define MPU6050_ACCE_SENS_2			  ((float) 16384)
#define MPU6050_ACCE_SENS_4			  ((float) 8192)
#define MPU6050_ACCE_SENS_8			  ((float) 4096)
#define MPU6050_ACCE_SENS_16		  ((float) 2048)
/**
 * @}
 */

/**
 * @defgroup MPU6050 Register Map
 * @brief    Library defines
 * @{
 */

// MPU6050 Register Map

// selfTest Registers
#define MPU6050_SELF_TEST_X             0x0D ///< Self test factory calibrated values register
#define MPU6050_SELF_TEST_Y             0x0E ///< Self test factory calibrated values register
#define MPU6050_SELF_TEST_Z             0x0F ///< Self test factory calibrated values register
#define MPU6050_SELF_TEST_A             0x10 ///< Self test factory calibrated values register
// Configuration Registers
#define MPU6050_SMPLRT_DIV              0x19 ///< sample rate divisor register
#define MPU6050_CONFIG                  0x1A ///< General configuration register
#define MPU6050_GYRO_CONFIG             0x1B ///< Gyro specfic configuration register
#define MPU6050_ACCEL_CONFIG            0x1C ///< Accelerometer specific configration register

// Slave 0 Registers
#define MPU6050_I2C_SLV0_ADDR           0x25 ///< Slave 0 Address register +RW bit
#define MPU6050_I2C_SLV0_REG            0x26 ///< Slave 0 base address register  
#define MPU6050_I2C_SLV0_CTRL           0x27 ///< Slave 0 Control register 
// Slave 1 Registers
#define MPU6050_I2C_SLV1_ADDR           0x28 ///< Slave 1 Address register +RW bit
#define MPU6050_I2C_SLV1_REG            0x29 ///< Slave 1 base address register  
#define MPU6050_I2C_SLV1_CTRL           0x2A ///< Slave 1 Control register 
// Slave 2 Registers
#define MPU6050_I2C_SLV2_ADDR           0x2B ///< Slave 2 Address register +RW bit
#define MPU6050_I2C_SLV2_REG            0x2C ///< Slave 2 base address register  
#define MPU6050_I2C_SLV2_CTRL           0x2D ///< Slave 2 Control register 
// Slave 3 Registers
#define MPU6050_I2C_SLV3_ADDR           0x2E ///< Slave 2 Address register +RW bit
#define MPU6050_I2C_SLV3_REG            0x2F ///< Slave 2 base address register  
#define MPU6050_I2C_SLV3_CTRL           0x30 ///< Slave 2 Control register 
// Slave 4 Registers only byte read/write operation 
#define MPU6050_I2C_SLV4_ADDR           0x31 ///< Slave 4 Address register +RW bit
#define MPU6050_I2C_SLV4_REG            0x32 ///< Slave 4 base address register  
#define MPU6050_I2C_SLV4_DO             0x33 ///< Slave 4 data output register  
#define MPU6050_I2C_SLV4_CTRL           0x34 ///< Slave 4 Control register 
#define MPU6050_I2C_SLV4_DI             0x35 ///< Slave 4 data input register  
            
// Pin interrupt Registers  
#define MPU6050_INT_PIN_CFG             0x37 ///< Interrupt pin configuration register
#define MPU6050_INT_ENABLE              0x38 ///< Interrupt enable configuration register
#define MPU6050_INT_STATUS              0x3A ///< Interrupt status register

// Accelerometer sensor
#define MPU6050_ACCEL_OUT               0x3B ///< base address for ACCEL sensor data reads
#define MPU6050_ACCEL_XOUT_H            0x3B ///< ACCEL_XOUT_H[15:8]
#define MPU6050_ACCEL_XOUT_L            0x3C ///< ACCEL_XOUT_L[7:0]
#define MPU6050_ACCEL_YOUT_H            0x3D ///< ACCEL_YOUT_H[15:8]
#define MPU6050_ACCEL_YOUT_L            0x3E ///< ACCEL_YOUT_L[7:0]
#define MPU6050_ACCEL_ZOUT_H            0x3F ///< ACCEL_ZOUT_H[15:8]
#define MPU6050_ACCEL_ZOUT_L            0x40 ///< ACCEL_ZOUT_L[7:0]
// Temperature sensor
#define MPU6050_TEMP                    0x41 ///<  base address for Temperature sensor
#define MPU6050_TEMP_H                  0x41 ///< Temperature data high byte register
#define MPU6050_TEMP_L                  0x42 ///< Temperature data low byte register
// Gyroscope sensor
#define MPU6050_GYRO_OUT                0x43 ///< base address for sensor data reads
#define MPU6050_GYRO_XOUT_H             0x43 ///< GYRO_XOUT_H[15:8]
#define MPU6050_GYRO_XOUT_L             0x44 ///< GYRO_XOUT_L[7:0]
#define MPU6050_GYRO_YOUT_H             0x45 ///< GYRO_YOUT_H[15:8]
#define MPU6050_GYRO_YOUT_L             0x46 ///< GYRO_YOUT_L[7:0]
#define MPU6050_GYRO_ZOUT_H             0x47 ///< GYRO_ZOUT_H[15:8]
#define MPU6050_GYRO_ZOUT_L             0x48 ///< GYRO_ZOUT_L[7:0]

//External sensor data registers to read 
#define MPU6050_EXT_SENS_DATA           0x49 ///< base address for external sensors data reads
#define MPU6050_EXT_SENS_DATA_00        0x49 ///< EXT_SENS_DATA_00[7:0]
#define MPU6050_EXT_SENS_DATA_01        0x4A ///< EXT_SENS_DATA_00[7:0]
#define MPU6050_EXT_SENS_DATA_02        0x4B ///< EXT_SENS_DATA_00[7:0]
#define MPU6050_EXT_SENS_DATA_03        0x4C ///< EXT_SENS_DATA_00[7:0]
#define MPU6050_EXT_SENS_DATA_04        0x4D ///< EXT_SENS_DATA_00[7:0]
#define MPU6050_EXT_SENS_DATA_05        0x4E ///< EXT_SENS_DATA_00[7:0]
#define MPU6050_EXT_SENS_DATA_06        0x4F ///< EXT_SENS_DATA_00[7:0]
#define MPU6050_EXT_SENS_DATA_07        0x50 ///< EXT_SENS_DATA_00[7:0]
#define MPU6050_EXT_SENS_DATA_08        0x51 ///< EXT_SENS_DATA_00[7:0]
#define MPU6050_EXT_SENS_DATA_09        0x52 ///< EXT_SENS_DATA_00[7:0]
#define MPU6050_EXT_SENS_DATA_10        0x53 ///< EXT_SENS_DATA_00[7:0]
#define MPU6050_EXT_SENS_DATA_11        0x54 ///< EXT_SENS_DATA_00[7:0]
#define MPU6050_EXT_SENS_DATA_12        0x55 ///< EXT_SENS_DATA_00[7:0]
#define MPU6050_EXT_SENS_DATA_13        0x56 ///< EXT_SENS_DATA_00[7:0]
#define MPU6050_EXT_SENS_DATA_14        0x57 ///< EXT_SENS_DATA_00[7:0]
#define MPU6050_EXT_SENS_DATA_15        0x58 ///< EXT_SENS_DATA_00[7:0]
#define MPU6050_EXT_SENS_DATA_16        0x59 ///< EXT_SENS_DATA_00[7:0]
#define MPU6050_EXT_SENS_DATA_17        0x5A ///< EXT_SENS_DATA_00[7:0]
#define MPU6050_EXT_SENS_DATA_18        0x5B ///< EXT_SENS_DATA_00[7:0]
#define MPU6050_EXT_SENS_DATA_19        0x5C ///< EXT_SENS_DATA_00[7:0]
#define MPU6050_EXT_SENS_DATA_20        0x5D ///< EXT_SENS_DATA_00[7:0]
#define MPU6050_EXT_SENS_DATA_21        0x5E ///< EXT_SENS_DATA_00[7:0]
#define MPU6050_EXT_SENS_DATA_22        0x5F ///< EXT_SENS_DATA_00[7:0]
#define MPU6050_EXT_SENS_DATA_23        0x60 ///< EXT_SENS_DATA_00[7:0]
//! External sensor data registers to write
#define MPU6050_I2C_SLV0_DO             0x63 ///< Slave 0 data output register 
#define MPU6050_I2C_SLV1_DO             0x64 ///< Slave 0 data output register 
#define MPU6050_I2C_SLV2_DO             0x65 ///< Slave 0 data output register 
#define MPU6050_I2C_SLV3_DO             0x66 ///< Slave 0 data output register 

//! FIFO Registers :: 1024 bytes internal FIFO for collecting data from the internal and external registers 
#define MPU6050_FIFO_EN                 0x23 ///< FIFO Enable register for both internal and external sensors (GYRO,ACCEL,TEMP, SLV0..4)
#define MPU6050_FIFO_COUNTH             0x72 ///< FIFO_COUNT[15:8]
#define MPU6050_FIFO_COUNTL             0x73 ///< FIFO_COUNT[7:0]
#define MPU6050_FIFO_R_W                0x74 ///< FIFO_DATA[7:0]

#define MPU6050_WHO_AM_I                0x75 ///< Divice ID register

//! Master-Mode Registers
#define MPU6050_I2C_MST_CTRL            0x24 ///<
#define MPU6050_I2C_MST_STATUS          0x36 ///<
#define MPU6050_I2C_MST_DELAY_CTRL      0x68 ///<

//! power Managment and Reset Registers
#define MPU6050_SIGNAL_PATH_RESET       0x68 ///< Signal path reset register
#define MPU6050_USER_CTRL               0x6A ///< FIFO and I2C Master control register
#define MPU6050_PWR_MGMT_1              0x6B ///< Primary power/sleep control register
#define MPU6050_PWR_MGMT_2              0x6C ///< Secondary power/sleep control register

/**
 * @}
 */

//********************************************************************************************
//
//   Library Typedefs /enum,union,struct } 
//
//********************************************************************************************

/**
 * @defgroup MPU6050_CONFIG Register  
 * @brief    setting bothe the FSYNC and low pass filter
 * @{
 */
/**
 * @brief FSYNC output values
 *
 * Allowed values for `setFsyncSampleOutput`.
 */
typedef enum _MPU6050__Fsync_out_t {
  MPU6050_FSYNC_OUT_DISABLED =0x00,
  MPU6050_FSYNC_OUT_TEMP     =0x01,
  MPU6050_FSYNC_OUT_GYROX    =0x02 ,
  MPU6050_FSYNC_OUT_GYROY    =0x03,
  MPU6050_FSYNC_OUT_GYROZ    =0x04,
  MPU6050_FSYNC_OUT_ACCELX   =0x05,
  MPU6050_FSYNC_OUT_ACCELY   =0x06,
  MPU6050_FSYNC_OUT_ACCEL_Z  =0x07,
} MPU6050_Fsync_out_t;

/**
 * @brief Digital low pass filter bandthwidth options
 *
 * Allowed values for `setFilterBandwidth`.
 */
typedef enum _MPU6050_LPF_bandwidth_t{
  MPU6050_BAND_260_HZ =0x00, ///< Docs imply this disables the filter
  MPU6050_BAND_184_HZ =0x01, ///< 184 Hz
  MPU6050_BAND_94_HZ  =0x02,  ///< 94 Hz
  MPU6050_BAND_44_HZ  =0x03,  ///< 44 Hz
  MPU6050_BAND_21_HZ  =0x04,  ///< 21 Hz
  MPU6050_BAND_10_HZ  =0x05,  ///< 10 Hz
  MPU6050_BAND_5_HZ   =0x06,   ///< 5 Hz
} MPU6050_LPF_bandwidth_t;
/**
 * @}
 */

/**
 * @defgroup MPU6050_GYRO_CONFIG  register  
 * @brief    setting the Gyroscope range
 * @{
 */
/**
 * @brief Gyroscope range options
 *  
 * Allowed values for `setGyroRange`.
 */

typedef enum _MPU6050_Gyro_Range_t {
	MPU6050_Gyro_Range_250s  = 0x00,  /*!< Range is +- 250 degrees/s */
	MPU6050_Gyro_Range_500s  = 0x01,  /*!< Range is +- 500 degrees/s */
	MPU6050_Gyro_Range_1000s = 0x02, /*!< Range is +- 1000 degrees/s */
	MPU6050_Gyro_Range_2000s = 0x03  /*!< Range is +- 2000 degrees/s */
} MPU6050_Gyro_Range_t;

/**
 * @}
 */

/**
 * @defgroup MPU6050_ACCEL_CONFIG  register  
 * @brief    setting bothe the FSYNC and low pass filter
 * @{
 */

/**
 * @brief Accelerometer range options
 *
 * Allowed values for `setAccelerometerRange`.
 */
typedef enum _MPU6050_Accel_Range_t {
	MPU6050_Accel_Range_2G = 0x00, /*!< Range is +- 2G */
	MPU6050_Accel_Range_4G = 0x01, /*!< Range is +- 4G */
	MPU6050_Accel_Range_8G = 0x02, /*!< Range is +- 8G */
	MPU6050_Accel_Range_16G =0x03 /*!< Range is +- 16G */
} MPU6050_Accel_Range_t;

/**
 * @brief Accelerometer high pass filter options
 *
 * Allowed values for `setHighPassFilter`.
 */
typedef enum _MPU6050_Accel_HPF_t{
  MPU6050_HIGHPASS_DISABLE  =0x00,
  MPU6050_HIGHPASS_5_HZ     =0x01,
  MPU6050_HIGHPASS_2_5_HZ   =0x02,
  MPU6050_HIGHPASS_1_25_HZ  =0x03,
  MPU6050_HIGHPASS_0_63_HZ  =0x04,
  MPU6050_HIGHPASS_UNUSED   =0x05,
  MPU6050_HIGHPASS_HOLD     =0x06,
} MPU6050_Accel_HPF_t;
/**
 * @}
 */


/**
 * @defgroup MPU6050_PWR_MGMT_1  register  
 * @brief    setting MPU6050 internal clock
 * @{
 */

/**
 * @brief Clock source options
 *  
 * Allowed values for `setClock`.
 */
typedef enum _MPU6050_Clock_Select_t {
  MPU6050_INTR_8MHz     =0x00,
  MPU6050_PLL_GYROX     =0x01,
  MPU6050_PLL_GYROY     =0x02,
  MPU6050_PLL_GYROZ     =0x03,
  MPU6050_PLL_EXT_32K   =0x04,
  MPU6050_PLL_EXT_19MHz =0x05,
  MPU6050_STOP          =0x07,
} MPU6050_Clock_Select_t;
/**
 * @}
 */

/**
 * @defgroup MPU6050_PWR_MGMT_2  register  
 * @brief    setting MPU6050 LP_WAKE_CTRL[1:0]
 *           power off and wake up the accelerometer at fixed intervals 
 *           to take a single measurement
 * @{
 */
/**
 * @brief Periodic measurement options
 *  
 * Allowed values for `setCycleRate`.
 */
typedef enum _MPU6050_Cycle_Rate_t{
  MPU6050_CYCLE_1_25_HZ, ///< 1.25 Hz
  MPU6050_CYCLE_5_HZ,    ///< 5 Hz
  MPU6050_CYCLE_20_HZ,   ///< 20 Hz
  MPU6050_CYCLE_40_HZ,   ///< 40 Hz
} MPU6050_Cycle_Rate_t;
/**
 * @}
 */

/**
 * @brief  MPU6050 can have 2 different slave addresses, depends on it's input AD0 pin
 *         This feature allows you to use 2 different sensors with this library at the same time
 */
typedef enum _MPU6050_Device_t {
	TM_MPU6050_Device_0 = 0x00, /*!< AD0 pin is set to low */
	TM_MPU6050_Device_1 = 0x02  /*!< AD0 pin is set to high */
} MPU6050_Device_t;

/**
 * @brief  MPU6050 result enumeration	
 */
typedef enum _MPU6050_Result_t {
	TM_MPU6050_Result_Ok                 =0x00, /*!< Everything OK */
	TM_MPU6050_Result_Error              =0x61, /*!< Unknown error */
	TM_MPU6050_Result_DeviceNotConnected =0x62, /*!< There is no device with valid slave address */
	TM_MPU6050_Result_DeviceInvalid      =0x63  /*!< Connected device with address is not MPU6050 */
} MPU6050_Result_t;

/**
 * @brief  Interrupts union and structure
 */
typedef union _MPU6050_Interrupt_t 
{
  uint8_t Status;
struct 
 {
		uint8_t DataReady:1;       /*!< Data ready interrupt */
		uint8_t reserved2:2;       /*!< Reserved bits */
		uint8_t Master:1;          /*!< Master interrupt. Not enabled with library */
		uint8_t FifoOverflow:1;    /*!< FIFO overflow interrupt. Not enabled with library */
		uint8_t reserved1:1;       /*!< Reserved bit */
		uint8_t MotionDetection:1; /*!< Motion detected interrupt */
		uint8_t reserved0:1;       /*!< Reserved bit */
	} F;
	
} MPU6050_Interrupt_t;

/**
 * @defgroup MPU6050 Data Structures 
 * @brief    these related to both the result of communication and data aqcusition 
 * * @{
 */
#define MPU6050_RAW_ALL_LEN    14

#define MPU6050_RAW_ACCEL_LEN  6
#define MPU6050_RAW_TEMP_LEN   2
#define MPU6050_RAW_GYRO_LEN   6

#define MPU6050_RAW_ACCEL_Base  0
#define MPU6050_RAW_TEMP_Base   6
#define MPU6050_RAW_GYRO_Base   8

typedef union _mpu6050_raw_t
{
    uint8_t Array[MPU6050_RAW_ALL_LEN];

  struct{
        uint8_t accel_x_high;
        uint8_t accel_x_low;
        uint8_t accel_y_high;
        uint8_t accel_y_low;
        uint8_t accel_z_high;
        uint8_t accel_z_low;

        uint8_t temp_high;
        uint8_t temp_low;

        uint8_t gyro_x_high;
        uint8_t gyro_x_low;
        uint8_t gyro_y_high;
        uint8_t gyro_y_low;
        uint8_t gyro_z_high;
        uint8_t gyro_z_low;

    };
}mpu6050_raw_t;
/**
 * @brief  Main MPU6050 structure
 */
typedef struct _MPU6050_t {
	/* Private */
	uint8_t Address;         /*!< I2C address of device. Only for private use */
	float Gyro_Mult;         /*!< Gyroscope corrector from raw data to "degrees/s". Only for private use */
	float Acce_Mult;         /*!< Accelerometer corrector from raw data to "g". Only for private use */
	/* Public */
	int16_t Accelerometer_X; /*!< Accelerometer value X axis */
	int16_t Accelerometer_Y; /*!< Accelerometer value Y axis */
	int16_t Accelerometer_Z; /*!< Accelerometer value Z axis */
	int16_t Gyroscope_X;     /*!< Gyroscope value X axis */
	int16_t Gyroscope_Y;     /*!< Gyroscope value Y axis */
	int16_t Gyroscope_Z;     /*!< Gyroscope value Z axis */
	float Temperature;       /*!< Temperature in degrees */
  mpu6050_raw_t data;
} MPU6050_t;


/**
 * @}
 */

//********************************************************************************************
//
// Data Structure
//
//********************************************************************************************
typedef union _mpu6050_big_accel_t
{
    /* data */
    uint8_t Array[6];
    struct{
        int16_t acc_x;
        int16_t acc_y;
        int16_t acc_z;
    };

  struct{
        int8_t acc_x_high;
        uint8_t acc_x_low;
        int8_t acc_y_hig;
        uint8_t acc_y_low;
        int8_t acc_z_high;
        uint8_t acc_z_low;
    };
}mpu6050_big_accel_t;

typedef union _mpu6050_big_gyro_t
{
    /* data */
    uint8_t Array[6];
    struct{
        uint16_t gyro_x;
        uint16_t gyro_y;
        uint16_t gyro_z;
    };

  struct{
        uint8_t gyro_x_high;
        uint8_t gyro_x_low;
        uint8_t gyro_y_high;
        uint8_t gyro_y_low;
        uint8_t gyro_z_high;
        uint8_t gyro_z_low;
    };
}mpu6050_big_gyro_t;

typedef union _mpu6050_big_temp_t
{
    /* data */
    uint8_t Array[2];
    uint16_t val;
  struct{
        uint8_t temp_high;
        uint8_t temp_low;
    };
}mpu6050_big_temp_t;



//********************************************************************************************
//
//  Global  variables' declarations 
//
//********************************************************************************************
typedef enum _MPU6050_STATE 
{

 MPU_WAIT,    //!< wait until data is available on the uart receive buffer
 MPU_INIT,
 MPU_ERROR ,    //!< wait until data is available on the uart receive buffer
 MPU_READ_ALL //!< read all sensors data 
}MPU6050_STATE;

extern MPU6050_t myMPU6050;
//********************************************************************************************
//
// Method protoypes
//
//********************************************************************************************

//********************************************************************************************
//
// Prototype function
//
//********************************************************************************************
/**
 * @defgroup TM_MPU6050_Functions
 * @brief    Library Functions
 * @{
 */


extern uint8_t mpu6050_init(MPU6050_t* mpu, MPU6050_Accel_Range_t Accel_Range,MPU6050_Gyro_Range_t Gyro_Range);
extern uint8_t mpu6050_reset(MPU6050_t* mpu);
extern uint8_t mpu6050_read_Accelerometer(MPU6050_t* mpu);
extern uint8_t mpu6050_read_Gyroscope(MPU6050_t* mpu);
extern uint8_t mpu6050_read_Temperature(MPU6050_t* mpu);
extern uint8_t mpu6050_read_All(MPU6050_t* mpu);



// set accessor methods :I2C Read/Write operation 
extern uint8_t mpu6050_setGyroRange(MPU6050_t* mpu, MPU6050_Gyro_Range_t Gyro_range);
extern uint8_t mpu6050_setAccelRange(MPU6050_t* mpu, MPU6050_Accel_Range_t Accel_Range);
extern uint8_t mpu6050_setDataRate(MPU6050_t* mpu, uint8_t rate);

extern uint8_t mpu6050_EnableInterrupts(MPU6050_t* mpu);
extern uint8_t mpu6050_DisableInterrupts(MPU6050_t* mpu);
extern uint8_t mpu6050_read_Interrupts(MPU6050_t* mpu, MPU6050_Interrupt_t* InterruptsStruct);


extern uint8_t mpu6050_setClock(MPU6050_t* mpu,MPU6050_Clock_Select_t clock_select);
extern uint8_t mpu6050_setSampleRateDivisor(MPU6050_t* mpu,uint8_t SampleRateDiv);
extern uint8_t mpu6050_setCycleRate(MPU6050_t* mpu,MPU6050_Cycle_Rate_t rate);
extern uint8_t mpu6050_enableSleep(MPU6050_t* mpu,uint8_t enable);
extern uint8_t mpu6050_enableCycle(MPU6050_t* mpu,uint8_t enable);
extern uint8_t mpu6050_setI2CBypass(MPU6050_t* mpu,uint8_t bypass);
extern uint8_t mpu6050_set_lpf(MPU6050_t* mpu,MPU6050_LPF_bandwidth_t bandwidth);
extern uint8_t mpu6050_set_hpf(MPU6050_t* mpu,MPU6050_Accel_HPF_t bandwidth);

extern uint8_t mpu6050_setInterruptPinPolarity(MPU6050_t* mpu,uint8_t active_low);
extern uint8_t mpu6050_setInterruptPinLatch(MPU6050_t* mpu,uint8_t held);

extern uint8_t mpu6050_setFsyncSampleOutput(MPU6050_t* mpu,MPU6050_Fsync_out_t fsync_output);
extern uint8_t mpu6050_setMotionInterrupt(MPU6050_t* mpu,uint8_t active);
extern uint8_t mpu6050_setMotionDetectionThreshold(MPU6050_t* mpu,uint8_t thr);
extern uint8_t mpu6050_setMotionDetectionDuration(MPU6050_t* mpu,uint8_t dur);
extern uint8_t mpu6050_setGyroStandby(MPU6050_t* mpu,uint8_t xAxisStandby, uint8_t yAxisStandby, uint8_t zAxisStandby);
extern uint8_t mpu6050_setAccelerometerStandby(MPU6050_t* mpu,uint8_t xAxisStandby, uint8_t yAxisStandby,uint8_t zAxisStandby);
extern uint8_t mpu6050_setTemperatureStandby(MPU6050_t* mpu,uint8_t enable);


// get accessor methods :I2c read operation
extern uint8_t mpu6050_read_reg(MPU6050_t* mpu,uint8_t reg_address,uint8_t * data);

extern uint8_t mpu6050_getClock(MPU6050_t* mpu,uint8_t * data);
extern uint8_t mpu6050_getSampleRateDivisor(MPU6050_t* mpu,uint8_t * data);
extern uint8_t mpu6050_getCycleRate(MPU6050_t* mpu,uint8_t * data);
extern uint8_t mpu6050_getFsyncSampleOutput(MPU6050_t* mpu,uint8_t * data);
extern uint8_t mpu6050_get_lpf(MPU6050_t* mpu,uint8_t * data);
extern uint8_t mpu6050_get_hpf(MPU6050_t* mpu,uint8_t * data);
extern uint8_t mpu6050_getAccelRange(MPU6050_t* mpu,uint8_t * data);
extern uint8_t mpu6050_getGyroRange(MPU6050_t* mpu,uint8_t * data);
extern uint8_t mpu6050_getMotionInterruptStatus(MPU6050_t* mpu,uint8_t *status);

// mpu data manipulation methods
extern void mpu6050_clear_All(MPU6050_t* mpu);
extern void mpu6050_clear_Accelometer(MPU6050_t* mpu);
extern void mpu6050_clear_Gyroscope(MPU6050_t* mpu);
extern void mpu6050_clear_Temperature(MPU6050_t* mpu);

// uart print methods
extern void mpu6050_uart_print(USART_TypeDef *uart,MPU6050_t* mpu);
extern void mpu6050_uart_print_Accelometer(USART_TypeDef *uart,MPU6050_t* mpu);
extern void mpu6050_uart_print_Gyroscope(USART_TypeDef *uart,MPU6050_t* mpu);
extern void mpu6050_uart_print_Temperature(USART_TypeDef *uart,MPU6050_t* mpu);

extern void mpu6050_uart_print_raw_Accelometer(USART_TypeDef *uart,MPU6050_t* mpu);
extern void mpu6050_uart_print_raw_Gyroscope(USART_TypeDef *uart,MPU6050_t* mpu);
extern void mpu6050_uart_print_raw_Temperature(USART_TypeDef *uart,MPU6050_t* mpu);
extern void mpu6050_uart_print_raw_Data(USART_TypeDef *uart,MPU6050_t* mpu);
extern void mpu6050_uart_print_raw_Array(USART_TypeDef *uart,MPU6050_t* mpu);

// lcd print methods

/* C++ detection */
#ifdef __cplusplus
}
#endif

#endif /* End of _MPU6050_H*/
