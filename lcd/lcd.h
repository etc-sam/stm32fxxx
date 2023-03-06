/**
 * @brief lcd.h
 *
 * @param student: Sameer Almaldein
 * @param ID: 679699
 * @param University TU-Chemnitz
 * @param Master : ASE(Automotive Software Engineering )
 */ 

#ifndef _LCD_8BIT_H
#define _LCD_8BIT_H
//********************************************************************************************
//
//  header  files
//
//********************************************************************************************

//********************************************************************************************
//
// LCD Constants
//
//********************************************************************************************
#define NB_ROW 		0x04 /* 2 display lines */
#define NB_COL 		0x14 /* 16 character per line  */

#define ROW0 		0x80 //first row
#define ROW1 		0xc0 //second row
#define ROW2		0x94 //
#define ROW3		0xd4 //
//********************************************************************************************
//
// Character LCD Commands
//
//********************************************************************************************
#define CMD_CLR   		0x01   //clear lcd command ---
#define CMD_HOME  		0x02   // return cursor to home

//display command for display on/off cursor on/off blink on/off
#define CMD_DISP			0x08
#define CUR_BLK    	        0x0f // cursor & display command
#define CUR_ON    	        0x0f // 0x0e cursor & display command
#define CUR_OFF 	        0x0c //cursor only off command

#define display_on_cursor_on_blink_on    0x0f  // display on, cursor on , blink on
#define display_on_cursor_on_blink_off   0x0E  // display on, cursor on , blink off
#define display_on_cursor_off_blink_off  0x0c  // display on, cursor off , blink off

// display control command shift left / right
#define DISP_SHL 		0x18   // display shift left command
#define DISP_SHR 		0x1c   //display shift right command

// cursor control command shift left / right
#define CUR_SHL   		0x10   //cursor shift left command
#define CUR_SHR  		0x14   //cursor shift right command

// entry mode command increment / decrement
#define entry_mode_dec		 0x04    // decrement and no display shift
#define entry_mode_inc		 0x06   // increment and no display shift

#define entry_mode_dec_shfit 0x05   // decrement and and display shift
#define entry_mode_inc_shift 0x07   // increment and and display shift

#define func8_2_10   0x3C //8-bit interface ,all rows,10*5 dots , 0x3c..0x3f
#define func8_2_7    0x38 //8-bit interface ,all rows,7*5 dots ,  0x38..0x3B
#define func8_1_10   0x34 //8-bit interface ,half rows,10*5 dots ,0x34..0x37
#define func8_1_7    0x30 //4-bit interface ,half rows,7*5 dots  ,0x30..0x33
#define func4_2_10   0x2C //4-bit interface ,all rows,10*5 dots , 0x2c..0x2f
#define func4_2_7    0x28 //4-bit interface ,all rows,7*5 dots ,  0x28..0x2B
#define func4_1_10   0x24 //4-bit interface ,half rows,10*5 dots, 0x24..0x27
#define func4_1_7    0x20 //4-bit interface ,half rows,7*5 dots , 0x20..0x23


#define DD_RAM 		 0X80 // DATA DISPLAY RAM COMMAND
#define CG_RAM 	     0X40 // character graphic RAM command
//********************************************************************************************
//
// special characters
//
//********************************************************************************************
#define rigth_arrow	 0x7E
#define left_arrow   0x7F
#define bold_black   0xff
#define deg			 0xdf
#define blank		 0x00
//********************************************************************************************
//
// character LCD Constant
//
//********************************************************************************************
#define BIT_MODE_4		0
#define BIT_MODE_8		1

#define ROW_FULL		1
#define ROW_HALF		0

#define RES_FULL		1
#define RES_HALF		0

