//=====================
//2013.7.30
//課題3
//荒川工業高等学校
//山崎晃史
//=====================
#include<p18f4550.h>
#include<delays.h>

char Led7seg[] = {
	0b01000000,    //0
	0b01111001,    //1
	0b00100100,    //2
	0b00110000,    //3
	0b00011001,    //4
	0b00010010,    //5
	0b00000010,    //6
	0b01011000,    //7
	0b00000000,    //8
	0b00010000,    //9
};

char i,j,k;   //変数の宣言

void led (void){  //7セグメントLEDの両方を点灯
	LATD = Led7seg[i];
	LATBbits.LATB2 = 1;
	LATBbits.LATB3 = 0;
	Delay1KTCYx(12);
	LATD = Led7seg[j];
	LATBbits.LATB3 = 1;
	LATBbits.LATB2 = 0;
	Delay1KTCYx(12);
}

//////////////メイン関数///////////////
void main(void){
	
	ADCON1 |= 0x0F;  //ADコンバータOFF
	
	TRISA = 0b11111000;  //入出力の初期化
	TRISB = 0b00000000;
	TRISC = 0b11111100;
	TRISD = 0b00000000;
	TRISE = 0b11111000;
	
	PORTA = 0;  //ポートの初期化
	PORTB = 0;
	PORTC = 0;
	PORTD = 0;
	PORTE = 0;
	
	LATBbits.LATB2 = 1;  //すべての7セグメントLEDをOFF
	LATBbits.LATB3 = 1;
	LATBbits.LATB4 = 1;
	LATBbits.LATB5 = 1;
	i = 0;
	j = 2;
	k = 0;
	
while(1){
	if(PORTAbits.RA5 == 0){
		led();
		k = 1;
		
		if(j == 0 && i == -1){
			i = 0;
			j = 2;
			led();
		}
		
		if(j == 0 && i == -1){
			i = 9;
			led();
		}
		
		if(j == 1 && i == -1){
			i = 9;
			led();
		}
		
		if(i == -1){
			j = j - 1;
			led();
		}
		
		i= i - 1;
		
	if(k = 1){
		LATBbits.LATB2 = 0;
		LATBbits.LATB3 = 0;
	}
		}
	}
}