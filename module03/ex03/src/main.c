#include <avr/io.h>
#include <util/delay.h>
#include <stdlib.h>
#include <stdbool.h>
#define RGB_LED_RED PD5
#define RGB_LED_BLUE PD3
#define RGB_LED_GREEN PD6
#define FOSC 16000000UL
#define BAUD 115200
#define BAUD_PRESCALE (((F_CPU / (USART_BAUDRATE * 16UL))) - 1)

char buffer[8];
unsigned int len = 8;

int round_ubbr()
{
    double ubbr = (double)FOSC / (16 * BAUD) - 1;
    return (ubbr < 0.0) ? (int)(ubbr - 0.5) : (int)(ubbr + 0.5);
}

void init_rgb(){
	// Configure pin output
    DDRD |= (1 << RGB_LED_RED) | (1 << RGB_LED_GREEN) | (1 << RGB_LED_BLUE);
	//Timer Rouge et Vert
	TCCR0A |= (1 << WGM00) | (1 << WGM01); // Mode Fast PWM
	TCCR0A |= (1 << COM0A1) | (1 << COM0B1);
	TCCR0B |= (1 << CS01); // Prescaler timer0

	// TImer Bleu
	TCCR2A |= (1 << WGM20) | (1 << WGM21); // Mode Fast PWM
	TCCR2A |= (1 << COM2B1); // PWM non inverse sur OC2B
	TCCR2B |= (1 << CS21); // Prescaler timer2 8Mhz (sortie du PWM)

}
void uart_init(unsigned int ubrr)
{
    UBRR0H = (unsigned char)(ubrr >> 8);
    UBRR0L = (unsigned char)(ubrr & 0xFF);
    UCSR0B = (1 << RXEN0) | (1 << TXEN0);
    UCSR0C = (1 << UCSZ01) | (1 << UCSZ00);
}

char uart_rx(void)
{
    while (!(UCSR0A & (1 << RXC0)));
    return UDR0;
}

void uart_tx(char c)
{
    while (!(UCSR0A & (1 << UDRE0)));
    UDR0 = c;
}

void set_rgb(uint8_t r, uint8_t g, uint8_t b)
{
    OCR0A = g;
    OCR0B = r;
    OCR2B = b;
}

void uart_printstr(const char *str)
{
    while (*str)
    {
        uart_tx(*str++);
    }
    uart_tx('\r');
}

int hex_char_to_int(char c)
{
    if (c >= '0' && c <= '9') return c - '0';
    if (c >= 'a' && c <= 'f') return c - 'a' + 10;
    if (c >= 'A' && c <= 'F') return c - 'A' + 10;
    return -1;
}

uint8_t hex_to_uint8(const char *hex)
{
    return (hex_char_to_int(hex[0]) << 4) | hex_char_to_int(hex[1]);
}

void process_color()
{
    if (buffer[0] == '#' && buffer[7] == '\0')
    {
        uint8_t r = hex_to_uint8(&buffer[1]);
        uint8_t g = hex_to_uint8(&buffer[3]);
        uint8_t b = hex_to_uint8(&buffer[5]);
        set_rgb(r, g, b);
        uart_printstr("\nColor updated\n");
    }
    else
    {
        uart_printstr("Invalid format, use #RRGGBB\n");
    }
}

int main()
{
    int ubbr = round_ubbr();
    char c;
    int i = 1;
    buffer[0] = '#';
	bool trigger;
    uart_init(ubbr);
    uart_printstr("Please enter a Hex color to display (format: #RRGGBB)\n");
    
    while (1)
    {
        c = uart_rx();
		if(!trigger)
			uart_tx(buffer[0]);
        uart_tx(c);
        
        if (i < 7 && ((c >= '0' && c <= '9') || (c >= 'a' && c <= 'f') || (c >= 'A' && c <= 'F')))
        {
            buffer[i++] = c;
			trigger = true;
        }
        else if (i == 7)
        {
			init_rgb();
            buffer[i] = '\0';
            process_color();
			trigger = false;
            i = 1;
        }
        else
        {
            uart_printstr("Invalid input, try again\n");
            i = 1;
			trigger = false;
        }
    }
}
