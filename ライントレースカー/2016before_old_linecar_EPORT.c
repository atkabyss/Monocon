/*
=================================================================
	PIC18F4550-HIDmon 
	Microchip XC18
		
	　■注意■
	　1. プログラム転送時には、ライントレース基板の電源を必ずOFFにする。
	　   USBの電源と干渉し、コンピュータに大きな損傷を与えることがある。
	　2. CポートのRC4,5はUSBと接続されているので取り扱い注意
	
	a.プログラム概要
		・電源投入時は、センサ感度調整モードになる。
		・黒タクトスイッチを押すと、ライントレースモードに移行する。
	
	b.配線
		・3つのセンサは、右からRA0、RA1、RA2、RA3、RA4に接続
		・右モータのモータドライバの入力 IN1はRD3、IN2はRD4
		・左モータのモータドライバの入力 IN1はRD0、IN2はRD1
	
	c.プログラムの説明
		0.モータの回転方向の確認
		　約2秒間モータが回転し、前進するように配線を変更
		
		1.センサの感度調整モード
		　プログラム開始と同時に、センサ感度調整モードに入る。
		　白い台の上で、半固定抵抗を左いっぱいに回す。
		　LEDが消灯するまで半固定抵抗を右に回していく。
		　黒いライン上位てLEDが点灯することを確認
		　
		　黒いタクトスイッチを押すと、
		　センサの感度調整モードが終了して、
		　ライントレースモードに移行
	
	2.ライントレースモード
		　RA1センサのみで、ライントレースを行う
		　
		　黒いタクトスイッチを押すと、
		　ライントレースモードが終了して、
		　停止モードに移行
		　		→電源スイッチをOFFにしてもOK
		　
	3.停止モード
		　赤色LEDが500msが点滅して、ライントレースを終了
=================================================================
*/
#include <xc.h>
#define _XTAL_FREQ	48000000			//48MHz __dealy_ms(): MAX 16
										//		__delay_us(): MAX 16426

// ■ポートの定義
// ボードに付属されているポートの定義
#define SW0		PORTCbits.RC2
#define YLED	LATCbits.LATC0
#define RLED	LATCbits.LATC1


// フォトセンサ関係

#define R1PHSW		PORTEbits.RE		// 左前フォトセンサ
#define R0PHSW		PORTEbits.RE0		// 右前フォトセンサ
#define C1PHSW		PORTEbits.RE1		// 中フォトセンサ**
#define L0PHSW		PORTEbits.RE2		// 左前フォトセンサ**
#define L1PHSW		PORTEbits.RE		// 左前フォトセンサ

// モータ関係
// 前進・後進が反転する場合は、
//	・対応策1	モータの取り付け端子を逆にする
//	・対応策2	IN1とIN2の定義を逆にする


#define lmIN1	LATBbits.LATB2		// 	左モータドライバ　IN1**
#define lmIN2	LATBbits.LATB3		// 	左モータドライバ　IN2**
#define lmIN3	LATBbits.LATB		// 	左モータドライバ　IN3
#define rmIN1	LATBbits.LATB1		// 	右モータドライバ　IN1
#define rmIN2	LATBbits.LATB0		// 	右モータドライバ　IN2
#define rmIN3	LATBbits.LATB		// 	右モータドライバ　IN3

// ON / OFF
#define B_LINE		1
#define W_LINE		!B_LINE

#define SW_OFF		1
#define SW_ON		!SW_OFF

#define LED_OFF		0
#define LED_ON		!LED_OFF

#define LED7OFF		1
#define LED7ON		!LED7OFF

#define M_STOP		0
#define M_CW		1
#define M_CCW		2
#define M_BRAKE		3


// ■関数の宣言
// 初期化ルーチン
void init(void);

// 遅延関係
void delay1ms(unsigned char);
void delay10ms(unsigned char);
void delay100ms(unsigned char);
void delay1s(unsigned char);
void forwardPwm(char);

// ライトレースカーの制御
#define forward		{lmIN1=1;lmIN2=0;rmIN1=1;rmIN2=0;}
#define lTurn		{lmIN1=1;lmIN2=1;rmIN1=1;rmIN2=0;}//**
#define rTurn		{lmIN1=1;lmIN2=0;rmIN1=1;rmIN2=1;}//**
#define stop		{lmIN1=0;lmIN2=0;rmIN1=0;rmIN2=0;}
#define sStop		{lmIN1=1;lmIN2=1;rmIN1=1;rmIN2=1;}


