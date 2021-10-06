/*======================================
���Z�����̂Â���R���e�X�g
�d�q��H�g������ �S�����(���)

�쐬����	�F7��31��
�쐬��		�F�R��W�j
�����w�Z	�F�����s���r��H�ƍ����w�Z

�t�@�C����	�Fp05.c
�ۑ�ԍ�	�F5��
======================================*/
#include<p18f4550.h>
#include<delays.h>

#define l2 LATBbits.LATB2	//����7�Z�OLED
#define l3 LATBbits.LATB3	//����7�Z�OLED
#define l4 LATBbits.LATB4
#define l5 LATBbits.LATB5
#define l7 LATDbits.LATD7
#define D01 Delay1KTCYx(30)
#define D1 Delay1KTCYx(120)
#define D10 Delay10KTCYx(120)
#define ts PORTAbits.RA3		//�^�N�g�X�C�b�`
#define ps PORTAbits.RA4		//�z�g�C���^���v�^
#define tgs PORTAbits.RA5		//�g�O���X�C�b�`

//=====�萔�̐錾
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
	0b00100000,	//a-10
	0b00000011,	//b-11
	0b00100111,	//c-12
	0b00100001,	//d-13
	0b00000110,	//E-14
	0b00001110,	//F-15
	0b00001001,	//H-16
	0b01000111,	//L-17
	0b01111111	//��\��-18
};

char STM[] = {0x01,0x03,0x02,0x06,0x04,0x0c,0x08,0x09};	//�X�e�b�s���O���[�^�̗㎥

//=====�ϐ��̐錾
unsigned char a,b,j,k,s,f,f2,f3,f4,f5;
char c,i;

//=====�֐��̐錾
void led(void);
void stmr(void);
void stml(void);
void dcmr(void);
void dcml(void);
void dcms(void);

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
	a = 18;
	b = 18;
	c = 0;
	i = 0;
	j = 0;
	k = 1;
	s = 0;
	f = 1;
	f2 = 0;
	f3 = 0;
	f4 = 0;
	f5 = 0;
	
	while(1){
		if(ts == 1 && ps == 1 && tgs == 1){
			f2 = 0;
			f3 = 0;
			f4 = 0;
		}
		
		if(tgs == 1 && f == 1){
			a = 18;
			b = 18;
			f4 = 0;
			f2 = 0;		//�^�N�g���������
			f3 = 0;		//�z�g���������
		}
		
		if(tgs == 0 && ts == 1 && ps == 1){
			f = 1;		//�g�O�����������
			f2 = 1;		//�^�N�g���������
			f3 = 1;		//�z�g���������
			f4 = 1;		//�g�O���̏�Ԕ���
			k = 1;
			a = 16;
			b = 17;
			led();
			stml();
		}
		
		if(ts == 0 && f2 == 1 && f4 == 1){
			f = 0;		//�g�O�����������
			f3 = 0;		//�z�g���������
			k = 2;
			a = 0;
			b = 17;
			led();
			stml();
		}
		
		if(ps == 0 && f3 == 1 && f4 == 1){
			f = 0;		//�g�O�����������
			f2 = 0;		//�^�N�g���������
			k = 0;
			a = 16;
			b = 9;
			led();
			stml();
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

void stmr(void){
	LATD = STM[i];
	l7 = 0;
	l7 = 1;
	l7 = 0;
	
	if(k == 1 || k == 2){
		led();
	}
	
	if(k == 2){
		led();
	}
	
	i++;
	
	if(i > 7){
		i = 0;
	}
}

void stml(void){
	LATD = STM[i];
	l7 = 0;
	l7 = 1;
	l7 = 0;
	led();
	
	if(k == 1 || k == 2){
		led();
	}
	
	if(k == 2){
		led();
	}
	
	i--;
	
	if(i < 0){
		i = 7;
	}
}

void dcmr(void){
	LATD = 0b00100000;
	l7 = 0;
	l7 = 1;
	l7 = 0;
}

void dcml(void){
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
