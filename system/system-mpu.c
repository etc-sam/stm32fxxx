/**
 * @brief system-task.c
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
//  global variables
//
//********************************************************************************************
uint32_t mpu_cycle=MPU_WAIT_TIMEOUT;
uint16_t mpu_sample_cnt=0;
uint32_t mpu_time=0;
uint8_t mpu_error=0;
uint8_t mpu_is_first_sample=0; 
uint8_t mpu_init_sucess=0;
 
mpu_sample_t cur_sample={0};
mpu_sample_t pre_sample={0};

//********************************************************************************************
//
//  static Methods prototype
//
//********************************************************************************************

//********************************************************************************************
//
//  Methods definition
//
//********************************************************************************************
void save_sample(mpu_sample_t * sample, MPU6050_t * mpu)
{
   sample->time_stamp=mpu_time;

  // integer values 
   sample->Accelerometer_nX=mpu->Accelerometer_nX;
   sample->Accelerometer_nY=mpu->Accelerometer_nY;
   sample->Accelerometer_nZ=mpu->Accelerometer_nZ;
   sample->Gyroscope_nX=mpu->Gyroscope_nX;
   sample->Gyroscope_nY=mpu->Gyroscope_nY;
   sample->Gyroscope_nZ=mpu->Gyroscope_nZ;

  // decimal values 
   sample->Accelerometer_fX=mpu->Accel_gr_X;
   sample->Accelerometer_fY=mpu->Accel_gr_Y;
   sample->Accelerometer_fZ=mpu->Accel_gr_Z;
   sample->Gyroscope_fX=mpu->Gyro_X;
   sample->Gyroscope_fY=mpu->Gyro_Y;
   sample->Gyroscope_fZ=mpu->Gyro_Z;
}
//-------------------------------------------------------------------------------------------
void copy_sample(mpu_sample_t * src,mpu_sample_t * dest)
{
   dest->time_stamp=src->time_stamp;

  // integer values 
   dest->Accelerometer_nX=src->Accelerometer_nX;
   dest->Accelerometer_nY=src->Accelerometer_nY;
   dest->Accelerometer_nZ=src->Accelerometer_nZ;
   dest->Gyroscope_nX=src->Gyroscope_nX;
   dest->Gyroscope_nY=src->Gyroscope_nY;
   dest->Gyroscope_nZ=src->Gyroscope_nZ;

  // decimal values 
   dest->Accelerometer_fX=src->Accelerometer_fX;
   dest->Accelerometer_fY=src->Accelerometer_fY;
   dest->Accelerometer_fZ=src->Accelerometer_fZ;
   dest->Gyroscope_fX=src->Gyroscope_fX;
   dest->Gyroscope_fY=src->Gyroscope_fY;
   dest->Gyroscope_fZ=src->Gyroscope_fZ;
}
//-------------------------------------------------------------------------------------------
uint8_t compare_sample(mpu_sample_t * current,mpu_sample_t * previous)
{
  mpu_flag_t flg;
  flg.val=0;
  if(mpu_settings.acq_sense!= MPU_ACQ_SENSE_GYR && mpu_settings.acq_sense!=MPU_ACQ_SENSE_GYR_TEM)
  { 
    // check acceleration
    if(current->Accelerometer_fX> (previous->Accelerometer_fX +mpu_settings.accel_thr ))
      flg.mot_accel_x=1;
    if(current->Accelerometer_fY> (previous->Accelerometer_fY +mpu_settings.accel_thr ))
      flg.mot_accel_y=1;
    if(current->Accelerometer_fZ> (previous->Accelerometer_fZ +mpu_settings.accel_thr ))
      flg.mot_accel_z=1;
  }

  // check Gyroscope
  if(mpu_settings.acq_sense!= MPU_ACQ_SENSE_ACC && mpu_settings.acq_sense!=MPU_ACQ_SENSE_ACC_TEM)
  {
    if(current->Gyroscope_fX > (previous->Gyroscope_fX +mpu_settings.gyro_thr ))
      flg.mot_gyro_x=1;
    if(current->Gyroscope_fY > (previous->Gyroscope_fY +mpu_settings.gyro_thr ))
      flg.mot_accel_y=1;
    if(current->Gyroscope_fZ >  (previous->Gyroscope_fZ +mpu_settings.gyro_thr ))
      flg.mot_accel_z=1;
  }
  return flg.val;
}
//-------------------------------------------------------------------------------------------

//********************************************************************************************
//
// MPU methods
//
//********************************************************************************************
void mpu_wait_handle(void)
{
   if(mpu_ticks>=mpu_cycle)
		{ 
			 if(mpu_init_sucess) mpu_state=MPU_READ;
			 else					       mpu_state=MPU_INIT;	
		} 
}
//----------------------------------------------------------------------------------------------
void mpu_init_handle(USART_TypeDef *uart,MPU6050_t* mpu)
{
	i2c_init_std(MPU6050_I2C,MPU6050_I2C_CLOCK,0x20);
	mpu_error=mpu6050_init((MPU6050_t *)&myMPU6050,mpu_settings.accel_range, mpu_settings.gyro_range);
	mpu_init_sucess=0;
	mpu_state=MPU_ERROR;
	if(mpu_error==I2C_OK)
	{
	  mpu_init_sucess=1;
	  mpu_state=MPU_READ;
	  pre_ticks=systemticks;
	  mpu_time=0;
    }
}
//----------------------------------------------------------------------------------------------
void mpu_acq_handle(USART_TypeDef *uart,MPU6050_t* mpu)
{
  if(mpu_sample_cnt< mpu_settings.max_sample_cnt)
	{
		mpu_read_handle(uart,mpu);	  	 
		if(mpu_error==I2C_OK)
		{
		  mpu_ticks=0;
		  mpu_state=MPU_WAIT;
		}
	}	
}
//----------------------------------------------------------------------------------------------
void mpu_read_handle(USART_TypeDef *uart,MPU6050_t* mpu)
{
	if(mpu_sample_cnt==0)
	{
		pre_ticks=systemticks;
		mpu_time=0;
		mpu_is_first_sample=1; 

	}
	mpu_time += (systemticks-pre_ticks)/100;
	pre_ticks=systemticks;
	mpu_error=mpu6050_read((MPU6050_t *)&myMPU6050,mpu_settings.acq_sense);
	mpu_state=MPU_ERROR;
	if(mpu_error==I2C_OK)
	{
	 mpu_sample_cnt++;
	 uart_print_integer(uart,mpu_sample_cnt,10);
	 uart_print (uart,"\t|");
	 uart_print_integer(uart,mpu_time,10);
	 mpu6050_uart_print(uart,(MPU6050_t *)&myMPU6050,mpu_settings.acq_sense,mpu_settings.acq_mode);
	 mpu_state=MPU_PROC;
	}
}
//----------------------------------------------------------------------------------------------
void mpu_proc_handle(USART_TypeDef *uart,MPU6050_t* mpu)
{
   mpu_flag_t result;
   result.val=0; 
    save_sample((mpu_sample_t*)&cur_sample,mpu);
  if(mpu_is_first_sample)
  {
    save_sample((mpu_sample_t*)&pre_sample,mpu);
    mpu_is_first_sample=0;
  }
  else
  {
     result.val=compare_sample((mpu_sample_t*)&cur_sample,(mpu_sample_t*)&pre_sample);
    if(result.val!=0)
    {
        uart_print (uart,"vibration detected betweent the time stamp:");
        uart_print_integer(uart,mpu_time,10);
        uart_print (uart,"  and sample no:");
        uart_print_integer(uart,mpu_sample_cnt,10);
         uart_print(uart,"\r\n");

        if(result.mot_accel_x)
          uart_print (uart,"vibration detected at ACCEL_X \n");
        if(result.mot_accel_y)
          uart_print (uart,"vibration detected at ACCEL_Y \n");
        if(result.mot_accel_z)
          uart_print (uart,"vibration detected at ACCEL_Z \n");

        if(result.mot_gyro_x)
          uart_print (uart,"vibration detected at GYRO_X \n");
        if(result.mot_gyro_y)
          uart_print (uart,"vibration detected at GYRO_Y \n");
        if(result.mot_gyro_z)
          uart_print (uart,"vibration detected at GYRO_Z \n");

         uart_print(uart,"\r\n");
    }
    copy_sample((mpu_sample_t*)&cur_sample,(mpu_sample_t*)&pre_sample);
  }
	mpu_ticks=0;
	mpu_state=MPU_WAIT;
}
//----------------------------------------------------------------------------------------------
/***/
void mpu_error_handle(USART_TypeDef *uart,MPU6050_t* mpu)
{
	uart_print(uart,"\t MPU-ER::");
  uart_print_integer(uart,mpu_error,10);
  uart_print(uart,"\n");
	i2c_uart_print(uart);			
	//mpu6050_error_handle((MPU6050_t *)&myMPU6050);
	mpu_init_sucess=0;
	mpu_ticks=0;
	mpu_state=MPU_WAIT;
}
//----------------------------------------------------------------------------------------------



