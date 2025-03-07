#define RGB_LED PD5
int main(void){
	DDRB |= (1 << RGB_LED);
	TCCR1B |= (1  << WGM12);

	while(1);
}
