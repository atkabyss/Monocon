/*======================================
高校生ものづくりコンテスト 関東地区予選会
電子回路組み立て部門

作成日 8月23日
作成者 石井恭輔
所属学校 東京都立蔵前工業高等学校

課題名 課題1
課題番号 p01
======================================*/

#include <xc.h>
#define _XTAL_FREQ  48000000
#define l0 LATBbits.LATB0		//7seg0
#define l1 LATBbits.LATB1		//7seg1
#define l2 LATBbits.LATB2		//7seg2
#define l3 LATBbits.LATB3		//7seg3
#define TSR PORTEbits.RE2		//赤タクトスイッチ
#define TSW PORTEbits.RE1		//トグルスイッチ
#define TSB PORTEbits.RE0		//黒タクトスイッチ
#define de __delay_ms(1)

//変数の宣言
int a,b,c,d,e,f,i,k=0,k2=0;

//関数の宣言
void t(void);
void x(void);

void main(void){
	//PICの設定
	ADCON1 |= 0x0F;		//ADコンバータOFF
	
	//入出力の設定
	TRISA = 0b11000000;
	TRISB = 0b00000000;
	TRISC = 0b11111100;
	TRISD = 0b00000000;
	TRISE = 0b11111111;
	
	//ポートの初期化
	PORTA = 0;
	PORTB = 0;
	PORTC = 0;
	PORTD = 0;
	PORTE = 0;
	
	//4つの7SEGを消灯
	l0 = 1;
	l1 = 1;
	l2 = 1;
	l3 = 1;
	
	//初期表示
	LATD = 0b00000000;		//8を表示
	l0 = 0;
	l1 = 1;
	
	//メイン関数
	while(1){
		for(i=1;i<1001;i++){		//10秒間
			__delay_ms(10);
			k = i / 100;
			if (k == 10) {
				k = 0;
			}
			if (k2 == 5){
				k2 = 0;	
			}
			t();
		}
		k2 = k2 + 1;
		/*
		for(i=0;i<100;i++){		//1秒間
			__delay_ms(10);
			x();
		}
		*/
	}
}

//自作関数
void t(void){
	
	if (k == 0) {
		LATD = 0b01000000;		//0を表示
		l0 = 1;
		l1 = 0;
	}
	if (k == 1) {
		LATD = 0b01111001;		//1を表示
		l0 = 1;
		l1 = 0;
		
	}
	if (k == 2) {
		LATD = 0b00100100;		//2を表示
		l0 = 1;
		l1 = 0;
	}
	if (k == 3) {
		LATD = 0b00110000;		//3を表示
		l0 = 1;
		l1 = 0;
	}
	if (k == 4) {
		LATD = 0b00011001;		//4を表示
		l0 = 1;
		l1 = 0;
	}
	if (k == 5) {
		LATD = 0b00010010;		//5を表示
		l0 = 1;
		l1 = 0;
	}
	if (k == 6) {
		LATD = 0b00000010;		//6を表示
		l0 = 1;
		l1 = 0;
	}
	if (k == 7) {
		LATD = 0b01111000;		//7を表示
		l0 = 1;
		l1 = 0;
	}
	if (k == 8) {
		LATD = 0b00000000;		//8を表示
		l0 = 1;
		l1 = 0;
	}
	if (k == 9) {
		LATD = 0b00010000;		//9を表示
		l0 = 1;
		l1 = 0;
	}	
	
	de;
	
	if (k2 == 0) {
		LATD = 0b01000000;		//0を表示
		l0 = 0;
		l1 = 1;
	}
	if (k2 == 1) {
		LATD = 0b01111001;		//1を表示
		l0 = 0;
		l1 = 1;
	}
	if (k2 == 2) {
		LATD = 0b00100100;		//2を表示
		l0 = 0;
		l1 = 1;
	}
	if (k2 == 3) {
		LATD = 0b00110000;		//3を表示
		l0 = 0;
		l1 = 1;
	}
	if (k2 == 4) {
		LATD = 0b00011001;		//4を表示
		l0 = 0;
		l1 = 1;
	}
	if (k2 == 5) {
		LATD = 0b00010010;		//5を表示
		l0 = 0;
		l1 = 1;
	}
	if (k2 == 6) {
		LATD = 0b00000010;		//6を表示
		l0 = 0;
		l1 = 1;
	}
	if (k2 == 7) {
		LATD = 0b01111000;		//7を表示
		l0 = 0;
		l1 = 1;
	}
	if (k2 == 8) {
		LATD = 0b00000000;		//8を表示
		l0 = 0;
		l1 = 1;

	}
	if (k2 == 9) {
		LATD = 0b00010000;		//9を表示
		l0 = 0;
		l1 = 1;

	}
	
	de;
	
}

/*
void x(void){
	LATD = 0b00011001;		//4を表示
	l0 = 0;
	l1 = 1;
	de;
		
	LATD = 0b01111111;		//消灯
	l0 = 1;
	l1 = 1;
}
*/
