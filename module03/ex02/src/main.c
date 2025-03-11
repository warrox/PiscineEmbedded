#include <avr/io.h>
#include <util/delay.h>
#define RGB_LED_RED PD5
#define RGB_LED_BLUE PD3
#define RGB_LED_GREEN PD6
/*Green : PD6(0C0A/AIN0)
RED : PD5(OC0B/T1)
BLUE : PD3(OC2B/int1)*/
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
void set_rgb(uint8_t r, uint8_t g, uint8_t b){
	OCR0A = g;
    OCR0B = r;
    OCR2B = b;
}
void wheel(uint8_t pos) {
	pos = 255 - pos;
	if (pos < 85) {
	set_rgb(255 - pos * 3, 0, pos * 3);
	} else if (pos < 170) {
	pos = pos - 85;
	set_rgb(0, pos * 3, 255 - pos * 3);
	} else {
	pos = pos - 170;
	set_rgb(pos * 3, 255 - pos * 3, 0);
	}
}
int main(void){
	init_rgb();	
	while(1){
		for(int i = 0; i < 255;++i){
			wheel(i);
			_delay_ms(10);
		}
	}
}
