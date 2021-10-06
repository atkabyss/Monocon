/*
=================================================================
	PIC18F4550-HIDmon 
	Microchip XC18
		
	　■注意■
	　1. プログラム転送時には、ライントレース基板の電源を必ずOFFにする。
	　   USBの電源と干渉し、コンピュータに大きな損傷を与えることがある。
	　2. CポートのRC4,5はUSBと接続されているので取り扱い注意
	
	a.プログラム概要
		ライントレースカー
		中央のセンサのみでライントレースを行う。
		プログラムスタート時は、センサの感度調整モードで起動
		黒タクトスイッチを押すと、ライントレースモードに移行する。
	
	b.配線
		・センサは、右からRA0、RA1、RA2、RA3、RA4に接続
		・モータ基板の入力(PIC12F675) GP2(IN3)、GP1(IN2)、GP0(IN1)
		・モータ基板の出力(PIC12F675) GP0(IN1)->GP5(OUT1)->IN1、GP1(IN2)->GP4(OUT2)->IN2
		・右のモータ基板の LATD3->GP0(IN1)、LATD4->GP1(IN2)、LATD5->GP2(IN3)
		・左のモータ基板の LATD0->GP0(IN1)、LATD1->GP1(IN2)、LATD2->GP2(IN3)
	
	c.プログラムの説明
		1.センサの感度調整モード
		　プログラム開始と同時に、センサ感度調整モードに入る。
		　半固定抵抗を調整して感度を調整する。
			センサが黒上だと、インジケータが点灯
			センサが白上だと、インジケータが消灯
		
		　黒いタクトスイッチを押すと、赤色LEDが消灯して
		　センサの感度調整モードが終了して
		　ライントレースモードに移行
	
	2.ライントレースモード
		　黄色LEDが点灯
		　1つのセンサのみ(RA1)で、ライントレースを行う
		　
		　黒いタクトスイッチを押すと、黄色LEDが消灯して
		　ライントレースモードが終了して
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


//ランプ関係
#define FLED0		PORTBbits.RB0		//ヘッドランプ右
#define FLED1		PORTBbits.RB1		//ヘッドランプ左
#define PLED0		PORTBbits.RB2		//パトランプ右
#define PLED1		PORTBbits.RB3		//パトランプ中右
#define PLED2		PORTBbits.RB4		//パトランプ中左
#define PLED3		PORTBbits.RB5		//パトランプ左
#define BLED0		PORTBbits.RB6		//バックランプ右
#define BLED1		PORTBbits.RB7		//バックランプ左

// フォトセンサ関係
#define R1PHSW		PORTAbits.RA0		// 右フォトセンサ
#define R0PHSW		PORTAbits.RA1		// 中フォトセンサ
#define C1PHSW		PORTAbits.RA2		// 左フォトセンサ
#define L0PHSW		PORTAbits.RA3		// 左フォトセンサ
#define L1PHSW		PORTAbits.RA4		// 左フォトセンサ

// モータ関係
// 前進・後進が反転する場合は、
//	・対応策1	モータの取り付け端子を逆にする
//	・対応策2	IN1とIN2の定義を逆にする
#define lmIN1	LATDbits.LATD0		// 	左モータドライバ　IN1
#define lmIN2	LATDbits.LATD1		// 	左モータドライバ　IN2
#define lmIN3	LATDbits.LATD2		// 	左モータドライバ　IN3
#define rmIN1	LATDbits.LATD3		// 	右モータドライバ　IN1
#define rmIN2	LATDbits.LATD4		// 	右モータドライバ　IN2
#define rmIN3	LATDbits.LATD5		// 	右モータドライバ　IN3

// ON / OFF
#define B_LINE		1
#define W_LINE		!B_LINE

#define SW_OFF		1
#define SW_ON		!SW_OFF

#define LED_OFF		0
#define LED_ON		!LED_OFF

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


// ライトレースカーの制御
#define forward		{lmIN1=1; lmIN2=0; rmIN1=1; rmIN2=0;}
#define rTurn		{lmIN1=1; lmIN2=0; rmIN1=1; rmIN2=1;}
#define lTurn		{lmIN1=1; lmIN2=1; rmIN1=1; rmIN2=0;}
#define stop		{lmIN1=0; lmIN2=0; rmIN1=0; rmIN2=0;}
#define sStop		{lmIN1=1; lmIN2=1; rmIN1=1; rmIN2=1;}
void forwardms(unsigned char);


/*--------------------------------------
	メイン関数
--------------------------------------*/
void main(void)
{
	// PICの初期化
	init();
	
	// ■ 前進・停止
	forward;
	delay1s(2);
	stop;
	
	// ■ センサの感度調整ルーチン
	// RLED = LED_ON;
	do {
	} while(SW0 == SW_OFF);
	delay1ms(30);				// チャタリング防止
	// RLED = LED_OFF;
	
	// OFFになるまで(ONの間繰り返す)
	while(SW0 == SW_ON);
	delay1ms(30);				// チャタリング防止
	

	// ■ ライントレースモード
	YLED = LED_ON;
	int count = 0;
	int lineflag = 0;
	int waittime = 0;
	int linetime = 0;
	int SW = 0;
	int PLED = 0;
	int PLEDT = 0;
	do {
		if (L1PHSW == W_LINE && C1PHSW == W_LINE && R1PHSW == W_LINE) SW = 0;	//左白 中白 右白
		if (L1PHSW == W_LINE && C1PHSW == W_LINE && R1PHSW == B_LINE) SW = 1;	//左白 中白 右黒
		if (L1PHSW == W_LINE && C1PHSW == B_LINE && R1PHSW == W_LINE) SW = 2;	//左白 中黒 右白
		if (L1PHSW == W_LINE && C1PHSW == B_LINE && R1PHSW == B_LINE) SW = 3;	//左白 中黒 右黒
		if (L1PHSW == B_LINE && C1PHSW == W_LINE && R1PHSW == W_LINE) SW = 4;	//左黒 中白 右白
		if (L1PHSW == B_LINE && C1PHSW == W_LINE && R1PHSW == B_LINE) SW = 5;	//左黒 中白 右黒
		if (L1PHSW == B_LINE && C1PHSW == B_LINE && R1PHSW == W_LINE) SW = 6;	//左黒 中黒 右白
		if (L1PHSW == B_LINE && C1PHSW == B_LINE && R1PHSW == B_LINE) SW = 7;	//左黒 中黒 左黒
		delay10ms(1);
		switch(SW){
			//ラインを探す(未定)
			case 0:{
				char dt=10;
				char i=0;;
			
					for (i=0; i<dt; i++) {
						rTurn;
					}
					for (i=dt; i<50; i++) {
						stop;
					}
				i=0;
			break;
			}
			//左モーター回転(右旋回)
			case 1:{
			rTurn;
			break;
			}
			//(直進)
			case 2:{
			forward;
			break;
			}
			//右モーター回転(C点認識)
			case 3:{
			rTurn;
			break;
			}
			//右モーター回転(左旋回)
			case 4:{
			lTurn;
			break;
			}
			//ラインを探す(未定)
			case 5:{
			forward;
			break;
			}
			//ラインを探す(左旋回)
			case 6:{
			lTurn;
			break;
			}
			//全部黒の動作
			case 7:{
			
				// 交差点の判定
				if (linetime > 6) {
					lineflag = 1;
					waittime = 0;
					linetime = 0;
				}
				else {
					linetime++;
				}
				
				forward;
				
			}
		
		}
		// 交差点の動作
		if (lineflag == 1) {
		
			//1秒待つ
			if (waittime > 650) {
				count++;
				waittime = 0;
				lineflag = 0;
			
				//バックランプ消灯
				BLED0 = 0;
				BLED1 = 0;
			}
			else {
				waittime++;
			
				//バックランプ点灯
				BLED0 = 1;
				BLED1 = 1;
				stop;
			}
		
		}
		
		switch (count){
		
			// スタートラインの処理
			case 1:{
				
			break;
			}
			// A点からB点までの処理
			case 2:{
			
				//パトランプタイマー
				if (PLEDT > 100) {
				
					PLED = 1;

				} else {
					
					PLEDT++;
				}
				
				//1秒毎にパトランプを切り替える
				switch(PLED){
					case 0:{
						PLED0 = 0;
						PLED1 = 0;
						PLED2 = 0;
						PLED3 = 0;
						break;
					}
					case 1:{
						PLED0 = 1;
						PLED1 = 1;
						PLED2 = 1;
						PLED3 = 1;
						break;
					}
				}
				
				break;
				
			}
			// B点以降の処理
			case 3:{
			
				PLED0 = 0;
				PLED1 = 0;
				PLED2 = 0;
				PLED3 = 0;
				break;
			}
		
		}
	
		// ヘッドランプは常に点灯
		FLED0 = 1;
		FLED1 = 1;
	
	}while(SW0 == SW_OFF);
	delay1ms(30);				// チャタリング防止
	YLED = LED_OFF;
	
	// OFFになるまで(ONの間繰り返す)
	while(SW0 == SW_ON);
	delay1ms(30);				// チャタリング防止
	
	
	// ■ ライントレース終了後の処理
	stop;
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
	int i;
	
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
	PORTA = 0;	LATA = 0;
	PORTB = 0;	LATB = 0;
	PORTC = 0;	LATB = 0;
	PORTD = 0;	LATB = 0;
	PORTE = 0;	LATB = 0;
	
	for(i=0; i<5; i++) {
		YLED=1; RLED=1;	__delay_ms(16);
		YLED=0; RLED=0;	__delay_ms(16);
	}
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
//	forwardの継続 ---------------
void forwardms(unsigned char unit)
{
	forward;
	unsigned char i;
	for (i=0; i<unit; i++) {
		__delay_ms(1);
	}
}
