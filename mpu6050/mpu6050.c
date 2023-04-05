
/**
 * @brief mpu6050.c
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
//  extern variables
//
//********************************************************************************************
 MPU6050_t myMPU6050={
  /* Private */
  	MPU6050_I2CADDR1,  /*!< I2C address of device. Only for private use */
	 1.0f,         			/*!< Gyroscope corrector from raw data to "degrees/s". Only for private use */
	 1.0f,         			/*!< Accelerometer corrector from raw data to "g". Only for private use */
	/* Public */
	  0,          /*!< Accelerometer value X axis */
	  0,          /*!< Accelerometer value Y axis */
	  0,          /*!< Accelerometer value Z axis */
	  0,          /*!< Gyroscope value X axis */
	  0,          /*!< Gyroscope value Y axis */
	  0,          /*!< Gyroscope value Z axis */
	  0.0f,        /*!< Temperature in degrees */
	  {{0,0,0,0,0,0,0,0,0,0,0,0,0,0}} /* raw data array*/
 };

//********** **********************************************************************************
//
//  static Methods
//
//********************************************************************************************

//********************************************************************************************
//
//  static  Methods definition
//
//********************************************************************************************

//********************************************************************************************
//
//  extern Methods
//
//********************************************************************************************

/**
 * @brief  Initializes MPU6050 and I2C peripheral
 * @param  mpu: Pointer to empty @ref TM_MPU6050_t structure
 * 		Device_ID: MPU6050 has one pin, AD0 which can be used to set address of device.
 *          This feature allows you to use 2 different sensors on the same board with same library.
 *          If you set AD0 pin to low, then this parameter should be MPU6050_Device_0,
 *          but if AD0 pin is high, then you should use MPU6050_Device_1
 *          
 *          Parameter can be a value of @ref MPU6050_Device_t enumeration
 * @param  Accel_Range: Set accelerometer sensitivity. This parameter can be a value of @ref MPU6050_Accel_Range_t enumeration
 * @param  Gyro_Range: Set gyroscope sensitivity. This parameter can be a value of @ref TM_MPU6050_Gyro_Range_t enumeration
 * @retval Initialization status:
 *            - MPU6050_Result_t: Everything OK
 *            - Other member: in other cases
 */
