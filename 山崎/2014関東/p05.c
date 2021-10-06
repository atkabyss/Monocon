/*======================================
平成26年度 高校生ものづくりコンテスト
電子回路組立部門 関東地区予選会(千葉)

作成日時	：8月5日
作成者		：12番 山崎晃史
所属学校	：東京都立荒川工業高等学校

ファイル名	：p05.c
課題番号	：5番
======================================*/
#include<p18f4550.h>
#include<delays.h>

#define l2 LATBbits.LATB2 //左の7セグメントLED
#define l3 LATBbits.LATB3 //左の7セグメントLED
#define l4 LATBbits.LATB4
#define l5 LATBbits.LATB5
#define l7 LATDbits.LATD7
#define D01	Delay100TCYx(120)	//0.001msの遅延
#define D05	Delay1KTCYx(60)	//0.005msの遅延
#define D1	Delay1KTCYx(120)	//0.01msの遅延
#define D10	Delay10KTCYx(120)	//0.1msの遅延
#define bs PORTAbits.RA5	//黒タクトスイッチ
#define rs PORTAbits.RA4	//赤タクトスイッチ
#define ps PORTAbits.RA3	//フォトIC

//=====定数の宣言
char l7s[] = {	//7セグメントLEDの表示設定
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
	0b00100001,	//d-13
	0b00000110,	//E-14
	0b00001110,	//F-15
	0b00001001,	//H-16
	0b01000111,	//L-17
	0b01111111	//非表示-18
};

char STM[] = {0x08,0x04,0x02,0x01};	//ステッピングモータの励磁設定

//=====変数の宣言
unsigned char b,j,k,f,f2,f3;
char a,c,i;

//=====関数の宣言
void set(void);	//PICの初期化設定
void led(void);	//2つのLEDを同時に表示させる関数
void stmr(void);	//ステッピングモータを時計回りに回転させる関数
void stml(void);	//ステッピングモータを反時計回りに回転させる関数

/*======================================
		メイン関数
======================================*/
void main(void){

	set();

	while(1){
		led();
		
		if(bs == 1){
			if(rs == 1){
			D1;
			}
			
			f = 1;
		}
		
		if(bs == 0 && f == 1 && f3 == 1){	//LED表示の切り替え動作
			f = 0;
			f2++;
			
			if(f2 > 3){
				f2 = 0;
			}
			
			switch(f2){
			case 0:
				a = 0;
				b = 0;
				
				break;
			
			case 1:
				a = 0;
				b = 1;
				
				break;
			
			case 2:
				a = 1;
				b = 2;
				
				break;
				
			case 3:
				a = 2;
				b = 0;
				
				break;
			}
		}
		
		if(rs == 1){
			f3 = 1;
		}
		
		if(rs == 0){	//LEDの状態によってステッピングモータの回転方向を選択
			f3 = 0;
		
			if(f2 == 1 || f2 == 2){
				stmr();
			}
		
			if(f2 == 3){
				stml();
			}
		}
	}
}

/*======================================
		自作関数
======================================*/
void set(void){	//PICの初期化設定
	
	ADCON1 |= 0x0F;	//ADコンバータをOFF
	
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

//=====すべての7セグメントLEDを初期化
	l2 = 1;
	l3 = 1;
	l4 = 1;
	l5 = 1;
	
//=====変数の初期化
	a = 0;	//左の7セグLメントLEDのデータを保持
	b = 0;	//右の7セグLメントLEDのデータを保持
	c = 0;	//カウント用
	i = 0;	//ステッピングモータ制御用
	j = 0;	//未使用
	k = 0;	//ステッピングモータの回転速度制御用
	f = 0;	//フラグ用
	f2 = 0;	//フラグ用
	f3 = 0;	//フラグ用
}

void led(void){	//2つのLEDを同時に表示させる関数
	LATD = l7s[a];
	l2 = 0;
	D05;
	l2 = 1;
	LATD = l7s[b];
	l3 = 0;
	D05;
	l3 = 1;
}

void stmr(void){	//ステッピングモータを時計回りに回転させる関数
	LATD = STM[i];
	l7 = 0;
	l7 = 1;
	l7 = 0;
	
	if(k == 1){
		D1;
	}
	
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
	
	if(k == 1){
		D1;
	}
	
	i--;
	
	if(i < 0){
		i = 3;
	}
}
