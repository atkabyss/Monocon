/*======================================
����24�N�x ���Z�����̂Â���R���e�X�g
�d�q��H�g������ �֓��n��\�I��

�쐬����	�F7��23��
�쐬��		�F�R��W�j
�����w�Z	�F�����s���r��H�ƍ����w�Z

�t�@�C����	�Fp007.c
�ۑ�ԍ�	�F7��
======================================*/
#include<p18f4550.h>
#include<delays.h>

#define l2 LATBbits.LATB2		//������7�Z�O�����gLED
#define l3 LATBbits.LATB3		//�E����7�Z�O�����gLED
#define l4 LATBbits.LATB4
#define l5 LATBbits.LATB5
#define l7 LATDbits.LATD7
#define D01 Delay1KTCYx(12)		//��0.01ms�̒x��
#define D1 Delay1KTCYx(120)		//��0.1ms�̒x��
#define D10 Delay10KTCYx(120)	//��1ms�̒x��
#define tgs PORTAbits.RA3		//�g�O���X�C�b�`
#define ts PORTAbits.RA4		//�^�N�g�X�C�b�`
#define ps PORTAbits.RA5		//�t�H�gIC

//=====�萔�̐錾=====
char l7s[] = {
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
	0b01111111,	//��\��-10
	0b00001001,	//H-11
	0b01000111	//L-12
};

char STMR[] = {0x08,0x04,0x02,0x01};
char STML[] = {0x01,0x02,0x04,0x08};

//=====�ϐ��̐錾=====
char a,b,c,c2,i,j,k,f,f2;

//=====�֐��̐錾=====
void led(void);		//2��LED�𓯎��ɕ\��������֐�
void stmr(void);	//�X�e�b�s���O���[�^�����v���ɉ�]������֐�
void stml(void);	//�X�e�b�s���O���[�^�𔽎��v���ɉ�]������֐�

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
	
//=====���ׂĂ�7�Z�O�����gLED������=====
	l2 = 1;
	l3 = 1;
	l4 = 1;
	l5 = 1;
	
//=====�ϐ��̏�����=====
	a = 1;		//����7�Z�OLED�̃f�[�^���i�[
	b = 0;		//�E��7�Z�OLED�̃f�[�^���i�[
	c = 0;		//�J�E���g�p
	c2 = 0;		//�J�E���g�p
	i = 0;		//�X�e�b�s���O���[�^����p
	j = 0;		//�X�e�b�s���O���[�^�̉�]������p
	k = 0;		//�X�e�b�s���O���[�^�̉�]���x����p
	f = 0;		//�t���O�p
	f2 = 0;		//�t���O�p
	
	LATD = l7s[a];	//����������
	l2 = 0;
	
	while(1){
		LATD = l7s[a];
		if(ts == 1){
			D01;
			f = 1;
		}
		
		if(ts == 0 && f == 1 && a == 2){	//�^�N�g���������Ƃ�1��2��؂�ւ�
			f = 0;
			a = 1;
		}
		
		if(ts == 0 && f == 1 && a == 1){
			f = 0;
			a = 2;
		}
		
//�t�H�g���Ռ����ꂽ�Ƃ��X�e�b�s���O���[�^����]
		
		if(ps == 0 && a == 1){	//LED�\����1�̂Ƃ�
			if(tgs == 1){			//�ᑬ���v���
				l2 = 1;
				k = 1;
				stmr();
				LATD = l7s[a];
				l2 = 0;
				D01;
			}
			
			if(tgs == 0){			//�������v���
				l2 = 1;
				k = 0;
				stmr();
				LATD = l7s[a];
				l2 = 0;
				D01;
			}
		}
		
		if(ps == 0 && a == 2){		//LED�\����2�̂Ƃ�
			if(tgs == 1){				//�ᑬ�����v���
				l2 = 1;
				k = 1;
				stml();
				LATD = l7s[a];
				l2 = 0;
				
			}
			
			if(tgs == 0){				//���������v���
				l2 = 1;
				k = 0;
				stml();
				LATD = l7s[a];
				l2 = 0;
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
	D01;
	l2 = 1;
	LATD = l7s[b];
	l3 = 0;
	D01;
	l3 = 1;
}

void stmr(void){	//�X�e�b�s���O���[�^�����v���ɉ�]������֐�
	LATD = STMR[i];
	l7 = 0;
	l7 = 1;
	l7 = 0;
	i++;
	D1;
	
	if(k == 1){
		D1;
	}
	
	if(i > 4){
		i = 0;
	}
}

void stml(void){	//�X�e�b�s���O���[�^�𔽎��v���ɉ�]������֐�
	LATD = STML[i];
	l7 = 0;
	l7 = 1;
	l7 = 0;
	i++;
	D1;
	
	if(k == 1){
		D1;
	}
	
	if(i > 4){
		i = 0;
	}
}