#define CMD_REG			0
#define DAT_REG			1
//********************************************************************************************
//
// Struct definition
//
//********************************************************************************************
typedef union _GLCD_FLAG_t
{
	uint8_t val;

	struct
	{
		uint8_t AC0:1;
		uint8_t AC1:1;
		uint8_t AC2:1;
		uint8_t AC3:1;
		uint8_t AC4:1;
		uint8_t AC5:1;
		uint8_t AC6:1;
		uint8_t BF:1;

	};

}GLCD_FLAG_t;

typedef struct _coordinate_t{
	uint8_t x;
	uint8_t y;
} coordinate_t;

#define LCD_OPTION_LEN	2

typedef union _lcd_options_t
{
	uint8_t Array[LCD_OPTION_LEN];
	uint16_t word;
	struct
	{
	 uint8_t entery_mode:1;	  // {1: Entery mode increment, 0: Entery mode decrement}
	 uint8_t resolution:1;    // {1: 10*5 dotsresolution, 0:7*5 dots }
	 uint8_t row_mode:1;	  // {1:full row,0:half row}
	 uint8_t bit_mode:1;      // {1:8bit ,0:4bit}
	 uint8_t inverted:1;      // {1: inverted, 0:not inverted}
	 uint8_t cursor_on:1;     // {1:cursor on, 0: cursor off}
	 uint8_t cursor_shift:1;  // {1:cursor shift right, 0: cursor shift left}
	 uint8_t display_shift:1; // {1:display shift right, 0: shift left}
	 uint8_t mux_bus:1;		  // define if the lcd bus is shared with other peripherals
	 uint8_t  res:7;
	};

}lcd_options_t;

//********************************************************************************************
//
//  Macros  and defines
//
//********************************************************************************************

//********************************************************************************************
//
//  Data Sructures
//
//********************************************************************************************
//********************************************************************************************
//
//  Global variables
//
//********************************************************************************************
extern const unsigned char bcd_tbl[];
extern const uint8_t lcd_line_cnt_max;
extern const uint8_t lcd_col_cnt_max;
extern volatile uint8_t lcd_buf[2][16];

extern coordinate_t lcd_coord;
extern lcd_options_t lcd_options;
extern uint8_t lcd_line_cnt;
extern uint8_t lcd_col_cnt;
extern GLCD_FLAG_t lcd_flag;

extern gpio_t lcd_db[8];
extern gpio_t lcd_rs;
extern gpio_t lcd_en;
//********************************************************************************************
//
//  extern Methods
//
//********************************************************************************************
extern void lcd_init(void);
extern void lcd_refresh(void);

// general command
extern void lcd_clear();
extern void lcd_cursor_home();
extern void lcd_cursor_on();
extern void lcd_cursor_off();
extern void lcd_cursor_blink();
extern void lcd_cursor_shift_left();
extern void lcd_cursor_shift_right();
extern void lcd_display_shift_left();
extern void lcd_display_shift_right();
extern void lcd_entery_mode_increment();
extern void lcd_entery_mode_decrement();

extern void lcd_set_display_cursor(uint8_t display, uint8_t cursor,uint8_t blink);
extern void lcd_set_line(uint8_t index);
extern void lcd_clear_line(uint8_t index);
extern void lcd_goto_xy(uint8_t x,uint8_t y);
extern void lcd_blank_line(uint8_t offest);
extern void lcd_init_cgram(uint8_t * pattern,uint8_t num);
extern void lcd_print_cgram(uint8_t x,uint8_t y,uint8_t pattern);

//uint8_t is_busy();
//uint8_t get_AC();

// text mode methods
extern void lcd_write_8bit(uint8_t val);
extern void lcd_write_16bit(uint16_t val);
extern void lcd_write_bcd_8bit(uint8_t val);
extern void lcd_write_bcd_16bit(uint16_t val);
extern void lcd_write_num(uint32_t val,uint8_t base);
extern void lcd_write_hex(uint32_t val);
extern void lcd_write_octal(uint32_t val);
extern void lcd_write_int(uint32_t val);
extern void lcd_write_bin(uint32_t val);

