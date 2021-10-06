//=====================
//2013.7.30
//課題3
//荒川工業高等学校
//山崎晃史
//=====================
#include<p18f4550.h>
#include<delays.h>

#define PA PORTAbits  //"PORTAbits"を"PA"として定義
#define Ds Delay1KTCYx(12)  //"Delay1KTCYx(12)"を"Ds"として定義
#define Dl Delay1KTCYx(120)  //"Delay1KTCYx(120)"を"Dl"として定義
#define L2 LATBbits.LATB2  //"LATBbits.LATB2"を"L2"として定義
#define L3 LATBbits.LATB3  //"LATBbits.LATB3"を"L3"として定義
#define L7 Led7seg  //"Led7seg"を"L7"として定義

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
	0b01111111,    //非表示
};

char i,j,k;   //変数の宣言

void led (void);  //7セグメントLEDの両方を点灯

	
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
	i = 10;
	j = 10;
	k = 0;
	
while(1){
	if(PA.RA5 == 0 && k==0){
		Dl;
		
		if(j>3){
			j = 2;
			i = 1;
		}
		
		i--;
		if(i==-1){
			i=9;
			j--;
			}
		if(j==-1){
			j=2;
			i=0;
			}
		k=1;
				}
	if(PA.RA5 == 1){
		Dl;
		k=0;
		}
	led();
	}
}

void led (void){  //7セグメントLEDの両方を点灯
	LATD = L7[i];
	L2 = 1;
	L3 = 0;
	Ds;
	LATD = L7[j];
	L3 = 1;
	L2 = 0;
	Ds;
}
