#include <xc.h>

#define _XTAL_FREQ 48000000
#define GSW PORTAbits.RA2
#define OSW PORTAbits.RA1
#define l0 LATBbits.LATB1
#define l1 LATBbits.LATB2
#define l2 LATBbits.LATB2
#define l3 LATBbits.LATB3


void main(void){
	ADCON1 |= 0x0F;
	
	TRISA = 0b11001110;
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
		if(OSW == 1 && GSW == 1){
			LATD = 0b11000000;
			l0 = 0;
			l1 = 1;
		}
		
		if(OSW == 0 && GSW == 1){
			LATD = 0b11111001;
			l0 = 0;
			l1 = 1;
		}
		
		if(OSW == 1 && GSW == 0){
			LATD = 0b11111001;
			l0 = 0;
			l1 = 1;
		}
		
		if(OSW == 0 && GSW == 0){
			LATD = 0b10100100;
			l0 = 0;
			l1 = 1;
		}
	}
}