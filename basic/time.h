/**
 * @brief time.c
 *
 * @param student: Sameer Almaldein
 * @param ID: 679699
 * @param University TU-Chemnitz
 * @param Master : ASE(Automotive Software Engineering )
 */ 


#ifndef _TIME_H_
#define _TIME_H_


typedef uint8_t second_t;

#define  MIN_LEN		2
typedef union _min_t
{
	uint8_t Array[MIN_LEN];
	uint16_t val;
	struct
	{
		uint8_t sec;
		uint8_t min;
	};
}minute_t;

#define  HOUR_LEN		2
typedef union _hour_t
{
	uint8_t Array[HOUR_LEN];
	uint16_t val;
	struct
	{
		uint8_t minute;
		uint8_t hour;
	};
}hour_t;

#define  EXTENDED_PERIOD_LEN		3
typedef union _ext_period_t
{
	uint8_t Array[EXTENDED_PERIOD_LEN];
	struct
	{
		uint8_t second;
		uint8_t minute;
		uint8_t hour;

	};
}ext_period_t;

#define  PERIOD_LEN		2
typedef union _period_t
{
	uint8_t Array[PERIOD_LEN];
	uint16_t val;
	struct
	{
		uint8_t minute;
		uint8_t hour;
	};
}period_t;

#define  TIME_LEN		4
typedef union _time_t
{
	uint8_t Array[TIME_LEN];
	uint32_t val;
	struct
	{
		uint8_t sec;
		uint8_t minute;
		uint8_t hour;
		uint8_t am_pm_mode; // 0:none , 1: am ,2:pm
	};
}_time_t;

#define  DATE_LEN		4
typedef union _date_t
{
	uint8_t Array[DATE_LEN];
	struct
	{
		uint16_t year;
		uint8_t month;
		uint8_t day;

	};
}date_t;

#define  DATETIME_LEN	8

typedef union _datetime_t
{
	uint8_t Array[DATETIME_LEN];
	struct
	{
		_time_t time;
		date_t date;
	};

}datetime_t;
//********************************************************************************************
//
// extern variables
//
//********************************************************************************************

//********************************************************************************************
//
// Prototype function
//
//********************************************************************************************
extern void _decrment(uint8_t *p, uint8_t len);

extern void minute_dec(minute_t* p);
extern void hour_dec(period_t* p);
extern void period_dec(period_t* p);
extern void ext_period_dec(ext_period_t* p);
extern void time_dec(_time_t* p);

extern uint8_t _timeout(uint8_t *p,uint8_t len);
extern uint8_t minute_timeout(minute_t* p);
extern uint8_t period_timeout(period_t* p);
extern uint8_t ext_period_timeout(ext_period_t* p);
extern uint8_t time_timeout(_time_t* p);



#endif /* _TIME_H_ */
