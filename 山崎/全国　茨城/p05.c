/*======================================
高校生ものづくりコンテスト
電子回路組立部門 全国大会(茨城)

作成日時	：7月31日
作成者		：山崎晃史
所属学校	：東京都立荒川工業高等学校

ファイル名	：p05.c
課題番号	：5番
======================================*/
#include<p18f4550.h>
#include<delays.h>

#define l2 LATBbits.LATB2	//左の7セグLED
#define l3 LATBbits.LATB3	//左の7セグLED
#define l4 LATBbits.LATB4
#define l5 LATBbits.LATB5
#define l7 LATDbits.LATD7
#define D01 Delay1KTCYx(30)
#define D1 Delay1KTCYx(120)
#define D10 Delay10KTCYx(120)
#define ts PORTAbits.RA3		//タクトスイッチ
#define ps PORTAbits.RA4		//ホトインタラプタ
#define tgs PORTAbits.RA5		//トグルスイッチ

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

char STM[] = {0x01,0x03,0x02,0x06,0x04,0x0c,0x08,0x09};	//ステッピングモータの励磁

//=====変数の宣言
unsigned char a,b,j,k,s,f,f2,f3,f4,f5;
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
	
//=====変数の初期化
	a = 18;
	b = 18;
	c = 0;
	i = 0;
	j = 0;
	k = 1;
	s = 0;
	f = 1;
	f2 = 0;
	f3 = 0;
	f4 = 0;
	f5 = 0;
	
	while(1){
		if(ts == 1 && ps == 1 && tgs == 1){
			f2 = 0;
			f3 = 0;
			f4 = 0;
		}
		
		if(tgs == 1 && f == 1){
			a = 18;
			b = 18;
			f4 = 0;
			f2 = 0;		//タクト操作を拒否
			f3 = 0;		//ホト操作を拒否
		}
		
		if(tgs == 0 && ts == 1 && ps == 1){
			f = 1;		//トグル操作を許可
			f2 = 1;		//タクト操作を許可
			f3 = 1;		//ホト操作を許可
			f4 = 1;		//トグルの状態判定
			k = 1;
			a = 16;
			b = 17;
			led();
			stml();
		}
		
		if(ts == 0 && f2 == 1 && f4 == 1){
			f = 0;		//トグル操作を拒否
			f3 = 0;		//ホト操作を拒否
			k = 2;
			a = 0;
			b = 17;
			led();
			stml();
		}
		
		if(ps == 0 && f3 == 1 && f4 == 1){
			f = 0;		//トグル操作を拒否
			f2 = 0;		//タクト操作を拒否
			k = 0;
			a = 16;
			b = 9;
			led();
			stml();
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
	
	if(k == 1 || k == 2){
		led();
	}
	
	if(k == 2){
		led();
	}
	
	i++;
	
	if(i > 7){
		i = 0;
	}
}

void stml(void){
	LATD = STM[i];
	l7 = 0;
	l7 = 1;
	l7 = 0;
	led();
	
	if(k == 1 || k == 2){
		led();
	}
	
	if(k == 2){
		led();
	}
	
	i--;
	
	if(i < 0){
		i = 7;
	}
}

void dcmr(void){
	LATD = 0b00100000;
	l7 = 0;
	l7 = 1;
	l7 = 0;
}

void dcml(void){
	LATD = 0b00010000;
	l7 = 0;
	l7 = 1;
	l7 = 0;
}

void dcms(void){
	LATD = 0b00110000;
	l7 = 0;
	l7 = 1;
	l7 = 0;
}
