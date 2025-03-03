#include <avr/io.h>
#include <util/delay.h>

#define LED_PIN PB0
#define BUTTON_PIN PD2

int main(void) {
    // Set PB0 as output (LED)
    DDRB |= (1 << LED_PIN);

    // Set PD2 as input (Button) and enable internal pull-up
    DDRD &= ~(1 << BUTTON_PIN);
    PORTD |= (1 << BUTTON_PIN);  // Active la résistance pull-up interne pour le bouton

    // Variable pour garder la trace de l'état du bouton
    uint8_t button_state = 0;  // 0 : bouton relâché, 1 : bouton pressé
    uint8_t last_button_state = 0;  // Variable pour mémoriser l'état précédent du bouton

    while (1) {
        // Lire l'état du bouton (0 signifie pressé en raison de la pull-up)
        button_state = !(PIND & (1 << BUTTON_PIN));  

        // Vérifie si le bouton vient d'être pressé (changement d'état)
        if (button_state && !last_button_state) {
            // Toggle la LED
            PORTB ^= (1 << LED_PIN);  // XOR avec 1 pour inverser l'état de la LED

            // Débounce
            _delay_ms(50);  // Attente pour éviter les rebonds du bouton
        }

        // Mettre à jour l'état précédent du bouton
        last_button_state = button_state;
    }

    return 0;
}