uint8_t mpu6050_init(MPU6050_t* mpu, MPU6050_Accel_Range_t Accel_Range,MPU6050_Gyro_Range_t Gyro_Range)
{
  //uint8_t temp=0,error=0;
	/* Format I2C address */
	//DataStruct->Address = MPU6050_I2C_ADDR | (uint8_t)DeviceNumber;
	

	//TM_I2C_Init(MPU6050_I2C, MPU6050_I2C_PINSPACK, MPU6050_I2C_CLOCK);
	
	/* Check if device is connected */
	/*if(I2C_IsDeviceConnected(MPU6050_I2C, mpu->Address) != I2C_Result_Ok) 
		  return MPU6050_Result_DeviceNotConnected;
	*/
	/* Check who am I */
	//TM_I2C_Read(MPU6050_I2C, DataStruct->Address, MPU6050_WHO_AM_I, &temp);
  //error=i2c_read_7bit_base_byte_std(MPU6050_I2C, mpu->Address, MPU6050_WHO_AM_I, &temp);
  //if(error) return error;
	//if (temp != MPU6050_DEVICE_ID ) 
	//	return TM_MPU6050_Result_DeviceInvalid;
	// Config SampleRateDivisor 

	uint8_t temp=0,error=0;	
	//_delay_ms(200);
	/*
		// Wakeup MPU6050 
    uart_print(USART1,"mpu_rst:");
    error=mpu6050_reset(mpu);
	uart_print(USART1,"\t rst:");
    uart_print_integer(USART1,error,10);
    uart_print(USART1,"\n");
	 if(error) return error;
	 */
	/*
	uart_print(USART1,"Read MPU6050_WHO_AM_I  :");	
	error=i2c_read_7bit_base_byte_std(MPU6050_I2C, mpu->Address, MPU6050_WHO_AM_I , &temp);
    uart_print(USART1,"\n Response MPU6050_WHO_AM_I  er:");
    uart_print_integer(USART1,error,16);
    uart_print(USART1,"\t rd:");
    uart_print_integer(USART1,temp,16);
    uart_print(USART1,"\r\n");
	if(error) return error;
  */


/*
	temp=0x67;
	uart_print(USART1,"write MPU6050_SMPLRT_DIV:");	
	error=i2c_write_7bit_base_byte_std(MPU6050_I2C, mpu->Address, MPU6050_SMPLRT_DIV, temp);//I2C_Read
    uart_print(USART1,"\t er:");
    uart_print_integer(USART1,error,16);
    uart_print(USART1,"\t rw:");
    uart_print_integer(USART1,temp,16);
    uart_print(USART1,"\r\n");
	//if(error) return error;

	temp=0x0;
	uart_print(USART1,"read MPU6050_SMPLRT_DIV:");	
	error=i2c_read_7bit_base_byte_std(MPU6050_I2C, mpu->Address, MPU6050_SMPLRT_DIV, &temp);//I2C_Read
    uart_print(USART1,"\t er:");
    uart_print_integer(USART1,error,16);
    uart_print(USART1,"\t rd:");
    uart_print_integer(USART1,temp,16);
    uart_print(USART1,"\r\n");
	//if(error) return error;


	temp=0xA4;
	uart_print(USART1,"write MPU6050_SMPLRT_DIV:");	
	error=i2c_write_7bit_base_byte_std(MPU6050_I2C, mpu->Address, MPU6050_SMPLRT_DIV, temp);//I2C_Read
    uart_print(USART1,"\t er:");
    uart_print_integer(USART1,error,16);
    uart_print(USART1,"\t rw:");
    uart_print_integer(USART1,temp,16);
    uart_print(USART1,"\r\n");
	//if(error) return error;

	temp=0x0;
	uart_print(USART1,"read MPU6050_SMPLRT_DIV:");	
	error=i2c_read_7bit_base_byte_std(MPU6050_I2C, mpu->Address, MPU6050_SMPLRT_DIV, &temp);//I2C_Read
    uart_print(USART1,"\t er:");
    uart_print_integer(USART1,error,16);
    uart_print(USART1,"\t rd:");
    uart_print_integer(USART1,temp,16);
    uart_print(USART1,"\r\n");
	//if(error) return error;

	temp=0;
	uart_print(USART1,"Read MPU6050_WHO_AM_I  :");	
	error=i2c_read_7bit_base_byte_std(MPU6050_I2C, mpu->Address, MPU6050_WHO_AM_I , &temp);
    uart_print(USART1,"\n Response MPU6050_WHO_AM_I  er:");
    uart_print_integer(USART1,error,16);
    uart_print(USART1,"\t rd:");
    uart_print_integer(USART1,temp,16);
    uart_print(USART1,"\r\n");
	//if(error) return error;
  
*/



	// Wakeup MPU6050 
    uart_print(USART1,"mpu_rst:");
    error=mpu6050_reset(mpu);
	uart_print(USART1,"\t rst:");
    uart_print_integer(USART1,error,10);
    uart_print(USART1,"\n");
	 //if(error) return error;

	// Config SampleRateDivisor 
	 uart_print(USART1,"mpu_smpl:");	
	 error=mpu6050_setSampleRateDivisor(mpu,MPU6050_DataRate_1KHz);
     uart_print(USART1,"\t smpl:");
     uart_print_integer(USART1,error,10);
     uart_print(USART1,"\n");
	//if(error) return error;
 	
	// Config low pass filter 
	uart_print(USART1,"mpu_lpf:");
	error=mpu6050_set_lpf(mpu,MPU6050_BAND_260_HZ);
	uart_print_integer(USART1,error,10);
    uart_print(USART1,"\n");
	//if(error) return error;
	// Configure High pass filter 
	uart_print(USART1,"mpu_hpf:");
	error=mpu6050_set_hpf(mpu,MPU6050_HIGHPASS_2_5_HZ);
	uart_print_integer(USART1,error,10);
    uart_print(USART1,"\n");
	//if(error) return error;

   // Config accelerometer 
	uart_print(USART1,"mpu_accel_rng:");
	error=mpu6050_setAccelRange(mpu,  Accel_Range);
	uart_print_integer(USART1,error,10);
    uart_print(USART1,"\n");
	//if(error) return error;

	///Config accelerometer 
	uart_print(USART1,"mpu_gyro_rng:");
	error=mpu6050_setGyroRange(mpu,Gyro_Range);
    uart_print_integer(USART1,error,10);
    uart_print(USART1,"\n");
	//if(error) return error;
  

  	/* Return OK */
	return TM_MPU6050_Result_Ok; //  or return I2C_NO_ERROR;
}
//--------------------------------------------------------------------------------------------------------
uint8_t mpu6050_reset(MPU6050_t* mpu)
{
  uint8_t error=0;
 
 error=i2c_write_7bit_base_byte_std(MPU6050_I2C,mpu->Address,MPU6050_PWR_MGMT_1, 0x00); // should be 0x80
	_delay_ms(200);
   if(error) return error;
	
  error=i2c_write_7bit_base_byte_std(MPU6050_I2C,mpu->Address,MPU6050_SIGNAL_PATH_RESET, 0x07); // should be0x80
	_delay_ms(200);
	if(error) return error;
	
  	/* Return OK */
	return TM_MPU6050_Result_Ok; //  or return I2C_NO_ERROR;
}
//--------------------------------------------------------------------------------------------------------
/**
 * @brief  Reads accelerometer data from sensor
 * @param  mpu: Pointer to @ref MPU6050_t structure to store data to
 * @retval Member of @ref MPU6050_Result_t:
 *            - MPU6050_Result_Ok: everything is OK
 *            - Other: in other cases
 */
uint8_t mpu6050_read_Accelerometer(MPU6050_t* mpu)
{
	uint8_t data[6]={0};
	uint8_t error=0;
	/* Read accelerometer data */
  error=i2c_read_7bit_base_nbyte_std(MPU6050_I2C,mpu->Address, MPU6050_ACCEL_XOUT_H, data, 6);
  if(error) return error;
	/* Format */
	mpu->Accelerometer_X = (int16_t)(data[0] << 8 | data[1]);	
	mpu->Accelerometer_Y = (int16_t)(data[2] << 8 | data[3]);
	mpu->Accelerometer_Z = (int16_t)(data[4] << 8 | data[5]);
	
  	/* Return OK */
	return TM_MPU6050_Result_Ok; //  or return I2C_NO_ERROR;
}
//--------------------------------------------------------------------------------------------------------
/**
 * @brief  Reads gyroscope data from sensor
 * @param  mpu: Pointer to @ref MPU6050_t structure to store data to
 * @retval Member of @ref MPU6050_Result_t:
 *            - MPU6050_Result_Ok: everything is OK
 *            - Other: in other cases
 */
