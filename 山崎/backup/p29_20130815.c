/*
	2013.8.5 �d�q��H�g������@�֓����
	�r��H�ƍ����w�Z�@�R��W�j
	
	�ۑ�5
	�g�O���X�C�b�`��"H"�̂Ƃ��X�e�b�s���O���[�^����]
	�������t�H�gIC��"���"�̂Ƃ��Ɏ��v���A"�Ռ�"�̂Ƃ��ɔ����v����ɉ�]
	
	���E��7�Z�O�����gLED�Ƀg�O���X�C�b�`�̏��"H""L"��\��
*/
#include<p18f4550.h>
#include<delays.h>

#define L2 LATBbits.LATB2
#define L3 LATBbits.LATB3
#define L4 LATBbits.LATB4
#define L5 LATBbits.LATB5
#define L7 LATDbits.LATD7
#define D1k Delay1KTCYx(120)
#define D10k Delay10KTCYx(120)
#define R3 PORTAbits.RA3
#define R4 PORTAbits.RA4
#define R5 PORTAbits.RA5

//==�萔�̐錾==
char L7s[] = { //7�Z�O�����gLED�̕\������
	0b01000000, //0
	0b01111001, //1
	0b00100100, //2
	0b00110000, //3
	0b00011001, //4
	0b00010010, //5
	0b00000010, //6
	0b01011000, //7
	0b00000000, //8
	0b00010000, //9
};

//==�ϐ��̐錾==
char i;
char STMR[] = {0x01,0x02,0x04,0x08};
char STML[] = {0x08,0x04,0x02,0x01};

//==�֐��̐錾==
void stml(void);
void stmr(void);

//=====���C���֐�=====
void main(void){
	
	ADCON1 |= 0x0F; //AD�R���o�[�^OFF
	
//=====���o�͂̐ݒ�=====
	TRISA = 0b11111000;
	TRISB = 0b00000000;
	TRISC = 0b11111100;
	TRISD = 0b00000000;
	TRISE = 0b11111000;
	
//=====�|�[�g�̏�����=====
	PORTA = 0;
	PORTB = 0;
	PORTC = 0;
	PORTD = 0;
	PORTE = 0;
	
//=====���ׂĂ�7�Z�O�����gLED������=====
	L2 = 1;
	L3 = 1;
	L4 = 1;
	L5 = 1;
	
while(1){
	if(){
	
	}
}
}

