#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define FOSC 16000000UL
#define BAUD 115200

volatile char buffer[] = "Hello World!\r\n";
volatile uint8_t index = 0;

int round_ubbr()
{
    double ubbr = (double)FOSC / (16 * BAUD) - 1;
    return (int)(ubbr + 0.5);
}

void uart_init(unsigned int ubrr)
{
   	UBRR0H = (unsigned char)(ubrr >> 8); // Chargement de la partie haute du registre de baud rate  
    UBRR0L = (unsigned char)(ubrr & 0xFF); // Chargement de la partie basse du registre de baud rate  
    UCSR0B = (1 << TXEN0) | (1 << UDRIE0); // Activation de la transmission et de l'interruption UDRE  
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00); // Configuration de l'UART en mode 8 bits  
    sei(); // Activation globale
}

// Interruption pour l'envoi des caractères
ISR(USART_UDRE_vect)
{
    if (buffer[index] != '\0') {
        UDR0 = buffer[index++];
    } else {
        UCSR0B &= ~(1 << UDRIE0);
        index = 0;
        _delay_ms(2000);
        UCSR0B |= (1 << UDRIE0);
    }
}

int main()
{
    int ubbr = round_ubbr();
    uart_init(ubbr);

    while (1)
    {
    }
}
