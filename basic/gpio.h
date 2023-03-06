/**
 * @brief gpio.h
 *
 * @param student: Sameer Almaldein
 * @param ID: 679699
 * @param University TU-Chemnitz
 * @param Master : ASE(Automotive Software Engineering )
 */ 

#ifndef _GPIO_H
#define _GPIO_H

//********************************************************************************************
//
//  header  files
//
//********************************************************************************************

//********************************************************************************************
//
//  Macros  and defines
//
//********************************************************************************************
enum GPIO_MODE{
    GPIO_MODE_ANALOG=0x00,
    GPIO_MODE_OUT_PP_10MHZ=0x01,
    GPIO_MODE_OUT_PP_2MHZ=0x02,
    GPIO_MODE_OUT_PP_50MHZ=0x03,
    GPIO_MODE_IN_FLOATING=0x04,
    GPIO_MODE_OUT_OD_10MHZ=0x05,
    GPIO_MODE_OUT_OD_2MHZ=0x06,
    GPIO_MODE_OUT_OD_50MHZ=0x07,
    GPIO_MODE_IN_PUPD=0x08,
    GPIO_MODE_AF_PP_10MHZ=0x09,
    GPIO_MODE_AF_PP_2MHZ=0x0A,
    GPIO_MODE_AF_PP_50MHZ=0x0B,
    GPIO_MODE_RESEVED=0x0C,
    GPIO_MODE_AF_OD_10MHZ=0x0D,
    GPIO_MODE_AF_OD_2MHZ=0x0E,
    GPIO_MODE_AF_OD_50MHZ=0x0F,
};
//********************************************************************************************
//
//  Data Sructures
//
//********************************************************************************************
typedef struct _gpio_t
{
 GPIO_TypeDef * port;
 uint16_t pin;
 } gpio_t;
//********************************************************************************************
//
//  extern variables
//
//********************************************************************************************
//********************************************************************************************
//
//  extern Methods
//
//********************************************************************************************
extern void gpio_init(GPIO_TypeDef * port,uint16_t pin,GPIOMode_TypeDef mode,GPIOSpeed_TypeDef speed);
extern void gpio_pinmode(gpio_t pio,GPIOMode_TypeDef mode,GPIOSpeed_TypeDef speed);

extern void gpio_pin_mode(gpio_t pio,uint8_t mode);
// output operation
extern void gpio_set(gpio_t pio);
extern void gpio_clear(gpio_t pio);
extern void gpio_toggle(gpio_t pio);

// intput operation
extern void gpio_in_pullup(gpio_t pio);
extern void gpio_in_pulldown(gpio_t pio);
extern void gpio_in_float(gpio_t pio);

extern uint8_t gpio_get(gpio_t pio);
extern uint8_t gpio_get_out(gpio_t pio);

#endif /* _GPIO_H */