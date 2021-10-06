/*======================================
平成24年度 高校生ものづくりコンテスト
電子回路組立部門 関東地区予選会

作成日時	：7月23日
作成者		：山崎晃史
所属学校	：東京都立荒川工業高等学校

ファイル名	：p005.c
課題番号	：5番
======================================*/
#include<p18f4550.h>
#include<delays.h>

#define l2 LATBbits.LATB2		//左側の7セグメントLED
#define l3 LATBbits.LATB3		//右側の7セグメントLED
#define l4 LATBbits.LATB4
#define l5 LATBbits.LATB5
#define l7 LATDbits.LATD7
#define D01 Delay1KTCYx(12)		//約0.01msの遅延
#define D1 Delay1KTCYx(120)		//約0.1msの遅延
#define D10 Delay10KTCYx(120)	//約1msの遅延
#define tgs PORTAbits.RA3		//トグルスイッチ
#define ts PORTAbits.RA4		//タクトスイッチ
#define ps PORTAbits.RA5		//フォトIC

//=====定数の宣言=====
char l7s[] = {
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
	0b01111111,	//非表示-10
	0b00001001,	//H-11
	0b01000111	//L-12
};

char STMR[] = {0x08,0x04,0x02,0x01};
char STML[] = {0x01,0x02,0x04,0x08};

//=====変数の宣言=====
char a,b,c,i,j,k,f,f2;

//=====関数の宣言=====
void led(void);		//2つのLEDを同時に表示させる関数
void stmr(void);	//ステッピングモータを時計回りに回転させる関数
void stml(void);	//ステッピングモータを反時計回りに回転させる関数

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
	
//=====すべての7セグメントLEDを消灯=====
	l2 = 1;
	l3 = 1;
	l4 = 1;
	l5 = 1;
	
//=====変数の初期化=====
	a = 0;		//左の7セグLEDのデータを格納
	b = 0;		//右の7セグLEDのデータを格納
	c = 0;		//カウント用
	i = 0;		//ステッピングモータ制御用
	j = 0;		//未使用
	k = 0;		//ステッピングモータの回転速度制御用
	f = 0;		//フラグ用
	f2 = 0;		//フラグ用
	
	while(1){
		if(tgs == 0){
			
			if(ps == 1){
				stmr();
			}
			
			if(ps == 0){
				stml();
			}
			
			LATD = l7s[11];
			l3 = 0;
			D1;
			l3 = 1;
		}
		
		if(tgs == 1){
			LATD = l7s[12];
			l3 = 0;
		}
		
	}
}

/*======================================
		自作関数
======================================*/
void led(void){		//2つのLEDを同時に表示させる関数
	LATD = l7s[a];
	l2 = 0;
	D01;
	l2 = 1;
	LATD = l7s[b];
	l3 = 0;
	D01;
	l3 = 1;
}

void stmr(void){	//ステッピングモータを時計回りに回転させる関数
	LATD = STMR[i];
	l7 = 0;
	l7 = 1;
	l7 = 0;
	i++;
	D1;
	
	if(i > 4){
		i = 0;
	}
}

void stml(void){	//ステッピングモータを反時計回りに回転させる関数
	LATD = STML[i];
	l7 = 0;
	l7 = 1;
	l7 = 0;
	i++;
	D1;
	
	if(i > 4){
		i = 0;
	}
}
