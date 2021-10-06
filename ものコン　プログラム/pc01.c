#include <xc.h>

#define _XTAL_FREQ 48000000
#define GSW PORTEbits.RE2
#define OSW PORTEbits.RE3
#define l0 LATBbits.LATB1
#define l1 LATBbits.LATB2
#define l2 LATBbits.LATB2
#define l3 LATBbits.LATB3


void main(void){
	ADCON1 |= 0x0F;
	
	TRISA = 0b11000000;
	TRISB = 0b00000000;
	TRISC = 0b11111100;
	TRISD = 0b00000000;
	TRISE = 0b00000111;
	
	PORTA = 0;
	PORTB = 0;
	PORTC = 0;
	PORTD = 0;
	PORTE = 0;
	
	LATBbits.LATB0 = 1;
	LATBbits.LATB1 = 1;
	LATBbits.LATB2 = 1;
	LATBbits.LATB3 = 1;
	
	while(1){
		if(GSW == 1 && OSW == 1){
			LATD = 0b00101011;
			l0 = 1;
			l1 = 0;
		}
		
		if(GSW == 0 && OSW == 1){
			LATD = 0b01110111;
			l0 = 1;
			l1 = 0;
		}
	}
}