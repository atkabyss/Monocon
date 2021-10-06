/*
	2013.8.5 電子回路組立部門　関東大会
	荒川工業高等学校　山崎晃史
	
	課題5
	トグルスイッチが"H"のときステッピングモータが回転
	ただしフォトICが"受光"のときに時計回り、"遮光"のときに反時計周りに回転
	
	かつ右の7セグメントLEDにトグルスイッチの状態"H""L"を表示
*/
#include<p18f4550.h>
#include<delays.h>

#define L2 LATBbits.LATB2
#define L3 LATBbits.LATB3
#define L4 LATBbits.LATB4
#define L5 LATBbits.LATB5
#define L7 LATDbits.LATD7
#define D1k Delay1KTCYx(120)
#define D10k Delay10KTCYx(120)
#define R3 PORTAbits.RA3
#define R4 PORTAbits.RA4
#define R5 PORTAbits.RA5

//==定数の宣言==
char L7s[] = { //7セグメントLEDの表示制御
	0b01000000, //0
	0b01111001, //1
	0b00100100, //2
	0b00110000, //3
	0b00011001, //4
	0b00010010, //5
	0b00000010, //6
	0b01011000, //7
	0b00000000, //8
	0b00010000, //9
};

//==変数の宣言==
char i;
char STMR[] = {0x01,0x02,0x04,0x08};
char STML[] = {0x08,0x04,0x02,0x01};

//==関数の宣言==
void stml(void);
void stmr(void);

//=====メイン関数=====
void main(void){
	
	ADCON1 |= 0x0F; //ADコンバータOFF
	
//=====入出力の設定=====
	TRISA = 0b11111000;
	TRISB = 0b00000000;
	TRISC = 0b11111100;
	TRISD = 0b00000000;
	TRISE = 0b11111000;
	
//=====ポートの初期化=====
	PORTA = 0;
	PORTB = 0;
	PORTC = 0;
	PORTD = 0;
	PORTE = 0;
	
//=====すべての7セグメントLEDを消灯=====
	L2 = 1;
	L3 = 1;
	L4 = 1;
	L5 = 1;
	
while(1){
	if(){
	
	}
}
}

