/*======================================
高校生ものづくりコンテスト 関東地区予選会
電子回路組み立て部門

作成日 8月23日
作成者 石井恭輔
所属学校 東京都立蔵前工業高等学校

課題名 課題4
課題番号 p04
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
int a,b,c,d,e,f,i;

//定数の宣言
char Led7seg[] ={
	0b01000000,
	0b01111001,
	0b00100100,
	0b00110000,
	0b00011001,
	0b00010010,
	0b00000010,
	0b01011000,
	0b00000000,
	0b00010000,
};

char STM[] = {0x08, 0x04, 0x02, 0x01};		//ステッピングモータが時計回り


//関数の宣言
void cnt(void);
void main(void){
	//PICの設定
	ADCON1 |= 0x0F;		//ADコンバータOFF
	
	//入出力の設定
	TRISA = 0b11000000;
	TRISB = 0b00000000;
	TRISC = 0b11111100;
	TRISD = 0b11000000;
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
	LATD = 0b00010000;		//9を表示
	l0 = 0;
	l1 = 1;
	
	//メイン関数
	while(1){
		if(TSR == 0){	//赤タクトスイッチがON
			f=1;
		}
		
		if(TSR == 1 && f == 1){		//赤タクトスイッチがONでフラグが立ったとき
			cnt();
		}
	}
}

//自作関数
void cnt(void){
	LATD = Led7seg[i];
	l0 = 0;
	l1 = 1;
	
	i--;
	if(i<=0){		//0以下になったら
		i=9;		//9に戻す
	}
	
	while(i<=0){		//iが0以下の時
		LATD = 0b01000000;
		l0 = 0;
		l1 = 1;
	}
	
	if(i=4,8){		//iが4の倍数の時
		LATD = STM[a];
		LATDbits.LATD7 = 0;
		LATDbits.LATD7 = 1;
		LATDbits.LATD7 = 0;
		__delay_ms(10);
		
		a++;
		if(a>=4){		//4番以降のパターンはないので
			a=0;		//0番に戻す
		}
	}
}