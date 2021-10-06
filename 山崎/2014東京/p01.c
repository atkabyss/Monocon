/*======================================
平成26年度 高校生ものづくりコンテスト
電子回路組立部門 東京都大会

作成日時	：7月20日
作成者		：10番 山崎晃史
所属学校	：東京都立荒川工業高等学校

ファイル名	：p01.c
課題番号	：1番
======================================*/
#include<p18f4550.h>
#include<delays.h>

#define l2 LATBbits.LATB2		//-----左の7セグメントLED
#define l3 LATBbits.LATB3		//-----右の7セグメントLED
#define l4 LATBbits.LATB4
#define l5 LATBbits.LATB5
#define l7 LATDbits.LATD7
#define D1 Delay1KTCYx(120)		//-----約0.1msの遅延
#define D10 Delay10KTCYx(120)	//-----約1msの遅延
#define bs PORTAbits.RA4		//-----青タクトスイッチ
#define ys PORTAbits.RA5		//-----黄色タクトスイッチ

//=====定数の宣言
char l7s[] = {					//-----7セグメントLEDの表示設定
	0b01000000,	//---0
	0b01111001,	//---1
	0b00100100,	//---2
	0b00110000,	//---3
	0b00011001,	//---4
	0b00010010,	//---5
	0b00000010,	//---6
	0b01011000,	//---7
	0b00000000,	//---8
	0b00010000,	//---9
	0b00100000,	//---a		---10
	0b00000011,	//---b		---11
	0b00100111,	//---c		---12
	0b00100001,	//---d		---13
	0b00000100,	//---e		---14
	0b00001110,	//---F		---15
	0b00101011,	//---OFF	---16
	0b01110111,	//---ON		---17
	0b00011100,	//---イルミネーションパターン1 (1および2の状態)		---18
	0b00100011,	//---イルミネーションパターン2 (3および4の状態)		---19
};
char STMR[] = {0x08,0x04,0x02,0x01};	//-----ステッピングモータを時計回りに回転
char STML[] = {0x01,0x02,0x04,0x08};	//-----ステッピングモータを反時計回りに回転

//=====変数の宣言
char a,b,c,i,j,k,f,f2;

//=====関数の宣言
void led(void);			//-----2つのLEDを同時に表示させる関数
void stmr(void);		//-----ステッピングモータを時計回りに回転させる関数
void stml(void);		//-----ステッピングモータを反時計回りに回転させる関数
void dcmr(void);		//-----DCモータを時計回りに回転させる関数
void dcml(void);		//-----DCモータを反時計回りに回転させる関数
void dcms(void);		//-----DCモータを停止させる関数

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
	
//=====すべての7セグメントLEDをOFF
	l2 = 1;
	l3 = 1;
	l4 = 1;
	l5 = 1;
	
//=====変数の初期化
	a = 0;		//-----左側の7セグメントLEDのデータを保持
	b = 0;		//-----右側の7セグメントLEDのデータを保持
	c = 0;		//-----カウント用
	i = 0;		//-----ステッピングモータ制御用
	j = 0;		//-----ステッピングモータの回転数制御用
	k = 0;		//-----未使用
	f = 0;		//-----フラグ用
	f2 = 0;		//-----フラグ用
	
	while(1){
		LATD = l7s[0];
		if(bs == 0 && ys == 1){			//-----条件：青タクトスイッチのみがONのとき
			l2 = 0;					//-----左側の7セグメントLEDを表示する
		}
		if(ys == 0 && bs == 1){			//-----条件：黄色タクトスイッチのみがONのとき
			l3 = 0;					//-----右側の7セグメントLEDを表示する
		}
		if(bs == 1 && ys == 1){	//-----条件：左右の7セグメントLEDがOFFのとき
			l2 = 1;					//-----両方の7セグメントLEDが消灯する
			l3 = 1;
		}
	}
}
/*======================================
	自作関数
======================================*/
void led(void){		//-----2つのLEDを同時に表示させる関数
	LATD = l7s[a];		//-----左側のLEDのデータを読み込み
	l2 = 0;				//-----左側のLEDを点灯
	D1;					//-----表示時間の確保
	l2 = 1;				//-----左側のLEDを消灯
	LATD = l7s[b];		//-----右側のLEDのデータを読み込み
	l3 = 0;				//-----右側のLEDを点灯
	D1;					//-----表示時間の確保
	l3 = 1;				//-----右側のLEDを消灯
}
void stmr(void){	//-----ステッピングモータを時計回りに回転させる関数
	LATD = STMR[i];		//-----時計回りのデータを読み込み
	l7 = 0;
	l7 = 1;
	l7 = 0;
	i++;
	if(i > 4){			//-----4つ以上のデータがないため0に戻す
		i = 0;
	}
	D1;					//-----脱調防止の遅延
}
void stml(void){	//-----ステッピングモータを時計回りに回転させる関数
	LATD = STML[i];		//-----反時計回りのデータを読み込み
	l7 = 0;
	l7 = 1;
	l7 = 0;
	i++;
	if(i > 4){			//-----4つ以上のデータがないため0に戻す
		i = 0;
	}
	D1;					//-----脱調防止の遅延
}
void dcmr(void){	//-----DCモータを時計回りに回転させる関数
	LATD = 0b00100000;	//-----時計回りのデータを読み込み
	l7 = 0;
	l7 = 1;
	l7 = 0;
}
void dcml(void){	//-----DCモータを反時計回りに回転させる関数
	LATD = 0b00010000;	//-----反時計回りのデータを読み込み
	l7 = 0;
	l7 = 1;
	l7 = 0;
}
void dcms(void){	//-----DCモータを停止させる関数
	LATD = 0b00110000;	//-----停止させるデータを読み込み
	l7 = 0;
	l7 = 1;
	l7 = 0;
}
