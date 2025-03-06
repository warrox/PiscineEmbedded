/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whamdi <whamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 10:01:14 by whamdi            #+#    #+#             */
/*   Updated: 2025/03/05 09:33:44 by whamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <avr/io.h>
#include <util/delay.h>

#define BUTTON_PIN_L PD2  // Bouton SW1 (incrémente)
#define BUTTON_PIN_R PD4  // Bouton SW2 (décrémente)

#define LED_PIN_0 PB0     // LED D1
#define LED_PIN_1 PB1     // LED D2
#define LED_PIN_2 PB2     // LED D3
#define LED_PIN_3 PB4     // LED D4

void init_led(void) {
    DDRB |= (1 << LED_PIN_0) | (1 << LED_PIN_1) | (1 << LED_PIN_2) | (1 << LED_PIN_3);
}

void init_button(void) {
    DDRD &= ~(1 << BUTTON_PIN_L); // PD2 en entrée
    PORTD |= (1 << BUTTON_PIN_L); // Activation de la pull-up interne

    DDRD &= ~(1 << BUTTON_PIN_R); // PD4 en entrée
    PORTD |= (1 << BUTTON_PIN_R); // Activation de la pull-up interne
}

void display_binary(uint8_t value) {
    // Met à jour les LEDS selon la valeur du compteur
    PORTB = (PORTB & ~((1 << LED_PIN_0) | (1 << LED_PIN_1) | (1 << LED_PIN_2) | (1 << LED_PIN_3))) |
            ((value & 0x01) << LED_PIN_0) |
            ((value & 0x02) << (LED_PIN_1 - 1)) |
            ((value & 0x04) << (LED_PIN_2 - 2)) |
            ((value & 0x08) << (LED_PIN_3 - 3));
}

uint8_t debounce(uint8_t pin) {
    if (!(PIND & (1 << pin))) { // Si bouton pressé (LOW)
        _delay_ms(50);          // Attendre pour éviter les rebonds
        if (!(PIND & (1 << pin))) // Vérifier encore
            return 1;
    }
    return 0;
}

int main(void) {
    init_led();
    init_button();

    uint8_t counter = 0; // Compteur de 0 à 15
    display_binary(counter); // Initialisation de l'affichage

    while (1) {
        if (debounce(BUTTON_PIN_L)) { // SW1 press
            if (counter < 15) counter++; // Incremente si pas au max
            display_binary(counter);
            while (!(PIND & (1 << BUTTON_PIN_L))); // Attendre relachement
        }
        if (debounce(BUTTON_PIN_R)) { // SW2 pressé
            if (counter > 0) counter--; // decremente si pas a 0
            display_binary(counter);
            while (!(PIND & (1 << BUTTON_PIN_R))); // Attendre relachement button
        }
    }
}