/*--------------------------------------
	メイン関数
--------------------------------------*/
void main(void)
{
	// PICの初期化
	init();
	
	
	// ■ モータの前進
	forward;
	delay1s(2);
	lTurn;
	delay1s(2);
	rTurn;
	delay1s(2);
	PORTDbits.RD5 = 1;
	PORTDbits.RD6 = 1;
	PORTDbits.RD7 = 1;
	delay1s(2);
	
	
	// ■ モータの停止
	stop;
	
	
	// ■ センサの感度調整ルーチン
	//RLED=LED_ON
	do {
		if(R0PHSW == SW_ON && C1PHSW == SW_OFF && L0PHSW == SW_OFF){
			PORTDbits.RD5 = 1;
		delay100ms(1);}
		if(R0PHSW == SW_OFF && C1PHSW == SW_ON && L0PHSW == SW_OFF){
			PORTDbits.RD6 = 1;
		delay100ms(1);}
		if(R0PHSW == SW_OFF && C1PHSW == SW_OFF && L0PHSW == SW_ON){
			PORTDbits.RD7 = 1;
		delay100ms(1);}
		LATD = 0;
		
		
		
		
	} while(SW0 == SW_OFF);
	delay1ms(30);				// チャタリング防止
	//RLED=LED_OFF
	// OFFになるまで(ONの間繰り返す)
	while(SW0 == SW_ON);
	delay1ms(30);				// チャタリング防止
	
	// ■ ライントレースモード
	while(1){
	do{
		forwardPwm(95);
	}while(SW0 == SW_OFF);
	delay1ms(30);
	
	while(SW0 == SW_ON);
	delay1ms(30);
	
	do{
		forwardPwm(100);
	}while(SW0 == SW_OFF);
	delay1ms(30);
	
	while(SW0 == SW_ON);
	delay1ms(30);
	}
	// ■ ライントレース終了後の処理
	STOP;
	while(1) {
		// 赤LEDの点滅
		RLED = LED_ON;
		delay100ms(5);
		RLED = LED_OFF;
		delay100ms(5);
	}
	
	while(1);
}
/*--------------------------------------
	PICの初期化作業
--------------------------------------*/
void init(void)
{
	// ■入出力ピンをデジタルモードに設定します
	ADCON1 |= 0x0F;		// 　ADコンバータOFF
	
	// ■入出力の設定をします
	// 　CポートはUSBが接続されているので注意 0で出力
	TRISA = 0b11111111;
	TRISB = 0b00000000;
	TRISC = 0b00111100;
	TRISD = 0b00000000;
	TRISE = 0b11111111;

	// ■ポートの初期化 すべて0
	PORTA = 0;
	PORTB = 0;
	PORTC = 0;
	PORTD = 0;
	PORTE = 0;
	
	
}
/*----------------------------------------
	遅延関係
------------------------------------------*/
//	1ms x unitのウエイト ---------------
void delay1ms(unsigned char unit)
{
	unsigned char i;
	for (i=0; i<unit; i++) {
		__delay_ms(1);
	}
}
//	10ms x unitのウエイト ---------------
void delay10ms(unsigned char unit)
{
	unsigned char i;
	for (i=0; i<unit; i++) {
		__delay_ms(10);
	}
}
//	100ms x unitのウエイト ---------------
void delay100ms(unsigned char unit)
{
	unsigned char i, j;
	for (i=0; i<unit; i++) {
		for (j=0; j<10; j++) {
			__delay_ms(10);
		}
	}
}
//	1s x unitのウエイト ---------------
void delay1s(unsigned char unit)
{
	unsigned char i, j, k;
	for (i=0; i<unit; i++) {
		for (j=0; j<100; j++) {
			__delay_ms(10);
		}
	}
}

void forwardPwm(char dt){
	char i;
	
	if(0<=dt && dt<=100){
		for(i=0;i<dt;i++){
			forward;
		}
		for(i=dt;i<100;i++){
			stop;
		}
	}
}
