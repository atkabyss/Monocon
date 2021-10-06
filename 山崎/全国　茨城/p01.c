/*======================================
���Z�����̂Â���R���e�X�g
�d�q��H�g������ �S�����(���)

�쐬����	�F7��31��
�쐬��		�F�R��W�j
�����w�Z	�F�����s���r��H�ƍ����w�Z

�t�@�C����	�Fp01.c
�ۑ�ԍ�	�F1��
======================================*/
#include<p18f4550.h>
#include<delays.h>

#define l2 LATBbits.LATB2	//����7�Z�OLED
#define l3 LATBbits.LATB3	//����7�Z�OLED
#define l4 LATBbits.LATB4
#define l5 LATBbits.LATB5
#define l7 LATDbits.LATD7
#define D01 Delay100TCYx(120)
#define D1 Delay1KTCYx(120)
#define D10 Delay10KTCYx(120)
#define ts PORTAbits.RA3		//�^�N�g�X�C�b�`
#define ps PORTAbits.RA4		//�z�g�C���^���v�^
#define tgs PORTAbits.RA5	//�g�O���X�C�b�`

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

char STM[] = {0x08,0x04,0x02,0x01};	//�X�e�b�s���O���[�^�̗㎥

//=====�ϐ��̐錾
unsigned char a,b,j,k,f,f2;
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
	
	while(1){
		if(tgs == 0 && ts == 0){
			LATD = l7s[16];
			l3 = 0;
			l2 = 1;
		}
		
		if(tgs == 1 && ts == 0){
			LATD = l7s[17];
			l2 = 0;
			l3 = 1;
		}
		
		if(ts == 1){
			l2 = 1;
			l3 = 1;
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
	D1;
	
	if(k == 1 && k == 2){
		D1;
	}
	
	if(k == 2){
		D1;
	}
	
	i++;
	
	if(i > 3){
		i = 0;
	}
}

void stml(void){
	LATD = STM[i];
	l7 = 0;
	l7 = 1;
	l7 = 0;
	D1;
	
	if(k == 1 && k == 2){
		D1;
	}
	
	if(k == 2){
		D1;
	}
	
	i--;
	
	if(i < 0){
		i = 3;
	}
}

void dcmr(void){
	LATD = 0b0010000;
	l7 = 0;
	l7 = 1;
	l7 = 0;
}

void dcml(void){
	LATD = 0b0001000;
	l7 = 0;
	l7 = 1;
	l7 = 0;
}

void dcms(void){
	LATD = 0b0011000;
	l7 = 0;
	l7 = 1;
	l7 = 0;
}
