
#include <avr/io.h>
#include <util/delay.h>

#define FOSC 16000000UL
#define BAUD 115200
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)	
char buffer[8];
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

void set_rgb(uint8_t r, uint8_t g, uint8_t b){
	OCR0A = g;
    OCR0B = r;
    OCR2B = b;
}

void uart_printstr(const char *str){
	int i = 0;
	while(str[i] != '\0'){
		uart_tx(str[i++]);
	}
	uart_tx('\r');
	_delay_ms(2000);
	// uart_printstr(str);
}

int	ft_isalnum(int c)
{
	if ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') || (c >= 'A'
			&& c <= 'F'))
	{
		return (1);
	}
	return (0);
}
int main()
{
	int ubbr = round_ubbr();
	char c;
	int i = 1;
	buffer[0] = '#';
    uart_init(ubbr);
	uart_printstr("Please enter a Hex color to display a color in format [#RRGGBB]\n");
    while (1)
    {
		c = uart_rx();
		uart_tx(c);	
		buffer[i++] = c;
		if(!ft_isalnum(buffer[i])){
			uart_printstr("Not a correct format, try again\n");
		}
		// if press enter add \0

    }
}
