
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
  MPU6050_I2CADDR1, //! I2C address of device
	 {{0,0,0,0,0,0,0,0,0,0,0,0,0,0}}, //! raw data array
		
		/*integer data */
	  0,          //! Accelerometer value X axis
	  0,          //! Accelerometer value Y axis
	  0,          //! Accelerometer value Z axis
	  0,          //! Gyroscope value X axis 
	  0,          //! Gyroscope value Y axis 
	  0,          //! Gyroscope value Z axis 
	  
		/*decimal data */
	  1.0f,        //! Gyroscope corrector from raw data to "degrees/s"
	  1.0f,        //! Accelerometer corrector from raw data to "g"
		0.0f,        //! Decimal Accelerometer value X axis 
	  0.0f,        //! Decimal Accelerometer value Y axis 
	  0.0f,        //! Decimal Accelerometer value Z axis 
	  0.0f,        //! Decimal Gyroscope value X axis 
	  0.0f,        //! Decimal Gyroscope value Y axis 
	  0.0f,        //! Decimal Gyroscope value Z axis 
    
		0.0f,       //! Decimal Accelerometer value X axis multiplied by SENSORS_GRAVITY_STANDARD
	  0.0f,       //! Decimal Accelerometer value Y axis multiplied by SENSORS_GRAVITY_STANDARD
	  0.0f,       //! Decimal Accelerometer value Z axis multiplied by SENSORS_GRAVITY_STANDARD 
	  0.0f,       //! Decimal Gyroscope value X axis multiplied by SENSORS_DPS_TO_RADS */
	  0.0f,       //! Decimal Gyroscope value Y axis multiplied by SENSORS_DPS_TO_RADS 
	  0.0f,       //! Decimal Gyroscope value Z axis multiplied by SENSORS_DPS_TO_RADS 
		
		0.0f       //! Temperature in degrees 
 };