// special write methods for print method
extern size_t lcd_write(uint8_t b);
extern size_t lcd_write_array(const uint8_t *buffer, size_t size);
extern size_t lcd_write_str(const char *buffer, size_t size);
extern size_t lcd_write_cstr(const char *str);

// special printing methods new ones based on write
extern size_t lcd_print_array(uint8_t buf[],uint8_t len);

//print text
extern size_t lcd_print_ch(char c);
extern size_t lcd_print(const char *str);
extern size_t lcd_print_xy(uint8_t x,uint8_t y,const char * str);
//size_t lcd_print(const String &s);
//size_t print(uint8_t x,uint8_t y,const String &s);

// print 8-bit integers both signed and unsigned from 0 .. up to 0xff
extern size_t lcd_print_uint8(uint8_t n, int base);
extern size_t lcd_print_uint8_xy(uint8_t x,uint8_t y,uint8_t n,int base);
extern size_t lcd_print_uint8_str(const char * buf,uint8_t n,int base);
extern size_t lcd_print_uint8_xy_str(uint8_t x,uint8_t y,const char * buf,uint8_t n,int base);

extern size_t lcd_print_int8(int8_t n, int base);
extern size_t lcd_print_int8_xy(uint8_t x,uint8_t y,int8_t n,int base);
extern size_t lcd_print_int8_str(const char * buf,int8_t n,int base);
extern size_t lcd_print_int8_xy_str(uint8_t x,uint8_t y,const char * buf,int8_t n,int base);


// print 16-bit integers both signed and unsigned from 0 .. up to 0xffff

extern size_t lcd_print_uint16(uint16_t n, int base);
extern size_t lcd_print_uint16_xy(uint8_t x,uint8_t y,uint16_t n,int base);
extern size_t lcd_print_uint16_str(const char * buf,uint16_t n,int base);
extern size_t lcd_print_uint16_xy_str(uint8_t x,uint8_t y,const char * buf,uint16_t n,int base);

extern size_t lcd_print_int16(int16_t n, int base);
extern size_t lcd_print_int16_xy(uint8_t x,uint8_t y,int16_t n,int base);
extern size_t lcd_print_int16_str(const char * buf,int16_t n,int base);
extern size_t lcd_print_int16_xy_str(uint8_t x,uint8_t y,const char * buf,int16_t n,int base);

// print 32-bit integers both signed and unsigned from 0 .. up to 0xff ff ff ff

extern size_t lcd_print_uint32(uint32_t n, int base);
extern size_t lcd_print_uint32_xy(uint8_t x,uint8_t y,uint32_t n,int base);
extern size_t lcd_print_uint32_str(const char * buf,uint32_t n,int base);
extern size_t lcd_print_uint32_xy_str(uint8_t x,uint8_t y,const char * buf,uint32_t n,int base);

extern size_t lcd_print_int32(int32_t n, int base );
extern size_t lcd_print_int32_xy(uint8_t x,uint8_t y,int32_t n,int base);
extern size_t lcd_print_int32_str(const char * buf,int32_t n,int base);
extern size_t lcd_print_int32_xy_str(uint8_t x,uint8_t y,const char * buf,int32_t n,int base);

// print 64-bit integers both signed and unsigned from 0 .. up to 0xff ff ff ff ff ff ff ff

extern size_t lcd_print_uint64(uint64_t n, int base);
extern size_t lcd_print_uint64_xy(uint8_t x,uint8_t y,uint64_t n,int base);
extern size_t lcd_print_uint64_str(const char * buf,uint64_t n,int base);
extern size_t lcd_print_uint64_xy_str(uint8_t x,uint8_t y,const char * buf,uint64_t n,int base);

