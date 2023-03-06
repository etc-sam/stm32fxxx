/**
 * @brief lcd.c
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
// Global variables
//
//********************************************************************************************
const unsigned char bcd_tbl[]="0123456789ABCDEF";

const uint8_t lcd_line_cnt_max=4;
const uint8_t lcd_col_cnt_max=16;

uint8_t lcd_line_cnt;
uint8_t lcd_col_cnt;
coordinate_t lcd_coord;
lcd_options_t lcd_options;
GLCD_FLAG_t lcd_flag;

volatile uint8_t lcd_buf[2][16]={0};

//************************************************************
//
// lcd  gpio pins
//
//************************************************************
gpio_t lcd_db[8]={
{GPIOA,7},   // lcd_db0=PA7
{GPIOA,6},   // lcd_db0=PA6
{GPIOA,5},   // lcd_db0=PA5
{GPIOA,4},   // lcd_db0=PA4
{GPIOA,3},   // lcd_db0=PA3
{GPIOA,2},   // lcd_db0=PA2   
{GPIOA,1},   // lcd_db0=PA1
{GPIOA,0},   // lcd_db0=PA0
 };
gpio_t lcd_rs={GPIOB,1};    // lcd_rs=PB1
gpio_t lcd_en={GPIOB,0};    // lcd_db0=PB0

//************************************************************
//
// static lcd  methods prototypes
//
//************************************************************
static void lcd_port_pinmode_in(void);
static void lcd_port_pinmode_out(void);
static void lcd_port_write_byte(uint8_t b);
static uint8_t lcd_port_read_byte(void);

static void lcd_rs_pinmode_in(void);
static void lcd_rs_pinmode_out(void);
static void lcd_rs_clear(void);
static void lcd_rs_set(void);

static void lcd_en_pinmode_in(void);
static void lcd_en_pinmode_out(void);

static void lcd_en_clear(void);
static void lcd_en_set(void);



//************************************************************
//
//  static external Methods
//
//************************************************************
static uint8_t lcd_read_busy(void);			//  read flag register
static uint8_t lcd_read_data(void);    		// read a data from lcd
static void lcd_write_data(uint8_t data);   // write to data register
static void lcd_write_cmd(uint8_t cmd);		// write a command
static void lcd_write_byte(uint8_t byte);	// read/write a byte
static uint8_t lcd_read_byte(void);			// read/write a byte

// special string to integer
static size_t lcd_print_as_number(unsigned long long n, uint8_t base);
static size_t lcd_print_as_Float(double n, uint8_t digits);

//************************************************************
//
// static lcd  methods
//
//************************************************************
void lcd_port_pinmode_in(void)
{
	
	for (uint8_t i=0;i<8;i++)
	{
		//gpio_pinmode(lcd_db[i],GPIO_Mode_IPU,0);             //db[i].pinmode(GPIO_Mode_IPU);
        //lcd_db[i].port->ODR|= (uint16_t)(1<<lcd_db[i].pin);  //db[i].pull_up();

        //gpio_pin_mode(lcd_db[i],GPIO_MODE_IN_PUPD);
        gpio_in_pullup(lcd_db[i]);


	}	
}
//-----------------------------------------------------------------------
void lcd_port_pinmode_out(void)
{
	// Make GLCD Port as a Digital Output
    for(uint8_t i=0;i<8;i++)    
    //gpio_pinmode(lcd_db[i],GPIO_Mode_Out_PP,GPIO_Speed_2MHz);
    gpio_pin_mode(lcd_db[i],GPIO_MODE_OUT_PP_2MHZ);  
}
//-----------------------------------------------------------------------
void lcd_port_write_byte(uint8_t val)
{

 for(uint8_t i=0;i<8;i++)
 {
  if(bit_is_set(val,i))
	  gpio_set(lcd_db[i]);  //GPIO_SetBits(lcd_db[i].port,(uint32_t)(1<<lcd_db[i].pin)); 
  else
	  gpio_clear(lcd_db[i]);//GPIO_ResetBits(lcd_db[i].port,(uint32_t)(1<<lcd_db[i].pin)); 
  }
 
}
//-----------------------------------------------------------------------
uint8_t lcd_port_read_byte(void)
{
   uint8_t val=0;
   uint8_t i=0;
   
	for (i=0;i<8;i++)
	{
		//GPIO_ReadInputDataBit(lcd_db[i].port,(uint32_t)(1<<lcd_db[i].pin)))		
		if (gpio_get(lcd_db[i]))  
		sbit(val,i);
		else
		cbit(val,i);
	}	
	return val;
}
//-----------------------------------------------------------------------
void lcd_rs_pinmode_in(void)
{
    //gpio_pinmode(lcd_rs,GPIO_Mode_IPU,0);
    gpio_in_pullup(lcd_rs);    
}
//-----------------------------------------------------------------------
void lcd_rs_pinmode_out(void)
{
   //gpio_pinmode(lcd_rs,GPIO_Mode_Out_PP,GPIO_Speed_2MHz);
   gpio_pin_mode(lcd_rs,GPIO_MODE_OUT_PP_2MHZ); 
}
//-----------------------------------------------------------------------
void lcd_rs_clear(void)
{
   gpio_clear(lcd_rs);//GPIO_ResetBits(lcd_rs.port,(uint32_t)(1<<lcd_rs.pin));
}
//-----------------------------------------------------------------------
void lcd_rs_set(void)
{
    gpio_set(lcd_rs);//GPIO_SetBits(lcd_rs.port,(uint32_t)(1<<lcd_rs.pin));
}
//-----------------------------------------------------------------------
void lcd_en_pinmode_in(void)
{
   //gpio_pinmode(lcd_en,GPIO_Mode_IPU,0);
   gpio_in_pullup(lcd_en); 
}
//-----------------------------------------------------------------------
void lcd_en_pinmode_out(void)
{
  //gpio_pinmode(lcd_en,GPIO_Mode_Out_PP,GPIO_Speed_2MHz);
  gpio_pin_mode(lcd_en,GPIO_MODE_OUT_PP_2MHZ);
}
//-----------------------------------------------------------------------
void lcd_en_clear(void)
{
   gpio_clear(lcd_en); //GPIO_ResetBits(lcd_en.port,(uint32_t)(1<<lcd_en.pin));
}
//-----------------------------------------------------------------------
void lcd_en_set(void)
{
  gpio_set(lcd_en);  //GPIO_SetBits(lcd_en.port,(uint32_t)(1<<lcd_en.pin));
}
//-----------------------------------------------------------------------
uint8_t lcd_read_busy()
{
 // instruction mode
	lcd_rs_clear();		// rs.clear();
 // read a byte from control register
  lcd_flag.val= lcd_read_byte();
 return lcd_flag.val;
}
//--------------------------------------------------------------------------------------------
uint8_t lcd_read_data()
{
  uint8_t val=0;
 // select Data mode
   lcd_rs_set(); // #rs.set();
 // read Dummy byte
  lcd_read_byte();
 // select Data mode
  lcd_rs_set(); // #rs.set();
 // read a data byte
  val= lcd_read_byte();
 return val;
}
//--------------------------------------------------------------------------------------------
uint8_t lcd_read_byte(void)
{
  uint8_t val=0;

 //set LCD port as an input port
  lcd_port_pinmode_in();

  // select read operation on GLCD
	//rw.set();

  //enable lcd to read
   lcd_en_set();	//en.set();
   // wait dummy cycles before read

	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");
    
    _delay_us(1);

	// Read a value to GLCD Port
	  val=lcd_port_read_byte();

	// end glcd to read operation
	 lcd_en_clear(); //en.clear();

	return val;
}
//--------------------------------------------------------------------------------------------
void lcd_write_cmd(uint8_t cmd)
{
	//while(is_busy());
	// command register select
	lcd_rs_clear();	//rs.clear();
	// write a command byte
	lcd_write_byte(cmd);
	_delay_us(100);
    //osalThreadDelayMilliseconds(2); //_delay_ms(2);
}
//--------------------------------------------------------------------------------------------
void  lcd_write_data(uint8_t data)
{
 //while(is_busy());
 // Data Select register
  lcd_rs_set();	//rs.set();
 // write a data byte
  lcd_write_byte(data);
 _delay_us(100);

  lcd_coord.x++;
  lcd_coord.x=lcd_coord.x%lcd_col_cnt;
}
//--------------------------------------------------------------------------------------------
void lcd_write_byte(uint8_t val)
{

 // Make LCD Port as a Digital Output
	lcd_port_pinmode_out();
 // select write operation on GLCD
	// rw.clear();

// Put value to GLCD Port
    lcd_port_write_byte(val);

 // enable glcd to write
	lcd_en_set(); //en.set();
    _delay_us(1);
	asm("nop");
	asm("nop");
	asm("nop");
	asm("nop");

	// end glcd  write operation
	lcd_en_clear(); //en.clear();

}
//--------------------------------------------------------------------------------------------
//********************************************************************************************
//
//  basic general commands
//
//********************************************************************************************
void lcd_clear()
{
	lcd_write_cmd(CMD_CLR);
	_delay_ms(3);
}
//-------------------------------------------------------------------------
void lcd_cursor_home()
{
	lcd_write_cmd(CMD_HOME);
}
//-------------------------------------------------------------------------
void lcd_cursor_on()
{
	lcd_write_cmd(display_on_cursor_on_blink_off);
}
//-------------------------------------------------------------------------
void lcd_cursor_off()
{
  lcd_write_cmd(display_on_cursor_off_blink_off);
}
//-------------------------------------------------------------------------
void lcd_cursor_blink()
{
   lcd_write_cmd(display_on_cursor_on_blink_on);
}
//-------------------------------------------------------------------------
void lcd_cursor_shift_left()
{
	lcd_write_cmd(CUR_SHL);
}
//-------------------------------------------------------------------------
void lcd_cursor_shift_right()
{
	lcd_write_cmd(CUR_SHR);
}
//-------------------------------------------------------------------------
void lcd_display_shift_left()
{
	lcd_write_cmd(DISP_SHL);
}
//-------------------------------------------------------------------------
void lcd_display_shift_right()
{
	lcd_write_cmd(DISP_SHR);
}
//-------------------------------------------------------------------------
void lcd_entery_mode_increment()
{
	lcd_write_cmd(entry_mode_inc);
}
//-------------------------------------------------------------------------
void lcd_entery_mode_decrement()
{
	lcd_write_cmd(entry_mode_dec);
}
//-------------------------------------------------------------------------
void lcd_set_display_cursor(uint8_t display, uint8_t cursor,uint8_t blink)
{
	BYTE_BITS cmd;
	cmd.byte=CMD_DISP;
	if(display)
	cmd.bit2=1;
	if(cursor)
	cmd.bit1=1;
	if(blink)
	cmd.bit0=1;
	lcd_write_cmd(cmd.byte);
}
//--------------------------------------------------------------------------------------------
//************************************************************
//
// extern lcd  methods
//
//************************************************************
void lcd_init()
{
	// initiate coordinates
	lcd_coord.x=0;
	lcd_coord.y=0;
	lcd_line_cnt=2;
    lcd_col_cnt=16;

	// lcd refresh
	lcd_refresh();
	// clear lcd
	lcd_clear();

	lcd_goto_xy(0,0);
}
//--------------------------------------------------------------------------------------------
void lcd_refresh(void)
{
 // PORTs initiate Direction
 //rw.pinmode(PIN_OUTPUT);
 lcd_rs_pinmode_out();	 	 //rs.pinmode(GPIO_Mode_Out_PP,GPIO_Speed_2MHz);
 lcd_en_pinmode_out(); 		 //en.pinmode(GPIO_Mode_Out_PP,GPIO_Speed_2MHz);
 // 8-bit operation and basic instruction set
 lcd_write_cmd(func8_2_10);
 //_delay_us(100);

 // 8-bit operation and basic instruction set
 lcd_write_cmd(func8_2_10);
 //_delay_us(200);

 // display on , cursor off, blink off
  lcd_write_cmd(display_on_cursor_off_blink_off);
 //	_delay_us(100);

 // entry mode increment and no display shift
  lcd_write_cmd(entry_mode_inc);
 //	_delay_us(100);

 // 8-bit operation and basic instruction set
  lcd_write_cmd(func8_2_10);
}
//--------------------------------------------------------------------------------------------
 uint8_t lcd_is_busy()
 {
  // read busy flag and address	counter
  lcd_read_busy();
  if(lcd_flag.BF)
	 return 1;
  return 0;
 }
 //--------------------------------------------------------------------------------------------
 uint8_t lcd_get_AC()
 {
   uint8_t val=0;
  // read busy flag and address	counter
	val=lcd_read_busy() &0x7f;
   return val;
 }
 //--------------------------------------------------------------------------------------------
 //********************************************************************************************
//
// text mode general methods ......
//
//********************************************************************************************
void lcd_set_line(uint8_t index)
{

}
//--------------------------------------------------------------------------------------------
void lcd_clear_line(uint8_t index)
{

}
//--------------------------------------------------------------------------------------------
void lcd_goto_xy(uint8_t x,uint8_t y)
{
 uint8_t cmd=0;
 lcd_coord.y=y%lcd_line_cnt;
 switch(lcd_coord.y)
 {
	 case 0: cmd=ROW0;	break;
	 case 1: cmd=ROW1;	break;
	 case 2: cmd=ROW2;	break;
	 case 3: cmd=ROW3;	break;
 }
 lcd_coord.x=x%lcd_col_cnt;
 cmd+=lcd_coord.x;
 lcd_write_cmd(cmd);
}
//--------------------------------------------------------------------------------------------
void lcd_write_8bit(uint8_t val)
{
	uint8_t temp=val>>4;
	temp&=0x0f;
	lcd_write_data(bcd_tbl[temp]);
	temp=val&0x0f;
	lcd_write_data(bcd_tbl[temp]);
}
//--------------------------------------------------------------------------------------------
void lcd_write_16bit(uint16_t val)
{
  //write high nibble of val
	lcd_write_8bit(val>>8);
 //write low nibble of val
	lcd_write_8bit(val);
}
//--------------------------------------------------------------------------------------------
void lcd_write_bcd_8bit(uint8_t val)
{
  uint8_t i=0;
  uint8_t Dig[3]={0};
  for(i=0;i<3;i++)
  {
	Dig[i]=val%10;
	val/=10;
  }
if(Dig[2]!=0)
 lcd_write_data(bcd_tbl[Dig[2]]);

if(Dig[2]!=0 ||Dig[1]!=0)
 lcd_write_data(bcd_tbl[Dig[1]]);
 lcd_write_data(bcd_tbl[Dig[0]]);
}
//--------------------------------------------------------------------------------------------
void lcd_write_bcd_16bit(uint16_t val)
{
	uint8_t i=0;
	uint8_t Dig[5]={0};
	for(i=0;i<5;i++)
	{
		Dig[i]=val%10;
		val/=10;
	}
	if(Dig[4]!=0)
	  lcd_write_data(bcd_tbl[Dig[4]]);

	if(Dig[4]!=0 ||Dig[3]!=0)
	  lcd_write_data(bcd_tbl[Dig[3]]);

	if(Dig[4]!=0 ||Dig[3]!=0|| Dig[2]!=0)
	  lcd_write_data(bcd_tbl[Dig[2]]);

	if(Dig[4]!=0 ||Dig[3]!=0|| Dig[2]!=0||Dig[1]!=0)
	  lcd_write_data(bcd_tbl[Dig[1]]);
	  lcd_write_data(bcd_tbl[Dig[0]]);
}
//--------------------------------------------------------------------------------------------
void lcd_init_cgram(uint8_t * pattern,uint8_t num)
{
  uint8_t i=0;
  uint8_t address=CG_RAM|((num<<3)&0xf8);
  lcd_write_cmd(address);
  for(i=0;i<8;i++)
	lcd_write_data(pattern[i]);
}
//--------------------------------------------------------------------------------------------
void lcd_print_cgram(uint8_t x,uint8_t y,uint8_t pattern)
{
 // goto to xy position
   lcd_goto_xy(x,y);
 // goto to xy position
   lcd_write_data(pattern);
}
//--------------------------------------------------------------------------------------------
void lcd_write_num(uint32_t val,uint8_t base)
{
	char buf[16]="";
	itoa(val,buf,base);
	lcd_print(buf);
}
//--------------------------------------------------------------------------------------------
void lcd_write_hex(uint32_t val)
{
  lcd_write_num(val,16);
}
//--------------------------------------------------------------------------------------------------------------------------------------
void lcd_write_octal(uint32_t val)
{
	lcd_write_num(val,8);
}
//--------------------------------------------------------------------------------------------------------------------------------------
void lcd_write_int(uint32_t val)
{
	lcd_write_num(val,10);
}
//----------------------------------------------------------------------------------------------------------------------------------------
void lcd_write_bin(uint32_t val)
{
	uint8_t i=0;
	for(i=0;i<8;i++)
	if(bit_is_clear(val,(7-i)))
		lcd_write_data('0');
	else
		lcd_write_data('1');
}
//----------------------------------------------------------------------------------------------------------------------------------------
//********************************************************************************************
//
// special write methods  ......
//
//********************************************************************************************
size_t lcd_write(uint8_t b)
{
 switch(b)
 {
	case '\n':lcd_goto_xy(0,lcd_coord.y+1);			break; // new line
	case '\t':lcd_goto_xy(lcd_coord.x+2,lcd_coord.y);	break; // new tab
	case '\r':lcd_goto_xy(0,lcd_coord.y);			break; // cursor home
	default: lcd_write_data(b);					break;
  }
	return 1;
}
//-----------------------------------------------------------------------------------------------
size_t lcd_write_array(const uint8_t *buffer, size_t size)
{
	size_t n = 0;
	while (size--) {
	if (lcd_write(*buffer++)) n++;
	else break;
	}
	return n;
}
//-----------------------------------------------------------------------------------------------
 size_t lcd_write_str(const char *buffer, size_t size)
 {
	 return lcd_write_array((const uint8_t *)buffer, size);
 }
//-----------------------------------------------------------------------------------------------
 size_t lcd_write_cstr(const char *str)
 {
   if (str == NULL) return 0;
	return lcd_write_array((const uint8_t *)str, strlen(str));
 }
//-----------------------------------------------------------------------------------------------
//********************************************************************************************
//
//   special print integer methods ......
//
//********************************************************************************************
size_t lcd_print_array(uint8_t buf[],uint8_t len)
{
	return lcd_write_array(buf,len);
}
//-----------------------------------------------------------------------------------------------
size_t lcd_print_as_number(unsigned long long n, uint8_t base)
{
	char buf[8 * sizeof(long long) + 1]; // Assumes 8-bit chars plus zero byte.
	char *str = &buf[sizeof(buf) - 1];

	*str = '\0';

	// prevent crash if called with base == 1
	if (base < 2) base = 10;

	do {
		char c = n % base;
		n /= base;

		*--str = c < 10 ? c + '0' : c + 'A' - 10;
	} while(n);

	return lcd_write_cstr(str);
}
//--------------------------------------------------------------------------------------------
size_t lcd_print_as_Float(double number, uint8_t digits)
{
	size_t n = 0;
	uint8_t i=0;

	if (isnan(number)) return lcd_print("nan");
	if (isinf(number)) return lcd_print("inf");
	if (number > 4294967040.0) return lcd_print ("ovf");  // constant determined empirically
	if (number <-4294967040.0) return lcd_print ("ovf");  // constant determined empirically

	// Handle negative numbers
	if (number < 0.0)
	{
		n += lcd_print_ch('-');
		number = -number;
	}

	// Round correctly so that print(1.999, 2) prints as "2.00"
	double rounding = 0.5;
	for (i=0; i<digits; ++i)
		rounding /= 10.0;

	number += rounding;

	// Extract the integer part of the number and print it
	unsigned long int_part = (unsigned long)number;
	double remainder = number - (double)int_part;
	n += lcd_print_int64(int_part,10);

	// Print the decimal point, but only if there are digits beyond
	if (digits > 0) {
		n += lcd_print_ch('.');
	}

	// Extract digits from the remainder one at a time
	while (digits-- > 0)
	{
		remainder *= 10.0;
		unsigned int toPrint = (unsigned int)(remainder);
		n += lcd_print_uint16((uint16_t)toPrint,10);
		remainder -= toPrint;
	}

	return n;
}
//--------------------------------------------------------------------------------------------
//********************************************************************************************
//
//   text ASCII print methods ......
//
//********************************************************************************************
size_t lcd_print_ch(char c)
{
	return lcd_write(c);
}
//-----------------------------------------------------------------------------------------------
size_t lcd_print(const char * str)
{
	return lcd_write_cstr(str);
}
//-----------------------------------------------------------------------------------------------
size_t lcd_print_xy(uint8_t x,uint8_t y,const char * str)
{
	// goto to xy position
	lcd_goto_xy(x,y);
	//write lcd text buffer
	return lcd_print(str);
}
//--------------------------------------------------------------------------------------------
//********************************************************************************************
//
// generic printf method ...... do not support floating points and only prints 32-bit integers
//
//********************************************************************************************
void lcd_printf(const char * fmt,...)
{
	char buf[16]="";
	va_list ptr;
	va_start(ptr,fmt);
	vsprintf(buf,fmt,ptr);
	va_end(ptr);
	lcd_print(buf);
}
//-----------------------------------------------------------------------------------------------------------------------------------------------------
void lcd_printf_xy(uint8_t x,uint8_t y,const char * fmt,...)
{
	char buf[16]="";
	va_list ptr;
	va_start(ptr,fmt);
	vsprintf(buf,fmt,ptr);
	va_end(ptr);
	lcd_print_xy(x,y,buf);
}
//------------------------------------------------------------------------------------------
/*
size_t lcd_print(const String &s)
{
	return lcd_write_str(s.c_str(), s.length());
}
//-----------------------------------------------------------------------------------------------
size_t lcd_print(uint8_t x,uint8_t y,const String &s)
{
  // goto to xy position
	 lcd_goto_xy(x,y);
 // print the string
	return lcd_write_str(s.c_str(), s.length());
}
//-----------------------------------------------------------------------------------------------
 */
