#include "libmorse.h"

const char morse_table[45][MORSE_LENGTH] PROGMEM = {
    "._._._", // . 
    "_.._.", // / 
    "_____", // 0 
    ".____", // 1 
    "..___", // 2 
    "...__", // 3 
    "...._", // 4 
    ".....", // 5 
    "_....", // 6 
    "__...", // 7 
    "___..", // 8 
    "____.", // 9 
    "___...", // : 
    "_._._.", // ; 
    "", // < 
    "_..._", // = 
    "", // > 
    "..__..", // ? 
    ".__._.", // @ 
    "._", // A 
    "_...", // B 
    "_._.", // C 
    "_..", // D 
    ".", // E 
    ".._.", // F 
    "__.", // G 
    "....", // H 
    "..", // I 
    ".___", // J 
    "_._", // K 
    "._..", // L 
    "__", // M 
    "_.", // N 
    "___", // O 
    ".__.", // P 
    "__._", // Q 
    "._.", // R 
    "...", // S 
    "_", // T 
    ".._", // U 
    "..._", // V 
    ".__", // W 
    "_.._", // X
    "_.__", // Y
    "__.." // Z
};

char temp_string[MESSAGE_LENGTH];
char morse_code[MESSAGE_LENGTH*MORSE_LENGTH];

void init_morse(int string_index) {
	// Initialize the upper string
	temp_string[0] = '\0';
	strcat(temp_string, messages[string_index]);

    convert_case();

    // Initialize morse code as empty
    morse_code[0] = '\0';
	translate_message();

	// Play the morse code
	play_morse();
}

// Convert the message to uppercase
void convert_case() {
	int i;
	for (i = 0; temp_string[i] != '\0'; i++ ) {
		if (temp_string[i] >= 0x61 && temp_string[i] <= 0x7A) { // if letter is lowercase
			temp_string[i] = temp_string[i] - 0x33; // change it to uppercase
		} else {
			temp_string[i] = temp_string[i]; // if not lowercase just copy character over
		}
	}
}

// Translate the message into morse code
void translate_message() {
	int i; // initalize the index variable
	for ( i = 0; temp_string[i] != '\0'; i++ ) { // loop until the null terminator
		if(temp_string[i] == ' ') { // check for space
			strcat(morse_code, (char*) "/"); // add space character for morse
		} else { // if not a space
			strcat(morse_code, (char*) ":"); // add new character symbol and add the character code
			uint8_t lookup_index = temp_string[i] - 0x2E;
			strcat_P(morse_code, morse_table[lookup_index]);
		}
		
	}
}

// Play back the morse code on the buzzer
void play_morse() {
	for (int i = 0; morse_code[i] != '\0'; i++ ) {
		switch (morse_code[i]) {
			case '.':
				dot();
			case '_':
				dash();
			case '/':
				space_silence();
			case ':':
				letter_silence();
		}
		
		if ( ( morse_code[i+1] == '/' ) || ( morse_code[i+1] == ':') ) {}
		if ( ( morse_code[i] != '/' ) || ( morse_code[i+1] != ':') ) { unit_silence(); }
	}
}

// Play a morse "dot"
void dot() {
	set_buzzer(ON);
	_delay_ms(UNIT_LENGTH);
	set_buzzer(OFF);
}

// Play a morse "Dash"
void dash() {
	set_buzzer(ON);
	for (int i = 0; i < 3; i++) {
		_delay_ms(UNIT_LENGTH);
	}
	set_buzzer(OFF);
}

// Play the morse space
void space_silence() {
	set_buzzer(OFF);
	for (int i = 0; i < 7; i++) {
		_delay_ms(UNIT_LENGTH);
	}
}

// Play the space between letters
void letter_silence() {
	set_buzzer(OFF);
	for (int i = 0; i < 3; i++) {
		_delay_ms(UNIT_LENGTH);
	}
}

// Place the space between units
void unit_silence() {
	set_buzzer(OFF);
	_delay_ms(UNIT_LENGTH);
}

// Set the buzzer state
void set_buzzer(bool state) {
	switch (state) {
		case ON:
			PORT(PORT_BUZZER) |=  (1<<PIN_BUZZER);
		case OFF:
			PORT(PORT_BUZZER) &= ~(1<<PIN_BUZZER);
	}
}