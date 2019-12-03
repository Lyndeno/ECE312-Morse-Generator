#include <avr/pgmspace.h>
#include <string.h>
#include <avr/io.h>
#include <stdint.h>
#include <stdbool.h>
#include "libio.h"
#include "main.h"

// End of Work ..._._
// Error ........
// Start of signal _._._

//char SOS[12] = "... ___ ...";

void init_morse(int);
void play_morse();
void convert_case(void);
void translate_message();

void dot(void);
void dash(void);
void space_silence(void);
void letter_silence(void);
void unit_silence(void);
void set_buzzer(bool);

#define MORSE_LENGTH 6
#define UNIT_LENGTH 250

#define ON 1
#define OFF 0