//********************************************************************************************
//
// print methods for  8-bit integers both signed and unsigned from 0 .. up to 0xff ......
//
//********************************************************************************************
size_t lcd_print_uint8(uint8_t n, int base)
{
	return lcd_print_uint64((uint64_t) n, base);
}
//-----------------------------------------------------------------------------------------------
size_t lcd_print_uint8_xy(uint8_t x,uint8_t y,uint8_t n,int base)
{
	return lcd_print_uint64_xy(x,y,(uint64_t) n, base);
}
//-----------------------------------------------------------------------------------------------
size_t lcd_print_uint8_str(const char * str,uint8_t n,int base)
{
	return lcd_print_uint64_str(str,(uint64_t) n, base);
}
//-----------------------------------------------------------------------------------------------
size_t lcd_print_uint8_xy_str(uint8_t x,uint8_t y,const char * str,uint8_t n,int base )
{
	return lcd_print_uint64_xy_str(x,y,str,(uint64_t) n, base);
}
//-----------------------------------------------------------------------------------------------
size_t lcd_print_int8_t(int8_t n, int base)
{
	return lcd_print_int64((int64_t) n, base);
}
//-----------------------------------------------------------------------------------------------
size_t lcd_print_int8_xy(uint8_t x,uint8_t y,int8_t n,int base)
{
	return lcd_print_int64_xy(x,y,(int64_t) n, base);
}
//-----------------------------------------------------------------------------------------------
size_t lcd_print_int8_str(const char * str,int8_t n,int base)
{
	return lcd_print_int64_str(str,(int64_t) n, base);
}
//-----------------------------------------------------------------------------------------------
size_t lcd_print_int8_xy_str(uint8_t x,uint8_t y,const char * str,int8_t n,int base)
{
	return lcd_print_int64_xy_str(x,y,str,(int64_t) n, base);
}
//-----------------------------------------------------------------------------------------------
//********************************************************************************************
//
// print methods for  16-bit integers both signed and unsigned from 0 .. up to 0xffff ......
//
//********************************************************************************************
size_t lcd_print_uint16(uint16_t n, int base)
{
	return lcd_print_uint64((uint64_t) n, base);
}
//-----------------------------------------------------------------------------------------------
size_t lcd_print_uint16_xy(uint8_t x,uint8_t y,uint16_t n,int base)
{
	return lcd_print_uint64_xy(x,y,(uint64_t) n, base);
}
//-----------------------------------------------------------------------------------------------
size_t lcd_print_uint16_str(const char * str,uint16_t n,int base)
{
	return lcd_print_uint64_str(str,(uint64_t) n, base);
}
//-----------------------------------------------------------------------------------------------
size_t lcd_print_uint16_xy_str(uint8_t x,uint8_t y,const char * str,uint16_t n,int base)
{
	return lcd_print_uint64_xy_str(x,y,str,(uint64_t) n, base);
}
//-----------------------------------------------------------------------------------------------
size_t lcd_print_int16(int16_t n, int base)
{
	return lcd_print_int64((int64_t) n, base);
}
//-----------------------------------------------------------------------------------------------
size_t lcd_print_int16_xy(uint8_t x,uint8_t y,int16_t n,int base)
{
	return lcd_print_int64_xy(x,y,(int64_t) n, base);
}
//-----------------------------------------------------------------------------------------------
size_t lcd_print_int16_str(const char * str,int16_t n,int base)
{
	return lcd_print_int64_str(str,(int64_t) n, base);
}
//-----------------------------------------------------------------------------------------------
size_t lcd_print_int16_xy_str(uint8_t x,uint8_t y,const char * str,int16_t n,int base)
{
  return lcd_print_int64_xy_str(x,y,str,(int64_t) n, base);
}
//-----------------------------------------------------------------------------------------------
//********************************************************************************************
//
// print methods for  32-bit integers both signed and unsigned from 0 .. up to 0xffffffff ......
//
//********************************************************************************************
size_t lcd_print_uint32(uint32_t n, int base)
{
  return lcd_print_uint64((uint64_t) n, base);
}
//-----------------------------------------------------------------------------------------------
size_t lcd_print_uint32_xy(uint8_t x,uint8_t y,uint32_t n,int base)
{
  return lcd_print_uint64_xy(x,y,(uint64_t) n, base);
}
//-----------------------------------------------------------------------------------------------
size_t lcd_print_uint32_str(const char * str,uint32_t n,int base)
{
	return lcd_print_uint64_str(str,(uint64_t) n, base);
}
//-----------------------------------------------------------------------------------------------
size_t lcd_print_uint32_xy_str(uint8_t x,uint8_t y,const char * str,uint32_t n,int base)
{
	return lcd_print_uint64_xy_str(x,y,str,(uint64_t) n, base);
}
//-----------------------------------------------------------------------------------------------
size_t lcd_print_int32(int32_t n, int base)
{
	return lcd_print_int64((int64_t) n, base);
}
//-----------------------------------------------------------------------------------------------
size_t lcd_print_int32_xy(uint8_t x,uint8_t y,int32_t n,int base)
{
	return lcd_print_int64_xy(x,y,(int64_t) n, base);
}
//-----------------------------------------------------------------------------------------------
size_t lcd_print_int32_str(const char * str,int32_t n,int base)
{
	return lcd_print_int64_str(str,(int64_t) n, base);
}
//-----------------------------------------------------------------------------------------------
size_t lcd_print_int32_xy_str(uint8_t x,uint8_t y,const char * str,int32_t n,int base)
{
	return lcd_print_int64_xy_str(x,y,str,(int64_t) n, base);
}
//-----------------------------------------------------------------------------------------------
//********************************************************************************************
//
// print methods for  64-bit integers both signed and unsigned from 0 .., 0xffffffffffffffff
//
//********************************************************************************************
size_t lcd_print_uint64(uint64_t n, int base)
{
   if (base == 0)
     return lcd_write(n);
   else
     return lcd_print_as_number(n,base);
}
//-----------------------------------------------------------------------------------------------
size_t lcd_print_uint64_xy(uint8_t x,uint8_t y,uint64_t n,int base)
{
  lcd_goto_xy(x,y);
  return lcd_print_uint64((uint64_t) n, base);
}
//-----------------------------------------------------------------------------------------------
size_t lcd_print_uint64_str(const char * str,uint64_t n,int base)
{
	int len=0;
	len=lcd_print(str);
	return lcd_print_uint64((uint64_t) n, base)+len;
}
//-----------------------------------------------------------------------------------------------
size_t lcd_print_uint64_xy_str(uint8_t x,uint8_t y,const char * str,uint64_t n,int base)
{
	lcd_goto_xy(x,y);
	return lcd_print_uint64_str(str,(uint64_t) n, base);
}
//-----------------------------------------------------------------------------------------------
size_t lcd_print_int64(int64_t n, int base)
{
if (base == 0) return lcd_write(n);
 else if (base == 10)
 {
	 if (n < 0)
	 {
		 int t = lcd_print_ch('-');
		 n = -n;
		 return lcd_print_as_number(n, 10) + t;
	 }
	 return lcd_print_as_number(n, 10);
 }
 else
	 return lcd_print_as_number(n, 10);
}
//-----------------------------------------------------------------------------------------------
size_t lcd_print_int64_xy(uint8_t x,uint8_t y,int64_t n,int base)
{
  lcd_goto_xy(x,y);
  return lcd_print_int64((int64_t) n, base);
}
//-----------------------------------------------------------------------------------------------
size_t lcd_print_int64_str(const char * str,int64_t n,int base)
{
	int len=lcd_print(str);
	return lcd_print_int64((int64_t) n, base)+len;
}
//-----------------------------------------------------------------------------------------------
size_t lcd_print_int64_xy_str(uint8_t x,uint8_t y,const char * str,int64_t n,int base)
{
	lcd_goto_xy(x,y);
	return lcd_print_int64_str(str,(int64_t) n, base);
}
//-----------------------------------------------------------------------------------------------
//********************************************************************************************
//
// // float and double: floating point numbers
//
//********************************************************************************************
size_t lcd_print_double(double n, int digits)
{
  return lcd_print_as_Float(n, digits);
}
//-----------------------------------------------------------------------------------------------
size_t lcd_print_double_xy(uint8_t x,uint8_t y,double n, int digits)
{
	lcd_goto_xy(x,y);
	return lcd_print_double(n, digits);
}
//-----------------------------------------------------------------------------------------------
size_t lcd_print_double_str(const char * str,double n, int digits)
{
 int len=lcd_print(str);
 return lcd_print_double(n, digits)+len;
}
//-----------------------------------------------------------------------------------------------
size_t lcd_print_double_xy_str(uint8_t x,uint8_t y,const char * str,double n, int digits)
{
	lcd_goto_xy(x,y);
	return lcd_print_double_str(str,n, digits);
}
//-----------------------------------------------------------------------------------------------
//********************************************************************************************
//
//  print real methods ......
//
//********************************************************************************************
void lcd_print_real(real_t t)
{
	if(t.sig==1)
	lcd_print("-");
	lcd_print_uint64((uint64_t)t.integer,10);
	lcd_print(".");
	lcd_print_uint64((uint64_t)t.decimal,10);
	lcd_print(" ");
}
//--------------------------------------------------------------------------------------------
void lcd_print_real_str(const char * buf,real_t t)
{
	lcd_print(buf);
	lcd_print_real(t);
}
//--------------------------------------------------------------------------------------------
void lcd_print_real_xy(uint8_t x,uint8_t y,real_t t)
{
	lcd_goto_xy(x,y);
	lcd_print_real(t);
}
//--------------------------------------------------------------------------------------------
void lcd_print_real_xy_str(uint8_t x,uint8_t y,const char * buf,real_t t)
{
	lcd_print_xy(x,y,buf);
	lcd_print_real(t);
}
//--------------------------------------------------------------------------------------------
void lcd_print_ureal(ureal_t t)
{
	lcd_print_uint64((uint64_t)t.integer,10);
	lcd_print(".");
	lcd_print_uint64((uint64_t)t.decimal,10);
	lcd_print(" ");
}
//--------------------------------------------------------------------------------------------
void lcd_print_ureal_str(const char * buf,ureal_t t)
{
	lcd_print(buf);
	lcd_print_ureal(t);
}
//--------------------------------------------------------------------------------------------
void lcd_print_ureal_xy(uint8_t x,uint8_t y,ureal_t t)
{
	lcd_goto_xy(x,y);
	lcd_print_ureal(t);
}
//--------------------------------------------------------------------------------------------
void lcd_print_ureal_xy_str(uint8_t x,uint8_t y,const char * buf,ureal_t t)
{
	lcd_print_xy(x,y,buf);
	lcd_print_ureal(t);
}
//--------------------------------------------------------------------------------------------

