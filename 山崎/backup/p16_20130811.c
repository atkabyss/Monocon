//==========================
//2013.7.30
//H23 課題5
//荒川工業高等学校
//山崎晃史
//==========================
#include<p18f4550.h>
#include<delays.h>

#define L2 LATBbits.LATB2  //"LATBbits.LATB2"を"L2"として定義
#define L3 LATBbits.LATB3  //"LATBbits.LATB3"を"L3"として定義
#define L4 LATBbits.LATB4  //"LATBbits.LATB4"を"L4"として定義
#define L5 LATBbits.LATB5  //"LATBbits.LATB5"を"L5"として定義
#define L7 LATDbits.LATD7  //"LATBbits.LATB7"を"L7"として定義
#define R4 PORTAbits.RA4  //"PORTAbits.RA4"を"R4"として定義
#define D1k Delay1KTCYx(120)  //"Delay1KTCYx(120)"を"D1k"として定義

//==定数の宣言==
char Led7seg[] = {  //7セグメントLEDの表示制御
	0b01000000,  //0
	0b01111001,  //1
	0b00111111,  //-
};
char STML[] = {0x08,0x04,0x02,0x01}; //ステッピングモータを右回転

//==変数の宣言==
char i,j,k,l,ts;

//==関数の宣言==
void STML1(void);  //ステッピングモータを1回転
void DD(void);  //7セグメントLEDの両方を表示

//===============メイン関数===============
void main(void){
	
	ADCON1 |= 0x0F;  //ADコンバータをOFF
	
//==============入出力の設定==============
	TRISA = 0b11111000;
	TRISB = 0b00000000;
	TRISC = 0b11111100;                          
	TRISD = 0b00000000;
	TRISE = 0b11111000;
	
//============ポートの初期化==============
	PORTA = 0;
	PORTB = 0;
	PORTC = 0;
	PORTD = 0;
	PORTE = 0;                   
	
//======すべての7セグメントLEDを消灯======
	L2 = 1;
	L3 = 1;
	L4 = 1;
	L5 = 1;

//==============変数の初期化==============
	i = 0;  
	j = 2;
	k = 2;
	ts = 0;  //フラグ用
	
while(1)
{   
	L2 = 0;
	L3 = 0;	
	DD();
	
	if(R4 == 0 && ts == 0){
		ts = 1;  //プログラム実行中のタクトスイッチの入力を拒否
		j = 0;
		k = 0;
		STML1();
		
		if(k>2){  //2進数の繰り上がり処理
			k = 0;
			j++;
		}
		
		DD();
		ts = 0;  //タクトスイッチの入力を許可
}
}
}
//==関数の宣言==
void STML1(void){  //ステッピングモータを右方向に1回転
	for(l=0;l<48;l++){
	LATD = STML[i];  //データのセット
	L7 = 0;
	L7 = 1;
	L7 = 0;
	D1k;  //脱調防止のwait
	i++;
	if(i>=4){  //4つ以上のデータが存在しないため
		i = 0;
		k++;  //ステッピングモータの回転数に1を加算
	}
	}
}

void DD(void){  //7セグメントLEDの両方を表示
	LATD = Led7seg[j];  //左の7セグメントLEDのデータをセット
	L2 = 0;  //左の7セグメントLEDを点灯
	L3 = 1;  //右の7セグメントLEDを消灯
	D1k;
	LATD = Led7seg[k];  //右の7セグメントLEDのデータをセット
	L3 = 0;  //右の7セグメントLEDを点灯
	L2 = 1;  //左の7セグメントLEDを消灯
	D1k;
	L2 = 1;
	L3 = 1;
}
