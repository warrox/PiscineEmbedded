/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whamdi <whamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:14:51 by whamdi            #+#    #+#             */
/*   Updated: 2025/03/07 14:16:38 by whamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <avr/io.h>

#define LED_PIN PB1

// Initialisation du Timer1
void init_timer1() {
	TCCR1A |= (1 << WGM11) | (1 << WGM10);
	TCCR1B |= (1 << WGM12) | (1 << WGM13); // set TIMER 1 on FAST pwm mode 15
	

	TCCR1A |= (1 << COM1A0); // active toggle on LED_D2 (table 15-3 p108)	

	TCCR1B |= (1 << CS12) | (1 << CS10); // active presecaler 1024
	OCR1A |= (F_CPU / 2048); //Toggle led 
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
