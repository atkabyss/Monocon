/*=================================================================
	3E29 山崎晃史
	課題研究用pg 
	
	ライントレースのみ
=================================================================
#################################################################
	
	正常動作したpg

	do {
		if(checkRPHSW() == WLINE && checkLPHSW() == WLINE)	fowrd();
		if(checkRPHSW() == BLINE)	left();
		if(checkLPHSW() == BLINE)	right();
		
/*		if(checkRPHSW() == BLINE){	//右センサON
			delay10ms(30);		// チャタリング防止
			rf++; //右フラグに加算
		}
		if(checkLPHSW() == BLINE){	//左センサON
			delay10ms(30);		// チャタリング防止
			lf++; //左フラグに加算
		}/*
	} while(PSW == SWOFF);
	delay1ms(30);

#################################################################*/
#include <p18f2550.h>
#include <delays.h>

//ポート
#define YLED	LATCbits.LATC0		// RC0　出力で黄色LED
#define RLED	LATCbits.LATC1		// RC1　出力で赤色LED
#define PSW 	PORTCbits.RC2		// RC2　入力でタクトSW
//リフレクタ
#define RPHSW	PORTAbits.RA0		// 右
#define CPHSW	PORTAbits.RA1		// 中
#define LPHSW	PORTAbits.RA2		// 左
#define RPHLED	LATAbits.LATA5		// 右インジケータ
#define CPHLED	LATCbits.LATC0		// 中インジケータ
#define LPHLED	LATCbits.LATC1		// 左インジケータ
//モータ
#define RDCM	LATBbits.LATB1		// 	右
#define LDCM	LATBbits.LATB0		// 	左
#define RDCMLED	LATCbits.LATC7		// 	右インジケータ
#define LDCMLED	LATCbits.LATC6		// 	右インジケータ
//ONOFF
#define BLINE	0
#define WLINE	!BLINE
#define SWON	0
#define SWOFF	!SWON
#define LEDOFF	0
#define LEDON	!LEDOFF
#define DCMOFF	0;
#define DCMON	!DCMOFF

//関数の宣言
void init(void);
void allLed(char);
char checkRPHSW(void);	//右フォトリフレクタ
char checkCPHSW(void);	//中フォトリフレクタ
char checkLPHSW(void);	//左フォトリフレクタ
void delay1ms(unsigned char);
void delay10ms(unsigned char);
void delay100ms(unsigned char);
void delay1s(unsigned char);
void fowrd(void);	//モータ前進
void right(void);	//モータ右回転
void left(void);	//モータ左回転
void Cline(void);	//交差ポイントを検出

//変数の宣言と初期化
int ff=0,			//フラグ制御用フラグ
	rf=0,			//右センサフラグ
	lf=0;			//左センサフラグ
char pf=0,
	cnt=0;
/*======================================
	メイン関数
======================================*/
void main(void)
{
	init();			//PICの初期化

	allLed(LEDON);	//LED点灯確認
	delay1s(1);
	allLed(LEDOFF);
	
	do {			//センサの感度調整ルーチン
		checkRPHSW();
		checkCPHSW();
		checkLPHSW();
	} while(PSW == SWOFF);
	delay1ms(30);				//チャタリング防止
	
	while(PSW == SWON);			//ONになるまで継続
	delay1ms(30);				//チャタリング防止
	
	do {		//ライントレース
		if(checkRPHSW() == WLINE && checkLPHSW() == WLINE)	fowrd();
		if(checkRPHSW() == BLINE)	left();
		if(checkLPHSW() == BLINE)	right();
		
		} while(PSW == SWOFF);
	delay1ms(30);				//チャタリング防止
	
	//初期A地点での動作
	while(pf == 3){
		PORTBbits.RB4 = 0; //モータ
		PORTBbits.RB5 = 0; //モータ
		PORTBbits.RB7 = 0; //LEDイルミpt1
	}
	
	//B地点での動作
	while(pf == 4){
		if(cnt == 0){
		PORTBbits.RB6 = 0; //LEDイルミpt2
		}
		delay1s(3);
		cnt = 1;
		if(cnt == 1){
		PORTBbits.RB6 = 0; //LEDイルミpt2停止
		}
	}
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
	
		
	//ONになるまで
	while(PSW == SWON);
	delay1ms(30);				//チャタリング防止
	
	
	//ライントレース終了後の処理
	RDCM = DCMOFF;
	LDCM = DCMOFF;
	allLed(LEDOFF);
	while(1) {
		// 赤LEDの点滅
		RLED = LEDON;
		delay100ms(5);
		RLED = LEDOFF;
		delay100ms(5);
	}
	
	while(1);
}
//前進
void fowrd(void)
{
	RDCMLED = LEDON;	RDCM = DCMON;
	LDCMLED = LEDON;	LDCM = DCMON;
}

