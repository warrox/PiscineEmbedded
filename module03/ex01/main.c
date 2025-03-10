#include <util/delay.h>
#include <avr/io.h>
#define RGB_LED_RED PD5
#define RGB_LED_BLUE PD3
#define RGB_LED_GREEN PD6
int main(void){
	
	DDRD |= (1 << RGB_LED_RED);
	DDRD |= (1 << RGB_LED_BLUE);
	DDRD |= (1 << RGB_LED_GREEN);
	while(1){
		PORTD |= (1 << RGB_LED_RED);
		_delay_ms(1000);
		PORTD &= ~(1 << RGB_LED_RED);
		_delay_ms(50);
		PORTD |= (1 << RGB_LED_GREEN);
		_delay_ms(1000);
		PORTD &= ~(1 << RGB_LED_GREEN);
		_delay_ms(50);
		PORTD |= (1 << RGB_LED_BLUE);
		_delay_ms(1000);
		PORTD &= ~(1 << RGB_LED_BLUE);
		_delay_ms(1000);
		//Yellow
		PORTD |= (1 << RGB_LED_RED);
		PORTD |= (1 << RGB_LED_GREEN);
		_delay_ms(10000);
		PORTD &= ~(1 << RGB_LED_RED);
		_delay_ms(50);
		//CYAN
		PORTD |= (1 << RGB_LED_BLUE);
		_delay_ms(1000);
		PORTD &= ~(1 << RGB_LED_GREEN);
		_delay_ms(50);
		//MAGENTA
		PORTD |= (1 << RGB_LED_RED);
		_delay_ms(1000);
		//WHITE
		PORTD |= (1 << RGB_LED_GREEN);
		_delay_ms(1000);
		PORTD &=~(1 << RGB_LED_RED);
		PORTD &=~(1 << RGB_LED_GREEN);
		PORTD &=~(1 << RGB_LED_BLUE);
		_delay_ms(50);	
	}
}
/*• T1/OC0B/PCINT21 – Port D, Bit 5
T1, Timer/Counter1 counter source.
OC0B, output compare match output: The PD5 pin can serve as an external output for the Timer/Counter0 compare match
B. The PD5 pin has to be configured as an output (DDD5 set (one)) to serve this function. The OC0B pin is also the output
pin for the PWM mode timer function.
PCINT21: Pin change interrupt source 21. The PD5 pin can serve as an external interrupt source*/
