/*======================================
����23�N�x	���Z�����̂Â���R���e�X�g
�d�q��H�g������	�S�����?

�쐬����	�F7��29��
�쐬��		�F�R��W�j
�����w�Z	�F�����s���r��H�ƍ����w�Z

�t�@�C����	�Fp04.c
�ۑ�ԍ�	�F4��
======================================*/
#include<p18f4550.h>
#include<delays.h>

#define l2 LATBbits.LATB2	//����7�Z�OLED
#define l3 LATBbits.LATB3	//�E��7�Z�OLED
#define l4 LATBbits.LATB4
#define l5 LATBbits.LATB5
#define l7 LATDbits.LATD7
#define D01 Delay100TCYx(120)	//0.001ms�̒x��
#define D1 Delay1KTCYx(120)		//0.01ms�̒x��
#define D10 Delay10KTCYx(120)	//0.1ms�̒x��
#define tgs PORTAbits.RA3	//�g�O���X�C�b�`
#define ts PORTAbits.RA4	//�^�N�g�X�C�b�`
#define ps PORTAbits.RA5	//�z�g�C���^���v�^

//=====�萔�̐錾
unsigned char l7s[] = {
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
	0b00001000,	//A-10
	0b00000011,	//b-11
	0b01000110,	//C-12
	0b00101011,	//OFF-13
	0b01110111,	//ON-14
	0b00111111	//--15
};
unsigned char STM[] = {0x08,0x04,0x02,0x01};

//=====�ϐ��̐錾
unsigned char a,j,k,f,f2;
char b,c,i;

//=====�֐��̐錾
void led(void);		//2��LED�𓯎��ɕ\��������֐�
void stmr(void);	//�X�e�b�s���O���[�^�����v���ɉ�]������֐�
void stml(void);	//�X�e�b�s���O���[�^�𔽎��v���ɉ�]������֐�
void dcmr(void);	//DC���[�^�����v���ɉ�]������֐�
void dcml(void);	//DC���[�^�𔽎��v���ɉ�]������֐�
void dcms(void);	//DC���[�^���~������֐�

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
	a = 15;	//����7�Z�OLED�̃f�[�^��ێ�
	b = 15;	//�E��7�Z�OLED�̃f�[�^��ێ�
	c = 0;	//�J�E���g�p
	i = 0;	//�X�e�b�s���O���[�^����p
	j = 0;	//���g�p
	k = 0;	//���g�p
	f = 1;	//�t���O�p
	f2 = 0;	//�t���O�p
	
	while(1){
		led();
		
		if(tgs == 0 && f == 1){
			D1;
			f = 0;
			a = 1;
			b = 0;
		}
		
		if(tgs == 0){
			for(c=0;c<50;c++){
				led();
			}
			
			if(tgs == 0){
				b--;
				
				if(b < 0){
					b = 9;
					a = 0;
				}
				
				if(a == 0 && b == 0){
					while(1){
						led();
					}
				}
			}
		
		
		
		}
	}
}
/*======================================
	����֐�
======================================*/
void led(void){		//2��LED�𓯎��ɕ\��������֐�
	LATD = l7s[a];
	l2 = 0;
	D1;
	l2 = 1;
	LATD = l7s[b];
	l3 = 0;
	D1;
	l3 = 1;
}

void stmr(void){	//�X�e�b�s���O���[�^�����v���ɉ�]������֐�
	LATD = STM[i];
	l7 = 0;
	l7 = 1;
	l7 = 0;
	D1;
	i++;
	
	if(i > 3){
	i = 0;
	}
}

void stml(void){	//�X�e�b�s���O���[�^�𔽎��v���ɉ�]������֐�
	LATD = STM[i];
	l7 = 0;
	l7 = 1;
	l7 = 0;
	D1;
	i--;
	
	if(i < 0){
	i = 3;
	}
}

void dcmr(void){	//DC���[�^�����v���ɉ�]������֐�
	LATD = 0b00100000;
	l7 = 0;
	l7 = 1;
	l7 = 0;
}

void dcml(void){	//DC���[�^�𔽎��v���ɉ�]������֐�
	LATD = 0b00010000;
	l7 = 0;
	l7 = 1;
	l7 = 0;
}

void dcms(void){	//DC���[�^���~������֐�
	LATD = 0b00110000;
	l7 = 0;
	l7 = 1;
	l7 = 0;
}
