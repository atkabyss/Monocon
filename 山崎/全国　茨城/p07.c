/*======================================
���Z�����̂Â���R���e�X�g
�d�q��H�g������ �S�����(���)

�쐬����	�F7��31��
�쐬��		�F�R��W�j
�����w�Z	�F�����s���r��H�ƍ����w�Z

�t�@�C����	�Fp07.c
�ۑ�ԍ�	�F7��
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
unsigned char a,b,j,k,s,f,f2,f3,f4,f5;
char c,i;

//=====�֐��̐錾
void led(void);
void stmr(void);
void stml(void);
void dcmr(void);
void dcml(void);
void dcms(void);
void ts_s(void);	//�^�N�g�̏�Ԃ��擾
void ps_s(void);	//�g�O���̏�Ԃ��擾

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
	a = 0;
	b = 0;
	c = 0;
	i = 0;
	j = 0;
	k = 0;
	s = 0;
	f = 0;
	f2 = 0;
	f3 = 1;
	f4 = 0;
	f5 = 0;
	
	LATD = l7s[0];
	l3 = 0;
	
	while(1){
		ts_s();
		ps_s();
		
		if(f == 1){
			for(c=0;c<10;c++){
				D10;
				ts_s();
			}
			
			if(f == 1){
				b++;
				
				if(b == 10){
					b = 0;
				}
			}
			LATD = l7s[b];
		}
		
		if(b <= 4)	s = 0;
		if(b >= 5)	s = 1;

		if(f2 == 1){
			f3 = 0;
			switch(s){
			case 0:	//b��4�ȉ��̂Ƃ�
				ps_s();
				l3 = 1;
				
				if(tgs == 0){
					stml();
				}
				
				if(tgs == 1){
					stmr();
				}
				
				LATD = l7s[b];
				l3 = 0;
				D1;
				
				break;
				
			case 1:	//b��5�ȏ�̂Ƃ�
				ps_s();
				l3 = 1;
				
				if(tgs == 0){
					dcml();
				}
				
				if(tgs == 1){
					dcmr();
				}
				
				LATD = l7s[b];
				l3 = 0;
				D1;
				
				break;
				
			default:
				break;
			}
			if(f2 == 0){
				dcms();
			}
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
	
	if(k == 1 || k == 2){
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
	
	if(k == 1 || k == 2){
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

void ts_s(void){
	if(ts == 0 && f == 0){
		D1;
		f = 1;
	}
	
	if(ts == 0 && f == 1){
		D1;
		f = 0;
	}
}

void ps_s(void){
	if(ps == 0 && f2 == 0){
		D1;
		f2 = 1;
	}
	
	if(ps == 0 && f2 == 1){
		D1;
		f2 = 0;
	}
}
