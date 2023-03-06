/**
 * @brief system.h
 *
 * @param student: Sameer Almaldein
 * @param ID: 679699
 * @param University TU-Chemnitz
 * @param Master : ASE(Automotive Software Engineering )
 */ 

#ifndef _SYSTEM_H
#define _SYSTEM_H

//********************************************************************************************
//
// including header  files
//
//********************************************************************************************

//********************************************************************************************
//
// data structure
//
//********************************************************************************************
typedef union _pilo_t
{
	uint8_t val;
	struct
	{
		uint8_t pilot_0:1;
		uint8_t pilot_1:1;
		uint8_t pilot_2:1;
		uint8_t pilot_3:1;
		uint8_t pilot_4:1;
		uint8_t pilot_5:1;
		uint8_t pilot_6:1;
		uint8_t pilot_7:1;
	};
}pilot_t;

typedef union _rly_t
{
	uint8_t val;
	struct
	{
		uint8_t rly_0:1;
		uint8_t rly_1:1;
		uint8_t rly_2:1;
		uint8_t rly_3:1;
		uint8_t rly_4:1;
		uint8_t rly_5:1;
		uint8_t :2;
	};
}rly_t;

//********************************************************************************************
//
// Global variables 
//
//********************************************************************************************
extern uint32_t systemticks;
extern uint8_t is_tick;
extern minute_t logout_timeout;

extern uint8_t  src_address; 
extern uint8_t  dst_address; 
extern uint8_t  me_address ;
//********************************************************************************************
//
// Method protoypes
//
//********************************************************************************************


extern void system_init(void);
extern void system_run(void);
extern void system_ticks(void);
extern void system_rtc(void);



#endif /* _SYSTEM_H */