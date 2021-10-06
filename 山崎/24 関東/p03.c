/*======================================
平成24年度 高校生ものづくりコンテスト
電子回路組立部門 関東地区予選

作成日時	：8月1日
作成者		：山崎晃史
所属学校	：東京都立荒川工業高等学校

ファイル名	：p03.c
課題番号	：3番
======================================*/
#include<p18f4550.h>
#include<delays.h>

#define l2 LATBbits.LATB2	//7セグ左
#define l3 LATBbits.LATB3	//7セグ右
#define l4 LATBbits.LATB4
#define l5 LATBbits.LATB5
#define l7 LATDbits.LATD7
#define D01 Delay100TCYx(120)	//0.001
#define D1 Delay1KTCYx(120)		//0.01
#define D10 Delay10KTCYx(120)	//0.1
#define tgs PORTAbits.RA3	//トグル
#define ts PORTAbits.RA4	//タクト
#define ps PORTAbits.RA5	//フォトIC

//=====定数の宣言=====
char l7s[] = {		//7セグLEDの表示設定
	0b01000000,	//0
	0b01111001,	//1
	0b00100100,	//2
	0b00110000,	//3
	0b00011001,	//4
	0b00010010,	//5
	0b00000010,	//6
	0b01011000,	//7
	0b00000000,	//8
	0b00010000,	//9
	0b00001001,	//H	-10
	0b01000111,	//L	-11
};
char STM[] = {0x01,0x03,0x02,0x06,0x04,0x0c,0x08,0x09};	//ステッピングモータの1-2相励磁

//=====変数の宣言=====
unsigned char a,b,j,k,f,f2;
char c,i;

//=====関数の宣言=====
void led(void);
void stmr(void);
void stml(void);

/*======================================
		メイン関数
======================================*/
void main(void){

//=====ADコンバータをOFF
	ADCON1 |= 0x0F;
	
//=====入出力の設定
	TRISA = 0b11111000;
	TRISB = 0b00000000;
	TRISC = 0b11111000;
	TRISD = 0b00000000;
	TRISE = 0b11111000;
	
//=====ポートの初期化
	PORTA = 0;
	PORTB = 0;
	PORTC = 0;
	PORTD = 0;
	PORTE = 0;
	
//=====すべての7セグLEDを消灯
	l2 = 1;
	l3 = 1;
	l4 = 1;
	l5 = 1;
	
//=====変数の初期化
	a = 1;
	b = 0;
	c = 0;
	i = 0;
	j = 0;
	k = 0;
	f = 0;
	f2 = 0;
	
	while(1){
		if(ps == 0){
			stmr();
		}
	}
}

/*======================================
		自作関数
======================================*/
void led(void){
	LATD = l7s[a];
	l2 = 0;
	D01;
	l2 = 1;
	LATD = l7s[b];
	l3 = 0;
	D01;
	l3 = 1;
}

void stml(void){
	LATD = STM[i];
	l7 = 0;
	l7 = 1;
	l7 = 0;
	D1;
	
	if(k == 1){
		D1;
	}
	
	i++;
	
	if(i > 7){
		i = 0;
	}
}

void stmr(void){
	LATD = STM[i];
	l7 = 0;
	l7 = 1;
	l7 = 0;
	D1;
	
	if(k == 1){
		D1;
	}
	
	i--;
	
	if(i < 0){
		i = 7;
	}
}
