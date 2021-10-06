/*============基本情報============
H22 高校生ものづくりコンテスト
電子回路組立部門　関東地区予選会

作成日時：8月7日
作成者：山崎晃史
所属学校：都立荒川工業高等学校

ファイル名：p40.c
課題番号：1番
================================*/
#include<p18f4550.h>
#include<delays.h>

#define L2 LATBbits.LATB2 //左の7セグメントLED
#define L3 LATBbits.LATB3 //右の7セグメントLED
#define L4 LATBbits.LATB4
#define L5 LATBbits.LATB5
#define L7 LATDbits.LATD7
#define D1k Delay1KTCYx(120) //約0.1msの遅延
#define D10k Delay10KTCYx(120) //約1msの遅延
#define GSW PORTAbits.RA5 //緑タクト
#define HSW PORTAbits.RA4 //ホトインタラプタ

//==定数の宣言==
char L7s[] = { //7セグメントLEDの表示設定
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
	0b00001000, //A
	0b00000011, //B
	0b00100111, //C
	0b00100001, //D
	0b00000110, //E
	0b00001110, //F
	0b00001001, //H
	0b01000111, //L
};
char STMR[] = {0x08,0x04,0x02,0x01}; //ステッピングモータを右回転
char STML[] = {0x01,0x02,0x04,0x08}; //ステッピングモータを左回転

//==変数の宣言==
char a,b,c,i,j,k,l,t;

//==関数の宣言==
void dd(void);
void stmr(void);
void stml(void);

//===========メイン関数==========
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
	
//==変数の初期化==
while(1){
	if(GSW == 0){
		LATD = L7s[16];
		L2 = 0;
		L3 = 1;
	}
	 
	if(GSW == 1){
		LATD = L7s[17];
		L2 = 1;
		L3 = 0;
	}
}
}
