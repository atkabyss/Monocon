#include <p18f4550.h>
#include <delays.h>

char STM [] = {0x01, 0x02 ,0x04 ,0x08};
char Led7seg[] = {
	0b0110000,
	0b1101101,
	0b1111001,
	0b0110010,
	0b1011010,
};
void main(void)
{

	char i,g,j;
	
	ADCON1 |= 0x0F;
	
	TRISA = 0b11000000;
	TRISB = 0b00000000;
	TRISC = 0b11111100;
	TRISD = 0b00000000;
	TRISE = 0b11111000;
	
	PORTA = 0;
	PORTB = 0;
	PORTC = 0;
	PORTD = 0;
	PORTE = 0;
	
	LATBbits.LATB2 = 0;
	LATBbits.LATB3 = 0;
	LATBbits.LATB4 = 0;
	LATBbits.LATB5 = 0;    
	
	i = 0;
	while(1) {
		LATD = STM[i];
		LATDbits.LATD7 = 0;
		LATDbits.LATD7 = 1;
		LATDbits.LATD7 = 0;
		Delay1KTCYx(120);
	}
        i++;
		if(i>=4) {
			i = 0;
			for (g=1; g<5; g++) {
				LATD = Led7seg[g];
				LATBbits.LATB2 = 0;
				
				for (j=0; j<10; j++) {
					Delay10KTCYx(120);
		}		
	}
}
	