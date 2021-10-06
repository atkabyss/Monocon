//=====================
//2013.7.31
//H23 課題4
//荒川工業高等学校
//山崎晃史
//=====================
#include<p18f4550.h>
#include<delays.h>

#define sw4 PORTAbits.RA4 //"PORTAbits.RA4"を"sw4"として定義
#define sw5 PORTAbits.RA5 //"PORTAbits.RA5"を"sw5"として定義
 
//==変数の宣言==
char i;

//==関数の宣言==
void DCMc(void);  //DCモータの回転制御
void DCMcr(void);  //DCモータの逆回転制御
void DCMs(void);  //DCモータの停止制御

//==============メイン関数===============
void main(void)
{
	ADCON1 |= 0x0F; //ADコンバータをOFF
	
//===============入出力の設定============
	TRISA = 0b11111000;
	TRISB = 0b00000000;
	TRISC = 0b11111100;
	TRISD = 0b00000000;
	TRISE = 0b11111000;
	
//============ポートの初期化=============
	PORTA = 0;
	PORTB = 0;
	PORTC = 0;
	PORTD = 0;
	PORTE = 0;
	
//======すべての7セグメントLEDをOFF======
	LATBbits.LATB2 = 1;
	LATBbits.LATB3 = 1;
	LATBbits.LATB4 = 1;
	LATBbits.LATB5 = 1;
	
while(1){
	if(sw4 == 0 && sw5 == 0){
		DCMc();
	}
	
	if(sw4 == 0 && sw5 == 1){
		DCMcr();
	}
	
	if(sw4 == 1){
		DCMs();
	}
}
}
//==関数の宣言==
void DCMc(void){
	char a;
	LATD = 0b00010000;  
	LATDbits.LATD7 = 0;
	LATDbits.LATD7 = 1;
	LATDbits.LATD7 = 0;
	Delay1KTCYx(120);
	for(a=0;a<4;a++){
	LATD = 0b00000000;  
	LATDbits.LATD7 = 0;
	LATDbits.LATD7 = 1;
	LATDbits.LATD7 = 0;
		Delay1KTCYx(120);
	}
}

void DCMcr(void){
	LATD = 0b00100000;  
	LATDbits.LATD7 = 0;
	LATDbits.LATD7 = 1;
	LATDbits.LATD7 = 0;
}

void DCMs(void){
	LATD = 0b00000000;  
	LATDbits.LATD7 = 0;
	LATDbits.LATD7 = 1;
	LATDbits.LATD7 = 0;
}