mpu_config_t mpu_settings={
 0, 												//mpu is not initialized,
 MPU6050_Accel_Range_2G,	  //mpu accelerometer range ==0:+-2G 
 MPU6050_Gyro_Range_500s,	  //mpu gyroscope  range == 1:+-500 d/s
 2,													//mpu accelerometer thershold 0..100  
 2,													//mpu gyroscope thershold 0..100
 MPU_ACQ_ALL,								// ACQ mode {0:all ,1:accel,2:gyro,3:temp,4:accel+gyro,5:acceel+temp, 6:gyro+temp}
 0,
 5,
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
  uint8_t temp=0,error=0;

  error=i2c_read_7bit_base_byte_std(MPU6050_I2C, mpu->Address, MPU6050_WHO_AM_I, &temp);
  if(error) return error;
	if (temp != MPU6050_DEVICE_ID ) 
	 return MPU6050_DeviceInvalid;
	
	// Wakeup MPU6050 
    uart_print(USART1,"mpu_rst:");
    error=mpu6050_reset(mpu);
	uart_print_integer(USART1,error,10);
    uart_print(USART1,"\n");
	i2c_uart_print(USART1);	
	if(error) return error;

	// Config SampleRateDivisor 
	uart_print(USART1,"mpu_smpl:");	
	error=mpu6050_setSampleRateDivisor(mpu,MPU6050_DataRate_1KHz);
    uart_print_integer(USART1,error,10);
    uart_print(USART1,"\n");
	i2c_uart_print(USART1);	
	 if(error) return error;
 	
	// Config low pass filter 
	uart_print(USART1,"mpu_lpf:");
	error=mpu6050_set_lpf(mpu,MPU6050_BAND_260_HZ);
	uart_print_integer(USART1,error,10);
    uart_print(USART1,"\n");
	i2c_uart_print(USART1);	
	if(error) return error;

	// Configure High pass filter 
	uart_print(USART1,"mpu_hpf:");
	error=mpu6050_set_hpf(mpu,MPU6050_HIGHPASS_2_5_HZ);
	uart_print_integer(USART1,error,10);
    uart_print(USART1,"\n");
	i2c_uart_print(USART1);	
	if(error) return error;

   // Config accelerometer 
	uart_print(USART1,"mpu_accel_rng:");
	error=mpu6050_setAccelRange(mpu,Accel_Range);
	uart_print_integer(USART1,error,10);
    uart_print(USART1,"\n");
	i2c_uart_print(USART1);	
	if(error) return error;

	///Config gyroscope 
	uart_print(USART1,"mpu_gyro_rng:");
	error=mpu6050_setGyroRange(mpu,Gyro_Range);
  uart_print_integer(USART1,error,10);
  uart_print(USART1,"\n");
	i2c_uart_print(USART1);	
	if(error) return error;
  
 /* Return OK */
	return  MPU6050_OK; //I2C_OK; 
}
//--------------------------------------------------------------------------------------------------------
uint8_t mpu6050_reset(MPU6050_t* mpu)
{
  uint8_t error=0;
 
 error=i2c_write_7bit_base_byte_std(MPU6050_I2C,mpu->Address,MPU6050_PWR_MGMT_1, 0x00); // should be 0x80
 if(error) return error;
	_delay_ms(100);
  error=i2c_write_7bit_base_byte_std(MPU6050_I2C,mpu->Address,MPU6050_SIGNAL_PATH_RESET, 0x07); // should be0x80
	if(error) return error;
	_delay_ms(100);
	
 /* Return OK */
	return  MPU6050_OK; 
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
	return MPU6050_OK; //  or return I2C_OK;
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
	return MPU6050_OK; //  or return I2C_OK;

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
  uint8_t temp=0,error=0;
	/* Config gyroscope */
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
	return MPU6050_OK; //  or return I2C_OK;
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
	return MPU6050_OK; //  or return I2C_OK; 
}
//--------------------------------------------------------------------------------------------------------
uint8_t mpu6050_setClock(MPU6050_t* mpu,MPU6050_Clock_Select_t clock_select)
{
	
	/* Return OK */
	return MPU6050_OK; //  or return I2C_OK;
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
	return MPU6050_OK; //  or return I2C_OK;
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
	return MPU6050_OK; //  or return I2C_OK;
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
	return MPU6050_OK; //  or return I2C_OK;
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
	return MPU6050_OK; //  or return I2C_OK;
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
	return MPU6050_OK; //  or return I2C_OK;
}
//--------------------------------------------------------------------------------------------------------
uint8_t mpu6050_set_hpf(MPU6050_t* mpu,MPU6050_Accel_HPF_t bandwidth)
{
  uint8_t error=0,temp=0;
	error=i2c_read_7bit_base_byte_std(MPU6050_I2C, mpu->Address, MPU6050_ACCEL_CONFIG, &temp);
  if(error) return error;

	temp =  (temp & 0xf8)|(uint8_t)bandwidth;
	error=i2c_write_7bit_base_byte_std(MPU6050_I2C, mpu->Address,MPU6050_ACCEL_CONFIG, temp);
  if(error) return error;

	/* Return OK */
	return MPU6050_OK; //  or return I2C_OK;
}
//--------------------------------------------------------------------------------------------------------
uint8_t mpu6050_setInterruptPinPolarity(MPU6050_t* mpu,uint8_t active_low)
{

  uint8_t temp=0,error=0;
	error=i2c_read_7bit_base_byte_std(MPU6050_I2C,mpu->Address,MPU6050_INT_PIN_CFG, &temp);
  if(error) return error;
	temp = (temp & 0x7E) | (uint8_t)active_low << 7;
	error=i2c_write_7bit_base_byte_std(MPU6050_I2C, mpu->Address,MPU6050_INT_PIN_CFG, temp);
	if(error) return error;
	/* Return OK */
	return MPU6050_OK; //  or return I2C_OK;
}
//--------------------------------------------------------------------------------------------------------
uint8_t mpu6050_setInterruptPinLatch(MPU6050_t* mpu,uint8_t held)
{
  uint8_t temp=0,error=0;
	error=i2c_read_7bit_base_byte_std(MPU6050_I2C,mpu->Address,MPU6050_INT_PIN_CFG, &temp);
  if(error) return error;
	temp = (temp & 0xdf) | (uint8_t)held << 5;
	error=i2c_write_7bit_base_byte_std(MPU6050_I2C, mpu->Address,MPU6050_INT_PIN_CFG, temp);
	if(error) return error;

	/* Return OK */
	return MPU6050_OK; //  or return I2C_OK;
}
//--------------------------------------------------------------------------------------------------------
uint8_t mpu6050_setFsyncSampleOutput(MPU6050_t* mpu,MPU6050_Fsync_out_t fsync_output)
{
	/* Return OK */
	return MPU6050_OK; //  or return I2C_OK;
}
//--------------------------------------------------------------------------------------------------------
uint8_t mpu6050_setMotionInterrupt(MPU6050_t* mpu,uint8_t active)
{
  uint8_t temp=0,error=0;
	error=i2c_read_7bit_base_byte_std(MPU6050_I2C,mpu->Address,MPU6050_INT_ENABLE, &temp);
  if(error) return error;
	temp = (temp & 0xbf) | (uint8_t)active << 6;
	error=i2c_write_7bit_base_byte_std(MPU6050_I2C, mpu->Address,MPU6050_INT_ENABLE, temp);

	/* Return OK */
	return MPU6050_OK; //  or return I2C_OK;
	}
