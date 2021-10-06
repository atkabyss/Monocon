/*======================================
高校生ものづくりコンテスト
電子回路組立部門 全国大会(茨城)

作成日時	：7月31日
作成者		：山崎晃史
所属学校	：東京都立荒川工業高等学校

ファイル名	：p01.c
課題番号	：1番
======================================*/
#include<p18f4550.h>
#include<delays.h>

#define l2 LATBbits.LATB2	//左の7セグLED
#define l3 LATBbits.LATB3	//左の7セグLED
#define l4 LATBbits.LATB4
#define l5 LATBbits.LATB5
#define l7 LATDbits.LATD7
#define D01 Delay100TCYx(120)
#define D1 Delay1KTCYx(120)
#define D10 Delay10KTCYx(120)
#define ts PORTAbits.RA3		//タクトスイッチ
#define ps PORTAbits.RA4		//ホトインタラプタ
#define tgs PORTAbits.RA5	//トグルスイッチ

//=====定数の宣言
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
	0b00100000,	//a-10
	0b00000011,	//b-11
	0b00100111,	//c-12
	0b00100001,	//d-13
	0b00000110,	//E-14
	0b00001110,	//F-15
	0b00001001,	//H-16
	0b01000111,	//L-17
	0b01111111	//非表示-18
};

char STM[] = {0x08,0x04,0x02,0x01};	//ステッピングモータの励磁

//=====変数の宣言
unsigned char a,b,j,k,f,f2;
char c,i;

//=====関数の宣言
void led(void);
void stmr(void);
void stml(void);
void dcmr(void);
void dcml(void);
void dcms(void);

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
	
	while(1){
		if(tgs == 0 && ts == 0){
			LATD = l7s[16];
			l3 = 0;
			l2 = 1;
		}
		
		if(tgs == 1 && ts == 0){
			LATD = l7s[17];
			l2 = 0;
			l3 = 1;
		}
		
		if(ts == 1){
			l2 = 1;
			l3 = 1;
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

void stmr(void){
	LATD = STM[i];
	l7 = 0;
	l7 = 1;
	l7 = 0;
	D1;
	
	if(k == 1 && k == 2){
		D1;
	}
	
	if(k == 2){
		D1;
	}
	
	i++;
	
	if(i > 3){
		i = 0;
	}
}

void stml(void){
	LATD = STM[i];
	l7 = 0;
	l7 = 1;
	l7 = 0;
	D1;
	
	if(k == 1 && k == 2){
		D1;
	}
	
	if(k == 2){
		D1;
	}
	
	i--;
	
	if(i < 0){
		i = 3;
	}
}

void dcmr(void){
	LATD = 0b0010000;
	l7 = 0;
	l7 = 1;
	l7 = 0;
}

void dcml(void){
	LATD = 0b0001000;
	l7 = 0;
	l7 = 1;
	l7 = 0;
}

void dcms(void){
	LATD = 0b0011000;
	l7 = 0;
	l7 = 1;
	l7 = 0;
}
