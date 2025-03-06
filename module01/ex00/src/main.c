#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>
#define LED_PIN PB1 
static void wait(){
	volatile uint32_t  i = 0; // use volatile to force compiler to use it + uint32 for capacity size for a loop of 250k
	while(i < 250000){
		i++;
	}
	
} 
//man p117
int main(void){
	DDRB |= (1 << LED_PIN); // set as output	
	while(1){
		PORTB ^= (1 << LED_PIN); // toggle
		wait();
	}
	return(0);
}
