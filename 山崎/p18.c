//========================
//2013.8.2
//H24 �ۑ�1
//�r��H�ƍ����w�Z
//�R��W�j
//========================
#include<p18f4550.h>
#include<delays.h>

#define L2 LATBbits.LATB2  //"LATBbits.LATB2"��"L2"�Ƃ��Ē�`
#define L3 LATBbits.LATB3  //"LATBbits.LATB3"��"L3"�Ƃ��Ē�`
#define L4 LATBbits.LATB4  //"LATBbits.LATB4"��"L4"�Ƃ��Ē�`
#define L5 LATBbits.LATB5  //"LATBbits.LATB5"��"L5"�Ƃ��Ē�`
#define D1k Delay1KTCYx(120)  //"Delay1KTCYx(120)"��"D1k"�Ƃ��Ē�`
#define R3 PORTAbits.RA3  //"PORTAbits.RA3"��"R3"�Ƃ��Ē�`
#define R4 PORTAbits.RA4  //"PORTAbits.RA4"��"R4"�Ƃ��Ē�`
#define R5 PORTAbits.RA5  //"PORTAbits.RA5"��"R5"�Ƃ��Ē�`
#define L7s Led7seg  //"Led7seg"��"L7s"�Ƃ��Ē�`

//==�萔�̒�`==
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
	0b01111111,  //��\��
};
//==============���C���֐�==============
void main(void){
	
	ADCON1 |= 0x0F;  //AD�R���o�[�^��OFF
	
//=============���o�͂̐ݒ�=============
	TRISA = 0b11111000;
	TRISB = 0b00000000;
	TRISC = 0b11111100;
	TRISD = 0b00000000;
	TRISE = 0b11111000;
	
//============�|�[�g�̏�����=============
	PORTA = 0;
	PORTB = 0;
	PORTC = 0;
	PORTD = 0;
	PORTE = 0;
	
//=====���ׂĂ�7�Z�O�����gLED������======
	L2 = 1;
	L3 = 1;
	L4 = 1;
	L5 = 1;
	
while(1){
	if(R4 == 0){
		LATD = L7s[17];
		L3 = 0;
	}
	
	if(R4 == 1){
		LATD = L7s[16];
		L3 = 0;
	}
}
}
