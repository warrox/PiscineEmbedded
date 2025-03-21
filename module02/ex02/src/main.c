#include <avr/io.h>
#include <util/delay.h>

#define FOSC 16000000UL
#define BAUD 115200
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)	
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
}
char uart_rx(void)
{
	// char c;
	while (!(UCSR0A & (1<<RXC0)));
	/* Get and return received data from buffer */
	return UDR0;
}


void uart_tx(char c)
{
    // Wait UDRE is empty
    while (!(UCSR0A & (1 << UDRE0)));
    // Mettre les données dans le registre de transmission
        UDR0 = c;
}

int main()
{
    int ubbr = round_ubbr();
    uart_init(ubbr);
    while (1)
    {
		char c = uart_rx();
		uart_tx(c);
    }
}
