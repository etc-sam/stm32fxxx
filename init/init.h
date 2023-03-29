/**
 * @brief init.h
 *
 * @param student: Sameer Almaldein
 * @param ID: 679699
 * @param University TU-Chemnitz
 * @param Master : ASE(Automotive Software Engineering )
 */ 


#ifndef _INIT_H
#define _INIT_H

//********************************************************************************************
//
// including header  files
//
//********************************************************************************************
#include "stm32f10x.h"
 #include "stm32f10x_conf.h"
 #include "stm32f10x_it.h"
 
 #include "basic.h"
 #include "init-macro.h"
 #include "TIM.h"
 #include "uart.h"
 
 #include "i2c.h"
 #include "mpu6050.h"

 #include "lcd.h"
 #include "keypad.h"
 #include "system-task.h"
 #include "system.h"
//********************************************************************************************
//
// data structure
//
//********************************************************************************************

//********************************************************************************************
//
// Global variables 
//
//********************************************************************************************
extern uint32_t TimingDelay,BlinkTimingDelay;
extern uint8_t lcd_update, blink_update;
extern pilot_t pilots;
extern rly_t relays;

extern gpio_t blink_led;
extern gpio_t pilot_en;
extern gpio_t pilot_db[8];

extern gpio_t rly[6];
//********************************************************************************************
//
// Method protoypes
//
//********************************************************************************************


extern void blink_init(void);
extern void blink(void);

extern void pilot_init(void);
extern void pilot_write(uint8_t val);

extern void rly_init(void);
extern void rly_write(uint8_t val);

extern void disable_buffer();

extern void _delay_us(uint32_t val);
extern void _delay_ms(uint32_t val);



#endif /* End of _INIT_H*/
