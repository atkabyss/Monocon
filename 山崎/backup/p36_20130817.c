/*==========基本情報==========
H24 高校生ものづくりコンテスト
電子回路組立部門　東京都大会

作成日時：8月7日
作成者：山崎晃史
所属学校：都立荒川工業高等学校

ファイル名：p35.c
課題番号：2番
============================*/
#include<p18f4550.h>
#include<delays.h>

#define L2 LATBbits.LATB2 //左の7セグメントLED
#define L3 LATBbits.LATB3 //右の7セグメントLED
#define L4 LATBbits.LATB4
#define L5 LATBbits.LATB5
#define L7 LATDbits.LATD7
#define D1k Delay1KTCYx(120) //約0.1msの遅延
#define D10k Delay10KTCYx(120) //約1msの遅延
#define BSW PORTAbits.RA4 //青タクト
#define RSW PORTAbits.RA3 //赤タクト

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
	0b00001000, //A
	0b00000011, //B
	0b00100111, //C
	0b00100001, //D
	0b00000110, //E
	0b00001110, //F
	0b00011100, //OFF
	0b00100011, //ON
	0b01111111, //非表示
};
char STMR[] = {0x08,0x04,0x02,0x01}; //ステッピングモータを右回転
char STML[] = {0x01,0x02,0x04,0x08}; //ステッピングモータを左回転

//==変数の宣言==
char a,b,c,i,j,k,l,m,t;

//==関数の宣言==
void stmr(void); //ステッピングモータを右回転
void stml(void); //ステッピングモータを左回転
void stms(void); //ステッピングモータを停止
void dd(void); //7セグメントLEDの両側を表示
void cu(void); //7セグメントLEDのカウントアップ

//==========メイン関数==========
void main(void){
	
	ADCON1 |= 0x0F; //ADコンバータをOFF
	
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
	a = 0; //ステッピングモータ制御
	b = 0; 
	c = 0;
	i = 0; //7セグメントLED
	j = 0; //7セグメントLED
	k = 0;
	l = 0;
	m = 0; //ステッピングモータ制御
	t = 0; //フラグ用
	
while(1){
	if(t == 0){ //初期設定
		LATD = L7s[0];
		L2 = 0;
		t = 1;
	}
	
	if(RSW == 0){
		L2 = 1;
		D10k;
		L2 = 0;
		D10k;
	}
	
	if(RSW == 1){
		L2 = 0;
	}
}
}
//==関数の宣言==
void stmr(void){ //ステッピングモータを右に1回転
	for(a = 0;a<48;a++){
		LATD = STMR[m];
		L7 = 0;
		L7 = 1;
		L7 = 0;
		D1k; //脱調防止の遅延
		
		if(m < 4){
			m = 0;
		}
	}
	
}
void stml(void){ //ステッピングモータを左に1回転
		for(a = 0;a<48;a++){
		LATD = STML[m];
		L7 = 0;
		L7 = 1;
		L7 = 0;
		D1k; //脱調防止の遅延
		
		if(m < 4){
			m = 0;
		}
	}
}
void stms(void){ //ステッピングモータを停止
	a = 50;
}
void dd(void){ //7セグメントLEDの両側を表示
	LATD = L7s[i]; //左側データのセット
	L2 = 0;
	L3 = 1;
	D1k;
	LATD = L7s[j]; //右側データのセット
	L2 = 1;
	L3 = 0;
	D1k;
}
void cu(void){ //7セグメントLEDのカウントアップ
	LATD = L7s[j];
	L3 = 0;
	
	j++;
	
	for(b = 0;b > 10;b++){
		D10k;
	}
}
