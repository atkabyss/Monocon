#include<p18f4550.h>
#include<delays.h>

char Led7seg[] ={
	0b01000000, //0
	0b11111111, //非表示
};

void main(void)
{
	char i;
	
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
	
	LATD = Led7seg[0];
	LATBbits.LATB2 = 0;
while(1){

	if(PORTAbits.RA3 == 0){
		LATD = Led7seg[1];
		Delay10KTCYx(120);
		LATD = Led7seg[0];
		Delay10KTCYx(120);
	}
	if(PORTAbits.RA3 == 1){
		LATD = Led7seg[0];
	}
}
}