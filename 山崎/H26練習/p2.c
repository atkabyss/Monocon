/*======================================
����25�N�x ���Z�����̂Â���R���e�X�g
�d�q��H�g������ ��B���

�쐬����	�F7��23��
�쐬��		�F�R��W�j
�����w�Z	�F�����s���r��H�ƍ����w�Z

�t�@�C����	�Fp2.c
�ۑ�ԍ�	�F2��
======================================*/
#include<p18f4550.h>
#include<delays.h>

#define l2 LATBbits.LATB2		//����7�Z�OLED
#define l3 LATBbits.LATB3		//�E��7�Z�OLED
#define l4 LATBbits.LATB4
#define l5 LATBbits.LATB5
#define l7 LATDbits.LATD7
#define D01 Delay1KTCYx(12)		//��0.01ms�̒x��
#define D1 Delay1KTCYx(120)		//��0.1ms�̒x��
#define D10 Delay10KTCYx(120)	//��1ms�̒x��
#define ps PORTAbits.RA3		//�z�g�C���^���v�^
#define tgs PORTAbits.RA4		//�g�O���X�C�b�`
#define ts PORTAbits.RA5		//�^�N�g�X�C�b�`

//=====�萔�̐錾=====
char l7s[] = {
	0b01000000,	//0
	0b01111001,	//1
	0b00100100,	//2
	0b00110000,	//3
	0b00011001,	//4
	0b00010010,	//5
	0b00000010,	//6
	0b01111000,	//7
	0b00000000,	//8
	0b00010000,	//9
	0b00001000,	//A-10
	0b00000011,	//b-11
	0b00100111,	//c-12
	0b00100001,	//d-13
	0b00000110,	//E-14
	0b00001110,	//F-15
	0b00001001,	//H-16
	0b01000111,	//L-17
	0b01111111	//��\��-18
};

char STMR[] = {0x08,0x04,0x02,0x01};
char STML[] = {0x01,0x02,0x04,0x08};
//=====�ϐ��̐錾=====
char a,b,c,i,j,k,f;

//=====�֐��̐錾=====
void led(void);
void stmr(void);
void stml(void);
void dcml(void);
void dcmr(void);
void dcms(void);

/*======================================
		���C���֐�
======================================*/
void main(void){

//=====AD�R���o�[�^��OFF=====
	ADCON1 |= 0x0F;
	
//=====���o�͂̐ݒ�=====
	TRISA = 0b11111000;
	TRISB = 0b00000000;
	TRISC = 0b11111000;
	TRISD = 0b00000000;
	TRISE = 0b11111000;
	
//=====�|�[�g�̏�����=====
	PORTA = 0;
	PORTB = 0;
	PORTC = 0;
	PORTD = 0;
	PORTE = 0;
	
//=====���ׂĂ�7�Z�OLED������=====
	l2 = 1;
	l3 = 1;
	l4 = 1;
	l5 = 1;

//=====�ϐ��̏�����=====
	a = 0;
	b = 0;
	c = 0;
	i = 0;
	j = 0;
	k = 0;
	f = 0;
	
	while(1){
		led();
		if(ts == 1){
			a = 0;
			b = 0;
			f = 0;
		}
		
		if(ts == 0 && f == 0){
			a = 0;
			b = 17;
			for(c=0;c<50;c++){
				led();
				if(ts == 1){
					b = 0;
				}
			}
			f = 1;
		}
		
		if(f == 1 && ts == 0 && tgs == 1){
			a = 1;
			b = 17;
			dcmr();
			D1;
			dcms();
			led();
			led();
		}
		
		if(f == 1 && ts == 0 && tgs == 0){
			a = 2;
			b = 16;
			dcmr();
		/*	D1;
			dcms();
			led();*/
		}
	}
}
/*======================================
		����֐�
======================================*/
void led(void){
	LATD = l7s[a];
	l2 = 0;
	D1;
	l2 = 1;
	LATD = l7s[b];
	l3 = 0;
	D1;
	l3 = 1;
}

void stmr(void){
	LATD = STMR[i];
	l7 = 0;
	l7 = 1;
	l7 = 0;
	i++;
	if(i < 4){
		i = 0;
	}
	D01;
}

void stml(void){
	LATD = STML[i];
	l7 = 0;
	l7 = 1;
	l7 = 0;
	i++;
	if(i < 4){
		i = 0;
	}
	D01;
}

void dcml(void){
	LATD = 0b00100000;
	l7 = 0;
	l7 = 1;
	l7 = 0;
}

void dcmr(void){
	LATD = 0b00010000;
	l7 = 0;
	l7 = 1;
	l7 = 0;
}

void dcms(void){
	LATD = 0b00110000;
	l7 = 0;
	l7 = 1;
	l7 = 0;
}
