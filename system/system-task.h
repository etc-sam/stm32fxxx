/**
 * @brief system-task.h
 *
 * @param student: Sameer Almaldein
 * @param ID: 679699
 * @param University TU-Chemnitz
 * @param Master : ASE(Automotive Software Engineering )
 */ 


#ifndef SYSTEM_TASK_H_
#define SYSTEM_TASK_H_


//********************************************************************************************
//
//  Pre-defined constants
//
//********************************************************************************************
//#define ADC_WAIT_TIMEOUT		100
//#define DISPLAY_WAIT_TIMEOUT 	15//
//#define GLCD_WAIT_TIMEOUT   	3000//
//#define INBUF_WAIT_TIMEOUT		8500
//#define BOOT_WAIT_TIMEOUT		3		// seconds
//#define USB_WAIT_TIMEOUT		8000

#define KEYPAD_WAIT_TIMEOUT		30000		//
#define MPU_WAIT_TIMEOUT		500000		//
#define KEYPAD_DEBOUNCE_TIMEOUT	3500	//
#define RTC_WAIT_TIMEOUT		100000

//********************************************************************************************
//
//  Pre-defined states 
//
//********************************************************************************************
//enum ADC_STATE{ADC_WAIT,ADC_READ,ADC_CLC,ADC_REST,ADC_STOP};
//enum USB_STATE{USB_WAIT,USB_READ};

//enum DISPLAY_STATE{DISP_WAIT,DISP_SHIFT,DISP_SIMAPHORE};
//enum GLCD_STATE{GLCD_WAIT,GLCD_SIMAPHORE,GLCD_RUN,GLCD_CMD_WR,GLCD_DATA_WR,GLCD_CMD_RD,GLCD_DATA_RD};

enum KEYPAD_STATE{KEYPAD_WAIT,KEYPAD_PSCAN,KEYPAD_DEBOUNCE,KEYPAD_SCAN,KEYPAD_PROCESS};
enum INBUF_STATE{INBUF_WAIT,INBUF_READ};
enum RTC_STATE{RTC_WAIT,RTC_RUN};

//enum TSTATUS{STARTUP=0,RUNTIME=1};
//********************************************************************************************
//
// system Task
//
//********************************************************************************************

#define SAMPLES_MAX_LEN	256

enum _MODE_t{_BOOT_UP,_OFF,_ON,_TRIGGER};

//********************************************************************************************
//
// global variables
//
//********************************************************************************************
 extern uint8_t keypad_state;
 extern uint32_t keypad_ticks;
 extern uint32_t keypad_debounce_cnt;
 
 extern uint8_t lcd_state;
 extern uint32_t lcd_ticks;
 
 extern uint8_t mpu_state;
 extern uint32_t mpu_ticks;
 extern uint8_t mpu_init_sucess;
 
 extern uint8_t pilot_state;
 extern uint32_t pilot_ticks;
  
 extern uint8_t rtc_state;
 extern uint32_t rtc_ticks;
 
//********************************************************************************************
//
// system Task
//
//********************************************************************************************
extern void rtc_task(void);
extern void uart_task(void);

extern void mpu6050_task(void);
extern void adc_task(void);


extern void keypad_task(void);
extern void lcd_task(void);
extern void pilot_task(void);
extern void input_task(void);




#endif /* SYSTEM-TASK_H_ */