//右回転
void right(void)
{
	RDCMLED = LEDOFF;	RDCM = DCMOFF;
	LDCMLED = LEDON;	LDCM = DCMON;
}

//左回転
void left(void)
{
	RDCMLED = LEDON;	RDCM = DCMON;
	LDCMLED = LEDOFF;	LDCM = DCMOFF;
}

//右センサチェック
char checkRPHSW(void)
{
	char mode;
	
	if(RPHSW == WLINE) {
		mode = WLINE;
		RPHLED = LEDON;
	}
	else {
		mode = BLINE;
		RPHLED = LEDOFF;
	}
	
	return mode;
}

//中センサチェック
char checkCPHSW(void)
{
	char mode;
	
	if(CPHSW == WLINE) {
		mode = WLINE;
		CPHLED = LEDON;
	}
	else {
		mode = BLINE;
		CPHLED = LEDOFF;
	}
	
	return mode;
}

//左センサチェック
char checkLPHSW(void)
{
	char mode;
	
	if(LPHSW == WLINE) {
		mode = WLINE;
		LPHLED = LEDON;
	}
	else {
		mode = BLINE;
		LPHLED = LEDOFF;
	}
	
	return mode;
}

//すべてのLEDを制御
void allLed(char mode)
{
	RPHLED  = mode;
	CPHLED  = mode;
	LPHLED  = mode;
	RDCMLED = mode;
	LDCMLED = mode;
}
//PICの初期化
void init(void)
{
	ADCON1 |= 0x0F;	//ADコンバータOFF
	
	//入出力の設定
	//CポートはUSBが接続されているので注意 0で出力
	TRISA = 0b11000111;
	TRISB = 0b00000000;
	TRISC = 0b00111100;

	//ポートの初期化
	PORTA = 0;
	PORTB = 0;
	PORTC = 0;
}

//1msの遅延
void delay1ms(unsigned char unit)
{
	unsigned char i;
	for(i=0; i<unit; i++) {
		Delay100TCYx(120);
	}
}

//10msの遅延
void delay10ms(unsigned char unit)
{
	unsigned char i;
	for(i=0; i<unit; i++) {
		Delay1KTCYx(120);	//10ms
	}
}

//100msの遅延
void delay100ms(unsigned char unit)
{
	unsigned char i;
	for(i=0; i<unit; i++) {
		Delay10KTCYx(120);	//100ms
	}
}

//1sの遅延
void delay1s(unsigned char unit)
{
	unsigned char i, j;
	for(j=0; j<unit; j++) {
		for(i=0; i<10; i++) {
			Delay10KTCYx(120);	//100ms
		}
	}
}

void Cline(void){	//交差ポイントを検出
	if(RPHSW == BLINE && LPHSW == BLINE){
		delay100ms(1);
		if(RPHSW == BLINE && LPHSW == BLINE){
			pf++;
		}
	delay1ms(30);				//チャタリング防止
	}
}