//--------------------------------------------------------------------------------------------------------
uint8_t mpu6050_setMotionDetectionThreshold(MPU6050_t* mpu,uint8_t thr)
{

  uint8_t error=0;
	error=i2c_write_7bit_base_byte_std(MPU6050_I2C, mpu->Address,MPU6050_MOT_THR, thr);
	if(error) return error;
	/* Return OK */
	return MPU6050_OK; //  or return I2C_OK;
}
//--------------------------------------------------------------------------------------------------------
uint8_t mpu6050_setMotionDetectionDuration(MPU6050_t* mpu,uint8_t dur)
{
  uint8_t error=0;
	error=i2c_write_7bit_base_byte_std(MPU6050_I2C, mpu->Address,MPU6050_MOT_THR, dur);
	if(error) return error;
	/* Return OK */
	return MPU6050_OK;
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
	return MPU6050_OK; //  or return I2C_OK;
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
	return MPU6050_OK; //  or return I2C_OK;
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
	return MPU6050_OK; //  or return I2C_OK;
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
	return MPU6050_OK; //  or return I2C_OK;
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
	return MPU6050_OK; //  or return I2C_NO_ERROR;
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
	return MPU6050_OK; //  or return I2C_NO_ERROR;
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
	return MPU6050_OK; //  or return I2C_OK;
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
	return MPU6050_OK; //  or return I2C_OK;
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
  return MPU6050_OK; //  or return I2C_OK;
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
	return MPU6050_OK; //  or return I2C_OK;
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
  return MPU6050_OK; //  or return I2C_OK;
}
//--------------------------------------------------------------------------------------------------------
uint8_t mpu6050_getMotionInterruptStatus(MPU6050_t* mpu,uint8_t *MotionStatus)
{
	uint8_t read,error=0;	
	/* Read interrupts status register */
  error=i2c_read_7bit_base_byte_std(MPU6050_I2C, mpu->Address, MPU6050_INT_STATUS, &read);
  if(error) return error;	
	
	*MotionStatus= (read & 0x40) >> 6;

	 /* Return OK */
  return MPU6050_OK; //  or return I2C_OK;
}
//--------------------------------------------------------------------------------------------------------
//********************************************************************************************
//
//   data manipulation  Methods
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
	
	mpu->Accel_X=0.0f;
  mpu->Accel_Y=0.0f;
	mpu->Accel_Z=0.0f;
	
	mpu->Gyro_X=0.0f;
	mpu->Gyro_Y=0.0f;
	mpu->Gyro_Z=0.0f;

	mpu->Temperature=0.0f;

}
//-------------------------------------------------------------------------------------------
void mpu6050_clear_Accelometer(MPU6050_t* mpu)
{
	uint8_t i=0;
 	for(i=0;i<MPU6050_RAW_ACCEL_LEN;i++)
 		mpu->data.Array[i+MPU6050_RAW_ACCEL_Base]=0;

 	mpu->Accelerometer_X=0;
 	mpu->Accelerometer_Y=0;
 	mpu->Accelerometer_X=0;
	mpu->Accel_X=0.0f;
  mpu->Accel_Y=0.0f;
	mpu->Accel_Z=0.0f;
}
//-------------------------------------------------------------------------------------------
void mpu6050_clear_Gyroscope(MPU6050_t* mpu)
{
	uint8_t i=0;
 	for(i=0;i<MPU6050_RAW_GYRO_LEN;i++)
 		mpu->data.Array[i+MPU6050_RAW_GYRO_Base]=0;

 	mpu->Gyroscope_X=0;
 	mpu->Gyroscope_Y=0;
 	mpu->Gyroscope_Z=0;
	mpu->Gyro_X=0.0f;
	mpu->Gyro_Y=0.0f;
	mpu->Gyro_Z=0.0f;

}
//-------------------------------------------------------------------------------------------
void mpu6050_clear_Temperature(MPU6050_t* mpu)
{
	mpu->data.temp_high=0;
	mpu->data.temp_low=0;
	mpu->Temperature=0.0f;
}
//-------------------------------------------------------------------------------------------
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
	mpu6050_clear_Accelometer(mpu);
	/* Read accelerometer data */
  error=i2c_read_7bit_base_nbyte_std(MPU6050_I2C,mpu->Address, MPU6050_ACCEL_XOUT_H, data, 6);
  if(error) return error;
	/* Format */
	mpu->Accelerometer_X = (int16_t)(data[0] << 8 | data[1]);	
	mpu->Accelerometer_Y = (int16_t)(data[2] << 8 | data[3]);
	mpu->Accelerometer_Z = (int16_t)(data[4] << 8 | data[5]);
	
	mpu->Accel_X=(float)mpu->Accelerometer_X * mpu->Acce_Mult;
	mpu->Accel_Y=(float)mpu->Accelerometer_Y * mpu->Acce_Mult;
	mpu->Accel_Z=(float)mpu->Accelerometer_Z * mpu->Acce_Mult;

	mpu->Accel_gr_X= mpu->Accel_X * SENSORS_GRAVITY_STANDARD;
	mpu->Accel_gr_Y= mpu->Accel_Y * SENSORS_GRAVITY_STANDARD;
	mpu->Accel_gr_Z= mpu->Accel_Z * SENSORS_GRAVITY_STANDARD;


	for(uint8_t i=0;i<MPU6050_RAW_ACCEL_LEN;i++)
	 mpu->data.Array[MPU6050_RAW_ACCEL_Base +i]=data[i];
 /* Return OK */
	return  MPU6050_OK; 
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
  mpu6050_clear_Gyroscope(mpu);

	/* Read accelerometer data */
  error=i2c_read_7bit_base_nbyte_std(MPU6050_I2C,mpu->Address, MPU6050_GYRO_XOUT_H, data, 6);
  if(error) return error;
	/* Format */
	mpu->Gyroscope_X = (int16_t)(data[0] << 8 | data[1]);	
	mpu->Gyroscope_Y = (int16_t)(data[2] << 8 | data[3]);
	mpu->Gyroscope_Z = (int16_t)(data[4] << 8 | data[5]);

	mpu->Gyro_X=(float)mpu->Gyroscope_X * mpu->Gyro_Mult;
	mpu->Gyro_Y=(float)mpu->Gyroscope_Y * mpu->Gyro_Mult;
	mpu->Gyro_Z=(float)mpu->Gyroscope_Z * mpu->Gyro_Mult;

	mpu->Gyro_rd_X= mpu->Gyro_X * SENSORS_DPS_TO_RADS;
	mpu->Gyro_rd_Y= mpu->Gyro_Y * SENSORS_DPS_TO_RADS;
	mpu->Gyro_rd_Z= mpu->Gyro_Z * SENSORS_DPS_TO_RADS;

	for(uint8_t i=0;i<MPU6050_RAW_GYRO_LEN;i++)
	 mpu->data.Array[MPU6050_RAW_GYRO_Base +i]=data[i];
		
 /* Return OK */
	return  MPU6050_OK; 
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
	mpu6050_clear_Temperature(mpu);
	/* Read accelerometer data */
  error=i2c_read_7bit_base_nbyte_std(MPU6050_I2C,mpu->Address,MPU6050_TEMP_H, data, 2);
  if(error) return error;
	/* Format */
	temp = (data[0] << 8 | data[1]);
	mpu->Temperature = (float)((int16_t)temp / (float)340.0 + (float)36.53);
	for(uint8_t i=0;i<MPU6050_RAW_TEMP_LEN;i++)
	 mpu->data.Array[MPU6050_RAW_TEMP_Base +i]=data[i];

 /* Return OK */
	return  MPU6050_OK; 
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
	
	int16_t temp ;
	uint8_t error=0; 
	mpu6050_clear_All(mpu);
	/* Read full raw data, 14bytes */
	error=i2c_read_7bit_base_nbyte_std(MPU6050_I2C, mpu->Address, MPU6050_ACCEL_XOUT_H, mpu->data.Array, MPU6050_RAW_ALL_LEN );
	if(error) return error;

	/* Format accelerometer data */
	mpu->Accelerometer_X = (int16_t)(mpu->data.Array[0] << 8 | mpu->data.Array[1]);	
	mpu->Accelerometer_Y = (int16_t)(mpu->data.Array[2] << 8 | mpu->data.Array[3]);
	mpu->Accelerometer_Z = (int16_t)(mpu->data.Array[4] << 8 | mpu->data.Array[5]);
 
 	mpu->Accel_X=(float)mpu->Accelerometer_X * mpu->Acce_Mult;
	mpu->Accel_Y=(float)mpu->Accelerometer_Y * mpu->Acce_Mult;
	mpu->Accel_Z=(float)mpu->Accelerometer_Z * mpu->Acce_Mult;

	mpu->Accel_gr_X= mpu->Accel_X * SENSORS_GRAVITY_STANDARD;
	mpu->Accel_gr_Y= mpu->Accel_Y * SENSORS_GRAVITY_STANDARD;
	mpu->Accel_gr_Z= mpu->Accel_Z * SENSORS_GRAVITY_STANDARD;
	
	/* Format gyroscope data */
	mpu->Gyroscope_X = (int16_t)(mpu->data.Array[8]  << 8 | mpu->data.Array[9]);
	mpu->Gyroscope_Y = (int16_t)(mpu->data.Array[10] << 8 | mpu->data.Array[11]);
	mpu->Gyroscope_Z = (int16_t)(mpu->data.Array[12] << 8 | mpu->data.Array[13]);

	mpu->Gyro_X=(float)mpu->Gyroscope_X * mpu->Gyro_Mult;
	mpu->Gyro_Y=(float)mpu->Gyroscope_Y * mpu->Gyro_Mult;
	mpu->Gyro_Z=(float)mpu->Gyroscope_Z * mpu->Gyro_Mult;

	mpu->Gyro_rd_X= mpu->Gyro_X * SENSORS_DPS_TO_RADS;
	mpu->Gyro_rd_Y= mpu->Gyro_Y * SENSORS_DPS_TO_RADS;
	mpu->Gyro_rd_Z= mpu->Gyro_Z * SENSORS_DPS_TO_RADS;

	/* Format temperature */
	temp = (mpu->data.Array[6] << 8 | mpu->data.Array[7]);
	mpu->Temperature = (float)((float)( (int16_t)temp) / (float)340.0f + (float)36.53);

	/* Return OK */
	return MPU6050_OK; //  or return I2C_OK;
}
//--------------------------------------------------------------------------------------------------------