//********************************************************************************************
//
//  print time & date related methods ......
//
//********************************************************************************************
void lcd_print_minute(minute_t p)
{
	lcd_print_uint64((uint64_t)p.min,10);
	lcd_print(":");
	lcd_print_uint64((uint64_t)p.sec,10);
	lcd_print(" ");
}
//--------------------------------------------------------------------------------------------
void lcd_print_minute_xy(uint8_t x,uint8_t y,minute_t p)
{
	lcd_goto_xy(x,y);
	lcd_print_minute(p);
}
//--------------------------------------------------------------------------------------------
void lcd_print_minute_str(const char * buf,minute_t p)
{
	lcd_print(buf);
	lcd_print_minute(p);
}
//--------------------------------------------------------------------------------------------
void lcd_print_minute_xy_str(uint8_t x,uint8_t y,const char * buf,minute_t p)
{
	lcd_print_xy(x,y,buf);
	lcd_print_minute(p);
}
//--------------------------------------------------------------------------------------------
void lcd_print_hour(hour_t p)
{
	lcd_print_uint64((uint64_t)p.hour,10);
	lcd_print(":");
	lcd_print_uint64((uint64_t)p.minute,10);
	lcd_print(" ");
}
//--------------------------------------------------------------------------------------------
void lcd_print_hour_xy(uint8_t x,uint8_t y,hour_t p)
{
	lcd_goto_xy(x,y);
	lcd_print_hour(p);
}
//--------------------------------------------------------------------------------------------
void lcd_print_hour_str(const char * buf,hour_t p)
{
	lcd_print(buf);
	lcd_print_hour(p);
}
//--------------------------------------------------------------------------------------------
void lcd_print_hour_xy_str(uint8_t x,uint8_t y,const char * buf,hour_t p)
{
	lcd_print_xy(x,y,buf);
	lcd_print_hour(p);
}
//--------------------------------------------------------------------------------------------
void lcd_print_period(period_t p)
{
	lcd_print_uint64((uint64_t)p.hour,10);
	lcd_print(":");
	lcd_print_uint64((uint64_t)p.minute,10);
	lcd_print(" ");
}
//--------------------------------------------------------------------------------------------
void lcd_print_period_xy(uint8_t x,uint8_t y,period_t p)
{
	lcd_goto_xy(x,y);
	lcd_print_period(p);
}
//--------------------------------------------------------------------------------------------
void lcd_print_period_str(const char * buf,period_t p)
{
	lcd_print(buf);
	lcd_print_period(p);
}
//--------------------------------------------------------------------------------------------
void lcd_print_period_xy_str(uint8_t x,uint8_t y,const char * buf,period_t p)
{
	lcd_print_xy(x,y,buf);
	lcd_print_period(p);
}
//--------------------------------------------------------------------------------------------
void lcd_print_ext_period(ext_period_t p)
{
	lcd_print_uint64((uint64_t)p.hour,10);
	lcd_print(":");
	lcd_print_uint64((uint64_t)p.minute,10);
	lcd_print(":");
	lcd_print_uint64((uint64_t)p.second,10);
	lcd_print(" ");
}
//--------------------------------------------------------------------------------------------
void lcd_print_ext_period_xy(uint8_t x,uint8_t y,ext_period_t p)
{
	lcd_goto_xy(x,y);
	lcd_print_ext_period(p);
}
//--------------------------------------------------------------------------------------------
void lcd_print_ext_period_str(const char * buf,ext_period_t p)
{
	lcd_print(buf);
	lcd_print_ext_period(p);
}
//--------------------------------------------------------------------------------------------
void lcd_print_ext_period_xy_str(uint8_t x,uint8_t y,const char * buf,ext_period_t p)
{
	lcd_print_xy(x,y,buf);
	lcd_print_ext_period(p);
}
//--------------------------------------------------------------------------------------------
void lcd_print_time(_time_t p)
{
  lcd_print_uint64((uint64_t)p.hour,10);
  lcd_print(":");
  lcd_print_uint64((uint64_t)p.minute,10);
  lcd_print(":");
  lcd_print_uint64((uint64_t)p.sec,10);
  lcd_print(" ");
  if(p.am_pm_mode==1)
   lcd_print("AM");
 else if(p.am_pm_mode==2)
   lcd_print(" PM");
  lcd_print(" ");
}
//--------------------------------------------------------------------------------------------
void lcd_print_time_xy(uint8_t x,uint8_t y,_time_t p)
{
  lcd_goto_xy(x,y);
  lcd_print_time(p);
}
//--------------------------------------------------------------------------------------------
void lcd_print_time_str(const char * buf,_time_t p)
{
 lcd_print(buf);
 lcd_print_time(p);
}
//--------------------------------------------------------------------------------------------
void lcd_print_time_xy_str(uint8_t x,uint8_t y,const char * buf,_time_t p)
{
  lcd_print_xy(x,y,buf);
  lcd_print_time(p);
}
//--------------------------------------------------------------------------------------------
void lcd_print_date(date_t p)
{
  lcd_print_uint64((uint64_t)p.day,10);
  lcd_print("/");
  lcd_print_uint64((uint64_t)p.month,10);
  lcd_print("/");
  lcd_print_uint64((uint64_t)p.year,10);
  lcd_print(" ");
}
//--------------------------------------------------------------------------------------------
void lcd_print_date_xy(uint8_t x,uint8_t y,date_t p)
{
  lcd_goto_xy(x,y);
  lcd_print_date(p);
}
//--------------------------------------------------------------------------------------------
void lcd_print_date_str(const char * buf,date_t p)
{
 lcd_print(buf);
 lcd_print_date(p);
}
//--------------------------------------------------------------------------------------------
void lcd_print_date_xy_str(uint8_t x,uint8_t y,const char * buf,date_t p)
{
 lcd_print_xy(x,y,buf);
 lcd_print_date(p);
}
//--------------------------------------------------------------------------------------------
void lcd_print_datetime(datetime_t p)
{
 lcd_print_date(p.date);
 lcd_print(" ");
 lcd_print_time(p.time);
}
//--------------------------------------------------------------------------------------------
void lcd_print_datetime_xy(uint8_t x,uint8_t y,datetime_t p)
{
  lcd_goto_xy(x,y);
  lcd_print_datetime(p);
}
//--------------------------------------------------------------------------------------------
void lcd_print_datetime_str(const char * buf,datetime_t p)
{
  lcd_print(buf);
  lcd_print_datetime(p);
}
//--------------------------------------------------------------------------------------------
void lcd_print_datetime_xy_str(uint8_t x,uint8_t y,const char * buf,datetime_t p)
{
 lcd_print_xy(x,y,buf);
 lcd_print_datetime(p);
}
//--------------------------------------------------------------------------------------------
void lcd_blank_line(uint8_t steps)
{
	uint8_t i=0;
	uint8_t cnt= lcd_col_cnt;//lcd_get_colums_cnt();
	uint8_t stop=lcd_coord.x+steps;
	if(stop>cnt)
	 stop=cnt;

for (i=0;i<stop;i++)
	lcd_print(" ");

}
//--------------------------------------------------------------------------------------------
/*size_t lcd_8bit_t::blank_line(uint8_t steps)
{
	uint8_t i =0;
	uint8_t cnt=get_colums_cnt();
	uint8_t stop=get_xy().x+steps;
	if(stop%2!=0)
	stop--;
	if(stop>cnt)
	stop=cnt-1;
	for (i=0;i<stop;i++)
	print(" ");
	return i;
}
//--------------------------------------------------------------------------------------------
*/
