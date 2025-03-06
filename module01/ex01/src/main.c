/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whamdi <whamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:14:51 by whamdi            #+#    #+#             */
/*   Updated: 2025/03/05 09:39:45 by whamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <avr/io.h>
#include <avr/interrupt.h>

#define LED_PIN PB1

// Initialisation du Timer1
void init_timer1() {
    // Mode CTC (Clear Timer on Compare Match)
    TCCR1B |= (1 << WGM12);

    // Préscaler de 256
    TCCR1B |= (1 << CS12);

    // Calcul de la valeur de comparaison pour 0,5 seconde
    // Fréquence d'horloge = 16 MHz
    // Fréquence de Timer1 = 16 MHz / 256 = 62500 Hz
    // Pour 0,5 seconde : 62500 * 0.5 = 31250
    OCR1A = 31249;

    // Activer l'interruption de comparaison A
    TIMSK1 |= (1 << OCIE1A);

    // Activer les interruptions globales
    sei();
}

// Interruption du Timer1
ISR(TIMER1_COMPA_vect) {
    // Basculer l'état de la LED
    PINB |= (1 << LED_PIN);
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
