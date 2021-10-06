/*=====================================
      ステッピングモータをｃｗに回転
=====================================*/
#include <xc.h>
#define _XTAL_FREQ 48000000
//ステッピングモータの励磁定義
char stm[] = {0x01, 0x02, 0x04, 0x08};
/*--------------------------------------
 メイン関数
---------------------------------------*/
void main(void)
{
	//■変数の定義
	char i;            
	//■初期化作業
	ADCON1 |= 0x0F       //ADコンバータＯＦＦ
	//□入出力の設定をします
	TRISA = 0b11000000;     //AポートRA0-5は出力
	TRISB = 0b00000000;     //Bポートはすべて出力
	TRISC = 0b11111100;     //CポートはRC0.1のみ出力
	TRISD = 0b00000000;     //Dポートはすべて出力
	TRISE = 0b00000111;     //EポートRE0-2は入力
	
	//□ポートの初期化すべて0
	PORTA = 0;
	PORTB = 0;
	PORTC = 0;
	PORTD = 0;
	PORTE = 0;
	
	//■4つの7SEG
	LATBbits.LATB2 = 0;
	LATBbits.LATB2 = 1;
	LATBbits.LATB2 = 2;
	LATBbits.LATB2 = 3;
	i = 0;             //
	while(1) {
		//ステッピングモータの回転１パルス分
		LATD = stm[1];       //データのセット
		LATBbits.LATD7 = 0;
		LATBbits.LATB7 = 1;
		LATBbits.LATB7 = 0;
		__delay_ms(10);
		
		i++;
		if(i>=4) { // 4番以上のパターンはないので
			i = 0; //0番のパターンに戻す
	
	