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

void uart_tx(char c)
{
    // Wait UDRE is empty
    while (!(UCSR0A & (1 << UDRE0)));
    // Mettre les données dans le registre de transmission
        UDR0 = c;
}
void uart_printstr(const char *str){
	int i = 0;
	while(str[i] != '\0'){
		uart_tx(str[i++]);
	}
	uart_tx('\r');
	_delay_ms(2000);
	uart_printstr(str);
}
void uart_init(unsigned int ubrr)
{
    //Set Baud Rate
    UBRR0H = (unsigned char)(ubrr >> 8);
    UBRR0L = (unsigned char) (ubrr & 0xFF);
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}


int main()
{
    int ubbr = round_ubbr();
    uart_init(ubbr);
	uart_printstr("Hello World!\n");
    while (1)
    {
    }
}
