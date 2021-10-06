/*============基本情報============
H25　高校生ものづくりコンテスト
電子回路組立部門　東京都大会

作成日時：8月6日
作成者：No.?? 山崎晃史
所属学校：荒川工業高等学校

ファイル名:p29.c
課題番号:2番
================================*/
#include<p18f4550.h>
#include<delays.h>

#define L2 LATBbits.LATB2 //左の7セグメントLED
#define L3 LATBbits.LATB3 //右の7セグメントLED
#define L4 LATBbits.LATB4
#define L5 LATBbits.LATB5
#define L7 LATDbits.LATD7 //クロックパルス
#define TGSW PORTAbits.RA5 //トグルスイッチ
#define HSW PORTAbits.RA4 //フォトインタラプタ
#define D1k Delay1KTCYx(120) //約0.1msの遅延
#define D10k Delay10KTCYx(120) //約1msの遅延

//==定数の宣言==
char STMR[] = {0x08,0x04,0x02,0x01}; //ステッピングモータを右回転
char STML[] = {0x01,0x02,0x04,0x08}; //ステッピングモータを左回転
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
	0b00001001, //H
	0b01000111, //L
};
//==変数の宣言==
char a,b,i,j,t;

//==関数の宣言==
void dd(void); //7セグメントLEDの両側表示
void stmr(void); //ステッピングモータを右回転
void seml(void); //ステッピングモータを左回転
void dcmr(void); //DCモータを右回転
void dcml(void); //DCモータを左回転

/*=========================
		メイン関数
=========================*/
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
	a = 0;
	b = 0;
	i = 10;
	j = 0;
	t = 0;
	
while(1){
	LATD = L7s[i]; //データのセット
	L2 = 0; //左の7セグを表示
	
	if(TGSW == 0){
		LATD = L7s[i]; //データのセット
		
		i++;
		
		D10k; //約1秒の遅延
		D10k;
		D10k;
		D10k;
		D10k;
		D10k;
		D10k;
		D10k;
		D10k;
		D10k;
	
		if(i == 16){
			i = 10;
		}
	}
}
}

//==関数の宣言==
void dd(void){ //7セグメントLEDの両側表示
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
	for(a = 0;a < 48;a++){
		LATD = STMR[b]; //データのセット
		L7 = 0;
		L7 = 1;
		L7 = 0;
		D1k; //チャタリング防止の遅延
		
		b++;
		
		if(b>4){ //4つ以上のデータはないため0に戻す
			b = 0;
		}
	}
}

void seml(void){ //ステッピングモータを左回転
	for(a = 0;a < 48;a++){
		LATD = STML[b]; //データのセット
		L7 = 0;
		L7 = 1;
		L7 = 0;
		D1k; //チャタリング防止の遅延
		
		b++;
		
		if(b>4){ //4つ以上のデータはないため0に戻す
			b = 0;
		}
	}
}

void dcmr(void){ //DCモータを右回転
	LATD = 0b00100000;
	L7 = 0;
	L7 = 1;
	L7 = 0;
	D1k;
}

void dcml(void){ //DCモータを右回転
	LATD = 0b00100000;
	L7 = 0;
	L7 = 1;
	L7 = 0;
	D1k;
}