uint8_t mpu6050_read(MPU6050_t* mpu,uint8_t acq_mode)
{
	
		switch(acq_mode)
		{

			case MPU_ACQ_ACC: 		return  mpu6050_read_Accelerometer(mpu);		
			case MPU_ACQ_GYR: 		return 	mpu6050_read_Gyroscope(mpu); 
			case MPU_ACQ_TEM: 		return 	mpu6050_read_Temperature(mpu); 

			case MPU_ACQ_ALL: 		 						
			case MPU_ACQ_ACC_GYR:  
			case MPU_ACQ_ACC_TEM:
			case MPU_ACQ_GYR_TEM:
			default:
					return 	mpu6050_read_All(mpu);
		}
}
//********************************************************************************************
//
//  uart Print and Display Methods
//
//********************************************************************************************
void mpu6050_uart_print(USART_TypeDef *uart,MPU6050_t* mpu,uint8_t acq_mode)
{
		uart_println (uart,"...............");
		switch(acq_mode)
		{

			case MPU_ACQ_ACC: 		mpu6050_uart_print_Accelometer(uart,mpu);	break;	
			case MPU_ACQ_GYR: 		mpu6050_uart_print_Gyroscope(uart,mpu);		break;
			case MPU_ACQ_TEM: 		mpu6050_uart_print_Temperature(uart,mpu);	break; 
			case MPU_ACQ_ACC_GYR: 
														mpu6050_uart_print_Accelometer(uart,mpu);
													  mpu6050_uart_print_Gyroscope(uart,mpu);		break;

			case MPU_ACQ_ACC_TEM:
														mpu6050_uart_print_Accelometer(uart,mpu);
														mpu6050_uart_print_Temperature(uart,mpu);	break; 
			case MPU_ACQ_GYR_TEM:
														mpu6050_uart_print_Gyroscope(uart,mpu);
														mpu6050_uart_print_Temperature(uart,mpu);	break; 
			 		 						
			case MPU_ACQ_ALL:
			default:
					mpu6050_uart_print_All(uart,mpu);
		}
		uart_println (uart,"...............");
}
//-------------------------------------------------------------------------------------------
void mpu6050_uart_print_All(USART_TypeDef *uart,MPU6050_t* mpu)
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
    uart_print(uart,"\n Accel ");
    uart_print(uart,"\t X:");
    uart_print_integer(uart,mpu->Accelerometer_X,10);
    uart_print(uart,"\t Y:");
    uart_print_integer(uart,mpu->Accelerometer_Y,10);
    uart_print(uart,"\t Z:");
    uart_print_integer(uart,mpu->Accelerometer_Z,10);
    uart_print(uart,"\n");
    uart_print(uart,"\t X:");
    uart_print_float(uart,mpu->Accel_X,2);
    uart_print(uart,"\t Y:");
    uart_print_float(uart,mpu->Accel_Y,2);
    uart_print(uart,"\t Z:");
    uart_print_float(uart,mpu->Accel_Z,2);
    uart_print(uart,"\n");
}
//-------------------------------------------------------------------------------------------
void mpu6050_uart_print_Gyroscope(USART_TypeDef *uart,MPU6050_t* mpu)
{
    uart_print(uart,"\n Gyro ");
    uart_print(uart,"\t X:");
    uart_print_integer(uart,mpu->Gyroscope_X,10);
    uart_print(uart,"\t Y:");
    uart_print_integer(uart,mpu->Gyroscope_Y,10);
    uart_print(uart,"\t Z:");
    uart_print_integer(uart,mpu->Gyroscope_Z,10);
    uart_print(uart,"\n");
    uart_print(uart,"\t X:");
    uart_print_float(uart,mpu->Gyro_X,2);
    uart_print(uart,"\t Y:");
    uart_print_float(uart,mpu->Gyro_Y,2);
    uart_print(uart,"\t Z:");
    uart_print_float(uart,mpu->Gyro_Z,2);
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
	uart_print(uart,"\t ACCEL_XOUT:0x");
	uart_print_integer(uart,t.word,16);

	t.byte.high=mpu->data.accel_y_high;
	t.byte.low=mpu->data.accel_y_low;
	uart_print(uart,"\t ACCEL_YOUT:0x");
	uart_print_integer(uart,t.word,16);

	t.byte.high=mpu->data.accel_z_high;
	t.byte.low=mpu->data.accel_z_low;
	uart_print(uart,"\t ACCEL_ZOUT:0x");
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
	uart_print(uart,"\t GYRO_XOUT:0x");
	uart_print_integer(uart,t.word,16);


	t.byte.high=mpu->data.gyro_y_high;
	t.byte.low=mpu->data.gyro_y_low;
	uart_print(uart,"\t GYRO_YOUT:0x");
	uart_print_integer(uart,t.word,16);

	t.byte.high=mpu->data.gyro_z_high;
	t.byte.low=mpu->data.gyro_z_low;
	uart_print(uart,"\t GYRO_ZOUT:0x");
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
		uart_print(uart,"):0x");
		uart_print_integer(uart,mpu->data.Array[i],16);
    	uart_print(uart,"\n");
		index++;
	}
	uart_print(uart,"\r\n\n");
}
//-------------------------------------------------------------------------------------------
//********************************************************************************************
//
//  lcd Print and Display Methods
//
//********************************************************************************************

//********************************************************************************************
//
//  Error Handling Methods
//
//********************************************************************************************
void mpu6050_error_handle(MPU6050_t* mpu)
{

}
//-------------------------------------------------------------------------------------------




/*


		// Wakeup MPU6050 
    uart_print(USART1,"mpu_rst:");
    error=mpu6050_reset(mpu);
	uart_print(USART1,"\t rst:");
    uart_print_integer(USART1,error,10);
    uart_print(USART1,"\n");
	 if(error) return error;
	 
	


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