// #include <avr/io.h>
// #include <avr/interrupt.h>
// #include <util/delay.h>
// #include <stdint.h>
//
// #define LED_PIN PB1
// #define BUTTON_L PD2
// #define BUTTON_R PD4
//
// void init_timer1() {
//     // Configurer Fast PWM mode 14 (ICR1 comme TOP)
//     TCCR1A |= (1 << WGM11); 
//     TCCR1B |= (1 << WGM12) | (1 << WGM13);
//     
//     // Configurer la sortie PWM non-inversée sur OC1A (LED_PIN)
//     TCCR1A |= (1 << COM1A1); 
//
//     // Définir le prescaler à 1024
//     TCCR1B |= (1 << CS12) | (1 << CS10);
//
//     // Définir la période du signal (TOP)
//     ICR1 = (F_CPU / 1024) - 1; // Période de la PWM (1s si F_CPU = 1MHz)
//
//     // Définir le rapport cyclique à 10% (10% de ICR1)
//     OCR1A = ICR1 / 10;
// }
//
// int main(void) {
//     uint8_t button_state_l = 0;
//
//     uint8_t button_state_r = 0;
// 	init_timer1();
//     DDRB |= (1 << LED_PIN);  // Configure PB1 comme sortie pour la LED
//
//     
//     uint16_t step = ICR1 / 10;  // Augmenter OCR1B par 10% d'OCR1A
//     uint16_t max_value = ICR1;  // Définit la valeur maximale pour OCR1B
// 	
//     while (1) {
//         button_state_l = !(PIND & (1 << BUTTON_L));  // Vérifie si le bouton est press
// 		button_state_r = !(PIND & (1 << BUTTON_R));
//         if (button_state_l) {
//             _delay_ms(50);  // Anti-rebond du bouton
//
//             // Augmente OCR1B de 10% d'OCR1A à chaque pression
//             if (OCR1A + step <= max_value) {
//                 OCR1A += step;  // Augmente OCR1B par 'step'
//             } else {
//                 OCR1A = ICR1 / 10;  // Si OCR1B dépasse OCR1A, remets-le à la valeur initiale
//             }
//         }
// 		if(button_state_r){
// 			_delay_ms(50);
// 			if(OCR1A - ICR1 / 10){
// 				OCR1A -= step;
// 			}
// 			else{
// 				OCR1A = ICR1 / 10;
// 			}
// 		}
//     }
//     return 0;
// }
//
//
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

    // Définir le prescaler à 1024
    TCCR1B |= (1 << CS12) | (1 << CS10);

    // Définir la période du signal (TOP)
    ICR1 = (F_CPU / 1024) - 1; // Période de la PWM (1s si F_CPU = 1MHz)

    // Définir le rapport cyclique à 10% (10% de ICR1)
    OCR1A = ICR1 / 10;
}

int main(void) {
    // Configurer la LED en sortie
    DDRB |= (1 << LED_PIN);

    // Configurer les boutons en entrée avec pull-up
    DDRD &= ~(1 << BUTTON_L) & ~(1 << BUTTON_R);
    PORTD |= (1 << BUTTON_L) | (1 << BUTTON_R);

    // Initialiser le Timer1
    init_timer1();

    // Définir `step` après `init_timer1()` pour qu'ICR1 soit bien défini
    uint16_t step = ICR1 / 10;
    uint16_t min_value = ICR1 / 10;  // 10% de ICR1
    uint16_t max_value = ICR1;  // 100% de ICR1

    uint8_t prev_button_l = 0;
    uint8_t prev_button_r = 0;

    while (1) {
        uint8_t button_l = !(PIND & (1 << BUTTON_L));
        uint8_t button_r = !(PIND & (1 << BUTTON_R));

        // Incrémentation par 10% (bouton gauche)
        if (button_l && !prev_button_l) {
            _delay_ms(50);  // Anti-rebond
            if (OCR1A + step <= max_value) {
                OCR1A += step;
            } else {
                OCR1A = min_value;  // Revient à 10% si dépasse 100%
            }
        }
        prev_button_l = button_l;

        // Décrémentation par 10% (bouton droit)
        if (button_r && !prev_button_r) {
            _delay_ms(50);  // Anti-rebond
            if (OCR1A > min_value) {
                OCR1A -= step;
            } else {
                OCR1A = min_value;  // Ne descend pas en dessous de 10%
            }
        }
        prev_button_r = button_r;
    }
}
