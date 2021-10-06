//==========================
//2013.7.30
//H23 課題6
//荒川工業高等学校
//山崎晃史
//==========================
#include<p18f4550.h>
#include<delays.h>

#define L2 LATBbits.LATB2  //"LATBbits.LATB2"を"L2"として定義
#define L3 LATBbits.LATB3  //"LATBbits.LATB3"を"L3"として定義
#define L4 LATBbits.LATB4  //"LATBbits.LATB4"を"L4"として定義
#define L5 LATBbits.LATB5  //"LATBbits.LATB5"を"L5"として定義
#define L7 LATDbits.LATD7  //"LATBbits.LATB7"を"L7"として定義
#define R4 PORTAbits.RA4  //"PORTAbits.RA4"を"R4"として定義
#define R5 PORTAbits.RA5  //"PORTAbits.RA5"を"R5"として定義
#define D1k Delay1KTCYx(120)  //"Delay1KTCYx(120)"を"D1k"として定義

//==変数の宣言==
char a;

//==関数の宣言==
void DCMl(void);  //DCモータを低速回転
void DCMh(void);  //DCモータを高速回転
void DCMs(void);  //DCモータを停止

//===============メイン関数===============
void main(void){
	
	ADCON1 |= 0x0F;  //ADコンバータをOFF
	
//==============入出力の設定==============
	TRISA = 0b11111000;
	TRISB = 0b00000000;
	TRISC = 0b11111100;                          
	TRISD = 0b00000000;
	TRISE = 0b11111000;
	
//============ポートの初期化==============
	PORTA = 0;
	PORTB = 0;
	PORTC = 0;
	PORTD = 0;
	PORTE = 0;                   
	
//======すべての7セグメントLEDを消灯======
	L2 = 1;
	L3 = 1;
	L4 = 1;
	L5 = 1;

//==============変数の初期化==============
	a = 0;
	
while(1)
{   
	if(R4 == 0 && R5 == 0){
		DCMh();
	}
	
	if(R4 == 0 && R5 == 1){
		DCMl();
	}
	
	if(R4 == 1){
		DCMs();
	}
}
}
//==関数の宣言==
void DCMl(void){
	char a;
	LATD = 0b00010000;  
	L7 = 0;
	L7 = 1;
	L7 = 0;
	D1k;
	for(a=0;a<4;a++){
		DCMs();
	}
}

void DCMh(void){
	LATD = 0b00010000;  
	L7 = 0;
	L7 = 1;
	L7 = 0;
}

void DCMs(void){
	LATD = 0b00110000;  
	L7 = 0;
	L7 = 1;
	L7 = 0;
	D1k;
}