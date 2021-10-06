/*======================================
����24�N�x ���Z�����̂Â���R���e�X�g
�d�q��H�g������ �֓��n��\�I

�쐬����	�F8��1��
�쐬��		�F�R��W�j
�����w�Z	�F�����s���r��H�ƍ����w�Z

�t�@�C����	�Fp03.c
�ۑ�ԍ�	�F3��
======================================*/
#include<p18f4550.h>
#include<delays.h>

#define l2 LATBbits.LATB2	//7�Z�O��
#define l3 LATBbits.LATB3	//7�Z�O�E
#define l4 LATBbits.LATB4
#define l5 LATBbits.LATB5
#define l7 LATDbits.LATD7
#define D01 Delay100TCYx(120)	//0.001
#define D1 Delay1KTCYx(120)		//0.01
#define D10 Delay10KTCYx(120)	//0.1
#define tgs PORTAbits.RA3	//�g�O��
#define ts PORTAbits.RA4	//�^�N�g
#define ps PORTAbits.RA5	//�t�H�gIC

//=====�萔�̐錾=====
char l7s[] = {		//7�Z�OLED�̕\���ݒ�
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
	0b00001001,	//H	-10
	0b01000111,	//L	-11
};
char STM[] = {0x01,0x03,0x02,0x06,0x04,0x0c,0x08,0x09};	//�X�e�b�s���O���[�^��1-2���㎥

//=====�ϐ��̐錾=====
unsigned char a,b,j,k,f,f2;
char c,i;

//=====�֐��̐錾=====
void led(void);
void stmr(void);
void stml(void);

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
	
//=====���ׂĂ�7�Z�OLED������
	l2 = 1;
	l3 = 1;
	l4 = 1;
	l5 = 1;
	
//=====�ϐ��̏�����
	a = 1;
	b = 0;
	c = 0;
	i = 0;
	j = 0;
	k = 0;
	f = 0;
	f2 = 0;
	
	while(1){
		if(ps == 0){
			stmr();
		}
	}
}

/*======================================
		����֐�
======================================*/
void led(void){
	LATD = l7s[a];
	l2 = 0;
	D01;
	l2 = 1;
	LATD = l7s[b];
	l3 = 0;
	D01;
	l3 = 1;
}

void stml(void){
	LATD = STM[i];
	l7 = 0;
	l7 = 1;
	l7 = 0;
	D1;
	
	if(k == 1){
		D1;
	}
	
	i++;
	
	if(i > 7){
		i = 0;
	}
}

void stmr(void){
	LATD = STM[i];
	l7 = 0;
	l7 = 1;
	l7 = 0;
	D1;
	
	if(k == 1){
		D1;
	}
	
	i--;
	
	if(i < 0){
		i = 7;
	}
}