uint8_t mpu6050_read_Gyroscope(MPU6050_t* mpu)
{
	uint8_t data[6]={0};
	uint8_t error=0;
	/* Read accelerometer data */
  error=i2c_read_7bit_base_nbyte_std(MPU6050_I2C,mpu->Address, MPU6050_GYRO_XOUT_H, data, 6);
  if(error) return error;
	/* Format */
	mpu->Gyroscope_X = (int16_t)(data[0] << 8 | data[1]);	
	mpu->Gyroscope_Y = (int16_t)(data[2] << 8 | data[3]);
	mpu->Gyroscope_Z = (int16_t)(data[4] << 8 | data[5]);
	
  	/* Return OK */
	return TM_MPU6050_Result_Ok; //  or return I2C_NO_ERROR;
}
//--------------------------------------------------------------------------------------------------------
/**
 * @brief  Reads temperature data from sensor
 * @param  *mpu: Pointer to @ref MPU6050_t structure to store data to
 * @retval Member of @ref MPU6050_Result_t:
 *            - MPU6050_Result_Ok: everything is OK
 *            - Other: in other cases
 */
MPU6050_Result_t mpu6050_read_Temperature(MPU6050_t* mpu)
{
	uint8_t data[2]={0};
	uint8_t error=0;
  	int16_t temp=0;
	/* Read accelerometer data */
  error=i2c_read_7bit_base_nbyte_std(MPU6050_I2C,mpu->Address,MPU6050_TEMP_H, data, 2);
  if(error) return error;
	/* Format */
	temp = (data[0] << 8 | data[1]);
	mpu->Temperature = (float)((int16_t)temp / (float)340.0 + (float)36.53);
  	/* Return OK */
	return TM_MPU6050_Result_Ok; //  or return I2C_NO_ERROR;
}
//--------------------------------------------------------------------------------------------------------
/**
 * @brief  Reads accelerometer, gyroscope and temperature data from sensor
 * @param  mpu: Pointer to @ref MPU6050_t structure to store data to
 * @retval Member of @ref MPU6050_Result_t:
 *            - MPU6050_Result_Ok: everything is OK
 *            - Other: in other cases
 */
uint8_t mpu6050_read_All(MPU6050_t* mpu)
{
	
	int16_t temp;
	//mpu6050_clear_All(mpu);
	/* Read full raw data, 14bytes */
	i2c_read_7bit_base_nbyte_std(MPU6050_I2C, mpu->Address, MPU6050_ACCEL_XOUT_H, mpu->data.Array, MPU6050_RAW_ALL_LEN );
	
	/* Format accelerometer data */
	mpu->Accelerometer_X = (int16_t)(mpu->data.Array[0] << 8 | mpu->data.Array[1]);	
	mpu->Accelerometer_Y = (int16_t)(mpu->data.Array[2] << 8 | mpu->data.Array[3]);
	mpu->Accelerometer_Z = (int16_t)(mpu->data.Array[4] << 8 | mpu->data.Array[5]);

	/* Format temperature */
	temp = (mpu->data.Array[6] << 8 | mpu->data.Array[7]);
	mpu->Temperature = (float)((float)( (int16_t)temp) / (float)340.0f + (float)36.53);
	
	/* Format gyroscope data */
	mpu->Gyroscope_X = (int16_t)(mpu->data.Array[8]  << 8 | mpu->data.Array[9]);
	mpu->Gyroscope_Y = (int16_t)(mpu->data.Array[10] << 8 | mpu->data.Array[11]);
	mpu->Gyroscope_Z = (int16_t)(mpu->data.Array[12] << 8 | mpu->data.Array[13]);

  	/* Return OK */
	return TM_MPU6050_Result_Ok; //  or return I2C_NO_ERROR;
}
//--------------------------------------------------------------------------------------------------------
//********************************************************************************************
//
//   related interrupt Methods
//
//********************************************************************************************

/*
 * @brief  Enables interrupts
 * @param  mpu: Pointer to @ref MPU6050_t structure indicating MPU6050 device
 * @retval Member of @ref MPU6050_Result_t enumeration
 */
uint8_t mpu6050_EnableInterrupts(MPU6050_t* mpu)
{
	uint8_t temp=0,error=0;	
	
	/* Enable interrupts for data ready and motion detect */
	error=i2c_write_7bit_base_byte_std(MPU6050_I2C, mpu->Address, MPU6050_INT_ENABLE, 0x21);//I2C_Write
	if(error) return error;
	/* Clear IRQ flag on any read operation */
	error=i2c_read_7bit_base_byte_std(MPU6050_I2C, mpu->Address, MPU6050_INT_PIN_CFG, &temp);//I2C_Read
	if(error) return error;
	temp |= 0x10;
	error=i2c_write_7bit_base_byte_std(MPU6050_I2C, mpu->Address, MPU6050_INT_PIN_CFG, temp);//I2C_Write
	if(error) return error;
	
  	/* Return OK */
	return TM_MPU6050_Result_Ok; //  or return I2C_NO_ERROR;
}
//--------------------------------------------------------------------------------------------------------
/**
 * @brief  Disables interrupts
 * @param  mpu: Pointer to @ref MPU6050_t structure indicating MPU6050 device
 * @retval Member of @ref MPU6050_Result_t enumeration
 */
uint8_t mpu6050_DisableInterrupts(MPU6050_t* mpu)
{
	/* Disable interrupts */
  return i2c_write_7bit_base_byte_std(MPU6050_I2C, mpu->Address, MPU6050_INT_ENABLE, 0x00);
}
//--------------------------------------------------------------------------------------------------------
/**
 * @brief  Reads and clears interrupts
 * @param  mpu: Pointer to @ref MPU6050_t structure indicating MPU6050 device
 * @param  *InterruptsStruct: Pointer to @ref MPU6050_Interrupt_t structure to store status in
 * @retval Member of @ref MPU6050_Result_t enumeration
 */
uint8_t mpu6050_read_Interrupts(MPU6050_t* mpu, MPU6050_Interrupt_t* InterruptsStruct)
{
	uint8_t read,error=0;
	
	/* Reset structure */
	InterruptsStruct->Status = 0;
	
	/* Read interrupts status register */
  error=i2c_read_7bit_base_byte_std(MPU6050_I2C, mpu->Address, MPU6050_INT_STATUS, &read);
  if(error) return error;	
	/* Fill value */
	InterruptsStruct->Status = read;
	
	/* Return OK */
	return TM_MPU6050_Result_Ok;
}
//--------------------------------------------------------------------------------------------------------

