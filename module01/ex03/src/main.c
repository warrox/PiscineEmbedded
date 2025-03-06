#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>
#include <stdint.h>

#define LED_PIN PB1
#define BUTTON_L PD2
#define BUTTON_R PD4
// Fonction d'interruption quand la valeur d'OCR1A est atteinte
ISR(TIMER1_COMPA_vect) {
    PORTB |= (1 << LED_PIN); // Allume la LED
}

// Fonction d'interruption quand la valeur d'OCR1B est atteinte
ISR(TIMER1_COMPB_vect) {
    PORTB &= ~(1 << LED_PIN); // Éteint la LED
}

int main(void) {
    uint8_t button_state_l = 0;

    uint8_t button_state_r = 0;

    DDRB |= (1 << LED_PIN);  // Configure PB1 comme sortie pour la LED

    TCCR1B |= (1 << WGM12);  // Mode CTC du Timer1

    // Configure le prescaler à 1024
    TCCR1B |= (1 << CS12) | (1 << CS10);

    OCR1A = (F_CPU / 1024);  // Définit OCR1A (la valeur TOP)

    uint16_t step = OCR1A / 10;  // Augmenter OCR1B par 10% d'OCR1A
    uint16_t max_value = OCR1A;  // Définit la valeur maximale pour OCR1B
	
    OCR1B = OCR1A / 10;  // Définit OCR1B à 10% d'OCR1A

    TIMSK1 |= (1 << OCIE1A) | (1 << OCIE1B);  // Active les interruptions pour OCR1A et OCR1B

    DDRD &= ~(1 << BUTTON_L);
    PORTD |= (1 << BUTTON_L);

	DDRD &= ~(1 << BUTTON_R);
    PORTD |= (1 << BUTTON_R);



    sei();  // Active les interruptions globales

    while (1) {
        button_state_l = !(PIND & (1 << BUTTON_L));  // Vérifie si le bouton est press
		button_state_r = !(PIND & (1 << BUTTON_R));
        if (button_state_l) {
            _delay_ms(50);  // Anti-rebond du bouton

            // Augmente OCR1B de 10% d'OCR1A à chaque pression
            if (OCR1B + step <= max_value) {
                OCR1B += step;  // Augmente OCR1B par 'step'
            } else {
                OCR1B = OCR1A / 10;  // Si OCR1B dépasse OCR1A, remets-le à la valeur initiale
            }
        }
		if(button_state_r){
			_delay_ms(50);
			if(OCR1B - OCR1A / 10){
				OCR1B -= step;
			}
			else{
				OCR1B = OCR1A / 10;
			}
		}
    }
    return 0;
}
