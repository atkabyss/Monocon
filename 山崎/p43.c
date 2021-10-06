/*============基本情報============
H22 高校生ものづくりコンテスト
電子回路組立部門　関東地区予選会

作成日時：8月8日
作成者：山崎晃史
所属学校：都立荒川工業高等学校

ファイル名：p42.c
課題番号：5番
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
void dd(void); //左右の7セグメントLEDを同時に表示
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
	a = 0; //遅延制御
	b = 0; //フラグ用
	c = 0;
	i = 0; //左の7セグメントLED表示制御
	j = 0; //右の7セグメントLED表示制御
	k = 0; //ステッピングモータの回転制御
	l = 0;
	t = 0; //初期化用
	
while(1){
	if(t == 0){
		LATD = L7s[i];
		L3 = 0;
		t = 1;
	}
	
	if(GSW == 0){
		b = 1;
	}
	
	if(b == 1){
		for(a = 0;a < 48;a++){
			i++;
			LATD = L7s[i];
			L3 = 0;
			D1k;
			L3 = 1;
			
			stmr();
			
			if(i > 2){
				i = 3;
				while(1){
					L3 = 0;
				}
				}
			}
		}
	}
}
//==関数の宣言==
void dd(void){ //左右の7セグメントLEDを同時に表示
	LATD = L7s[i];
	L2 = 0;
	L3 = 1;
	D1k;
	LATD = L7s[j];
	L2 = 1;
	L3 = 0;
	D1k;
}
void stmr(void){ //ステッピングモータを右回転
	for(c = 0;c < 48;c++){
		LATD = STMR[k];
		L7 = 0;
		L7 = 1;
		L7 = 0;
		LATD = L7s[i];
		L3 = 0;
		D1k;
		L3 = 1;
		
		k++;
		
		if(k > 4){
			k = 0;
		}
	}
}
void stml(void);