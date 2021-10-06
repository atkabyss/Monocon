#include<p18f4550.h>

char Led7seg[] ={
	0b00011100, //上
	0b00100011, //下
};

void main(void)
{
	ADCON1 |= 0x0F; //ADコンバーターオフ
	
	TRISA = 0b11111000;
	TRISB = 0b00000000;
	TRISC = 0b11111100;
	TRISD = 0b00000000;
	TRISE = 0b11111000;
	
	PORTA = 0;
	PORTB = 0;
	PORTC = 0;
	PORTD = 0;
	PORTE = 0;
	
	LATBbits.LATB2 = 1;
	LATBbits.LATB3 = 1;
	LATBbits.LATB4 = 1;
	LATBbits.LATB5 = 1;
	
while(1){
	
	if(PORTAbits.RA4 == 1){
		LATD = Led7seg [0];
		LATBbits.LATB3 = 0;
	}
	if(PORTAbits.RA4 == 0){
		LATD = Led7seg [1];
		LATBbits.LATB3 = 0;
	}
}
}