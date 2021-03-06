/*======================================================================
	ステッピングモータをCWに回転
======================================================================*/
#include <p18f4550.h>
#include <delays.h>

//■定数の定義
//ステッピングモータの励磁定義
char STM[] = {0x08, 0x04, 0x02, 0x01};
char Led7seg[] = {
	0b01111001,
	0b00100100,
	0b00110000,
	0b00011001,
	0b00010010,
};

/*--------------------------------------
	メイン関数
--------------------------------------*/
void main(void)
{
	// ■変数の定義
	char i,j,k;
	
	//■初期化作業
	ADCON1 |= 0x0F; //ADコンバータOFF
	
	//□入出力の設定
	TRISA = 0b11000000; //AポートRA0-5は出力(0)
	TRISB = 0b00000000; //Bポートはすべて出力(0)
	TRISC = 0b11111100; //CポートはRC0,1のみを出力(0)
	TRISD = 0b00000000; //Dポートはすべて出力(0)
	TRISE = 0b11111000; //Eポートはすべて出力(0)
	
	// □ポートの初期化 すべて0
	PORTA = 0;
	PORTB = 0;
	PORTC = 0;
	PORTD = 0;
	PORTE = 0;
	
	//■4つの7SEGを消灯
	LATBbits.LATB2 = 1;
	LATBbits.LATB3 = 1;
	LATBbits.LATB4 = 1;
	LATBbits.LATB5 = 1;
	i = 0;
	j = 0;
	k = 0;
	while(1){
			for(j=0;j<48;j+2){
			LATD = STM[i]; //データのセット
			LATDbits.LATD7 = 0;
			LATDbits.LATD7 = 1;
			LATDbits.LATD7 = 0;
			
			LATD = Led7seg[k]; 
			LATBbits.LATB2 = 0;
			Delay1KTCYx(120); //脱調防止のwait
			i++;
			if(i>=4){
				i = 0;
			}
		}
			k++;
		if(k>=5){
			k = 0;
		}
	}
}