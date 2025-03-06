
#include <avr/io.h>
#include <util/delay.h>

#define LED_PIN PB0
#define BUTTON_PIN PD2

int main(void) {
    // Set PB0 as output (LED)
	// used the back of the microcontroller to se which pin is connected to led and so on.
    DDRB |= (1 << LED_PIN); // configure la pin en output pour la led PB0 -> D1

    // PORTD |= (1 << BUTTON_PIN);
	PORTB |= (1 << LED_PIN);  // Turn LED on 
    return 0;
}