extern size_t lcd_print_int64(int64_t n, int base);
extern size_t lcd_print_int64_xy(uint8_t x,uint8_t y,int64_t n,int base);
extern size_t lcd_print_int64_str(const char * str,int64_t n,int base);
extern size_t lcd_print_int64_xy_str(uint8_t x,uint8_t y,const char * str,int64_t n,int base);

// float and double: floating point numbers
extern size_t lcd_print_double(double n, int digits);
extern size_t lcd_print_double_xy(uint8_t x,uint8_t y,double n, int digits);
extern size_t lcd_print_double_str(const char * str,double n, int digits);
extern size_t lcd_print_double_xy_str(uint8_t x,uint8_t y,const char * str,double n, int digits);


// print real
extern void lcd_print_real(real_t t);
extern void lcd_print_real_str(const char * buf,real_t t);
extern void lcd_print_real_xy(uint8_t x,uint8_t y,real_t t);
extern void lcd_print_real_xy_str(uint8_t x,uint8_t y,const char * buf,real_t t);
extern void lcd_print_ureal(ureal_t t);
extern void lcd_print_ureal_str(const char * buf,ureal_t t);
extern void lcd_print_ureal_xy(uint8_t x,uint8_t y,ureal_t t);
extern void lcd_print_ureal_xy_str(uint8_t x,uint8_t y,const char * buf,ureal_t t);

// print  time& date related methods
extern void lcd_print_minute(minute_t p);
extern void lcd_print_minute_str(const char * buf,minute_t p);
extern void lcd_print_minute_xy(uint8_t x,uint8_t y,minute_t p);
extern void lcd_print_minute_xy_str(uint8_t x,uint8_t y,const char * buf,minute_t p);

extern void lcd_print_hour(hour_t p);
extern void lcd_print_hour_str(const char * buf,hour_t p);
extern void lcd_print_hour_xy(uint8_t x,uint8_t y,hour_t p);
extern void lcd_print_hour_xy_str(uint8_t x,uint8_t y,const char * buf,hour_t p);

extern void lcd_print_period(period_t p);
extern void lcd_print_period_str(const char * buf,period_t p);
extern void lcd_print_period_xy(uint8_t x,uint8_t y,period_t p);
extern void lcd_print_period_xy_str(uint8_t x,uint8_t y,const char * buf,period_t p);

extern void lcd_print_ext_period(ext_period_t p);
extern void lcd_print_ext_period_str(const char * buf,ext_period_t p);
extern void lcd_print_ext_period_xy(uint8_t x,uint8_t y,ext_period_t p);
extern void lcd_print_ext_period_xy_str(uint8_t x,uint8_t y,const char * buf,ext_period_t p);

extern void lcd_print_time(_time_t p);
extern void lcd_print_time_str(const char * buf,_time_t p);
extern void lcd_print_time_xy(uint8_t x,uint8_t y,_time_t p);
extern void lcd_print_time_xy_str(uint8_t x,uint8_t y,const char * buf,_time_t p);

extern void lcd_print_date(date_t p);
extern void lcd_print_date_str(const char * buf,date_t p);
extern void lcd_print_date_xy(uint8_t x,uint8_t y,date_t p);
extern void lcd_print_date_xy_str(uint8_t x,uint8_t y,const char * buf,date_t p);

extern void lcd_print_datetime(datetime_t p);
extern void lcd_print_datetime_str(const char * buf,datetime_t p);
extern void lcd_print_datetime_xy(uint8_t x,uint8_t y,datetime_t p);
extern void lcd_print_datetime_xy_str(uint8_t x,uint8_t y,const char * buf,datetime_t p);


// print with generic format
extern void lcd_printf(const char * fmt,...);
extern void lcd_printf_xy(uint8_t x,uint8_t y,const char * fmt,...);

  
//extern coordinate_t get_xy(){return coord;}
//extern uint8_t get_lines_cnt()const {return line_cnt;}
//extern uint8_t get_colums_cnt()const{return col_cnt;}


#endif /* _LCD_8BIT_H  */


