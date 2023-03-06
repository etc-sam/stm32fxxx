/**
 * @brief keypad.h
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

//********************************************************************************************
//
//  Keypad  Structures
//
//********************************************************************************************
typedef union _key_btn_t
{
	uint8_t  val;
	struct
	{
		uint8_t :2;
		uint8_t usr:1;
		uint8_t set:1;
		uint8_t shft:1;
		uint8_t up:1;
		uint8_t down:1;
		uint8_t esc:1;
	};
} Keypad_btn_t;
//********************************************************************************************
//
//  extern variables
//
//********************************************************************************************
extern Keypad_btn_t key_val;
extern gpio_t keypad_en;
extern gpio_t keypad_port[8];

extern uint8_t keypad_unpressed_mask;
//extern uint8_t keypad_Enter_cnt,keypad_Timeout_cnt;
//extern uint8_t keypad_Reset_cnt,keypad_Start_cnt;

//********************************************************************************************
//
//********************************************************************************************
extern void keypad_init(uint8_t unpressed_val);
extern uint8_t keypad_scan(void);
extern void keypad_process(void);
extern uint8_t keypad_is_pressed(void);
extern void keypad_port_input_pullup(void);


extern void keypad_up_key_handle(void);
extern void keypad_down_key_handle(void);
extern void keypad_set_key_handle(void);
extern void keypad_esc_key_handle(void);
extern void keypad_shft_key_handle(void);
extern void keypad_info_key_handle(void);
