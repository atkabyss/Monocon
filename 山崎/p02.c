/*======================================================================
	ステッピングモータをCWに回転
======================================================================*/
#include <p18f4550.h>
#include <delays.h>

//■定数の定義
//ステッピングモータの励磁定義
char STM[] = {0x01, 0x02, 0x04, 0x08};

/*--------------------------------------
	メイン関数
--------------------------------------*/
void main(void)
{
	// ■変数の定義
	char i;
	
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
	while(1){
		if(PORTCbits.RC2 == 0){ //タクトスイッチON
			LATD = 0b00010000; //DCモータのCWリセット
			LATDbits.LATD7 = 0;
			LATDbits.LATD7 = 1;
			LATDbits.LATD7 = 0;
			}
		else{
			LATD = 0b00000000; //DCモータのSTOPリセット
			LATDbits.LATD7 = 0;
			LATDbits.LATD7 = 1;
			LATDbits.LATD7 = 0;
		}
	}
}
