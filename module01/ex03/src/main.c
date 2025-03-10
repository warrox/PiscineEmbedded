#include <avr/io.h>
#include <util/delay.h>
#include <stdint.h>

#define LED_PIN PB1
#define BUTTON_L PD2
#define BUTTON_R PD4

void init_timer1() {
    // Configurer Fast PWM mode 14 (ICR1 comme TOP)
    TCCR1A |= (1 << WGM11); 
    TCCR1B |= (1 << WGM12) | (1 << WGM13);
    
    // Configurer la sortie PWM non inversée sur OC1A (LED_PIN)
    TCCR1A |= (1 << COM1A1); 

    // Définir le prescaler à 256
    TCCR1B |= (1 << CS12) ;

    // Définir la période du signal (TOP)
    ICR1 = 62499; // Période de la PWM (1s si F_CPU = 1MHz)

    // Définir le rapport cyclique à 10% (10% de ICR1)
    OCR1A = 6249;
}

int main(void) {
    // Configurer la LED en sortie
    DDRB |= (1 << LED_PIN);

    // Configurer les boutons en entrée avec pull-up
    DDRD &= ~(1 << BUTTON_L) & ~(1 << BUTTON_R);
    PORTD |= (1 << BUTTON_L) | (1 << BUTTON_R);

    // Initialiser le Timer1
    init_timer1();
	unsigned int counter = 0;
    uint16_t step = 6249;
    uint16_t min_value = ICR1 / 10;  // 10% de ICR1
    uint16_t max_value = ICR1;  // 100% de ICR1

    uint8_t prev_button_l = !(PIND & (1 << BUTTON_L));
    uint8_t prev_button_r = !(PIND & (1 << BUTTON_R));

    while (1) {
        uint8_t button_l = !(PIND & (1 << BUTTON_L));
        uint8_t button_r = !(PIND & (1 << BUTTON_R));

        // Incrémentation par 10% (bouton gauche)
        if (button_l && !prev_button_l) {
            _delay_ms(100);
            if (OCR1A + step <= max_value || counter <= 9) {
                OCR1A += step;
			}
			counter ++;
            // } else {
            //     OCR1A = min_value;  // Revient à 10% si dépasse 100%
            // }
        }
        prev_button_l = button_l;

        // Décrémentation par 10% (bouton droit)
        if (button_r) {
            _delay_ms(100);
            if (OCR1A > min_value && counter > 0) {
                OCR1A -= step;
            } else {
                OCR1A = min_value;  // Ne descend pas en dessous de 10%
            }
			counter --;
        }
        prev_button_r = button_r;
    }
}

