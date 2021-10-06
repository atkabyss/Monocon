/*======================================
平成23年度	高校生ものづくりコンテスト
電子回路組立部門	全国大会?

作成日時	：7月29日
作成者		：山崎晃史
所属学校	：東京都立荒川工業高等学校

ファイル名	：p04.c
課題番号	：4番
======================================*/
#include<p18f4550.h>
#include<delays.h>

#define l2 LATBbits.LATB2	//左の7セグLED
#define l3 LATBbits.LATB3	//右の7セグLED
#define l4 LATBbits.LATB4
#define l5 LATBbits.LATB5
#define l7 LATDbits.LATD7
#define D01 Delay100TCYx(120)	//0.001msの遅延
#define D1 Delay1KTCYx(120)		//0.01msの遅延
#define D10 Delay10KTCYx(120)	//0.1msの遅延
#define tgs PORTAbits.RA3	//トグルスイッチ
#define ts PORTAbits.RA4	//タクトスイッチ
#define ps PORTAbits.RA5	//ホトインタラプタ

//=====定数の宣言
unsigned char l7s[] = {
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
	0b00001000,	//A-10
	0b00000011,	//b-11
	0b01000110,	//C-12
	0b00101011,	//OFF-13
	0b01110111,	//ON-14
	0b00111111	//--15
};
unsigned char STM[] = {0x08,0x04,0x02,0x01};

//=====変数の宣言
unsigned char a,j,k,f,f2;
char b,c,i;

//=====関数の宣言
void led(void);		//2つのLEDを同時に表示させる関数
void stmr(void);	//ステッピングモータを時計回りに回転させる関数
void stml(void);	//ステッピングモータを反時計回りに回転させる関数
void dcmr(void);	//DCモータを時計回りに回転させる関数
void dcml(void);	//DCモータを反時計回りに回転させる関数
void dcms(void);	//DCモータを停止させる関数

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
	a = 15;	//左の7セグLEDのデータを保持
	b = 15;	//右の7セグLEDのデータを保持
	c = 0;	//カウント用
	i = 0;	//ステッピングモータ制御用
	j = 0;	//未使用
	k = 0;	//未使用
	f = 1;	//フラグ用
	f2 = 0;	//フラグ用
	
	while(1){
		led();
		
		if(tgs == 0 && f == 1){
			D1;
			f = 0;
			a = 1;
			b = 0;
		}
		
		if(tgs == 0){
			for(c=0;c<50;c++){
				led();
			}
			
			if(tgs == 0){
				b--;
				
				if(b < 0){
					b = 9;
					a = 0;
				}
				
				if(a == 0 && b == 0){
					while(1){
						led();
					}
				}
			}
		
		
		
		}
	}
}
/*======================================
	自作関数
======================================*/
void led(void){		//2つのLEDを同時に表示させる関数
	LATD = l7s[a];
	l2 = 0;
	D1;
	l2 = 1;
	LATD = l7s[b];
	l3 = 0;
	D1;
	l3 = 1;
}

void stmr(void){	//ステッピングモータを時計回りに回転させる関数
	LATD = STM[i];
	l7 = 0;
	l7 = 1;
	l7 = 0;
	D1;
	i++;
	
	if(i > 3){
	i = 0;
	}
}

void stml(void){	//ステッピングモータを反時計回りに回転させる関数
	LATD = STM[i];
	l7 = 0;
	l7 = 1;
	l7 = 0;
	D1;
	i--;
	
	if(i < 0){
	i = 3;
	}
}

void dcmr(void){	//DCモータを時計回りに回転させる関数
	LATD = 0b00100000;
	l7 = 0;
	l7 = 1;
	l7 = 0;
}

void dcml(void){	//DCモータを反時計回りに回転させる関数
	LATD = 0b00010000;
	l7 = 0;
	l7 = 1;
	l7 = 0;
}

void dcms(void){	//DCモータを停止させる関数
	LATD = 0b00110000;
	l7 = 0;
	l7 = 1;
	l7 = 0;
}
