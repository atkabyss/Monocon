/*================基本情報=================
平成25年度　高校生ものづくりコンテスト
電子回路組立部門　東京都大会

作成日時：8月10日
作成者：2番　山崎晃史
所属学校：東京都立荒川工業高等学校

ファイル名：p05.c
課題番号：5番
=========================================*/
#include<p18f4550.h>
#include<delays.h>

#define L2 LATBbits.LATB2 //左の7セグメントLED
#define L3 LATBbits.LATB3 //右の7セグメントLED
#define L4 LATBbits.LATB4
#define L5 LATBbits.LATB5
#define L7 LATDbits.LATD7
#define D1k Delay1KTCYx(120) //約0.1msの遅延
#define D10k Delay10KTCYx(120) //約1msの遅延
#define GSW PORTAbits.RA5 //緑タクトスイッチ
#define OSW PORTAbits.RA3 //橙タクトスイッチ

//==定数の宣言==
char L7s[] = { //7セグメントLEDの表示制御
	0b01000000, //0
	0b01111001, //1
	0b00100100, //2
	0b00010010, //5
	0b00000000, //8
	0b01111110, //イルミネーションパターン1
	0b01111101, //イルミネーションパターン2
	0b01111011, //イルミネーションパターン3
	0b01110111, //イルミネーションパターン4
	0b01101111, //イルミネーションパターン5
	0b01011111, //イルミネーションパターン6
	0b00101011, //OFF
	0b01110111, //ON
	0b01111111, //非表示
};
char STMR[] = {0x08,0x04,0x02,0x01}; //ステッピングモータを右回転
char STML[] = {0x01,0x02,0x04,0x08}; //ステッピングモータを左回転
	
//==変数の宣言==
char a,b,i,j,k,f;

//==関数の宣言==
void dd(void); //7セグメントLEDの両側を同時に表示
void stmr(void); //ステッピングモータを右回転
void stml(void); //ステッピングモータを左回転
void dcmr(void); //DCモータを右回転
void dcms(void); //DCモータを停止
void ilh(void); //イルミネーションの高速表示
void ill(void); //イルミネーションの低速表示

//=================メイン関数=================
void main(void)
{
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
	a = 0; //ステッピングモータの回転制御用
	b = 0; //未使用
	i = 0; //左の7セグメントLED表示用
	j = 0; //右の7セグメントLED表示用
	k = 0; //繰り返し作業用
	f = 0; //フラグ用
	
while(1){
	if(OSW == 0){ //橙タクトスイッチがONのとき
		dcmr();
	}
	if(OSW == 1){ //橙タクトスイッチがOFFのとき
		dcms();
	}
}
}
//==関数の宣言==
void dd(void){ //7セグメントLEDの両側を同時に表示
	LATD = L7s[i]; //左の7セグメントLEDのデータをセット
	L2 = 0; //左の7セグメントLEDをON
	L3 = 1; //右の7セグメントLEDをOFF
	D1k; //脱調防止の遅延
	LATD = L7s[j]; //右の7セグメントLEDのデータをセット
	L2 = 1; //左の7セグメントLEDをOFF
	L3 = 0; //右の7セグメントLEDをON
	D1k; //脱調防止の遅延
}
void stmr(void){ //ステッピングモータを右回転
	LATD = STMR[a]; //データのセット
	L7 = 0;
	L7 = 1;
	L7 = 0;
	D1k; //脱調防止の遅延
	
	a++;
	
	if(a > 4){ //4つ以上のデータがないため0に戻す
		a = 0;
	}
}
void stml(void){ //ステッピングモータを左回転
	LATD = STML[a]; //データのセット
	L7 = 0;
	L7 = 1;
	L7 = 0;
	D1k; //脱調防止の遅延
	
	a++;
	
	if(a > 4){ //4つ以上のデータがないため0に戻す
		a = 0;
	}
}
void dcmr(void){ //DCモータを右回転
	LATD = 0b00100000; //データのセット
	L7 = 0;
	L7 = 1;
	L7 = 0;
	D1k; //脱調防止の遅延
}
void dcms(void){ //DCモータを停止
	LATD = 0b00110000; //データのセット
	L7 = 0;
	L7 = 1;
	L7 = 0;
	D1k; //脱調防止の遅延
}
void ilh(void){ //イルミネーションの高速表示
	LATD = L7s[5]; //イルミネーションパターン1のデータをセット
	L2 = 0;
	for(k = 0;k < 5;k++){
		D1k; //約0.5msの遅延
	}
	L2 = 1; 
	L3 = 0;
	for(k = 0;k < 5;k++){ 
		D1k;
	}
	LATD = L7s[6];
	for(k = 0;k < 5;k++){
		D1k;
	}
	LATD = L7s[7];
	for(k = 0;k < 5;k++){
		D1k;
	}
	LATD = L7s[8];
	for(k = 0;k < 5;k++){
		D1k;
	}
	L3 = 1;
	L2 = 0;
	LATD = L7s[8];
	for(k = 0;k < 5;k++){
		D1k;
	}
	LATD = L7s[9];
	for(k = 0;k < 5;k++){
		D1k;
	} 
	LATD = L7s[10];
	for(k = 0;k < 5;k++){
		D1k;
	}
}
void ill(void){ //イルミネーションの低速表示
	LATD = L7s[5]; //イルミネーションパターン1のデータをセット
	L2 = 0; 
	D10k; //約1msの遅延
	L2 = 1; 
	L3 = 0;    
	D10k;
	LATD = L7s[6];
	D10k;
	LATD = L7s[7];
	D10k;
	LATD = L7s[8];
	D10k;
	L3 = 1;
	L2 = 0;
	LATD = L7s[8];
	D10k;
	LATD = L7s[9];
	D10k;
	LATD = L7s[10];
	D10k;
}