//********************************************************************************************
//
//   set methods: used to change the internal registers values for MPU6050
//
//********************************************************************************************

/**
 * @brief  Sets gyroscope sensitivity
 * @param  *mpu: Pointer to @ref TM_MPU6050_t structure indicating MPU6050 device
 * @param  GyroscopeSensitivity: Gyro sensitivity value. This parameter can be a value of @ref MPU6050_Gyro_Range_t enumeration
 * @retval Member of @ref TM_MPU6050_Result_t enumeration
 */
uint8_t mpu6050_setGyroRange(MPU6050_t* mpu, MPU6050_Gyro_Range_t Gyro_range)
{
  uint8_t temp=0;
  uint8_t error=0;
	/* Config gyroscope */
	//TM_I2C_Read(MPU6050_I2C, DataStruct->Address, MPU6050_GYRO_CONFIG, &temp);
  error=i2c_read_7bit_base_byte_std(MPU6050_I2C,mpu->Address,MPU6050_GYRO_CONFIG, &temp);
  if(error) return error;
	temp = (temp & 0xE7) | (uint8_t)Gyro_range << 3;
	error=i2c_write_7bit_base_byte_std(MPU6050_I2C, mpu->Address, MPU6050_GYRO_CONFIG, temp);//TM_I2C_Write(MPU6050_I2C, mpu->Address, MPU6050_GYRO_CONFIG, temp);
	if(error) return error;

	switch (Gyro_range) 
    {
		case MPU6050_Gyro_Range_250s: mpu->Gyro_Mult = (float)1 / MPU6050_GYRO_SENS_250;  break;
		case MPU6050_Gyro_Range_500s: mpu->Gyro_Mult = (float)1 / MPU6050_GYRO_SENS_500;  break;
		case MPU6050_Gyro_Range_1000s:mpu->Gyro_Mult = (float)1 / MPU6050_GYRO_SENS_1000; break;
		case MPU6050_Gyro_Range_2000s:mpu->Gyro_Mult = (float)1 / MPU6050_GYRO_SENS_2000; break;
		default:
		break;
	}
	
  	/* Return OK */
	return TM_MPU6050_Result_Ok; //  or return I2C_NO_ERROR;
}
//--------------------------------------------------------------------------------------------------------
/**
 * @brief  Sets accelerometer sensitivity
 * @param  *mpu: Pointer to @ref MPU6050_t structure indicating MPU6050 device
 * @param  AccelerometerSensitivity: Gyro sensitivity value. This parameter can be a value of @ref MPU6050_AccelRange_t enumeration
 * @retval Member of @ref MPU6050_Result_t enumeration
 */
uint8_t mpu6050_setAccelRange(MPU6050_t* mpu, MPU6050_Accel_Range_t Accel_Range)
{
	uint8_t temp=0;
	uint8_t error=0;
	/* Config accelerometer */
	error=i2c_read_7bit_base_byte_std(MPU6050_I2C, mpu->Address, MPU6050_ACCEL_CONFIG, &temp);
  if(error) return error;
	temp = (temp & 0xE7) | (uint8_t)Accel_Range << 3;
	error=i2c_write_7bit_base_byte_std(MPU6050_I2C, mpu->Address, MPU6050_ACCEL_CONFIG, temp);
  if(error) return error;
	
	/* Set sensitivities for multiplying gyro and accelerometer data */
	switch (Accel_Range) 
	{
		case MPU6050_Accel_Range_2G:  mpu->Acce_Mult = (float)1 / MPU6050_ACCE_SENS_2;  break;
		case MPU6050_Accel_Range_4G:  mpu->Acce_Mult = (float)1 / MPU6050_ACCE_SENS_4;  break;
		case MPU6050_Accel_Range_8G:  mpu->Acce_Mult = (float)1 / MPU6050_ACCE_SENS_8;  break;
		case MPU6050_Accel_Range_16G: mpu->Acce_Mult = (float)1 / MPU6050_ACCE_SENS_16; break; 
		default:
		break;
	}
  	/* Return OK */
	return TM_MPU6050_Result_Ok; //  or return I2C_NO_ERROR;
}
//--------------------------------------------------------------------------------------------------------
uint8_t mpu6050_setClock(MPU6050_t* mpu,MPU6050_Clock_Select_t clock_select)
{
  return 0;
}
//--------------------------------------------------------------------------------------------------------
/**
 * @brief  Sets output data rate
 * @param  *mpu: Pointer to @ref MPU6050_t structure indicating MPU6050 device
 * @param  rate: Data rate value. An 8-bit value for prescaler value
 * @retval Member of @ref MPU6050_Result_t enumeration
 */
