#include <avr/io.h>

#define LED_PIN PB1

void init_timer1() {
    // Configurer Fast PWM mode 14 (ICR1 comme TOP)
    TCCR1A |= (1 << WGM11); 
    TCCR1B |= (1 << WGM12) | (1 << WGM13);
    
    // Configurer la sortie PWM non-inversée sur OC1A (LED_PIN)
    TCCR1A |= (1 << COM1A1); 

    // Définir le prescaler à 1024
    TCCR1B |= (1 << CS12) | (1 << CS10);

    // Définir la période du signal (TOP)
    ICR1 = (F_CPU / 1024) - 1; // Période de la PWM (1s si F_CPU = 1MHz)

    // Définir le rapport cyclique à 10% (10% de ICR1)
    OCR1A = ICR1 / 10;
}

int main(void) {
    // Configurer la broche de la LED comme sortie
    DDRB |= (1 << LED_PIN);

    // Initialiser le Timer1
    init_timer1();

    while (1) {
    }

    return 0;
}
