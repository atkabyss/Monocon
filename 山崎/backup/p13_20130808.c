#include<p18f4550.h>
#include<delays.h>

char Led7seg[] = {       //7セグメントLEDの表示制御
	0b01000000,      //0
	0b01111001,      //1
	0b00100100,      //2
	0b00110000,      //3
	0b00011001,      //4
	0b00010010,      //5
	0b00000010,      //6
	0b01011000,      //7
	0b00000000,      //8
	0b00010000,      //9
	0b00001000,      //A
	0b00000011,      //B
	0b01000110,      //C
	0b00100001,      //D
	0b00000110,      //E
	0b00001110,      //F
	0b01110111,      //ON
	0b00101011,      //OFF
};

//////////////////メイン関数////////////////////
void main (void)
{   
	char i;
	
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
    i = 0;

while(1){
	
	LATD = Led7seg[i];
	LATBbits.LATB3 = 0;
	
	if(PORTAbits.RA4 == 0){
		for(i=0;i<17;i++){
		LATD = Led7seg[i];         
		Delay10KTCYx(120);
		Delay10KTCYx(120);
		Delay10KTCYx(120);
		Delay10KTCYx(120);
		Delay10KTCYx(120);
		Delay10KTCYx(120);
		Delay10KTCYx(120);
		Delay10KTCYx(120);
		Delay10KTCYx(120);
		Delay10KTCYx(120);
        
		if(i>=15){
		i = -1;
		}
		}
	}
}
}