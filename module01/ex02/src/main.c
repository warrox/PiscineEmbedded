/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: whamdi <whamdi@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/04 16:14:51 by whamdi            #+#    #+#             */
/*   Updated: 2025/03/05 15:26:22 by whamdi           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <avr/io.h>
#include <avr/interrupt.h>

#define LED_PIN PB1

ISR(TIMER1_COMPA_vect) {
    PORTB |= (1 << LED_PIN);
}

ISR(TIMER1_COMPB_vect) {
    PORTB &= ~(1 << LED_PIN);
}

int main(void) {
    DDRB |= (1 << LED_PIN);

    TCCR1B |= (1 << WGM12);

    TCCR1B |= (1 << CS12) | (1 << CS10);

    OCR1A = (F_CPU / 1024); 

    OCR1B = OCR1A / 10;

    TIMSK1 |= (1 << OCIE1A) | (1 << OCIE1B);

    sei();

    while (1) {
    }
    return 0;
}