uint8_t mpu6050_setDataRate(MPU6050_t* mpu, uint8_t rate)
{
 	return i2c_write_7bit_base_byte_std(MPU6050_I2C, mpu->Address, MPU6050_SMPLRT_DIV, rate);
}
//--------------------------------------------------------------------------------------------------------
uint8_t mpu6050_setSampleRateDivisor(MPU6050_t* mpu,uint8_t SampleRateDiv)
{
	 return i2c_write_7bit_base_byte_std(MPU6050_I2C, mpu->Address, MPU6050_SMPLRT_DIV, SampleRateDiv);
}
//--------------------------------------------------------------------------------------------------------
uint8_t mpu6050_setCycleRate(MPU6050_t* mpu,MPU6050_Cycle_Rate_t rate)
{
	uint8_t error=0,temp=0;
	error=i2c_read_7bit_base_byte_std(MPU6050_I2C, mpu->Address, MPU6050_PWR_MGMT_2, &temp);
  if(error) return error;
	temp = (temp & 0x3f) | (uint8_t)rate << 6;
	error=i2c_write_7bit_base_byte_std(MPU6050_I2C, mpu->Address, MPU6050_PWR_MGMT_2, temp);
  if(error) return error;
  	/* Return OK */
	return TM_MPU6050_Result_Ok; //  or return I2C_NO_ERROR;
}
//--------------------------------------------------------------------------------------------------------
uint8_t mpu6050_enableSleep(MPU6050_t* mpu,uint8_t enable)
{
	uint8_t error=0,temp=0;
	error=i2c_read_7bit_base_byte_std(MPU6050_I2C, mpu->Address, MPU6050_PWR_MGMT_1, &temp);
  if(error) return error;
	temp = (temp & 0xaf) | (uint8_t)enable << 6;
	error=i2c_write_7bit_base_byte_std(MPU6050_I2C, mpu->Address, MPU6050_PWR_MGMT_1, temp);
  if(error) return error;
  	/* Return OK */
	return TM_MPU6050_Result_Ok; //  or return I2C_NO_ERROR;
}
//--------------------------------------------------------------------------------------------------------
uint8_t mpu6050_enableCycle(MPU6050_t* mpu,uint8_t enable)
{
	uint8_t error=0,temp=0;
	error=i2c_read_7bit_base_byte_std(MPU6050_I2C, mpu->Address, MPU6050_PWR_MGMT_1, &temp);
  if(error) return error;
	temp = (temp & 0xcf) | (uint8_t)enable << 5;
	error=i2c_write_7bit_base_byte_std(MPU6050_I2C, mpu->Address, MPU6050_PWR_MGMT_1, temp);
  if(error) return error;
  	/* Return OK */
	return TM_MPU6050_Result_Ok; //  or return I2C_NO_ERROR;
}
//--------------------------------------------------------------------------------------------------------
uint8_t mpu6050_setI2CBypass(MPU6050_t* mpu,uint8_t bypass)
{
 	uint8_t error=0,temp=0;
	error=i2c_read_7bit_base_byte_std(MPU6050_I2C, mpu->Address, MPU6050_INT_PIN_CFG, &temp);
  if(error) return error;
	temp =  (uint8_t)bypass << 1;
	error=i2c_write_7bit_base_byte_std(MPU6050_I2C, mpu->Address,MPU6050_INT_PIN_CFG, temp);
  if(error) return error;

	error=i2c_read_7bit_base_byte_std(MPU6050_I2C, mpu->Address, MPU6050_USER_CTRL, &temp);
  if(error) return error;
	temp &=0x57;
	error=i2c_write_7bit_base_byte_std(MPU6050_I2C, mpu->Address,MPU6050_USER_CTRL, temp);
  if(error) return error;
  	/* Return OK */
	return TM_MPU6050_Result_Ok; //  or return I2C_NO_ERROR;
}
//--------------------------------------------------------------------------------------------------------
uint8_t mpu6050_set_lpf(MPU6050_t* mpu,MPU6050_LPF_bandwidth_t bandwidth)
{
  uint8_t error=0,temp=0;
	error=i2c_read_7bit_base_byte_std(MPU6050_I2C, mpu->Address, MPU6050_CONFIG, &temp);
   if(error) return error;
	temp =  (temp & 0xf8)|(uint8_t)bandwidth;
	error=i2c_write_7bit_base_byte_std(MPU6050_I2C, mpu->Address,MPU6050_CONFIG, temp);
	 if(error) return error;
  	/* Return OK */
	return TM_MPU6050_Result_Ok; //  or return I2C_NO_ERROR;
}
//--------------------------------------------------------------------------------------------------------
uint8_t mpu6050_set_hpf(MPU6050_t* mpu,MPU6050_Accel_HPF_t bandwidth)
{
  uint8_t error=0,temp=0;
	error=i2c_read_7bit_base_byte_std(MPU6050_I2C, mpu->Address, MPU6050_ACCEL_CONFIG, &temp);
	uart_print(USART1,"\t rd_AccCONFIG:");
    uart_print_integer(USART1,error,10);
	uart_print(USART1,"\t ");
    uart_print_integer(USART1,temp,10);
	uart_print(USART1,"\n");
	i2c_uart_print(USART1);	
  //if(error) return error;

	temp =  (temp & 0xf8)|(uint8_t)bandwidth;
	uart_print(USART1,"\t to write");
    uart_print_integer(USART1,temp,10);
	uart_print(USART1,"\n");

	error=i2c_write_7bit_base_byte_std(MPU6050_I2C, mpu->Address,MPU6050_ACCEL_CONFIG, temp);
	uart_print(USART1,"\t wr_CONFIG:");
    uart_print_integer(USART1,error,10);
	uart_print(USART1,"\t ");
    uart_print_integer(USART1,temp,10);
	uart_print(USART1,"\n");
	i2c_uart_print(USART1);
  //if(error) return error;
    /* Return OK */
	return TM_MPU6050_Result_Ok; //  or return I2C_NO_ERROR;
}
//--------------------------------------------------------------------------------------------------------
uint8_t mpu6050_setInterruptPinPolarity(MPU6050_t* mpu,uint8_t active_low)
{
	/*
	  Adafruit_BusIO_Register int_pin_config =
      Adafruit_BusIO_Register(i2c_dev, MPU6050_INT_PIN_CONFIG, 1);
  Adafruit_BusIO_RegisterBits int_level =
      Adafruit_BusIO_RegisterBits(&int_pin_config, 1, 7);
  int_level.write(active_low);
	*/
 return 0;
}
//--------------------------------------------------------------------------------------------------------
uint8_t smpu6050_etInterruptPinLatch(MPU6050_t* mpu,uint8_t held)
{
	/*
	  Adafruit_BusIO_Register int_pin_config =
      Adafruit_BusIO_Register(i2c_dev, MPU6050_INT_PIN_CONFIG, 1);
  Adafruit_BusIO_RegisterBits int_latch =
      Adafruit_BusIO_RegisterBits(&int_pin_config, 1, 5);
  int_latch.write(held);
	*/
 return 0;
}
//--------------------------------------------------------------------------------------------------------
uint8_t mpu6050_setFsyncSampleOutput(MPU6050_t* mpu,MPU6050_Fsync_out_t fsync_output)
{
 return 0;
}
//--------------------------------------------------------------------------------------------------------
uint8_t mpu6050_setMotionInterrupt(MPU6050_t* mpu,uint8_t active)
{
	/*
	  Adafruit_BusIO_Register int_enable =
      Adafruit_BusIO_Register(i2c_dev, MPU6050_INT_ENABLE, 1);
  Adafruit_BusIO_RegisterBits int_motion =
      Adafruit_BusIO_RegisterBits(&int_enable, 1, 6);
  int_motion.write(active);

 */
return 0;
}
//--------------------------------------------------------------------------------------------------------
uint8_t mpu6050_setMotionDetectionThreshold(MPU6050_t* mpu,uint8_t thr)
{
	/*
	  Adafruit_BusIO_Register threshold =
    Adafruit_BusIO_Register(i2c_dev, MPU6050_MOT_THR, 1);
    threshold.write(thr);
	*/
 return 0;
}
//--------------------------------------------------------------------------------------------------------
uint8_t mpu6050_setMotionDetectionDuration(MPU6050_t* mpu,uint8_t dur)
{
		/*
	  Adafruit_BusIO_Register duration =
      Adafruit_BusIO_Register(i2c_dev, MPU6050_MOT_DUR, 1);
  duration.write(dur);
	*/
 return 0;
}
//--------------------------------------------------------------------------------------------------------
uint8_t mpu6050_setGyroStandby(MPU6050_t* mpu,uint8_t xAxisStandby, uint8_t yAxisStandby, uint8_t zAxisStandby)
{
 uint8_t error=0,temp=0,stdby=0;
	error=i2c_read_7bit_base_byte_std(MPU6050_I2C, mpu->Address, MPU6050_PWR_MGMT_2, &temp);
  if(error) return error;
	stdby=(uint8_t)(xAxisStandby << 2 | yAxisStandby << 1 | zAxisStandby);
	temp = (temp & 0xf8) |stdby;
	error=i2c_write_7bit_base_byte_std(MPU6050_I2C, mpu->Address, MPU6050_PWR_MGMT_2, temp);
  if(error) return error;
  	/* Return OK */
	return TM_MPU6050_Result_Ok; //  or return I2C_NO_ERROR;
}
//--------------------------------------------------------------------------------------------------------
uint8_t mpu6050_setAccelerometerStandby(MPU6050_t* mpu,uint8_t xAxisStandby, uint8_t yAxisStandby,uint8_t zAxisStandby)
{
  uint8_t error=0,temp=0,stdby=0;
	error=i2c_read_7bit_base_byte_std(MPU6050_I2C, mpu->Address, MPU6050_PWR_MGMT_2, &temp);
  if(error) return error;
	stdby=(uint8_t)(xAxisStandby << 2 | yAxisStandby << 1 | zAxisStandby);
	temp = (uint8_t) (temp & 0xf8) | (stdby<<3) ;
	error=i2c_write_7bit_base_byte_std(MPU6050_I2C, mpu->Address, MPU6050_PWR_MGMT_2, temp);
  if(error) return error;
  	/* Return OK */
	return TM_MPU6050_Result_Ok; //  or return I2C_NO_ERROR;
}
//--------------------------------------------------------------------------------------------------------
uint8_t mpu6050_setTemperatureStandby(MPU6050_t* mpu,uint8_t enable)
{
  uint8_t error=0,temp=0;
	error=i2c_read_7bit_base_byte_std(MPU6050_I2C, mpu->Address, MPU6050_PWR_MGMT_1, &temp);
  if(error) return error;
	temp = (temp & 0xE7) | (enable<<3) ;
	error=i2c_write_7bit_base_byte_std(MPU6050_I2C, mpu->Address, MPU6050_PWR_MGMT_1, temp);
  if(error) return error;
  	/* Return OK */
	return TM_MPU6050_Result_Ok; //  or return I2C_NO_ERROR;
}
//--------------------------------------------------------------------------------------------------------

