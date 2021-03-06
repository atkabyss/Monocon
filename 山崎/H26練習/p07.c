/*======================================
平成23年度	高校生ものづくりコンテスト
電子回路組立部門	全国大会?

作成日時	：7月29日
作成者		：山崎晃史
所属学校	：東京都立荒川工業高等学校

ファイル名	：p07.c
課題番号	：7番
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
unsigned char a,j,k,f,f2,f3;
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
	a = 0;	//左の7セグLEDのデータを保持
	b = 0;	//右の7セグLEDのデータを保持
	c = 0;	//カウント用
	i = 0;	//ステッピングモータ制御用
	j = 48;	//ステッピングモータステップ数カウント用
	k = 0;	//未使用
	f = 0;	//フラグ用
	f2 = 0;	//フラグ用
	f3 = 0;	//フラグ用
	
	LATD = l7s[b];
	l3 = 0;
	
	while(1){
		if(ts == 1 && f == 1){
			f = 0;
			j = 48;
		}
		if(ts == 0){
			f2 = 1;		//復帰動作を許可
			f3 = 1;		//ステップ数の記憶を許可
			l3 = 1;
			stmr();
			l3 = 0;
			LATD = l7s[b];
			D1;
		}
		
		if(ps == 0 && j <= 24 && f2 == 1){	//0-4の範囲のとき
			f2 = 0;		//復帰動作を繰り返し実行しない
			for(c=0;c<j+1;c++){
				l3 = 1;
				stml();
				LATD = l7s[b];
				l3 = 0;
				D1;
			}
			D1;
			b = 0;
			LATD = l7s[b];
			f = 1;
		}
		
		if(ps == 0 && j > 24 && f2 == 1){	//	//4-8の範囲のとき
			f2 = 0;		//復帰動作を繰り返し実行しない
			k = 23 - (j - 24);
			for(c=0;c<k;c++){
				l3 = 1;
				stmr();
				LATD = l7s[b];
				l3 = 0;
				D1;
			}
			D1;
			b = 0;
			LATD = l7s[b];
			f = 1;
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
	if(f3 == 1){
		j++;
		
		if(j > 47){
			j = 0;
			b++;
			if(b > 5){
				b = 1;
			
		}
		}
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
}

void stml(void){	//ステッピングモータを反時計回りに回転させる関数
	if(f3 == 1){
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
