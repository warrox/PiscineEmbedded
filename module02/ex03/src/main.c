#include <avr/io.h>
#include <avr/interrupt.h>
#include <util/delay.h>

#define FOSC 16000000UL
#define BAUD 115200
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)	
// Initialisation UART

int round_ubbr()
{
    double ubbr = (double)FOSC / (16 * BAUD) - 1;
    if (ubbr < 0.0)
        return (int)(ubbr - 0.5);
    else
        return (int)(ubbr + 0.5);
}

void uart_init(unsigned int ubrr)
{
    //Set Baud Rate
    UBRR0H = (unsigned char)(ubrr >> 8);
    UBRR0L = (unsigned char) (ubrr & 0xFF);
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
	UCSR0B |= (1 << RXCIE0);
	sei();
}

void uart_tx(char c)
{
    while (!(UCSR0A & (1 << UDRE0))); // Attendre que le buffer soit vide
    UDR0 = c;
}

ISR(USART_RX_vect)
{
    char c = UDR0;

    if (c >= 'A' && c <= 'Z')
        c += 32;
    else if (c >= 'a' && c <= 'z')
        c -= 32;

    uart_tx(c);
}

int main()
{
	int ubbr = round_ubbr();
    uart_init(ubbr); // Initialisation UART
    while (1)
    {
    }
    return 0;
}
