//=========================
//2013.8.2
//H24関東大会 課題3
//荒川工業高等学校
//山崎晃史
//=========================
#include<p18f4550.h>
#include<delays.h>
                                               
#define L2 LATBbits.LATB2  //"LATBbits.LATB2"を"L2"として定義
#define L3 LATBbits.LATB3  //"LATBbits.LATB3"を"L3"として定義
#define L4 LATBbits.LATB4  //"LATBbits.LATB4"を"L4"として定義
#define L5 LATBbits.LATB5  //"LATBbits.LATB5"を"L5"として定義
#define L7 LATDbits.LATD7  //"LATDbits.LATD7"を"L7"として定義
#define D1k Delay1KTCYx(120)  //"Delay1KTCYx(120)"を"D1k"として定義
#define D10k Delay10KTCYx(120)  //"Delay10KTCYx(120)"を"D10k"として定義
#define R3 PORTAbits.RA3  //"PORTAbits.RA3"を"R3"として定義
#define R4 PORTAbits.RA4  //"PORTAbits.RA4"を"R4"として定義
#define R5 PORTAbits.RA5  //"PORTAbits.RA5"を"R5"として定義
#define L7s Led7seg  //"Led7seg"を"L7s"として定義

//==定数の宣言==
char L7s[] = {
	0b01000000,  //0
	0b01111001,  //1
	0b00100100,  //2
	0b00110000,  //3
	0b00011001,  //4
	0b00010010,  //5 
	0b00000010,  //6
	0b01011000,  //7
	0b00000000,  //8
	0b00010000,  //9
	0b00001001,  //H
	0b01000111,  //L
	0b01111111,  //非表示
};
char STMl[] = {0x08, 0x04, 0x02, 0x01};
char STMr[] = {0x01, 0x02, 0x04, 0x08};

//==変数の宣言==
char a,b,i,j,k,l;

//==関数の宣言==
void STML(void);
void STMR(void);
void DCML(void);
void DCMR(void);
void dd(void);

//==============メイン関数==============
void main(void){
	
	ADCON1 |= 0x0F;  //ADコンバータをOFF
	
//=============入出力の設定=============
	TRISA = 0b11111000;
	TRISB = 0b00000000;
	TRISC = 0b11111100;
	TRISD = 0b00000000;
	TRISE = 0b11111000;
	
//============ポートの初期化============
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
	a = 0;  //フラグ用変数
	b = 0;  //フラグ用変数
	i = 0;
	j = 0;
	k = 0;
	l = 0;
	
while(1){
	if(R5 == 0){
		STML();
	}
	
	if(R5 == 1){
		a = 0;
	}
	
}
}
//==関数の宣言==
void STML(void){
	for(a=0;a<48;a++){  //ステッピングモータを時計回りに1回転させる
		LATD = STMl[k];
		L7 = 0;
		L7 = 1;
		L7 = 0;
		D1k;  //脱調防止のwait 
		
		k++;
		
		if(k >= 4){
			k = 0;
		}
		
		if(R5 == 1){
			a = 50;
		}
	}
}
void STMR(void){
	for(a=0;a>48;a++){  //ステッピングモータを反時計回りに1回転させる
		LATD = STMr[k];
		L7 = 0;
		L7 = 1;
		L7 = 0;
		D1k;  //脱調防止のwait
		
		k++;
		
		if(k >= 4){
			k = 0;
		}
	}
}
void DCML(void){  //DCモータを時計回りに回転
	LATD = 0b00100000;
	L7 = 0;
	L7 = 1;
	L7 = 0;
	D1k;
}
	
void DCMR(void){  //DCモータを反時計回りに回転
	LATD = 0b00010000;
	L7 = 0;
	L7 = 1;
	L7 = 0;
	D1k;
}
	
void dd(void){  //7セグメントLEDの両方を表示
	LATD = L7s[i];
	L2 = 0;
	L3 = 1;
	D1k;
	LATD = L7s[j];
	L3 = 0;
	L2 = 1;
	D1k;
}