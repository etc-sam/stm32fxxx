/**
 * @brief uart-cmd.h
 *
 * @param student: Sameer Almaldein
 * @param ID: 679699
 * @param University TU-Chemnitz
 * @param Master : ASE(Automotive Software Engineering )
 */ 
#ifndef _UART_CMD_H
#define _UART_CMD_H

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


//********************************************************************************************
//
//    constants
//
//********************************************************************************************

//********************************************************************************************
//
//  data structures
//
//********************************************************************************************
//********************************************************************************************
//
// global variables
//
//********************************************************************************************

//********************************************************************************************
//
//  enum 
//
//********************************************************************************************
/**
 * @brief commands types theat can be send on the uart
 * 
 * @details list an enumerated numbers for some of supperted commands 
 *          to check/debug the functionality of the raspnet project @ Atmega
 * 
 * @param _    =0 changes the speed of blinking leds
 * @param _    =1 increases the speed delay of the blinking leds
 * @param _    =2 decreases the speed delay of the blinking leds
 * @param _   =3 returns information about the value of speed delay  
 * @param _    =4 returns the crc32 for a sequnce of bytes to debug crc32 function operation
 * @param _    =5 sends a message through uart from rasperpi to atmega to be sent as raspnet message
 * @param _    =6 reserved to receive a message for  future usage
 */
enum CMD_TYPES
{
  
  _MPU_STOP         =0, //!< MPU6050 Stop Command to STOP Monitoring
  _MPU_WHO_IAM      =1, //!< MPU6050 Command to check the Device ID 

  _MPU_INIT         =2, //!< MPU6050 init Command to initialize the Device
  _MPU_READ_REG     =3, //!< MPU6050 Read_reg Command to read any register in the memory map
  _MPU_WRITE_REG    =4, //!< MPU6050 write_reg Command to write any register in the memory map
  
  _MPU_READ_ALL     =5, //!< MPU6050 Read all Command all Accelerator , GYRO, Temp 
  _MPU_READ_ACCEL   =6, //!< MPU6050 Read Accelometer Command only Accelerator Sensor
  _MPU_READ_GYRO    =7, //!< MPU6050 Read GYroscope Command only Gyroscope Sensor
  _MPU_READ_TEMP    =8, //!< MPU6050 Read Temperature Command only temperature Sensor

  _MPU_INFO         =9, //!< MPU6050 Read internal register info setting related to accel,gyro,temp

};
 //********************************************************************************************
//
// Data Structure
//
//********************************************************************************************

//********************************************************************************************
//
//  Global  variables' declarations 
//
//********************************************************************************************



//********************************************************************************************
//
// Method protoypes
//
//********************************************************************************************


//********************************************************************************************
//
//  uart commands Prototype function
//
//********************************************************************************************

//! handles the whole message as if it is a correct command structure
extern void uart_handle_cmd(USART_TypeDef * usartx ,uint8_t * cmd,size_t cmd_len, uint8_t * data, size_t data_len);

//! handle frame received on the uart rx buffer 
extern  void uart_handle_frame(USART_TypeDef * usartx);

//! run command: force system to run data acquestion of MPU6050 sensors
extern void  uart_run_cmd_handle(USART_TypeDef * usartx);
//! halt command: force system to stop data acquestion of MPU6050 sensors
extern void  uart_hlt_cmd_handle(USART_TypeDef * usartx);

//! init command: initialize MPU6050 Module
extern void  uart_init_cmd_handle(USART_TypeDef * usartx);
//! info command: returns the current mpu6050 status
extern void  uart_info_cmd_handle(USART_TypeDef * usartx);
//! who command: returns the content of WHO_IAM register 
extern void  uart_who_cmd_handle(USART_TypeDef * usartx);

//! reset command: reset the module MPU6050 
extern void  uart_rst_cmd_handle(USART_TypeDef * usartx);

//! read command: read aspecific register or sensor in MPU6050 Module
extern void  uart_read_cmd_handle(USART_TypeDef * usartx,uint8_t * data, size_t data_len);

//! write register command: write to aspecific register in MPU6050 Module
extern void  uart_write_cmd_handle(USART_TypeDef * usartx,uint8_t * data, size_t data_len);

//! sample command: define the Sample rate divider MPU6050 Module  
extern uint8_t  uart_smpl_cmd_handle(USART_TypeDef * usartx,uint8_t * data, size_t data_len);

//!  range command: define the range of (Accel,gyro) in MPU6050 Module  
extern void  uart_rng_cmd_handle(USART_TypeDef * usartx,uint8_t * data, size_t data_len);

//!  clk command: define the clock source for MPU6050 Module  
extern void  uart_clk_cmd_handle(USART_TypeDef * usartx,uint8_t * data, size_t data_len);

//! lpf command: define the lpf  MPU6050 Module 
extern uint8_t  uart_lpf_cmd_handle(USART_TypeDef * usartx,uint8_t * data, size_t data_len);

//! hpf command: define the hpf  MPU6050 Module 
extern uint8_t  uart_hpf_cmd_handle(USART_TypeDef * usartx,uint8_t * data, size_t data_len);

//! test command: activate selft test for  MPU6050 Module 
extern void  uart_tst_cmd_handle(USART_TypeDef * usartx,uint8_t * data, size_t data_len);

//! cyc command: activate  cyclic data aqusation due to specific period  MPU6050 Module 
extern void  uart_cyc_cmd_handle(USART_TypeDef * usartx,uint8_t * data, size_t data_len);

//********************************************************************************************
//
// uart sub command command and frame handling definition
//
//********************************************************************************************
//! 
extern void uart_write_cmd_param_exe(USART_TypeDef * usartx,param_t p, uint8_t * reg_address, uint8_t * reg_val);

extern uint8_t uart_write_reg_exe(USART_TypeDef * usartx, MPU6050_t * mpu,uint8_t reg_address, uint8_t reg_val);

extern uint8_t uart_read_cmd_param_exe(USART_TypeDef * usartx,param_t p);
extern uint8_t uart_read_reg_exe(USART_TypeDef * usartx, MPU6050_t * mpu,uint8_t reg_address);
extern uint8_t uart_read_all_exe(USART_TypeDef * usartx,MPU6050_t * mpu);
extern uint8_t uart_read_accelerometer_exe(USART_TypeDef * usartx,MPU6050_t * mpu);
extern uint8_t uart_read_gyroscope_exe(USART_TypeDef * usartx,MPU6050_t * mpu);
extern uint8_t uart_read_temperature_exe(USART_TypeDef * usartx,MPU6050_t * mpu);




#endif /* End of _UART_CMD_H*/

