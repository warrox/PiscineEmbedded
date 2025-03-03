
#include <avr/io.h>
#include <util/delay.h>

#define LED_PIN PB0
#define BUTTON_PIN PD2

int main(void) {
    // Set PB0 as output (LED)
    DDRB |= (1 << LED_PIN);

    // Set PD2 as input (Button) and enable internal pull-up
    DDRD &= ~(1 << BUTTON_PIN);
    PORTD |= (1 << BUTTON_PIN);

    while (1) {
        // Check if button is pressed (active low)
        if (!(PIND & (1 << BUTTON_PIN))) {
            PORTB |= (1 << LED_PIN);  // Turn LED on
        } else {
            PORTB &= ~(1 << LED_PIN); // Turn LED off
        }
        _delay_ms(50); // Simple debounce
    }

    return 0;
}
