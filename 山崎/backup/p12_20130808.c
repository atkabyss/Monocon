#include<p18f4550.h>
#include<delays.h>

char Led7seg[] = {       //7セグメントLEDの表示制御
	0b01110111,      //ON
	0b00101011,      //OFF
};

//////////////////メイン関数////////////////////
void main(void)
{
	ADCON1 |= 0x0F;  //ADコンバータの初期化
	
	TRISA = 0b11111000;    //入出力の制御
	TRISB = 0b00000000;
	TRISC = 0b11111100;
	TRISD = 0b00000000;
	TRISE = 0b11111000;
	
	PORTA = 0;    //ポートの初期化
	PORTB = 0;
	PORTC = 0;
	PORTD = 0;
	PORTE = 0;
	
	LATBbits.LATB2 = 1;     //7セグメントLEDの表示OFF
	LATBbits.LATB3 = 1;
	LATBbits.LATB4 = 1;
	LATBbits.LATB5 = 1;

while(1){
	
	if(PORTAbits.RA4 = 0){
		LATD = Led7seg[0];
		LATBbits.LATB2 = 0;
	}
    
	if(PORTAbits.RA4 = 1){
		LATD = Led7seg[1];
		LATBbits.LATB2 = 0;
	}
}
}
