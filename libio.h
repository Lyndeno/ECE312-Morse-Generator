#include <avr/io.h>
#include <util/delay.h>

#ifndef LIBIO_H
#define LIBIO_H

#define DDR(x) (*(&x - 1))     // address of data direction register of port x
#define PORT(x) (*(&x)) 
#define PIN(x) (*(&x - 2)) 

#define PORT_LR PORTD

#define PORT_ENTER PORTB

#define PORT_BUZZER PORTD

#define PIN_LEFT PORTD6

#define PIN_RIGHT PORTD7

#define PIN_ENTER PORTB0

#define PIN_BUZZER PORTD5

#ifndef F_CPU
#define F_CPU 1000000
#endif

#endif






/*
#define DDR(x) (*(&x - 1))     // address of data direction register of port x
#define PORT(x) (*(&x)) 
#define PIN(x) (*(&x - 2)) 

#ifndef PORT_LR
#define PORT_LR PORTD
#endif

#ifndef PORT_ENTER
#define PORT_ENTER PORTB
#endif

#ifndef PORT_BUZZER
#define PORT_BUZZER PORTD
#endif

#ifndef PIN_LEFT
#define PIN_LEFT PORTD6
#endif

#ifndef PIN_RIGHT
#define PIN_RIGHT PORTD7
#endif

#ifndef PIN_ENTER
#define PIN_ENTER PORTB0
#endif

#ifndef PIN_BUZZER
#define PIN_BUZZER PORTD5
#endif

#ifndef F_CPU
#define F_CPU 1000000
#endif
*/