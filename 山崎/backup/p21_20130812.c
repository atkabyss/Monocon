//========================
//2013.8.2
//H24 課題4
//荒川工業高等学校
//山崎晃史
//========================
#include<p18f4550.h>
#include<delays.h>

#define L2 LATBbits.LATB2  //"LATBbits.LATB2"を"L2"として定義
#define L3 LATBbits.LATB3  //"LATBbits.LATB3"を"L3"として定義
#define L4 LATBbits.LATB4  //"LATBbits.LATB4"を"L4"として定義
#define L5 LATBbits.LATB5  //"LATBbits.LATB5"を"L5"として定義
#define D1k Delay1KTCYx(120)  //"Delay1KTCYx(120)"を"D1k"として定義
#define D10k Delay10KTCYx(120)  //"Delay1KTCYx(120)"を"D10k"として定義
#define R3 PORTAbits.RA3  //"PORTAbits.RA3"を"R3"として定義
#define R4 PORTAbits.RA4  //"PORTAbits.RA4"を"R4"として定義
#define R5 PORTAbits.RA5  //"PORTAbits.RA5"を"R5"として定義
#define L7s Led7seg  //"Led7seg"を"L7s"として定義

//==定数の宣言==
char L7s[] = {
	0b01000000,  //0
	0b01111001,  //1
	0b00100100,  //2
	0b00110000,  //3
	0b00011001,  //4
	0b00010010,  //5
	0b00000010,  //6
	0b01011000,  //7
	0b00000000,  //8
	0b00010000,  //9
	0b00100000,  //A
	0b00000011,  //B
	0b00100111,  //C
	0b00100001,  //D
	0b00000100,  //E
	0b00001110,  //F
	0b00011100,  //OFF
	0b00100011,  //ON
	0b01111111,  //非表示
};
//==変数の宣言==
char i,j,a,b;

//==関数の宣言==
void dd(void);  //7セグメントLEDの両方を表示

//==============メイン関数==============
void main(void){
	
	ADCON1 |= 0x0F;  //ADコンバータをOFF
	
//=============入出力の設定=============
	TRISA = 0b11111000;
	TRISB = 0b00000000;
	TRISC = 0b11111100;
	TRISD = 0b00000000;
	TRISE = 0b11111000;
	
//============ポートの初期化=============
	PORTA = 0;
	PORTB = 0;
	PORTC = 0;
	PORTD = 0;
	PORTE = 0;
	
//=====すべての7セグメントLEDを消灯======
	L2 = 1;
	L3 = 1;
	L4 = 1;
	L5 = 1;

//==変数の初期化==
	i = 0;
	j = 10;
	a = 0;  //フラグ用変数
	b = 0;  //フラグ用変数
while(1){
	
	if(a == 0){  //プログラム開始時aを表示
		LATD = L7s[10];
		L3 = 0;
		a = 1;
	}
	
	if(R4 == 0){  //青タクトスイッチが押されている時iを1にする
		i = 1;
	}
	
	if(R4 == 1){  //青タクトスイッチが押されていない時iを0にする
		i = 0;
	}
	
	if(i == 1){  //青タクトスイッチが押されているときカウントアップをする
		LATD = L7s[j];
		for(b=0;b<10;b++){
				D10k;
			}
		j++;
	}
	
	if(j > 16){  //表示がfを超えたときaに戻す
		j = 10;
	}
}
}