//********************************************************************************************
//
//   get Methods
//
//********************************************************************************************
uint8_t mpu6050_read_reg(MPU6050_t* mpu,uint8_t reg_address,uint8_t * data)
{
 	/* read MPU6050_SMPLRT_DIV register*/
  uint8_t error=0, temp=0;	
  error=i2c_read_7bit_base_byte_std(MPU6050_I2C,mpu->Address,reg_address,&temp);
  if(error) return error;
	*data=temp;
  	/* Return OK */
	return TM_MPU6050_Result_Ok; //  or return I2C_NO_ERROR;
}
//--------------------------------------------------------------------------------------------------------
uint8_t mpu6050_getClock(MPU6050_t* mpu,uint8_t * data)
{
 /* read MPU6050_PWR_MGMT_1 register*/
  uint8_t error=0, temp=0;	
  error=i2c_read_7bit_base_byte_std(MPU6050_I2C,mpu->Address,MPU6050_PWR_MGMT_1,&temp);
  if(error) return error;
	*data=temp & 0x07;
  	/* Return OK */
	return TM_MPU6050_Result_Ok; //  or return I2C_NO_ERROR;
}
//--------------------------------------------------------------------------------------------------------
uint8_t mpu6050_getSampleRateDivisor(MPU6050_t* mpu,uint8_t * data)
{
	/* read MPU6050_SMPLRT_DIV register*/
	return mpu6050_read_reg(mpu,MPU6050_SMPLRT_DIV,data);
}
//--------------------------------------------------------------------------------------------------------
uint8_t mpu6050_getCycleRate(MPU6050_t* mpu,uint8_t * data)
{
 /* read MPU6050_PWR_MGMT_2 register*/
  uint8_t error=0, temp=0;	
  error=i2c_read_7bit_base_byte_std(MPU6050_I2C,mpu->Address,MPU6050_PWR_MGMT_2,&temp);
  if(error) return error;
	*data=(uint8_t)(temp>>6)& 0x02;
  	/* Return OK */
	return TM_MPU6050_Result_Ok; //  or return I2C_NO_ERROR;
}
//--------------------------------------------------------------------------------------------------------
uint8_t mpu6050_getFsyncSampleOutput(MPU6050_t* mpu,uint8_t* data)
{
	/* read MPU6050_CONFIG register*/
  uint8_t error=0, temp=0;	
  error=i2c_read_7bit_base_byte_std(MPU6050_I2C,mpu->Address,MPU6050_CONFIG,&temp);
  if(error) return error;
	*data=((uint8_t)temp>>3) &0x03 ;
  	/* Return OK */
	return TM_MPU6050_Result_Ok; //  or return I2C_NO_ERROR;
}
//--------------------------------------------------------------------------------------------------------
uint8_t mpu6050_get_lpf(MPU6050_t* mpu,uint8_t* lpf)
{
	/* read MPU6050_CONFIG register*/
  uint8_t error=0, temp=0;	
  error=i2c_read_7bit_base_byte_std(MPU6050_I2C,mpu->Address,MPU6050_CONFIG,&temp);
  if(error) return error;
		*lpf=temp & 0x07 ;
  	/* Return OK */
	return TM_MPU6050_Result_Ok; //  or return I2C_NO_ERROR;
}
//--------------------------------------------------------------------------------------------------------
uint8_t mpu6050_get_hpf(MPU6050_t* mpu,uint8_t* hpf)
{
  /* read MPU6050_ACCEL_CONFIG register*/
  uint8_t error=0, temp=0;	
  error=i2c_read_7bit_base_byte_std(MPU6050_I2C,mpu->Address,MPU6050_ACCEL_CONFIG,&temp);
  if(error) return error;
  *hpf=temp & 0x07 ;
  /* Return OK */
  return TM_MPU6050_Result_Ok; //  or return I2C_NO_ERROR;
}
//--------------------------------------------------------------------------------------------------------
uint8_t mpu6050_getAccelRange(MPU6050_t* mpu,uint8_t * data)
{
  /* read MPU6050_ACCEL_CONFIG register*/
  uint8_t error=0, temp=0;

  error=i2c_read_7bit_base_byte_std(MPU6050_I2C,mpu->Address,MPU6050_ACCEL_CONFIG,&temp);
  if(error) return error;	
  *data=((uint8_t)temp>>3) &0x03 ;
  	/* Return OK */
	return TM_MPU6050_Result_Ok; //  or return I2C_NO_ERROR;
}
//--------------------------------------------------------------------------------------------------------
uint8_t mpu6050_getGyroRange(MPU6050_t* mpu,uint8_t *data)
{
  /* read MPU6050_GYRO_CONFIG register*/
  uint8_t error=0, temp=0;	
  error=i2c_read_7bit_base_byte_std(MPU6050_I2C,mpu->Address,MPU6050_GYRO_CONFIG,&temp);
  if(error) return error;	
  *data=((uint8_t)temp>>3) &0x03 ;
  /* Return OK */
  return TM_MPU6050_Result_Ok; //  or return I2C_NO_ERROR;
}
//--------------------------------------------------------------------------------------------------------
uint8_t mpu6050_getMotionInterruptStatus(MPU6050_t* mpu,uint8_t *status)
{
 /* 
   Adafruit_BusIO_Register status =
      Adafruit_BusIO_Register(i2c_dev, MPU6050_INT_STATUS, 1);

  Adafruit_BusIO_RegisterBits motion =
      Adafruit_BusIO_RegisterBits(&status, 1, 6);
  return (bool)motion.read();
 */
  return 0;
}
//--------------------------------------------------------------------------------------------------------
//********************************************************************************************
//
//   Print and Display Methods
//
//********************************************************************************************
void mpu6050_clear_All(MPU6050_t* mpu)
{
	uint8_t i=0;
	for(i=0;i<MPU6050_RAW_ALL_LEN;i++)
 		mpu->data.Array[i]=0;
	
	mpu->Accelerometer_X=0;
 	mpu->Accelerometer_Y=0;
 	mpu->Accelerometer_X=0;	
	mpu->Gyroscope_X=0;
 	mpu->Gyroscope_Y=0;
 	mpu->Gyroscope_Z=0;
	mpu->Temperature=0.0f;
}
//-------------------------------------------------------------------------------------------
void mpu6050_clear_Accelometer(MPU6050_t* mpu)
{
	uint8_t i=0;
 	mpu->Accelerometer_X=0;
 	mpu->Accelerometer_Y=0;
 	mpu->Accelerometer_X=0;
 	for(i=0;i<MPU6050_RAW_ACCEL_LEN;i++)
 		mpu->data.Array[i+MPU6050_RAW_ACCEL_Base]=0;
}
//-------------------------------------------------------------------------------------------
void mpu6050_clear_Gyroscope(MPU6050_t* mpu)
{
	uint8_t i=0;
 	mpu->Gyroscope_X=0;
 	mpu->Gyroscope_Y=0;
 	mpu->Gyroscope_Z=0;
 	for(i=0;i<MPU6050_RAW_GYRO_LEN;i++)
 		mpu->data.Array[i+MPU6050_RAW_GYRO_Base]=0;
}
//-------------------------------------------------------------------------------------------
void mpu6050_clear_Temperature(MPU6050_t* mpu)
{
	mpu->Temperature=0.0f;
	mpu->data.temp_high=0;
	mpu->data.temp_low=0;
}
//-------------------------------------------------------------------------------------------
//********************************************************************************************
//
//   Print and Display Methods
//
//********************************************************************************************
void mpu6050_uart_print(USART_TypeDef *uart,MPU6050_t* mpu)
{
	// print Accelometer
	 mpu6050_uart_print_Accelometer(uart,mpu);
	// print Gyroscope
	  mpu6050_uart_print_Gyroscope(uart,mpu);
	// print temprature
	 mpu6050_uart_print_Temperature(uart,mpu);
}
//-------------------------------------------------------------------------------------------
void mpu6050_uart_print_Accelometer(USART_TypeDef *uart,MPU6050_t* mpu)
{
    uart_print(uart,"\t Accel_X:");
    uart_print_integer(uart,mpu->Accelerometer_X,10);
    uart_print(uart,"\t Accel_Y:");
    uart_print_integer(uart,mpu->Accelerometer_Y,10);
    uart_print(uart,"\t Accel_Z:");
    uart_print_integer(uart,mpu->Accelerometer_Z,10);
    uart_print(uart,"\n");
}
//-------------------------------------------------------------------------------------------
void mpu6050_uart_print_Gyroscope(USART_TypeDef *uart,MPU6050_t* mpu)
{
    uart_print(uart,"\t Gyro_X:");
    uart_print_integer(uart,mpu->Gyroscope_X,10);
    uart_print(uart,"\t Gyro_Y:");
    uart_print_integer(uart,mpu->Gyroscope_Y,10);
    uart_print(uart,"\t Gyro_Z:");
    uart_print_integer(uart,mpu->Gyroscope_Z,10);
    uart_print(uart,"\n");
}
//-------------------------------------------------------------------------------------------
void mpu6050_uart_print_Temperature(USART_TypeDef *uart,MPU6050_t* mpu)
{
	uart_print(uart,"\t Temp:");
	uart_print_float(uart,mpu->Temperature,2);
    uart_print(uart,"\n");
}
//-------------------------------------------------------------------------------------------
void mpu6050_uart_print_raw_Data(USART_TypeDef *uart,MPU6050_t* mpu)
{
	 mpu6050_uart_print_raw_Accelometer(uart,mpu);
	 mpu6050_uart_print_raw_Gyroscope(uart,mpu);
	 mpu6050_uart_print_raw_Temperature(uart,mpu);
}
//-------------------------------------------------------------------------------------------
void mpu6050_uart_print_raw_Accelometer(USART_TypeDef *uart,MPU6050_t* mpu)
{
	WORD_BYTES t;
	t.word=0;

	t.byte.high=mpu->data.accel_x_high;
	t.byte.low=mpu->data.accel_x_low;
	uart_print(uart,"\t ACCEL_XOUT:");
	uart_print_integer(uart,t.word,16);

	t.byte.high=mpu->data.accel_y_high;
	t.byte.low=mpu->data.accel_y_low;
	uart_print(uart,"\t ACCEL_YOUT:");
	uart_print_integer(uart,t.word,16);

	t.byte.high=mpu->data.accel_z_high;
	t.byte.low=mpu->data.accel_z_low;
	uart_print(uart,"\t ACCEL_ZOUT:");
	uart_print_integer(uart,t.word,16);
    uart_print(uart,"\r\n");
}
//-------------------------------------------------------------------------------------------
void mpu6050_uart_print_raw_Gyroscope(USART_TypeDef *uart,MPU6050_t* mpu)
{
	WORD_BYTES t;
	t.word=0;
	
	t.byte.high=mpu->data.gyro_x_high;
	t.byte.low=mpu->data.gyro_x_low;
	uart_print(uart,"\t GYRO_XOUT:");
	uart_print_integer(uart,t.word,16);


	t.byte.high=mpu->data.gyro_y_high;
	t.byte.low=mpu->data.gyro_y_low;
	uart_print(uart,"\t GYRO_YOUT:");
	uart_print_integer(uart,t.word,16);

	t.byte.high=mpu->data.gyro_z_high;
	t.byte.low=mpu->data.gyro_z_low;
	uart_print(uart,"\t GYRO_ZOUT:");
	uart_print_integer(uart,t.word,16);
    uart_print(uart,"\r\n");
}
//-------------------------------------------------------------------------------------------
void mpu6050_uart_print_raw_Temperature(USART_TypeDef *uart,MPU6050_t* mpu)
{
	WORD_BYTES t;
	t.word=0;
	
	t.byte.high=mpu->data.temp_high;
	t.byte.low=mpu->data.temp_low;

	uart_print(uart,"\t TEMP_OUT:");
	uart_print_integer(uart,t.word,16);
    uart_print(uart,"\r\n");
}
//-------------------------------------------------------------------------------------------
void mpu6050_uart_print_raw_Array(USART_TypeDef *uart,MPU6050_t* mpu)
{
	uint8_t i=0, index=MPU6050_ACCEL_OUT;
	for (i=0;i<MPU6050_RAW_ALL_LEN ;i++)
	{
	 	
		uart_print(uart,"\t reg @ (");
		uart_print_integer(uart,index,16);
		uart_print(uart,"):");
		uart_print_integer(uart,mpu->data.Array[i],16);
    	uart_print(uart,"\n");
		index++;
	}
	uart_print(uart,"\r\n\n");
}
//-------------------------------------------------------------------------------------------
