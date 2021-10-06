/*======================================
����26�N�x ���Z�����̂Â���R���e�X�g
�d�q��H�g������ �����s���

�쐬����	�F7��20��
�쐬��		�F10�� �R��W�j
�����w�Z	�F�����s���r��H�ƍ����w�Z

�t�@�C����	�Fp05.c
�ۑ�ԍ�	�F5��
======================================*/
#include<p18f4550.h>
#include<delays.h>

#define l2 LATBbits.LATB2		//-----����7�Z�O�����gLED
#define l3 LATBbits.LATB3		//-----�E��7�Z�O�����gLED
#define l4 LATBbits.LATB4
#define l5 LATBbits.LATB5
#define l7 LATDbits.LATD7
#define D1 Delay1KTCYx(120)		//-----��0.1ms�̒x��
#define D10 Delay10KTCYx(120)	//-----��1ms�̒x��
#define TGS PORTAbits.RA3		//�g�O���X�C�b�`
#define PS PORTAbits.RA4		//�t�H�g�X�C�b�`
#define TS PORTAbits.RA5		//�^�N�g�X�C�b�`

//=====�萔�̐錾
char l7s[] = {					//-----7�Z�O�����gLED�̕\���ݒ�
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
	0b01111111,	//---��\��	---18
};

//=====�ϐ��̐錾
char a,b,c,i,j;

//=====�֐��̐錾
void led(unsigned char a,unsigned char b);			//-----2��7�Z�O�����gLED�𓯎��ɕ\��������֐�
void ch(void);
/*======================================
	���C���֐�
======================================*/
void main(void){
//=====AD�R���o�[�^��OFF
	ADCON1 |= 0x0F;
	
//=====���o�͂̐ݒ�
	TRISA = 0b11111000;
	TRISB = 0b00000000;
	TRISC = 0b11111000;
	TRISD = 0b00000000;
	TRISE = 0b11111000;
	
//=====�|�[�g�̏�����
	PORTA = 0;
	PORTB = 0;
	PORTC = 0;
	PORTD = 0;
	PORTE = 0;
	
//=====���ׂĂ�7�Z�O�����gLED��OFF
	l2 = 1;
	l3 = 1;
	l4 = 1;
	l5 = 1;
	
	while(1){
		if(TS == 0){
		ch();
		for(i=0;i<10;i++){
			led(i,i);
			for(j=0;j<10;j++){
			D10;
			}
			if(i==10)
			i=0;
		}
		}
	}
}
/*======================================
	����֐�
======================================*/
void led(unsigned char a,unsigned char b){		//-----2��7�Z�O�����gLED�𓯎��ɕ\��������֐�
	LATD = l7s[a];		//-----������LED�̃f�[�^��ǂݍ���
	l2 = 0;				//-----������LED��_��
	D1;					//-----�\�����Ԃ̊m��
	l2 = 1;				//-----������LED������
	LATD = l7s[b];		//-----�E����LED�̃f�[�^��ǂݍ���
	l3 = 0;				//-----�E����LED��_��
	D1;					//-----�\�����Ԃ̊m��
	l3 = 1;				//-----�E����LED������
}
void ch(void){
	char a=1,b=1;
while(1){
	if(TS==0)
	D1;
	a=0
	else if(TS==a)
	D1;
	else if(TS==b){
	D1;
	break;
	}
}
}
