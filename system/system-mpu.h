/**
 * @brief system-mpu.h
 *
 * @param student: Sameer Almaldein
 * @param ID: 679699
 * @param University TU-Chemnitz
 * @param Master : ASE(Automotive Software Engineering )
 */ 


#ifndef SYSTEM_MPU_H_
#define SYSTEM_MPU_H_


//********************************************************************************************
//
//  Pre-defined constants
//
//********************************************************************************************

//********************************************************************************************
//
// Data structure
//
//********************************************************************************************
typedef union _mpu_flag_t
{
  uint8_t val;
  struct{
        uint8_t mot_accel_x:1;
        uint8_t mot_accel_y:1;
        uint8_t mot_accel_z:1;
        uint8_t mot_gyro_x:1;
        uint8_t mot_gyro_y:1;
        uint8_t mot_gyro_z:1;
        uint8_t :2;
        };
}mpu_flag_t;

//********************************************************************************************
//
// global variables
//
//********************************************************************************************
 extern uint32_t mpu_cycle;
 extern uint16_t mpu_sample_cnt;
 extern uint32_t mpu_time;
 extern uint8_t mpu_error; 
 extern uint8_t mpu_is_first_sample; 
 extern uint8_t mpu_init_sucess;
 extern mpu_sample_t cur_sample;
 extern mpu_sample_t pre_sample;
 
 
//********************************************************************************************
//
// MPU Methods
//
//********************************************************************************************
extern void save_sample(mpu_sample_t * sample, MPU6050_t * mpu);
extern void copy_sample(mpu_sample_t * src,mpu_sample_t * dest);
extern uint8_t compare_sample(mpu_sample_t * src,mpu_sample_t * dest);


extern void mpu_wait_handle(void);
extern void mpu_init_handle(USART_TypeDef *uart,MPU6050_t* mpu);
extern void mpu_acq_handle(USART_TypeDef *uart,MPU6050_t* mpu);
extern void mpu_read_handle(USART_TypeDef *uart,MPU6050_t* mpu);
extern void mpu_proc_handle(USART_TypeDef *uart,MPU6050_t* mpu);
extern void mpu_error_handle(USART_TypeDef *uart,MPU6050_t* mpu);



#endif /* SYSTEM-TASK_H_ */
