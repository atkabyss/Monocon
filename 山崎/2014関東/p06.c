/*======================================
����26�N�x ���Z�����̂Â���R���e�X�g
�d�q��H�g������ �֓��n��\�I��(��t)

�쐬����	�F8��5��
�쐬��		�F12�� �R��W�j
�����w�Z	�F�����s���r��H�ƍ����w�Z

�t�@�C����	�Fp06.c
�ۑ�ԍ�	�F6��
======================================*/
#include<p18f4550.h>
#include<delays.h>

#define l2 LATBbits.LATB2 //����7�Z�O�����gLED
#define l3 LATBbits.LATB3 //����7�Z�O�����gLED
#define l4 LATBbits.LATB4
#define l5 LATBbits.LATB5
#define l7 LATDbits.LATD7
#define D01	Delay100TCYx(120)	//0.001ms�̒x��
#define D05	Delay1KTCYx(60)	//0.005ms�̒x��
#define D1	Delay1KTCYx(120)	//0.01ms�̒x��
#define D10	Delay10KTCYx(120)	//0.1ms�̒x��
#define bs PORTAbits.RA5	//���^�N�g�X�C�b�`
#define rs PORTAbits.RA4	//�ԃ^�N�g�X�C�b�`
#define ps PORTAbits.RA3	//�t�H�gIC

//=====�萔�̐錾
char l7s[] = {	//7�Z�O�����gLED�̕\���ݒ�
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
	0b00100001,	//d-13
	0b00000110,	//E-14
	0b00001110,	//F-15
	0b00001001,	//H-16
	0b01000111,	//L-17
	0b01111111	//��\��-18
};

char STM[] = {0x08,0x04,0x02,0x01};	//�X�e�b�s���O���[�^�̗㎥�ݒ�

//=====�ϐ��̐錾
unsigned char b,j,k,f,f2,f3;
char a,c,i;

//=====�֐��̐錾
void set(void);	//PIC�̏������ݒ�
void led(void);	//2��LED�𓯎��ɕ\��������֐�
void stmr(void);	//�X�e�b�s���O���[�^�����v���ɉ�]������֐�
void stml(void);	//�X�e�b�s���O���[�^�𔽎��v���ɉ�]������֐�

/*======================================
		���C���֐�
======================================*/
void main(void){

	set();
	a = 16;
	b = 0;
	
	while(1){
		led();
		
		if(bs == 1){
			if(rs == 0){
				D1;
			}
			f = 1;
		}
		
		if(bs == 0 && f == 1 && f2 == 1){	//���^�N�g�X�C�b�`��OFF��ON�œ���
			f = 0;
			b++;
			
			if(b > 9){
				b = 0;
			}
			
			j = b % 2;	//����������𔻒f
			
			if(j == 0){
				a = 16;
			}
			
			if(j == 1){
				a = 17;
			}
		}
		
		if(ps == 1){
			f2 = 1;
		}
		
		if(ps == 0){
			f2 = 0;
			if(a == 16){	//�\���������̂Ƃ�
				stmr();
				
				if(rs == 0){	//�ᑬ��]
					k = 1;
				}
				
				if(rs == 1){	//������]
					k = 0;
				}
			}
			
			if(a == 17){	//�\������̂Ƃ�
				stml();
				
				if(rs == 0){	//�ᑬ��]
					k = 1;
				}
				
				if(rs == 1){	//������]
					k = 0;
				}
			}
		}
	}
}
/*======================================
		����֐�
======================================*/
void set(void){	//PIC�̏������ݒ�
	
	ADCON1 |= 0x0F;	//AD�R���o�[�^��OFF
	
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

//=====���ׂĂ�7�Z�O�����gLED��������
	l2 = 1;
	l3 = 1;
	l4 = 1;
	l5 = 1;
	
//=====�ϐ��̏�����
	a = 0;	//����7�Z�OL�����gLED�̃f�[�^��ێ�
	b = 0;	//�E��7�Z�OL�����gLED�̃f�[�^��ێ�
	c = 0;	//�J�E���g�p
	i = 0;	//�X�e�b�s���O���[�^����p
	j = 0;	//�E��7�Z�O�����gLED������������𔻒�
	k = 0;	//�X�e�b�s���O���[�^�̉�]���x����p
	f = 0;	//�t���O�p
	f2 = 0;	//�t���O�p
	f3 = 0;	//�t���O�p
}

void led(void){	//2��LED�𓯎��ɕ\��������֐�
	LATD = l7s[a];
	l2 = 0;
	D05;
	l2 = 1;
	LATD = l7s[b];
	l3 = 0;
	D05;
	l3 = 1;
}

void stmr(void){	//�X�e�b�s���O���[�^�����v���ɉ�]������֐�
	LATD = STM[i];
	l7 = 0;
	l7 = 1;
	l7 = 0;
	
	if(k == 1){
		led();	//�_�C�i�~�b�N�h���C�u���̂�x���Ƃ��ė��p
	}
	
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
	
	if(k == 1){
		led();	//�_�C�i�~�b�N�h���C�u���̂�x���Ƃ��ė��p
	}
	
	i--;
	
	if(i < 0){
		i = 3;
	}
}
