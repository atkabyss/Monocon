/*======================================
平成25年度 高校生ものづくりコンテスト
電子回路組立部門 九州大会

作成日時	：7月23日
作成者		：山崎晃史
所属学校	：東京都立荒川工業高等学校

ファイル名	：p3.c
課題番号	：3番
======================================*/
#include<p18f4550.h>
#include<delays.h>

#define l2 LATBbits.LATB2		//左の7セグLED
#define l3 LATBbits.LATB3		//右の7セグLED
#define l4 LATBbits.LATB4
#define l5 LATBbits.LATB5
#define l7 LATDbits.LATD7
#define D01 Delay1KTCYx(12)		//約0.01msの遅延
#define D1 Delay1KTCYx(120)		//約0.1msの遅延
#define D10 Delay10KTCYx(120)	//約1msの遅延
#define ps PORTAbits.RA3		//ホトインタラプタ
#define tgs PORTAbits.RA4		//トグルスイッチ
#define ts PORTAbits.RA5		//タクトスイッチ

//=====定数の宣言=====
char l7s[] = {
	0b01000000,	//0
	0b01111001,	//1
	0b00100100,	//2
	0b00110000,	//3
	0b00011001,	//4
	0b00010010,	//5
	0b00000010,	//6
	0b01111000,	//7
	0b00000000,	//8
	0b00010000,	//9
	0b00001000,	//A-10
	0b00000011,	//b-11
	0b00100111,	//c-12
	0b00100001,	//d-13
	0b00000110,	//E-14
	0b00001110,	//F-15
	0b00001001,	//H-16
	0b01000111,	//L-17
	0b01111111	//非表示-18
};

char STMR[] = {0x08,0x04,0x02,0x01};
char STML[] = {0x01,0x02,0x04,0x08};
//=====変数の宣言=====
char a,b,c,i,j,k,f;

//=====関数の宣言=====
void led(void);
void stmr(void);
void stml(void);
void dcml(void);
void dcmr(void);
void dcms(void);

/*======================================
		メイン関数
======================================*/
void main(void){

//=====ADコンバータをOFF=====
	ADCON1 |= 0x0F;
	
//=====入出力の設定=====
	TRISA = 0b11111000;
	TRISB = 0b00000000;
	TRISC = 0b11111000;
	TRISD = 0b00000000;
	TRISE = 0b11111000;
	
//=====ポートの初期化=====
	PORTA = 0;
	PORTB = 0;
	PORTC = 0;
	PORTD = 0;
	PORTE = 0;
	
//=====すべての7セグLEDを消灯=====
	l2 = 1;
	l3 = 1;
	l4 = 1;
	l5 = 1;

//=====変数の初期化=====
	a = 0;
	b = 0;
	c = 0;
	i = 0;
	j = 0;
	k = 0;
	f = 0;
	
	while(1){
		led();
		if(tgs == 1){
			a = 0;
			b = 0;
			j = 0;
			f = 1;
		}
		
		if(tgs == 0){
			if(f == 1){
				for(c=0;c<50;c++){
				led();
					if(tgs == 1){
						a = 0;
						b = 0;
						j = 0;
						f = 1;
					}
				}
			}
			j++;
			if(j > 5){
				j = 0;
			}
			switch(j){
			case 0:
				a = 0;
				b = 0;
				break;
				
			case 1:
				a = 1;
				b = 5;
				break;
				
			case 2:
				a = 3;
				b = 0;
				break;
				
			case 3:
				a = 4;
				b = 5;
				break;
				
			case 4:
				a = 3;
				b = 0;
				break;
			
			case 5:
				a = 1;
				b = 5;
				break;
				
			default:
				break;
			}
		}
		
		if(ts == 0){
			switch(j){
			case 0:
				a = 0;
				b = 0;
				break;
				
			case 1:
				a = 18;
				b = 15;
				break;
				
			case 2:
				a = 1;
				b = 14;
				break;
				
			case 3:
				a = 2;
				b = 13;
				break;
				
			case 4:
				a = 1;
				b = 14;
				break;
			
			case 5:
				a = 18;
				b = 15;
				break;
				
			default:
				break;
			}
		}
	}
}
/*======================================
		自作関数
======================================*/
void led(void){
	LATD = l7s[a];
	l2 = 0;
	D1;
	l2 = 1;
	LATD = l7s[b];
	l3 = 0;
	D1;
	l3 = 1;
}

void stmr(void){
	LATD = STMR[i];
	l7 = 0;
	l7 = 1;
	l7 = 0;
	i++;
	if(i < 4){
		i = 0;
	}
	D01;
}

void stml(void){
	LATD = STML[i];
	l7 = 0;
	l7 = 1;
	l7 = 0;
	i++;
	if(i < 4){
		i = 0;
	}
	D01;
}

void dcml(void){
	LATD = 0b00100000;
	l7 = 0;
	l7 = 1;
	l7 = 0;
}

void dcmr(void){
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
